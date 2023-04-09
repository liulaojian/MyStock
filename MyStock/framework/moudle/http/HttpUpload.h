
#include "afxwin.h"
#include "afxinet.h"

class HttpUpload
{
public:
	HttpUpload();
	virtual ~HttpUpload();

	CHttpConnection* m_pConnection;
	CString MakeRequestHeaders(CString& strBoundary);
	CString MakePreFileData(CString& strBoundary, CString& strFileName, int iRecordID);
	CString MakePostFileData(CString& strBoundary);
	//BOOL SendTrack();    
	BOOL SendTrack(CString _mFilePath,CString defServerName,CString defObjectName);


};
