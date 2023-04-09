#include "stdafx.h"
#include "IndustryDataMgr.h"
#include "Util.h"
#include "Convert.h"
#include "StockDataMgr.h"
CIndustryDataMgr* CIndustryDataMgr::s_pIntance = NULL;


CIndustryDataMgr::CIndustryDataMgr()
{
	
}

CIndustryDataMgr::~CIndustryDataMgr()
{
	
}


CIndustryDataMgr* CIndustryDataMgr::GetInstance()
{
	if (s_pIntance == NULL)
	{
		s_pIntance = new CIndustryDataMgr();
	}

	return s_pIntance;
}

bool CIndustryDataMgr::Init(void)
{
	if (bInited)
		return false;

	LoadIndustryDataList();

	bInited = true;
	return true;
}

bool CIndustryDataMgr::LoadIndustryDataList(void)
{
	CString strPathFile;

	strPathFile = GetReturnPath();

	strPathFile += "\\行业.txt";

	CStdioFile industryFile;
	CString strTotal;
	if (industryFile.Open(strPathFile, CFile::modeRead))
	{
		CString strTemp;

		while (industryFile.ReadString(strTemp))
		{
			strTemp.Trim();
			strTemp.Trim('\n');
			strTemp.Trim('\r');
			strTemp.Trim('\n');
			strTemp.Trim('\r');

			strTotal += strTemp;
		}

		industryFile.Close();
	}
	
	CStringArray arryList;
	StringSplit(strTotal, arryList, ';');
	for (int i = 0; i < arryList.GetCount(); i++)
	{
		CString strInfo = arryList.GetAt(i);
		CStringArray arryList2;
		StringSplit(strInfo, arryList2, ',');
		if (arryList2.GetCount() == 4)
		{
			IndustryData* pIndustryData = new IndustryData();
			pIndustryData->strIndustryCode= (LPCSTR)arryList2.GetAt(0);
			pIndustryData->strIndustryName = (LPCSTR)arryList2.GetAt(1);
			CString strList= arryList2.GetAt(3);
			CStringArray arryList3;
			StringSplit(strList, arryList3, '_');
			for (int n = 0; n < arryList3.GetCount(); n++)
			{
				CString strCode;
				CString strTemp= arryList3.GetAt(n);
				if (strTemp.Left(2) == "60")
				{
					strCode = "SH";
					strCode += strTemp;
				}
				else
				{
					strCode = "SZ";
					strCode += strTemp;
				}

				if (StockDataMgr()->IsStockInCodeList(strCode))
				{
					pIndustryData->vecIndustryCfg.push_back((LPCSTR)strCode);
				}

				
			}
			vecIndustryDataList.push_back(pIndustryData);

		}

	}

	return true;
}


std::vector<std::string> CIndustryDataMgr::FindIndustryByStockCode(std::string strCode)
{
	std::vector<std::string> result;
	IndustryData* pIndustryData = NULL;
	for (int i = 0; i < vecIndustryDataList.size(); i++)
	{
		pIndustryData = vecIndustryDataList[i];
		for (int j = 0; j < pIndustryData->vecIndustryCfg.size(); j++)
		{
			if (pIndustryData->vecIndustryCfg[j] == strCode)
			{
				result.push_back(pIndustryData->strIndustryName);
			}
		}
	}

	return result;
}

//获取行业板块股数
int CIndustryDataMgr::GetIndustryStockNums(std::string strIndustryName)
{
	IndustryData* pIndustryData = NULL;
	for (int i = 0; i < vecIndustryDataList.size(); i++)
	{
		pIndustryData = vecIndustryDataList[i];
		if (pIndustryData->strIndustryName == strIndustryName)
		{
			return pIndustryData->vecIndustryCfg.size();
		}
	}

	return 0;
}

std::vector<std::string> CIndustryDataMgr::GetIndustryNameList(void)
{
	std::vector<std::string> vecList;
	for (int i = 0; i < vecIndustryDataList.size(); i++)
	{
		vecList.push_back(vecIndustryDataList[i]->strIndustryName);
	}
	return vecList;
}
