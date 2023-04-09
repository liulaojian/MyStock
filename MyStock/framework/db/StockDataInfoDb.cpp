#include "stdafx.h"
#include "StockDataInfoDb.h"
#include "CommonMacro.h"
#include "Util.h"
#include "StockDataMgr.h"
#include "Convert.h"
CStockDataInfoDb* CStockDataInfoDb::s_pIntance = NULL;

CStockDataInfoDb::CStockDataInfoDb()
{
	bDatabaseOpen=FALSE;
}


CStockDataInfoDb::~CStockDataInfoDb()
{

}

CStockDataInfoDb* CStockDataInfoDb::GetInstance()
{
	if (s_pIntance == NULL)
	{
		s_pIntance = new CStockDataInfoDb();
		CHECKF(s_pIntance);
	}

	return s_pIntance;
}


CString CStockDataInfoDb::GetStockDayTableName(CString strStockCode)
{
	CString strName;
	strName="Day_";
	strName+=strStockCode;
	return strName;
}


CString CStockDataInfoDb::GetStockMin5TableName(CString strStockCode)
{
	CString strName;
	strName="Min5_";
	strName+=strStockCode;
	return strName;
}


//打开数据库
bool CStockDataInfoDb::DataBaseOpen(void)
{

	if(bDatabaseOpen)
		return true;

	CString strPath;
	strPath=GetReturnPath();
	strPath+="\\";
	strPath+=STOCKDATA_DATABASE;

	int nlen=0, codepage;
	char cpath[130];
	wchar_t wpath[130];
	codepage = AreFileApisANSI() ? CP_ACP : CP_OEMCP;
	nlen = MultiByteToWideChar(codepage, 0, strPath.GetBuffer(0), -1, NULL, 0);
	MultiByteToWideChar(CP_ACP, 0, strPath.GetBuffer(0), -1, wpath, nlen); 
	nlen=WideCharToMultiByte(CP_UTF8 , 0, wpath, -1, 0, 0, 0, 0);
	WideCharToMultiByte(CP_UTF8 , 0, wpath, -1, cpath, nlen, 0, 0);
	//	return sqlite3_open_v2(cpath, db, Flags, NULL);
	std::string path( cpath);
	mDatabase.Open(path);

	bDatabaseOpen=TRUE;
	
	return true;
}

//关闭数据库
bool CStockDataInfoDb::DataBaseClose(void)
{
	if(!bDatabaseOpen)
		return true;
	mDatabase.Close();
	bDatabaseOpen=FALSE;
	return true;
}

//数据库日表是否存在
BOOL CStockDataInfoDb::IsDbDayTableExist(CString strStockCode)
{
	CString strTableName=GetStockDayTableName(strStockCode);
	string sql;
	sql="select count(*) from sqlite_master where type='table' and name ='";
	sql+=(LPCSTR)strTableName;
	sql+="'";
	DataBaseOpen();
	int ret;
	ret=mDatabase.ExecScalar(sql);
	if(ret>0)
		return TRUE;
	else
		return FALSE;
}


//数据库5分钟表是否存在
BOOL CStockDataInfoDb::IsDbMin5TableExist(CString strStockCode)
{
	CString strTableName=GetStockMin5TableName(strStockCode);
	string sql;
	sql="select count(*) from sqlite_master where type='table' and name ='";
	sql+=(LPCSTR)strTableName;
	sql+="'";
	DataBaseOpen();
	int ret;
	ret=mDatabase.ExecScalar(sql);
	if(ret>0)
		return TRUE;
	else
		return FALSE;
}

//创建日表
bool CStockDataInfoDb::CreateDayTable(std::string strTableName)
{
	DEBUG_TRY
	
	DataBaseOpen();
	vector<pair<string, string> > fields;
	fields.push_back(make_pair("id","integer primary key autoincrement"));
	fields.push_back(make_pair("daydate","text unique"));
	fields.push_back(make_pair("beginprice","real"));   
	fields.push_back(make_pair("maxprice","real")); 
	fields.push_back(make_pair("minprice","real")); 
	fields.push_back(make_pair("endprice","real")); 
	fields.push_back(make_pair("totalvolume","integer")); 
	fields.push_back(make_pair("totalprice","real")); 
	bool bResult=mDatabase.CreateTable(strTableName, fields);
	return true;
	DEBUG_CATCH2("%s", __FUNCTION__);
	return false;
}

