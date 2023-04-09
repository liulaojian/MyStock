#include "stdafx.h"
#include "StockDataMgr.h"
#include "CommonMacro.h"
#include "XmlOperator.h"
#include "Util.h"
#include "zbTypeDef.h"
#include "SystemMgr.h"
#include "Convert.h"

#define TDXDir  "D:\\new_jyplug"

CStockDataMgr* CStockDataMgr::s_pIntance = NULL;


CStockDataMgr::CStockDataMgr()
{
	::InitializeCriticalSection(&dayTableLock);
	::InitializeCriticalSection(&min5TableLock);
	::InitializeCriticalSection(&stockListLock);
}

CStockDataMgr::~CStockDataMgr()
{
	::DeleteCriticalSection(&dayTableLock);
	::DeleteCriticalSection(&min5TableLock);
	::DeleteCriticalSection(&stockListLock);

}


CStockDataMgr* CStockDataMgr::GetInstance()
{
	if (s_pIntance == NULL)
	{
		s_pIntance = new CStockDataMgr();
		CHECKF(s_pIntance);
	}

	return s_pIntance;
}

BOOL  CStockDataMgr::IsStockInCodeList(CString strStockCode)
{
	for (int i = 0; i < vecStockCodeList.size(); i++)
	{
		if (vecStockCodeList[i]->strStockCode == strStockCode)
			return TRUE;
	}

	return FALSE;
}
BOOL  CStockDataMgr::LoadFromStockCodeXml(CString strXmlPath)
{
	for(int i=0;i<vecStockCodeList.size();i++)
	{
		if(vecStockCodeList[i])
			SAFE_DELETE(vecStockCodeList[i]);
	}
	vecStockCodeList.clear();

	VecTiXmlElement vecTiXmlElement;
	vecTiXmlElement=CXmlOperator::QueryNode_Element((LPCTSTR)strXmlPath,"StockCodes","StockCode");
	TiXmlElement* pNode=NULL;
	StockCode *pStockCode=NULL;
	for(int i=0;i<vecTiXmlElement.size();i++)
	{
		pNode=vecTiXmlElement[i];
		if(pNode)
		{
			pStockCode=new StockCode();
			pStockCode->strStockCode="";
			TiXmlAttribute* pAttr = NULL;   
			for (pAttr = pNode->FirstAttribute(); pAttr; pAttr = pAttr->Next())    
			{    
				std::string strAttName = pAttr->Name();  
				std::string strAttValue = pAttr->Value();  
				if(strAttName=="code")
				{
					pStockCode->strStockCode=strAttValue.c_str();
				}
				else if(strAttName=="name")
				{
					pStockCode->strStockName=strAttValue.c_str();

					CString strDayPath = TDXDir;
					CString strDayName = pStockCode->strStockCode;
					strDayName = strDayName.MakeLower();
					strDayName += ".day";
					strDayPath += "\\vipdoc";
					if (pStockCode->strStockCode.Left(2) == "SH")
					{
						strDayPath += "\\sh\\lday\\";
						strDayPath += strDayName;
					}
					else
					{
						strDayPath += "\\sz\\lday\\";
						strDayPath += strDayName;
					}

					pStockCode->strStockDayFilePath = strDayPath;

					CString strMin5Path = TDXDir;
					CString strMin5Name = pStockCode->strStockCode;
					strMin5Name = strMin5Name.MakeLower();
					strMin5Name += ".lc5";
					strMin5Path += "\\vipdoc";
					if (pStockCode->strStockCode.Left(2) == "SH")
					{
						strMin5Path += "\\sh\\fzline\\";
						strMin5Path += strMin5Name;
					}
					else
					{
						strMin5Path += "\\sz\\fzline\\";
						strMin5Path += strMin5Name;
					}
					pStockCode->strStockMinFilePath = strMin5Path;

				}
				/*
				else if(strAttName=="dayfilepath")
				{
					pStockCode->strStockDayFilePath=strAttValue.c_str();
				}
				else if(strAttName=="minfilepath")
				{
					pStockCode->strStockMinFilePath=strAttValue.c_str();
				}*/
			}    

			if(pStockCode->strStockCode!="")
			{
				BOOL bFound=FALSE;
				for(int i=0;i<vecStockCodeList.size();i++)
				{
					if(vecStockCodeList[i]->strStockCode==pStockCode->strStockCode)
					{
						bFound=TRUE;
						break;
					}
				}
				if(!bFound)
					vecStockCodeList.push_back(pStockCode);
			}
			else
				SAFE_DELETE(pStockCode);

		}
	}
	return TRUE;
}

