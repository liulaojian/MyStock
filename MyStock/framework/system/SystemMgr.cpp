#include "stdafx.h"
#include "SystemMgr.h"
#include "CommonMacro.h"
#include "Convert.h"
#include "Util.h"
#include "zbTypeDef.h"
CSystemMgr* CSystemMgr::s_pIntance = NULL;

CSystemMgr::CSystemMgr()
{
	strStockXmlFile="";
	strTitle="";
	mXuLiehao=0;
	mVolumeSerialNumber=0;
	bFakeMode=FALSE;
}

CSystemMgr::~CSystemMgr()
{

}


CSystemMgr* CSystemMgr::GetInstance()
{
	if (s_pIntance == NULL)
	{
		s_pIntance = new CSystemMgr();
		CHECKF(s_pIntance);
	}

	return s_pIntance;
}


//从股票数据导出目录中产生股票xml文件信息
CString CSystemMgr::BuildStockXmlInfo(void)
{
	CString strFoldername;
	strFoldername="F:\\stock\\day";
	Vec_CString vecFileNameList;
	CString m_cstrFileList="";
	CFileFind tempFind;
	BOOL bFound; //判断是否成功找到文件
	bFound=tempFind.FindFile(strFoldername   +   "\\*.txt");   
	CString strTmp;   //如果找到的是文件夹 存放文件夹路径
	while(bFound)      //遍历所有文件
	{
		bFound=tempFind.FindNextFile(); //第一次执行FindNextFile是选择到第一个文件，以后执行为选择
		//到下一个文件
		//if(!tempFind.IsDots()) continue; //如果找到的是返回上层的目录 则结束本次查找
		if(tempFind.IsDirectory())   //找到的是文件夹，则遍历该文件夹下的文件
		{
			
		}
		else
		{
			strTmp=tempFind.GetFileName(); //保存文件名，包括后缀名
			vecFileNameList.push_back(strTmp);
		}
	}
	tempFind.Close();
	CString strTotal="";
	for(int i=0;i<vecFileNameList.size();i++)
	{
		CString strLine;
		strLine=BuildSingleFileStockXmlInfo(strFoldername,vecFileNameList[i]);
		if(strLine!="")
		{
			strTotal+=strLine;
			strTotal+="\r\n";
		}
	}


	return strTotal;
}

BOOL  CSystemMgr::SaveStockXmlInfo(CString strStockInfo)
{
	CStdioFile saveFile;
	CString strFilePath;

	strFilePath=GetReturnPath();
	strFilePath+="\\XmlInfo.txt";

	if(saveFile.Open(strFilePath,CFile::modeCreate|CFile::modeWrite))
	{
		saveFile.WriteString(strStockInfo);
		saveFile.Close();
	}
	return TRUE;
}

CString CSystemMgr::BuildSingleFileStockXmlInfo(CString strFileDir,CString strFileName)
{
	CStdioFile dayFile;
	CString strFilePath=strFileDir;
	strFilePath+="\\";
	strFilePath+=strFileName;
	CString strStockName="";
	if(dayFile.Open(strFilePath,CFile::modeRead))
	{
		CString strTemp;
		if(dayFile.ReadString(strTemp))
		{
			CStringArray arryVal;
			StringSplit(strTemp,arryVal,' ');
			int mNums=arryVal.GetSize();
			if(mNums==4)
			{
				strStockName=arryVal.GetAt(1);
			}
		}

		dayFile.Close();
	}

	CString strResult="";
	CString strStockCode=strFileName;
	strStockCode.Replace("#","");
	CStringArray arryVal;
	StringSplit(strStockCode,arryVal,'.');
	if(arryVal.GetSize()==2)
	{
		strStockCode=arryVal.GetAt(0);

		if(strStockName!="")
		{
			strResult="<StockCode code=\"";
			strResult+=strStockCode;
			strResult+="\" name=\"";
			strResult+=strStockName;
			strResult+="\" dayfilepath=\"F:\\stock\\day\\";
			strResult+=strFileName;
			strResult+="\" minfilepath=\"F:\\stock\\mintue\\";
			strResult+=strFileName;
			strResult+="\"/>";
			return strResult;
		}
	}
	

	return "";
}




void  CSystemMgr::SetMyStockXmlFile(CString strFilePath)
{
	strStockXmlFile=strFilePath;
	CString strPath;
	strPath=GetReturnPath();
	strPath+="\\";
	strPath+=MYSTOCK_INI;
	::WritePrivateProfileString("MyStock","StockXmlFile", strStockXmlFile, strPath);
}

CString CSystemMgr::DoGetMyStockXmlFile(void)
{
	CString strPath;
	strPath=GetReturnPath();
	strPath+="\\";
	strPath+=MYSTOCK_INI;
	CString strTemp;
	::GetPrivateProfileString("MyStock","StockXmlFile","F:\\stock\\MyStock\\StockCode.xml", strTemp.GetBuffer(MAX_PATH), MAX_PATH,strPath);

	strStockXmlFile=strTemp;

	return strStockXmlFile;
}


CString  CSystemMgr::DoGetTitle(void)
{
	CString strPath;
	strPath=GetReturnPath();
	strPath+="\\";
	strPath+=MYSTOCK_INI;
	CString strTemp;
	::GetPrivateProfileString("MyStock","Title","MyStock", strTemp.GetBuffer(MAX_PATH), MAX_PATH,strPath);

	strTitle=strTemp;

	return strTitle;
}

void  CSystemMgr::SetTitle(CString strVal)
{
	strTitle=strVal;
	CString strPath;
	strPath=GetReturnPath();
	strPath+="\\";
	strPath+=MYSTOCK_INI;
	::WritePrivateProfileString("MyStock","Title", strTitle, strPath);
}


BOOL CSystemMgr::DoGetXuLieHao(void)
{
	CString strPath;
	strPath=GetReturnPath();
	strPath+="\\";
	strPath+=MYSTOCK_INI;
	CString strTemp;
	::GetPrivateProfileString("MyStock","XuLieHao","0", strTemp.GetBuffer(MAX_PATH), MAX_PATH,strPath);

	mXuLiehao=(DWORD)atof((LPCSTR)strTemp);

	return TRUE;
}

void CSystemMgr::SetXuLieHao(DWORD xuliehao)
{
	mXuLiehao=xuliehao;
	CString strPath;
	strPath=GetReturnPath();
	strPath+="\\";
	strPath+=MYSTOCK_INI;
	CString strValue;
	strValue.Format("%lu",xuliehao);
	::WritePrivateProfileString("MyStock","XuLieHao", strValue, strPath);
}

BOOL CSystemMgr:: CheckXuLieHao(void)
{
	DWORD VolumeSerialNumber;
	DoGetXuLieHao();
	GetVolumeInformation("c:\\",NULL,12,&VolumeSerialNumber,NULL,NULL,NULL,10);

	//char pNum[10];
	//itoa(mVolumeSerialNumber,pNum,16);

	VolumeSerialNumber^=0x12345678;

	if(VolumeSerialNumber==mXuLiehao)
		return TRUE;
	return FALSE;
}


DWORD CSystemMgr::GetVolumeSerialNumber(void)
{
	GetVolumeInformation("c:\\",NULL,12,&mVolumeSerialNumber,NULL,NULL,NULL,10);

	return mVolumeSerialNumber;
}