//创建5分钟表
bool CStockDataInfoDb::CreateMin5Table(std::string strTableName)
{
	DEBUG_TRY
	DataBaseOpen();
	vector<pair<string, string> > fields;
	fields.push_back(make_pair("id","integer primary key autoincrement"));
	fields.push_back(make_pair("min5datetime","text unique"));
	fields.push_back(make_pair("beginprice","real"));   
	fields.push_back(make_pair("maxprice","real")); 
	fields.push_back(make_pair("minprice","real")); 
	fields.push_back(make_pair("endprice","real")); 
	fields.push_back(make_pair("totalvolume","integer")); 
	fields.push_back(make_pair("totalprice","real")); 
	bool bResult=mDatabase.CreateTable(strTableName, fields);
	return true;
	DEBUG_CATCH2("%s", __FUNCTION__);
	return false;
}


//创建表
bool CStockDataInfoDb::CreateTable(void)
{

	Vec_StockCodeList vecStockCodeList;

	vecStockCodeList=StockDataMgr()->GetStockCodeList();

	StockCode *pStockCode=NULL;

	DataBaseOpen();
	for(int i=0;i<vecStockCodeList.size();i++)
	{
		pStockCode=vecStockCodeList[i];
		if(!pStockCode)
			continue;
		CString strStockCode;
		strStockCode=pStockCode->strStockCode;
		if(!IsDbDayTableExist(strStockCode))
		{
			CString strDayTableName=GetStockDayTableName(strStockCode);
			CreateDayTable((LPCSTR)strDayTableName);

		}

		if(!IsDbMin5TableExist(strStockCode))
		{
			CString strMin5TableName=GetStockMin5TableName(strStockCode);

			CreateMin5Table((LPCSTR)strMin5TableName);
		}

	}
	DataBaseClose();

	return false;
}

//日数据批量插入
bool CStockDataInfoDb::StockDay_Table_InsertVec(CString strStockCode,Vec_DbStockDayData vecDbStockDayData)
{
	DataBaseOpen();
	CString strDayTableName=GetStockDayTableName(strStockCode);
	if(!IsDbDayTableExist(strStockCode))
	{
		CreateDayTable((LPCSTR)strDayTableName);
	}
	DbStockDayData *pDbStockDayData=NULL;
	bool bResult=true;
	mDatabase.ExecDML("BEGIN");

	for(int i=0;i<vecDbStockDayData.size();i++)
	{
		pDbStockDayData=vecDbStockDayData[i];
		if(!pDbStockDayData)
			continue;
		vector<std::string> fields;
		fields.push_back("daydate");
		fields.push_back("beginprice");
		fields.push_back("maxprice");
		fields.push_back("minprice");
		fields.push_back("endprice");
		fields.push_back("totalvolume");
		fields.push_back("totalprice");
		vector<std::string> Values;
		Values.clear();
		Values.push_back(pDbStockDayData->strDate);
		Values.push_back(FloatConvrtString(pDbStockDayData->fBeginPrice));
		Values.push_back(FloatConvrtString(pDbStockDayData->fMaxPrice));
		Values.push_back(FloatConvrtString(pDbStockDayData->fMinPrice));
		Values.push_back(FloatConvrtString(pDbStockDayData->fEndPrice));
		Values.push_back(int_to_string(pDbStockDayData->mTotalVolume));
		Values.push_back(FloatConvrtString(pDbStockDayData->fTotalPrice));
		DEBUG_TRY
		bResult=mDatabase.InsertRow((LPCSTR)strDayTableName,fields,Values);
		DEBUG_CATCH2("%s", __FUNCTION__);
	}
	mDatabase.ExecDML("COMMIT");
	//DataBaseClose();
	return true;
}

