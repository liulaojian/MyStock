#include "stdafx.h"
#include "HttpUpload.h"

HttpUpload::HttpUpload()
{


}

HttpUpload::~HttpUpload()
{

}


CString HttpUpload::MakeRequestHeaders(CString &strBoundary)//��ͷ
{
	CString strFormat;
	CString strData;

	strFormat = _T("Content-Type: multipart/form-data; boundary=%s\r\n");//�������ļ�����Content-Type����Ϊ: multipart/form-data

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
	strFormat += _T("Content-Disposition: form-data; name=\"test1\"");//�����ļ����ݣ������Դ���������Ϣ
	strFormat += _T("\r\n\r\n");
	strFormat += _T("my name is xiaoxiong");
	strFormat += _T("\r\n");

	strFormat += _T("--%s");
	strFormat += _T("\r\n");
	strFormat += _T("Content-Disposition: form-data; name=\"test2\"");
	strFormat += _T("\r\n\r\n");
	strFormat += _T("����");
	strFormat += _T("\r\n");


	strFormat += _T("--%s");
	strFormat += _T("\r\n");
	strFormat += _T("Content-Disposition: form-data; name=\"upfile\"; filename=\"%s\"");
	//�ļ���ַ��Ϣ���˴���upfile����PHP��������һ�£������file.php ��37��˵��
	strFormat += _T("\r\n");
	strFormat += _T("Content-Type: image/gif");

	strFormat += _T("\r\n\r\n");
	strData.Format(strFormat,  strBoundary, strBoundary, strBoundary, strFileName);//

	return strData;
}

CString HttpUpload::MakePostFileData(CString &strBoundary)//���������
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

BOOL HttpUpload::SendTrack(CString _mFilePath,CString defServerName,CString defObjectName)//��������
{
	//CString _mFilePath;
	//_mFilePath = "d:\\aaa.png";//Ҫ���ı����ļ���ַ

	int startp = _mFilePath.ReverseFind('\\');
	int namelen = _mFilePath.GetLength()-startp-1;

	CString pcmname = _mFilePath;//.Mid(startp+1,namelen);


	//CString defServerName ="127.0.0.1";//��������ַ���������Ҳ�ڱ��أ�����дΪ��127.0.0.1����ץ�������Ϊlocalhost��ץ��������
	//CString defObjectName ="/weixin/file.php";//����ĵ�ַ���������˴����ļ����·��


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
	strHTTPBoundary = _T("---------------------------7b4a6d158c9");//����߽�ֵ
	strPreFileData = MakePreFileData(strHTTPBoundary, pcmname, iRecordID);
	strPostFileData = MakePostFileData(strHTTPBoundary);

	dwTotalRequestLength = strPreFileData.GetLength() + strPostFileData.GetLength() + fTrack.GetLength();//�������������ܳ���

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
		pHTTP->AddRequestHeaders(MakeRequestHeaders(strHTTPBoundary));//���Ͱ�ͷ����
		pHTTP->SendRequestEx(dwTotalRequestLength, HSR_SYNC | HSR_INITIATE);

#ifdef _UNICODE
		pHTTP->Write(W2A(strPreFileData), strPreFileData.GetLength());
#else
		pHTTP->Write((LPSTR)(LPCSTR)strPreFileData, strPreFileData.GetLength());//д�������������Ϣ
#endif

		dwReadLength = -1;
		while (0 != dwReadLength)
		{
			strDebugMessage.Format(_T("%u / %u\n"), fTrack.GetPosition(), fTrack.GetLength());
			TRACE(strDebugMessage);
			dwReadLength = fTrack.Read(pBuffer, dwChunkLength);
			if (0 != dwReadLength)
			{
				pHTTP->Write(pBuffer, dwReadLength);//д������������ļ����ö����ƽ��д���
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