BOOL CStockDataMgr::InitStockTableList(void)
{
	StockCode *pStockCode=NULL;
	CStockDayTable *pStockDayTable=NULL;
	CStockMin5Table *pStockMin5Table=NULL;
	int mMaxSize=vecStockCodeList.size();
	for(int i=0;i<vecStockCodeList.size();i++)
	{
		pStockCode=vecStockCodeList[i];

		if(!pStockCode)
		 continue;

		printf("Loading %s  Index %d Of %d\n",pStockCode->strStockCode,i,mMaxSize);
		pStockDayTable=new CStockDayTable(pStockCode->strStockCode);

		if(pStockCode->strStockDayFilePath!="")
		{
			if(IsExpStock(pStockCode->strStockCode))
			{
				pStockDayTable->LoadFromDayFile(pStockCode->strStockDayFilePath);
			}
			else
			{
				CStockDayTable *pExpStockDayTable;
				pExpStockDayTable=GetStockDayTable("SH000001");
				pStockDayTable->LoadFromDayFileRepairDate(pStockCode->strStockDayFilePath,pExpStockDayTable);
			}
			if(pStockDayTable->GetStockDayDataListSize()>0)
				vecStockDayTableList.push_back(pStockDayTable);
			else
			{
				pStockCode->strStockDayFilePath = "";
				pStockCode->strStockMinFilePath = "";
			}
		}

		if(pStockCode->strStockMinFilePath!="")
		{
			pStockMin5Table=new CStockMin5Table(pStockCode->strStockCode);
			if(IsExpStock(pStockCode->strStockCode))
			{
				pStockMin5Table->LoadFromMin5File(pStockCode->strStockMinFilePath);
			}
			else
			{
				CStockMin5Table *pExpStockMin5Table;
				pExpStockMin5Table=GetStockMin5Table("SH000001");
				pStockMin5Table->LoadFromMin5FileRepairDate(pStockCode->strStockMinFilePath,pExpStockMin5Table);
			}
			//pStockMin5Table->AddNearestStockData(pStockMin5Table->GetNearestStockDataFormHttp(100));
			if (pStockMin5Table->GetStockMin5DataListSize() > 0)
				vecStockMin5TableList.push_back(pStockMin5Table);
		}

	}

	Vec_StockCodeList vecTempStockCodeList;
	for (int i = 0; i < vecStockCodeList.size(); i++)
	{
		pStockCode = vecStockCodeList[i];

		if (!pStockCode)
			continue;
		if (pStockCode->strStockDayFilePath != "")
			vecTempStockCodeList.push_back(pStockCode);
	}
	vecStockCodeList.clear();
	vecStockCodeList = vecTempStockCodeList;
	return TRUE;
}

BOOL CStockDataMgr::Init(void)
{
	CString strPath;
/*
#ifdef _DEBUG

	strPath=GetReturnPath();
	strPath+="\\";
	strPath+=STOCK_CODE_XML_NAME;

#else*/
	strPath=SystemMgr()->GetMyStockXmlFile();

	if(!IsFileExists(strPath))
	{
		strPath=GetReturnPath();
		strPath+="\\";
		strPath+=STOCK_CODE_XML_NAME;

	}
//#endif
	
	LoadFromStockCodeXml(strPath);

	InitStockTableList();


	return TRUE;
}

CStockDayTable* CStockDataMgr::GetStockDayTable(CString strStockCode)
{
	CStockDayTable *pStockDayTable=NULL;
	LockDayTable();
	for(int i=0;i<vecStockDayTableList.size();i++)
	{
		if(!vecStockDayTableList[i])
			continue;
		if(vecStockDayTableList[i]->GetStockCode()==strStockCode)
		{
			pStockDayTable=vecStockDayTableList[i];
			UnlockDayTable();
			return pStockDayTable;
		}

	}
	UnlockDayTable();
	return NULL;

}

int  CStockDataMgr::GetStockDayTableIndex(CString strStockCode)
{
	int mResult=-1;
	LockDayTable();
	for(int i=0;i<vecStockDayTableList.size();i++)
	{
		if(!vecStockDayTableList[i])
			continue;
		if(vecStockDayTableList[i]->GetStockCode()==strStockCode)
		{
			mResult=i;
			UnlockDayTable();
			return mResult;
		}

	}
	UnlockDayTable();
	return mResult;
}

