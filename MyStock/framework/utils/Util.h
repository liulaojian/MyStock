

CString  GetReturnPath(void) ;

CString GetFileMd5(CString FileDirectory) ;

CString GetFileMd5_6(CString FileDirectory) ;

BOOL Mkdir(CString m_sFilePath);

//获取文件名和扩展名
CString GetFileTitleFromFileName(CString FileName,CString& ExtendName) ;


__int64 GetNowTime(void);

CString GetYMDHMS(void);


BOOL NistGetTime(LPFILETIME OutTime) ;


CString  GetHostIpList(void);

CString AnalysisDomain(CString strDomain);


CString GetCurTimeString(void);

CString GetCurDateString(void);

CString GetCurHourMinString(void);

//获取1970后的秒数  时间戳
unsigned int GetUnixTimer(void);

//通过时间戳转成日期字符串
CString GetDateTimeStringByUnixTimestame(unsigned int timestamp);

bool IsDirectoryExists(CString const& path);

bool IsFileExists(CString const& path);

BOOL KillProcessFromName(CString strProcessName) ;

CString GetApplicationVersion();


CString EncryTeleNum(CString strTeleNum);
CString DecryTeleNum(CString strEncryTeleNum);

int getMAC(char * mac) ;


BOOL BrowseDir(CString& path, HWND hwndOwner, CString title);