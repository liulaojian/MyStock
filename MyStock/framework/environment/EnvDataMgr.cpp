#include "stdafx.h"
#include "EnvDataMgr.h"
#include "CommonMacro.h"
#include "XmlOperator.h"
#include "Util.h"
#include "Convert.h"

CEnvDataMgr* CEnvDataMgr::s_pIntance = NULL;
CEnvDataMgr::CEnvDataMgr()
{

}

CEnvDataMgr::~CEnvDataMgr()
{

}

CEnvDataMgr* CEnvDataMgr::GetInstance()
{
	if (s_pIntance == NULL)
	{
		s_pIntance = new CEnvDataMgr();
		CHECKF(s_pIntance);
	}

	return s_pIntance;
}



BOOL CEnvDataMgr:: LoadEnvIntereDataFromXml(CString strXmlPath)
{
	for(int i=0;i<vecEnvInterestDataList.size();i++)
	{
		if(vecEnvInterestDataList[i])
			SAFE_DELETE(vecEnvInterestDataList[i]);
	}
	vecEnvInterestDataList.clear();

	VecTiXmlElement vecTiXmlElement;
	vecTiXmlElement=CXmlOperator::QueryNode_Element((LPCTSTR)strXmlPath,"Interests","Interest");
	TiXmlElement* pNode=NULL;
	CEnvInterestData *pEnvInterestData=NULL;
	for(int i=0;i<vecTiXmlElement.size();i++)
	{
		pNode=vecTiXmlElement[i];
		if(pNode)
		{
			pEnvInterestData=new CEnvInterestData();
			TiXmlAttribute* pAttr = NULL;   
			for (pAttr = pNode->FirstAttribute(); pAttr; pAttr = pAttr->Next())    
			{    
				std::string strAttName = pAttr->Name();  
				std::string strAttValue = pAttr->Value();  
				if(strAttName=="date")
				{
					pEnvInterestData->SetDate(strAttValue.c_str());
					
				}
				else if(strAttName=="deposit_after")
				{
					pEnvInterestData->SetDepositAfter(atof(strAttValue.c_str()));
				}
				else if(strAttName=="deposit_range")
				{
					pEnvInterestData->SetDepositRange(atof(strAttValue.c_str()));
				}
				else if(strAttName=="loans_after")
				{
					pEnvInterestData->SetLoansAfter(atof(strAttValue.c_str()));

				}
				else if(strAttName=="loans_range")
				{
					pEnvInterestData->SetLoansRange(atof(strAttValue.c_str()));
				}

			}    

			if(pEnvInterestData->GetDate()!="")
				vecEnvInterestDataList.push_back(pEnvInterestData);
			else
				SAFE_DELETE(pEnvInterestData);

		}
	}

	return TRUE;
}



BOOL CEnvDataMgr:: LoadEnvReserveDataFromXml(CString strXmlPath)
{
	for(int i=0;i<vecEnvReserveDataList.size();i++)
	{
		if(vecEnvReserveDataList[i])
			SAFE_DELETE(vecEnvReserveDataList[i]);
	}
	vecEnvReserveDataList.clear();

	VecTiXmlElement vecTiXmlElement;
	vecTiXmlElement=CXmlOperator::QueryNode_Element((LPCTSTR)strXmlPath,"Reserves","Reserve");
	TiXmlElement* pNode=NULL;
	CEnvReserveData *pEnvReserveData=NULL;
	for(int i=0;i<vecTiXmlElement.size();i++)
	{
		pNode=vecTiXmlElement[i];
		if(pNode)
		{
			pEnvReserveData=new CEnvReserveData();
			TiXmlAttribute* pAttr = NULL;   
			for (pAttr = pNode->FirstAttribute(); pAttr; pAttr = pAttr->Next())    
			{    
				std::string strAttName = pAttr->Name();  
				std::string strAttValue = pAttr->Value();  
				if(strAttName=="date")
				{
					pEnvReserveData->SetDate(strAttValue.c_str());
				}
				else if(strAttName=="big_after")
				{
					pEnvReserveData->SetBigAfter(atof(strAttValue.c_str()));
				}
				else if(strAttName=="big_range")
				{
					pEnvReserveData->SetBigRange(atof(strAttValue.c_str()));
				}
				else if(strAttName=="small_after")
				{
					pEnvReserveData->SetSmallAfter(atof(strAttValue.c_str()));
				}
				else if(strAttName=="small_range")
				{
					pEnvReserveData->SetSmallRange(atof(strAttValue.c_str()));
				}

			}    

			if(pEnvReserveData->GetDate()!="")
				vecEnvReserveDataList.push_back(pEnvReserveData);
			else
				SAFE_DELETE(pEnvReserveData);

		}
	}

	return TRUE;
}


BOOL CEnvDataMgr:: Init(void)
{
	CString strPath;
	strPath=GetReturnPath();
	strPath+="\\";
	strPath+=ENV_DATA_XML_NAME;

	LoadEnvIntereDataFromXml(strPath);
	LoadEnvReserveDataFromXml(strPath);

	return TRUE;
}



Vec_EnvInterestDataList CEnvDataMgr::GetEnvInterestDataListOfPreDate(CString strDate,int mNums)
{
	Vec_EnvInterestDataList vecDataList;
	CTime mDateTime=ConverStringToCTime(strDate);
	int mPos=-1;
	int mMaxDay=-99999;
	for(int i=0;i<vecEnvInterestDataList.size();i++)
	{
		CString strCheckTime=vecEnvInterestDataList[i]->GetDate();
		CTime mCheckDateTime=ConverStringToCTime(strCheckTime);

		CTimeSpan span=mCheckDateTime-mDateTime;
		int iDay=span.GetDays();
		if(iDay>mMaxDay && iDay<0)
		{
			mMaxDay=iDay;
			mPos=i;
		}
	}

	if(mPos<0)
		return vecDataList;


	if((mPos+1)<=mNums)
	{
		for(int i=0;i<=mPos;i++)
		{
			vecDataList.push_back(vecEnvInterestDataList[i]);
		}
	}
	else
	{
		int mN=mPos-mNums;

		for(int i=mN;i<=mPos;i++)
		{
			vecDataList.push_back(vecEnvInterestDataList[i]);
		}
	}

	return vecDataList;

}

Vec_EnvReserveDataList CEnvDataMgr::GetEnvReserveDataListOfPreDate(CString strDate,int mNums)
{
	Vec_EnvReserveDataList vecDataList;
	CTime mDateTime=ConverStringToCTime(strDate);
	int mPos=-1;
	int mMaxDay=-99999;
	for(int i=0;i<vecEnvReserveDataList.size();i++)
	{
		CString strCheckTime=vecEnvReserveDataList[i]->GetDate();
		CTime mCheckDateTime=ConverStringToCTime(strCheckTime);

		CTimeSpan span=mCheckDateTime-mDateTime;
		int iDay=span.GetDays();
		if(iDay>mMaxDay && iDay<0)
		{
			mMaxDay=iDay;
			mPos=i;
		}
	}

	if(mPos<0)
		return vecDataList;

	if((mPos+1)<=mNums)
	{
		for(int i=0;i<=mPos;i++)
		{
			vecDataList.push_back(vecEnvReserveDataList[i]);
		}
	}
	else
	{
		int mN=mPos-mNums;

		for(int i=mN;i<=mPos;i++)
		{
			vecDataList.push_back(vecEnvReserveDataList[i]);
		}
	}
	

	return vecDataList;
}