CString CStockDataMgr::GetStockDayBeginDate(CString strStockCode)
{
	CStockDayTable *pStockDayTable=NULL;
	pStockDayTable=GetStockDayTable(strStockCode);
	if(!pStockDayTable)
		return "";

	return pStockDayTable->GetStockBeginDate();
}


CString CStockDataMgr::GetStockDayEndDate(CString strStockCode)
{
	CStockDayTable *pStockDayTable=NULL;
	pStockDayTable=GetStockDayTable(strStockCode);
	if(!pStockDayTable)
		return "";

	return pStockDayTable->GetStockEndDate();

}


CString CStockDataMgr::GetStockDayDateReverseIndex(CString strStockCode,int index)
{
	CStockDayTable *pStockDayTable=NULL;
	pStockDayTable=GetStockDayTable(strStockCode);
	if(!pStockDayTable)
		return "";

	return pStockDayTable->GetStockDayDateReverseIndex(index);

}


CString CStockDataMgr::GetStockDayDatePreOfIndex(CString strStockCode,CString strDate,int prenums)
{
	CStockDayTable *pStockDayTable=NULL;
	pStockDayTable=GetStockDayTable(strStockCode);
	if(!pStockDayTable)
		return "";

	return pStockDayTable->GetStockDayDatePreOfIndex(strDate,prenums);
}

CString CStockDataMgr::GetStockDayDateAftOfIndex(CString strStockCode,CString strDate,int aftnums)
{
	CStockDayTable *pStockDayTable=NULL;
	pStockDayTable=GetStockDayTable(strStockCode);
	if(!pStockDayTable)
		return "";

	return pStockDayTable->GetStockDayDateAftOfIndex(strDate,aftnums);
}

//是否是指数
BOOL  CStockDataMgr::IsExpStock(CString strStockCode)
{
	if(strStockCode=="SH000001" || strStockCode=="SH000016" || strStockCode=="SH000300" || strStockCode=="SZ399001"||  strStockCode=="SZ399006" )
		return TRUE;
	return FALSE;
}

CString CStockDataMgr::GetStockName(CString strStockCode)
{
	LockStockList();
	for(int i=0;i<vecStockCodeList.size();i++)
	{
		if(vecStockCodeList[i]->strStockCode==strStockCode)
		{
			UnlockStockList();
			return vecStockCodeList[i]->strStockName;
		}
	}
	UnlockStockList();
	return "";
}

Vec_CString CStockDataMgr::GetStockCodeStringList(void)
{
	Vec_CString vecList;
	LockStockList();
	for(int i=0;i<vecStockCodeList.size();i++)
	{
		vecList.push_back(vecStockCodeList[i]->strStockCode);
	}
	UnlockStockList();
	return vecList;
}

CString CStockDataMgr::GetStockCode(CString strStockName)
{
	LockStockList();
	for(int i=0;i<vecStockCodeList.size();i++)
	{
		if(vecStockCodeList[i]->strStockName==strStockName)
		{
			UnlockStockList();
			return vecStockCodeList[i]->strStockCode;
		}
	}
	UnlockStockList();
	return "";
}


CStockMin5Table* CStockDataMgr::GetStockMin5Table(CString strStockCode)
{
	CStockMin5Table *pStockMin5Table=NULL;
	LockMin5Table();
	for(int i=0;i<vecStockMin5TableList.size();i++)
	{
		if(!vecStockMin5TableList[i])
			continue;
		if(vecStockMin5TableList[i]->GetStockCode()==strStockCode)
		{
			pStockMin5Table=vecStockMin5TableList[i];
			{
				UnlockMin5Table();
				return pStockMin5Table;
			}
		}

	}
	UnlockMin5Table();
	return NULL;
}

CString CStockDataMgr::GetStockMin5BeginDateTime(CString strStockCode)
{
	CStockMin5Table *pStockMin5Table=NULL;
	pStockMin5Table=GetStockMin5Table(strStockCode);
	if(!pStockMin5Table)
		return "";

	return pStockMin5Table->GetStockMin5BeginDateTime();
}

CString CStockDataMgr::GetStockMin5EndDateTime(CString strStockCode)
{
	CStockMin5Table *pStockMin5Table=NULL;
	pStockMin5Table=GetStockMin5Table(strStockCode);
	if(!pStockMin5Table)
		return "";

	return pStockMin5Table->GetStockMin5EndDateTime();
}