//日数据查询(全部)
bool  CStockDataInfoDb::StockDay_Table_Query(CString strStockCode, Vec_DbStockDayData &vecDbStockDayData)
{
	DEBUG_TRY
	DataBaseOpen();
	int id;
	string sqlexec;
	vector<string> fieldName;
	vector<string> fieldValue;
	DbStockDayData *pDbStockDayData=NULL;
	CString strDayTableName=GetStockDayTableName(strStockCode);
	sqlexec="select * from ";
	sqlexec+=(LPCSTR)strDayTableName;
	bool ret=mDatabase.ExecQuery(sqlexec,fieldName,fieldValue);
	vector <std::string>::iterator it;
	unsigned int i=0;
	while(i<fieldValue.size())
	{
		pDbStockDayData=new DbStockDayData();
		id=string_to_int(fieldValue[i]);
		pDbStockDayData->strDate=fieldValue[i+1];
		pDbStockDayData->fBeginPrice=atof(fieldValue[i+2].c_str());
		pDbStockDayData->fMaxPrice=atof(fieldValue[i+3].c_str());
		pDbStockDayData->fMinPrice=atof(fieldValue[i+4].c_str());
		pDbStockDayData->fEndPrice=atof(fieldValue[i+5].c_str());
		pDbStockDayData->mTotalVolume=string_to_int(fieldValue[i+6]);
		pDbStockDayData->fTotalPrice=atof(fieldValue[i+7].c_str());
		vecDbStockDayData.push_back(pDbStockDayData);
		i+=8;
	}
	//DataBaseClose();
	return true;
	DEBUG_CATCH2("%s", __FUNCTION__);
	return false;
}


//日数据删除
bool CStockDataInfoDb::StockDay_Table_Delete(CString strStockCode,CString strDate)
{
	CString strDayTableName=GetStockDayTableName(strStockCode);

	DEBUG_TRY
	bool ret=false;
	DataBaseOpen();
	ret=mDatabase.DeleteRow((LPCSTR)strDayTableName,"daydate",(LPCSTR)strDate);
	//DataBaseClose();
	return ret;
	DEBUG_CATCH2("%s", __FUNCTION__);
	return false;
}

//日数据更新
bool CStockDataInfoDb::StockDay_Table_Update(CString strStockCode,DbStockDayData * pDbStockDayData)
{
	if(!pDbStockDayData)
		return false;
	bool ret=false;
	std::string key,keyValue;
	key="daydate";
	keyValue=pDbStockDayData->strDate;
	CString strDayTableName=GetStockDayTableName(strStockCode);
	vector<std::string> fields;
	fields.push_back("daydate");
	fields.push_back("beginprice");
	fields.push_back("maxprice");
	fields.push_back("minprice");
	fields.push_back("endprice");
	fields.push_back("totalvolume");
	fields.push_back("totalprice");
	vector<std::string> Values;
	Values.clear();
	Values.push_back(pDbStockDayData->strDate);
	Values.push_back(FloatConvrtString(pDbStockDayData->fBeginPrice));
	Values.push_back(FloatConvrtString(pDbStockDayData->fMaxPrice));
	Values.push_back(FloatConvrtString(pDbStockDayData->fMinPrice));
	Values.push_back(FloatConvrtString(pDbStockDayData->fEndPrice));
	Values.push_back(int_to_string(pDbStockDayData->mTotalVolume));
	Values.push_back(FloatConvrtString(pDbStockDayData->fTotalPrice));
	DataBaseOpen();
	ret=mDatabase.UpdateRow((LPCSTR)strDayTableName,key,keyValue,fields,Values);
	//DataBaseClose();
	return ret;	
}

