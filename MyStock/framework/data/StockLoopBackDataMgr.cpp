#include "stdafx.h"
#include "StockLoopBackDataMgr.h"
#include "CommonMacro.h"
#include "T_FreeVector.h"


CStockLoopBackDataMgr* CStockLoopBackDataMgr::s_pIntance = NULL;

CStockLoopBackDataMgr::CStockLoopBackDataMgr()
{
	strLoopBackDayDate="";
	strLoopBackMin5DateTime="";
	

	::InitializeCriticalSection(&dayTableLock);
	::InitializeCriticalSection(&min5TableLock);
	::InitializeCriticalSection(&dayLPTableLock);
	::InitializeCriticalSection(&min5LPTableLock);
}

CStockLoopBackDataMgr::~CStockLoopBackDataMgr()
{
	::DeleteCriticalSection(&dayTableLock);
	::DeleteCriticalSection(&min5TableLock);
	::DeleteCriticalSection(&dayLPTableLock);
	::DeleteCriticalSection(&min5LPTableLock);

}

CStockLoopBackDataMgr* CStockLoopBackDataMgr::GetInstance()
{
	if (s_pIntance == NULL)
	{
		s_pIntance = new CStockLoopBackDataMgr();
		CHECKF(s_pIntance);
	}

	return s_pIntance;
}

//建立回测日数据
BOOL CStockLoopBackDataMgr::BuildtLoopBackDayData(void)
{

	if(strLoopBackDayDate=="")
		return FALSE;

	CFreeVector<Vec_StockDayTableList>::freeVector(vecStockDayTableList);
	CFreeVector<Vec_StockDayTableList>::freeVector(vecLPStockDayTableList);

	Vec_CString vecStockCodeList;
	vecStockCodeList=StockDataMgr()->GetStockCodeStringList();

	for(int i=0;i<vecStockCodeList.size();i++)
	{
		CString strStockCode=vecStockCodeList[i];
		CStockDayTable *pStockDayTable=StockDataMgr()->GetStockDayTable(strStockCode);
		if(pStockDayTable)
		{
			int mPos=pStockDayTable->GetStockDayIndex(strLoopBackDayDate);
			
			Vec_StockDayData vecData=pStockDayTable->GetStockDayDataList();
			
			if(mPos>0 && mPos<vecData.size())
			{
				Vec_StockDayData vecStockDayData;

				for(int j=0;j<mPos;j++)
				{
					vecStockDayData.push_back(vecData[j]);
				}

				CStockDayTable *pLPBFStockDayTable=new CStockDayTable(strStockCode);
				pLPBFStockDayTable->LoadFromVec(vecStockDayData);
				vecStockDayTableList.push_back(pLPBFStockDayTable);

				Vec_StockDayData vecLPStockDayData;

				for(int j=mPos;j<vecData.size();j++)
				{
					vecLPStockDayData.push_back(vecData[j]);
				}


				CStockDayTable *pLPStockDayTable=new CStockDayTable(strStockCode);
				pLPStockDayTable->LoadFromVec(vecLPStockDayData);
				vecLPStockDayTableList.push_back(pLPStockDayTable);
			}

			

		}

	}


	return TRUE;
}

//建立回测5分钟数据
BOOL CStockLoopBackDataMgr::BuildtLoopBackMin5Data(void)
{
	if(strLoopBackMin5DateTime=="")
		return FALSE;
	
	CFreeVector<Vec_StockMin5TableList>::freeVector(vecStockMin5TableList);
	CFreeVector<Vec_StockMin5TableList>::freeVector(vecLPStockMin5TableList);


	Vec_CString vecStockCodeList;
	vecStockCodeList=StockDataMgr()->GetStockCodeStringList();

	for(int i=0;i<vecStockCodeList.size();i++)
	{
		CString strStockCode=vecStockCodeList[i];
		CStockMin5Table *pStockMin5Table=StockDataMgr()->GetStockMin5Table(strStockCode);
		if(pStockMin5Table)
		{
			int mPos=pStockMin5Table->GetStockMin5Index(strLoopBackMin5DateTime);

			Vec_StockMin5Data vecData=pStockMin5Table->GetStockMin5DataList();

			if(mPos>0 && mPos<vecData.size())
			{
				Vec_StockMin5Data vecMin5Data;
				for(int j=0;j<mPos;j++)
				{
					vecMin5Data.push_back(vecData[j]);
				}
				CStockMin5Table  *pLPBFStockMin5Table=new CStockMin5Table(strStockCode);
				pLPBFStockMin5Table->LoadFromVec(vecMin5Data);
				vecStockMin5TableList.push_back(pLPBFStockMin5Table);

				Vec_StockMin5Data vecLPMin5Data;
				
				for(int j=mPos;j<vecData.size();j++)
				{
					vecLPMin5Data.push_back(vecData[j]);
				}
				CStockMin5Table  *pLPStockMin5Table=new CStockMin5Table(strStockCode);
				pLPStockMin5Table->LoadFromVec(vecLPMin5Data);
				vecLPStockMin5TableList.push_back(pLPStockMin5Table);

			}

		}
	
	}
	return TRUE;
}




CStockMin5Data * CStockLoopBackDataMgr::GetLoopBackNowMin5Data(CString strStockCode,int mMin5LoopBackNowPos)
{
	CStockMin5Table* pStockMin5Table=GetLPStockMin5Table(strStockCode);
	if(pStockMin5Table==NULL)
		return NULL;


	CStockMin5Data * pStockMin5Data=pStockMin5Table->GetStockMin5DataByIndex(mMin5LoopBackNowPos);



	return pStockMin5Data;

}


CStockDayTable* CStockLoopBackDataMgr::GetStockDayTable(CString strStockCode)
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

CStockDayTable* CStockLoopBackDataMgr::GetLPStockDayTable(CString strStockCode)
{

	CStockDayTable *pStockDayTable=NULL;
	LockLPDayTable();
	for(int i=0;i<vecLPStockDayTableList.size();i++)
	{
		if(!vecLPStockDayTableList[i])
			continue;
		if(vecLPStockDayTableList[i]->GetStockCode()==strStockCode)
		{
			pStockDayTable=vecLPStockDayTableList[i];
			UnlockLPDayTable();
			return pStockDayTable;
		}

	}
	UnlockLPDayTable();
	return NULL;
}

CStockMin5Table* CStockLoopBackDataMgr::GetStockMin5Table(CString strStockCode)
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

CStockMin5Table* CStockLoopBackDataMgr::GetLPStockMin5Table(CString strStockCode)
{
	CStockMin5Table *pStockMin5Table=NULL;
	LockLPMin5Table();
	for(int i=0;i<vecLPStockMin5TableList.size();i++)
	{
		if(!vecLPStockMin5TableList[i])
			continue;
		if(vecLPStockMin5TableList[i]->GetStockCode()==strStockCode)
		{
			pStockMin5Table=vecLPStockMin5TableList[i];
			{
				UnlockLPMin5Table();
				return pStockMin5Table;
			}
		}

	}
	UnlockLPMin5Table();
	return NULL;
}