//获取指数最近日期（可当作股票的最近日期）
CString CStockDataMgr::GetExpLastDayDate(void)
{
	CStockDayTable *pExpDayTable=NULL;
	pExpDayTable=GetStockDayTable("SH000001");
	if(!pExpDayTable)
		return "";
	return pExpDayTable->GetLastStockDate();
}

//获取倒序指定的指数最近日期
CString CStockDataMgr::GetExpLastDayDateByReverse(int index)
{
	CStockDayTable *pExpDayTable=NULL;
	pExpDayTable=GetStockDayTable("SH000001");
	if(!pExpDayTable)
		return "";
	return pExpDayTable->GetLastStockDateByReverse(index);
}

//获取倒序指定的日期前指定周期的日期
CString CStockDataMgr::GetExpPreDayDateByPreDateIndex(CString strDate,int preIndex)
{
	CStockDayTable *pExpDayTable=NULL;
	pExpDayTable=GetStockDayTable("SH000001");
	if(!pExpDayTable)
		return "";

	return pExpDayTable->GetStockDayDatePreOfIndexReverse(strDate,preIndex);
}

//指定时间，指数天数据是否存在
BOOL CStockDataMgr::IsExpDayDataExist(CString strDate)
{
	CStockDayTable *pExpDayTable=NULL;
	pExpDayTable=GetStockDayTable("SH000001");
	if(!pExpDayTable)
		return FALSE;

	if(pExpDayTable->GetStockDayDataByDate(strDate)!=NULL)
		return TRUE;

	return FALSE;
}

//获取指数最近5分钟日期（可当作股票的最近5分钟日期）
CString CStockDataMgr::GetExpLastMin5Date(void)
{
	CStockMin5Table *pExpMin5Table=NULL;
	pExpMin5Table=GetStockMin5Table("SH000001");
	if(!pExpMin5Table)
		return "";
	return pExpMin5Table->GetLastStockMin5DataDateTime();
}



//指定时间，指数5分钟数据是否存在
BOOL CStockDataMgr::IsExpMin5DataExist(CString strDateTime)
{
	CStockMin5Table *pExpMin5Table=NULL;
	pExpMin5Table=GetStockMin5Table("SH000001");
	if(!pExpMin5Table)
		return FALSE;

	if(pExpMin5Table->GetStockMin5Index(strDateTime)==-1)
		return FALSE;

	return TRUE;
}

//获取前一天的日期根据日期时间
CString  CStockDataMgr::GetExpPreDayDateByDateTime(CString strDateTime)
{
	CStockDayTable *pExpDayTable=NULL;
	pExpDayTable=GetStockDayTable("SH000001");
	if(!pExpDayTable)
		return "";
	CString strTime="";
	CString strDate="";
	CStringArray arryVal;
	StringSplit(strDateTime,arryVal,' ');
	if(arryVal.GetSize()==2)
	{
		strDate=arryVal.GetAt(0);
		strTime=arryVal.GetAt(1);
	}
	else
		return "";
	int index=pExpDayTable->GetStockDayIndex(strDate);
	if(index<=0)
		return "";

	index--;

	CString strResult=pExpDayTable->GetStockDayDateByIndex(index);

	return strResult;
}



//获取股票板块类型
int  CStockDataMgr::GetStockBoard(CString strStockCode)
{
	if(IsExpStock(strStockCode))
		return STOCK_BOARD_ZS;
	CString strTemp=strStockCode.Left(2);
	if(strTemp=="SH")
	{
		return STOCK_BOARD_SH;
	}
	else
	{
		strTemp=strStockCode.Mid(2);
		CString strTemp2;
		strTemp2=strTemp.Left(3);
		
		
		strTemp2=strTemp.Left(1);
		if(strTemp2=="3")
			return STOCK_BOARD_CY;
		else
			return STOCK_BOARD_SZ;
		
	}
}

//通过板块类型获取指数代码
CString CStockDataMgr::GetExpCodeByBoardType(int  mType)
{
	if(STOCK_BOARD_ZS==mType)
		return "SH000001";
	else if(STOCK_BOARD_SH==mType)
		return "SH000001";
	else if(STOCK_BOARD_SZ==mType)
		return "SZ399001";
	else
		return "SZ399006";
}