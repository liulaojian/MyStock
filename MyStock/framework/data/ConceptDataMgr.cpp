#include "stdafx.h"
#include "ConceptDataMgr.h"
#include "Util.h"
#include "Convert.h"

CConceptDataMgr* CConceptDataMgr::s_pIntance = NULL;


CConceptDataMgr::CConceptDataMgr()
{

}

CConceptDataMgr::~CConceptDataMgr()
{

}


CConceptDataMgr* CConceptDataMgr::GetInstance()
{
	if (s_pIntance == NULL)
	{
		s_pIntance = new CConceptDataMgr();
	}

	return s_pIntance;
}


bool CConceptDataMgr::Init(void)
{
	if (bInited)
		return false;

	LoadConceptDataList();

	bInited = true;
	return true;
}

bool CConceptDataMgr::LoadConceptDataList(void)
{
	CString strPathFile;

	strPathFile = GetReturnPath();

	strPathFile += "\\¸ÅÄî.txt";

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
			ConceptData* pConceptData = new ConceptData();
			pConceptData->strConceptCode = (LPCSTR)arryList2.GetAt(0);
			pConceptData->strConceptName = (LPCSTR)arryList2.GetAt(1);
			if (arryList2.GetAt(1).Find("×òÈÕ") != -1)
			{
				continue;
			}
			CString strList = arryList2.GetAt(3);
			CStringArray arryList3;
			StringSplit(strList, arryList3, '_');
			for (int n = 0; n < arryList3.GetCount(); n++)
			{
				CString strCode;
				CString strTemp = arryList3.GetAt(n);
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

				pConceptData->vecConceptCfg.push_back((LPCSTR)strCode);
			}
			vecConceptDataList.push_back(pConceptData);

		}

	}

	return true;
}

std::vector<std::string> CConceptDataMgr::FindConceptByStockCode(std::string strCode)
{
	std::vector<std::string> result;
	ConceptData* pConceptData = NULL;
	for (int i = 0; i < vecConceptDataList.size(); i++)
	{
		pConceptData = vecConceptDataList[i];
		for (int j = 0; j < pConceptData->vecConceptCfg.size(); j++)
		{
			if (pConceptData->vecConceptCfg[j] == strCode)
			{
				result.push_back(pConceptData->strConceptName);
			}
		}
	}

	return result;
}