//5分钟数据批量插入
bool  CStockDataInfoDb::StockMin5_Table_InsertVec(CString strStockCode,Vec_DbStock5MinData vecDbStock5MinData)
{
	CString strMin5TableName=GetStockMin5TableName(strStockCode);
	if(!IsDbMin5TableExist(strStockCode))
	{
		CreateMin5Table((LPCSTR)strMin5TableName);
	}

	DbStock5MinData *pDbStock5MinData=NULL;
	bool bResult=true;
	mDatabase.ExecDML("BEGIN");

	for(int i=0;i<vecDbStock5MinData.size();i++)
	{
		pDbStock5MinData=vecDbStock5MinData[i];
		if(!pDbStock5MinData)
			continue;

		vector<std::string> fields;
		fields.push_back("min5datetime");
		fields.push_back("beginprice");
		fields.push_back("maxprice");
		fields.push_back("minprice");
		fields.push_back("endprice");
		fields.push_back("totalvolume");
		fields.push_back("totalprice");
		vector<std::string> Values;
		Values.clear();
		Values.push_back(pDbStock5MinData->strDateTime);
		Values.push_back(FloatConvrtString(pDbStock5MinData->fBeginPrice));
		Values.push_back(FloatConvrtString(pDbStock5MinData->fMaxPrice));
		Values.push_back(FloatConvrtString(pDbStock5MinData->fMinPrice));
		Values.push_back(FloatConvrtString(pDbStock5MinData->fEndPrice));
		Values.push_back(int_to_string(pDbStock5MinData->mTotalVolume));
		Values.push_back(FloatConvrtString(pDbStock5MinData->fTotalPrice));
		DEBUG_TRY
		bResult=mDatabase.InsertRow((LPCSTR)strMin5TableName,fields,Values);
		DEBUG_CATCH2("%s", __FUNCTION__);
	}

	mDatabase.ExecDML("COMMIT");
	//DataBaseClose();
	return true;
}


//5分钟数据查询(全部)
bool CStockDataInfoDb::StockMin5_Table_Query(CString strStockCode, Vec_DbStock5MinData &vecDbStock5MinData)
{
	DEBUG_TRY
	DataBaseOpen();
	int id;
	string sqlexec;
	vector<string> fieldName;
	vector<string> fieldValue;
	DbStock5MinData *pDbStock5MinData=NULL;
	CString strMin5TableName=GetStockMin5TableName(strStockCode);
	sqlexec="select * from ";
	sqlexec+=(LPCSTR)strMin5TableName;
	bool ret=mDatabase.ExecQuery(sqlexec,fieldName,fieldValue);
	vector <std::string>::iterator it;
	unsigned int i=0;
	while(i<fieldValue.size())
	{
		pDbStock5MinData=new DbStock5MinData();
		id=string_to_int(fieldValue[i]);
		pDbStock5MinData->strDateTime=fieldValue[i+1];
		pDbStock5MinData->fBeginPrice=atof(fieldValue[i+2].c_str());
		pDbStock5MinData->fMaxPrice=atof(fieldValue[i+3].c_str());
		pDbStock5MinData->fMinPrice=atof(fieldValue[i+4].c_str());
		pDbStock5MinData->fEndPrice=atof(fieldValue[i+5].c_str());
		pDbStock5MinData->mTotalVolume=string_to_int(fieldValue[i+6]);
		pDbStock5MinData->fTotalPrice=atof(fieldValue[i+7].c_str());
		vecDbStock5MinData.push_back(pDbStock5MinData);
		i+=8;
	}
	//DataBaseClose();
	return true;
	DEBUG_CATCH2("%s", __FUNCTION__);
	return false;
}


//5分钟数据删除
bool CStockDataInfoDb::StockMin5_Table_Delete(CString strStockCode,CString strDateTime)
{
	CString strMin5TableName=GetStockMin5TableName(strStockCode);

	DEBUG_TRY
	bool ret=false;
	DataBaseOpen();
	ret=mDatabase.DeleteRow((LPCSTR)strMin5TableName,"min5datetime",(LPCSTR)strDateTime);
	//DataBaseClose();
	return ret;
	DEBUG_CATCH2("%s", __FUNCTION__);
	return false;

}



