#include "stdafx.h"
#include "HttpUpload.h"

HttpUpload::HttpUpload()
{


}

HttpUpload::~HttpUpload()
{

}


CString HttpUpload::MakeRequestHeaders(CString &strBoundary)//包头
{
	CString strFormat;
	CString strData;

	strFormat = _T("Content-Type: multipart/form-data; boundary=%s\r\n");//二进制文件传送Content-Type类型为: multipart/form-data

	strData.Format(strFormat, strBoundary);
	return strData;
}

CString HttpUpload::MakePreFileData(CString &strBoundary, CString &strFileName, int iRecordID)
{
	/**/////////////////////////////////////////////////////////////////////////////////
	//Content-Type:
	//JPG image/pjpeg
	//PNG image/x-png
	//BMP image/bmp
	//TIF image/tiff
	//GIF image/gif
	CString strFormat;
	CString strData;



	strFormat += _T("--%s");
	strFormat += _T("\r\n");
	strFormat += _T("Content-Disposition: form-data; name=\"test1\"");//除了文件数据，还可以传送其它信息
	strFormat += _T("\r\n\r\n");
	strFormat += _T("my name is xiaoxiong");
	strFormat += _T("\r\n");

	strFormat += _T("--%s");
	strFormat += _T("\r\n");
	strFormat += _T("Content-Disposition: form-data; name=\"test2\"");
	strFormat += _T("\r\n\r\n");
	strFormat += _T("哈哈");
	strFormat += _T("\r\n");


	strFormat += _T("--%s");
	strFormat += _T("\r\n");
	strFormat += _T("Content-Disposition: form-data; name=\"upfile\"; filename=\"%s\"");
	//文件地址信息，此处的upfile需与PHP服务器端一致，具体见file.php 第37行说明
	strFormat += _T("\r\n");
	strFormat += _T("Content-Type: image/gif");

	strFormat += _T("\r\n\r\n");
	strData.Format(strFormat,  strBoundary, strBoundary, strBoundary, strFileName);//

	return strData;
}

CString HttpUpload::MakePostFileData(CString &strBoundary)//发送请求包
{
	CString strFormat;
	CString strData;

	strFormat = _T("\r\n");	
	strFormat += _T("--%s");
	strFormat += _T("\r\n");
	strFormat += _T("Content-Disposition: form-data; name=\"upload\"");
	strFormat += _T("\r\n\r\n");
	strFormat += _T("hello");
	strFormat += _T("\r\n");
	strFormat += _T("--%s--");
	strFormat += _T("\r\n");


	strData.Format(strFormat, strBoundary, strBoundary);

	return strData;
}

BOOL HttpUpload::SendTrack(CString _mFilePath,CString defServerName,CString defObjectName)//发送数据
{
	//CString _mFilePath;
	//_mFilePath = "d:\\aaa.png";//要传的本地文件地址

	int startp = _mFilePath.ReverseFind('\\');
	int namelen = _mFilePath.GetLength()-startp-1;

	CString pcmname = _mFilePath;//.Mid(startp+1,namelen);


	//CString defServerName ="127.0.0.1";//服务器地址，如服务器也在本地，建议写为：127.0.0.1可以抓包，如果为localhost刚抓不到包。
	//CString defObjectName ="/weixin/file.php";//保存的地址，服务器端处理文件相对路径


	// USES_CONVERSION;
	CInternetSession Session;
	CHttpConnection *pHttpConnection = NULL;
	INTERNET_PORT   nPort = 80;
	CFile fTrack;
	CHttpFile* pHTTP;
	CString strHTTPBoundary;
	CString strPreFileData;
	CString strPostFileData;
	DWORD dwTotalRequestLength;
	DWORD dwChunkLength;
	DWORD dwReadLength;
	DWORD dwResponseLength;
	TCHAR szError[MAX_PATH];
	void* pBuffer;
	LPSTR szResponse;
	CString strResponse;
	BOOL bSuccess = TRUE;

	CString strDebugMessage;

	if (FALSE == fTrack.Open(_mFilePath, CFile::modeRead | CFile::shareDenyWrite))
	{
		AfxMessageBox(_T("Unable to open the file."));
		return FALSE;
	}

	int iRecordID = 1;
	strHTTPBoundary = _T("---------------------------7b4a6d158c9");//定义边界值
	strPreFileData = MakePreFileData(strHTTPBoundary, pcmname, iRecordID);
	strPostFileData = MakePostFileData(strHTTPBoundary);

	dwTotalRequestLength = strPreFileData.GetLength() + strPostFileData.GetLength() + fTrack.GetLength();//计算整个包的总长度

	dwChunkLength = 64 * 1024;

	pBuffer = malloc(dwChunkLength);

	if (NULL == pBuffer)
	{
		return FALSE;
	}

	try
	{
		pHttpConnection = Session.GetHttpConnection(defServerName,nPort);
		pHTTP = pHttpConnection->OpenRequest(CHttpConnection::HTTP_VERB_POST, defObjectName);
		pHTTP->AddRequestHeaders(MakeRequestHeaders(strHTTPBoundary));//发送包头请求
		pHTTP->SendRequestEx(dwTotalRequestLength, HSR_SYNC | HSR_INITIATE);

#ifdef _UNICODE
		pHTTP->Write(W2A(strPreFileData), strPreFileData.GetLength());
#else
		pHTTP->Write((LPSTR)(LPCSTR)strPreFileData, strPreFileData.GetLength());//写入服务器所需信息
#endif

		dwReadLength = -1;
		while (0 != dwReadLength)
		{
			strDebugMessage.Format(_T("%u / %u\n"), fTrack.GetPosition(), fTrack.GetLength());
			TRACE(strDebugMessage);
			dwReadLength = fTrack.Read(pBuffer, dwChunkLength);
			if (0 != dwReadLength)
			{
				pHTTP->Write(pBuffer, dwReadLength);//写入服务器本地文件，用二进制进行传送
			}
		}

#ifdef _UNICODE
		pHTTP->Write(W2A(strPostFileData), strPostFileData.GetLength());
#else
		pHTTP->Write((LPSTR)(LPCSTR)strPostFileData, strPostFileData.GetLength());
#endif

		pHTTP->EndRequest(HSR_SYNC);

		dwResponseLength = pHTTP->GetLength();
		while (0 != dwResponseLength)
		{
			szResponse = (LPSTR)malloc(dwResponseLength + 1);
			szResponse[dwResponseLength] = '\0';
			pHTTP->Read(szResponse, dwResponseLength);
			strResponse += szResponse;
			free(szResponse);
			dwResponseLength = pHTTP->GetLength();
		}



	} 
	catch (CException* e)
	{
		e->GetErrorMessage(szError, MAX_PATH);
		e->Delete();
		AfxMessageBox(szError);
		bSuccess = FALSE;
	}

	pHTTP->Close();
	delete pHTTP;

	fTrack.Close();

	if (NULL != pBuffer)
	{
		free(pBuffer);
	}
	return bSuccess;
}