//5分钟数据更新
bool CStockDataInfoDb::StockMin5_Table_Update(CString strStockCode,DbStock5MinData * pDbStock5MinData)
{
	if(!pDbStock5MinData)
		return false;

	CString strMin5TableName=GetStockMin5TableName(strStockCode);

	bool ret=false;
	std::string key,keyValue;
	key="min5datetime";
	keyValue=pDbStock5MinData->strDateTime;

	vector<std::string> fields;
	fields.push_back("min5datetime");
	fields.push_back("beginprice");
	fields.push_back("maxprice");
	fields.push_back("minprice");
	fields.push_back("endprice");
	fields.push_back("totalvolume");
	fields.push_back("totalprice");
	vector<std::string> Values;
	Values.clear();
	Values.push_back(pDbStock5MinData->strDateTime);
	Values.push_back(FloatConvrtString(pDbStock5MinData->fBeginPrice));
	Values.push_back(FloatConvrtString(pDbStock5MinData->fMaxPrice));
	Values.push_back(FloatConvrtString(pDbStock5MinData->fMinPrice));
	Values.push_back(FloatConvrtString(pDbStock5MinData->fEndPrice));
	Values.push_back(int_to_string(pDbStock5MinData->mTotalVolume));
	Values.push_back(FloatConvrtString(pDbStock5MinData->fTotalPrice));
	DataBaseOpen();
	ret=mDatabase.UpdateRow((LPCSTR)strMin5TableName,key,keyValue,fields,Values);
	//DataBaseClose();
	return ret;	

}


//将Vec_StockDayData 天数据列表 转换为  Vec_DbStockDayData 天数据库列表
Vec_DbStockDayData  CStockDataInfoDb::ConvertVecStockDayDataToVecDbStockDayData(Vec_StockDayData vecStockDayData )
{
	CStockDayData * pStockDayData=NULL;
	Vec_DbStockDayData vecDbStockDayData;
	for(int i=0;i<vecStockDayData.size();i++)
	{
		pStockDayData=vecStockDayData[i];
		if(!pStockDayData)
			continue;
		DbStockDayData *pDbStockDayData=new DbStockDayData();

		pDbStockDayData->strDate=pStockDayData->GetDate();

		pDbStockDayData->fBeginPrice=pStockDayData->GetBeginPrice();

		pDbStockDayData->fMaxPrice=pStockDayData->GetMaxPrice();

		pDbStockDayData->fMinPrice=pStockDayData->GetMinPrice();

		pDbStockDayData->fEndPrice=pStockDayData->GetEndPrice();

		pDbStockDayData->mTotalVolume=pStockDayData->GetTotalVolume();

		pDbStockDayData->fTotalPrice=pStockDayData->GetTotalPrice();

		vecDbStockDayData.push_back(pDbStockDayData);
	}

	return vecDbStockDayData;
}


//将Vec_StockMin5Data 天数据列表 转换为  Vec_DbStock5MinData 天数据库列表
Vec_DbStock5MinData CStockDataInfoDb::ConvertVecStockMin5DataToVecDbStock5MinData(Vec_StockMin5Data vecStockMin5Data)
{
	CStockMin5Data *pStockMin5Data=NULL;
	Vec_DbStock5MinData vecDbStock5MinData;
	for(int i=0;i<vecStockMin5Data.size();i++)
	{
		pStockMin5Data=vecStockMin5Data[i];
		if(!pStockMin5Data)
			continue;

		DbStock5MinData *pDbStock5MinData=new DbStock5MinData();
		pDbStock5MinData->strDateTime=pStockMin5Data->GetDate();
		pDbStock5MinData->strDateTime+=" ";
		pDbStock5MinData->strDateTime+=pStockMin5Data->GetTime();

		pDbStock5MinData->fBeginPrice=pStockMin5Data->GetBeginPrice();
		pDbStock5MinData->fMaxPrice=pStockMin5Data->GetMaxPrice();
		pDbStock5MinData->fMinPrice=pStockMin5Data->GetMinPrice();
		pDbStock5MinData->fEndPrice=pStockMin5Data->GetEndPrice();
		pDbStock5MinData->mTotalVolume=pStockMin5Data->GetTotalVolume();
		pDbStock5MinData->fTotalPrice=pStockMin5Data->GetTotalPrice();
		vecDbStock5MinData.push_back(pDbStock5MinData);
	}

	return vecDbStock5MinData;
}