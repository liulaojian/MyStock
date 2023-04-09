#include "stdafx.h"
#include <Wincrypt.h>

#include <winsock.h>
#include <Nb30.h>
#include "Log.h"
#include "tlhelp32.h"
#pragma comment(lib, "Ws2_32.lib")
#pragma comment (lib, "Version.lib")
#pragma comment(lib,"netapi32.lib")
//��ȡ��������Ŀ¼
CString  GetReturnPath(void)  
{   
	CString    sPath;   
	GetModuleFileName(NULL,sPath.GetBufferSetLength(MAX_PATH+1),MAX_PATH);   
	sPath.ReleaseBuffer    ();   
	int    nPos;   
	nPos=sPath.ReverseFind('\\');   
	sPath=sPath.Left(nPos);   
	return    sPath;   
}


CString GetFileMd5(CString FileDirectory)  
{
	CString strFileMd5;
	HANDLE hFile=CreateFile(FileDirectory,GENERIC_READ,FILE_SHARE_READ,NULL,OPEN_EXISTING,NULL,NULL);
	if (hFile==INVALID_HANDLE_VALUE)                                        //���CreateFile����ʧ��  
	{   
		//��ʾCreateFile����ʧ�ܣ����������š�visual studio�п��ڡ����ߡ�>��������ҡ������ô���ŵõ�������Ϣ��  
		CloseHandle(hFile);
		return "";
	}
	HCRYPTPROV hProv=NULL;
	if(CryptAcquireContext(&hProv,NULL,NULL,PROV_RSA_FULL,CRYPT_VERIFYCONTEXT)==FALSE)       //���CSP��һ����Կ�����ľ��
		{
		return "";
	}
	HCRYPTPROV hHash=NULL;
	//��ʼ������������hash������������һ����CSP��hash������صľ��������������������    CryptHashData���á�
	if(CryptCreateHash(hProv,CALG_MD5,0,0,&hHash)==FALSE)
	{
		return "";
	}
	DWORD dwFileSize=GetFileSize(hFile,0);    //��ȡ�ļ��Ĵ�С
	if (dwFileSize==0xFFFFFFFF)               //�����ȡ�ļ���Сʧ��  
	{
		return "";
	}
	byte* lpReadFileBuffer=new byte[dwFileSize];
	DWORD lpReadNumberOfBytes;
	if (ReadFile(hFile,lpReadFileBuffer,dwFileSize,&lpReadNumberOfBytes,NULL)==0)        //��ȡ�ļ�  
	{
		return "";
	}
	if(CryptHashData(hHash,lpReadFileBuffer,lpReadNumberOfBytes,0)==FALSE)      //hash�ļ�  
	{
		return "";
	}
	delete[] lpReadFileBuffer;
	CloseHandle(hFile);          //�ر��ļ����
	BYTE *pbHash;
	DWORD dwHashLen=sizeof(DWORD);
	if (!CryptGetHashParam(hHash,HP_HASHVAL,NULL,&dwHashLen,0)) //��Ҳ��֪��ΪʲôҪ����������CryptGetHashParam������ǲ��յ�msdn       
	{
		return "";
	}
	pbHash=(byte*)malloc(dwHashLen);
	TCHAR str[12]={0};
	if(CryptGetHashParam(hHash,HP_HASHVAL,pbHash,&dwHashLen,0))//���md5ֵ 
	{
		for(DWORD i=0;i<dwHashLen;i++)         //���md5ֵ 
		{
			memset(str,0,12);
			CString strFilePartM=_T("");
			_stprintf(str,_T("%02x"),pbHash[i]);
			strFileMd5+=str;
		}
	} 

		//�ƺ���
	if(CryptDestroyHash(hHash)==FALSE)          //����hash����  
	{
			return strFileMd5;
	}
	if(CryptReleaseContext(hProv,0)==FALSE)
	{
		return strFileMd5;
	}

	return strFileMd5;
}


CString GetFileMd5_6(CString FileDirectory)  
{
	CString strMd5=GetFileMd5(FileDirectory);
	if(strMd5.GetLength()>6)
		strMd5=strMd5.Left(6);
	return strMd5;
}


BOOL Mkdir(CString m_sFilePath)
{
	CFileFind m_FileFind;
	//CString m_sFilePath = "D://Program Files//Adobe//Adobe Flash CS3";
	if(!m_FileFind.FindFile(m_sFilePath))  //·���������򴴽���·��
	{
		CreateDirectory(m_sFilePath,NULL);
		return TRUE;
	}

	return FALSE;
}

//��ȡ�ļ�������չ��
CString GetFileTitleFromFileName(CString FileName,CString& ExtendName) 
{
	int Where;
	Where=FileName.ReverseFind('\\');
	if(Where==-1)
	{
		Where=FileName.ReverseFind('/');
	}
	CString FileTitle=FileName.Right(FileName.GetLength()-1-Where);
	int Which=FileTitle.ReverseFind('.');
	ExtendName=FileTitle.Right(FileTitle.GetLength()-Which-1);
	if (Which!=-1)
	{
		FileTitle=FileTitle.Left(Which);
	}
	return FileTitle;
}



//��ȡ��ǰʱ��ĺ�����
__int64 GetNowTime(void)
{
	CTime now = CTime::GetCurrentTime();			//��ȡ 1970 �����ڵ����������Ժ���Ҫ*1000
	__int64 time = now.GetTime();		
	return (time*1000);
}

//��ȡ������ʱ����
CString GetYMDHMS(void)
{
	char szTime[32]={0};
	CTime time;
	time = CTime::GetCurrentTime();
	sprintf(szTime, "%4d_%2d_%2d_%2d_%2d_%2d",
		time.GetYear(), time.GetMonth(), time.GetDay(),
		time.GetHour(), time.GetMinute(), time.GetSecond());
	return szTime;
}


BOOL NistGetTime(LPFILETIME OutTime)  
{  
	BOOL bOk;  
	struct hostent *host;  

	bOk = FALSE;  
	if (host = gethostbyname("time.nist.gov"))  // 
	{  
		SOCKET s;  
		in_addr ia;  
		CHAR IpText[32];  

		memcpy(&ia, host->h_addr, host->h_length);  
		lstrcpyA(IpText, inet_ntoa(ia));  
		s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);  
		if (s != INVALID_SOCKET)  
		{  
			sockaddr_in sac;  

			memset(&sac, 0, sizeof(sac));  
			sac.sin_family = AF_INET;  
			sac.sin_port = htons(37);  
			sac.sin_addr.s_addr = inet_addr(IpText);  
			if (connect(s, (sockaddr*)&sac, sizeof(sac)) == 0)  
			{  
				ULONG nTime;  

				if (recv(s, (PCHAR)&nTime, sizeof(nTime), 0) == sizeof(nTime))  
				{  
					LONGLONG llt;  

					nTime = ntohl(nTime);  
					llt = 0x014F373BFDE04000;//1900.1.1  
					llt += LONGLONG(nTime) * 10000000;  
					memcpy(OutTime, &llt, sizeof(FILETIME));  
					bOk = TRUE;  
				}  
			}  
			closesocket(s);  
		}  
	}  
	return bOk;  
}  


void FileTimeToTime_t( FILETIME ft, time_t *t ) 
{ 
	LONGLONG ll; 

	ULARGE_INTEGER            ui; 
	ui.LowPart            = ft.dwLowDateTime; 
	ui.HighPart            = ft.dwHighDateTime; 

	ll            = ft.dwHighDateTime << 32 + ft.dwLowDateTime; 

	*t            = ((LONGLONG)(ui.QuadPart - 116444736000000000) / 10000000); 
}



//��ȡ����ip��ַ�б�
CString  GetHostIpList(void)
{
	CString strResult="";
	CString strTemp;
	WSADATA wsaData;  
	WORD sockVersion=MAKEWORD(2,2);  
	if (::WSAStartup (sockVersion,&wsaData)!=0)  
		return "";
	char szHost[256];  
	//ȡ�ñ�����������  
	::gethostname(szHost,256);  
	hostent *pHost=::gethostbyname(szHost);  
	//��ӡ������IP��ַ  
	in_addr addr;  
	for(int i=0;;i++)  
	{  
		char *p=pHost->h_addr_list[i];  
		if(p==NULL)  
			break;  
		memcpy(&addr.S_un.S_addr,p,pHost->h_length);  
		if(strResult!="")
			strResult+="#";
		strTemp=::inet_ntoa(addr);  
		strResult+=strTemp;
	}  
	::WSACleanup();  
	return strResult;
}


CString AnalysisDomain(CString strDomain)
{
	
	CString strResult="";
	
	
	HOSTENT* host_entry;  
	//int iStar = ::GetCurrentTime();  
	//char host_name[256] = (LPCTSTR)strDomain;//ע�����ﲻҪ��http://��Щǰ׺  
	host_entry = gethostbyname((LPCTSTR)strDomain);  
	//printf("%s\n",host_name);  
	if(host_entry != 0)  
	{  
		strResult.Format("%d.%d.%d.%d",(host_entry->h_addr_list[0][0]&0x00ff),  
			(host_entry->h_addr_list[0][1]&0x00ff),  
			(host_entry->h_addr_list[0][2]&0x00ff),  
			(host_entry->h_addr_list[0][3]&0x00ff));  
	}  

	return strResult;

}

CString GetCurDateString(void)
{
	CTime t = CTime::GetCurrentTime(); //��ȡϵͳ����
	int d=t.GetDay(); //��ü���
	int y=t.GetYear(); //��ȡ���
	int m=t.GetMonth(); //��ȡ��ǰ�·�
	int h=t.GetHour(); //��ȡ��ǰΪ��ʱ
	int mm=t.GetMinute(); //��ȡ����
	int s=t.GetSecond(); //��ȡ��
	int w=t.GetDayOfWeek(); //��ȡ���ڼ���ע��1Ϊ�����죬7Ϊ������
	CString strResult;
	strResult.Format("%d%02d%02d",y, m, d);
	return strResult;
}

CString GetCurHourMinString(void)
{
	CTime t = CTime::GetCurrentTime(); //��ȡϵͳ����
	int d=t.GetDay(); //��ü���
	int y=t.GetYear(); //��ȡ���
	int m=t.GetMonth(); //��ȡ��ǰ�·�
	int h=t.GetHour(); //��ȡ��ǰΪ��ʱ
	int mm=t.GetMinute(); //��ȡ����
	int s=t.GetSecond(); //��ȡ��
	CString strResult;
	strResult.Format("%02d%02d", h, mm);
	return strResult;
}



bool IsDirectoryExists(CString const& path)
{ 
	//�ж��Ƿ����
	if(!PathFileExists(path))
		return false;
	//�ж��Ƿ�ΪĿ¼
	DWORD attributes = ::GetFileAttributes(path);  
	attributes &= FILE_ATTRIBUTE_DIRECTORY;
	return attributes == FILE_ATTRIBUTE_DIRECTORY;
}

bool IsFileExists(CString const& path)
{
	if(!PathFileExists(path))
		return false;

	return true;

}

CString GetCurTimeString(void)
{
	SYSTEMTIME stLocal;  

	::GetLocalTime(&stLocal);  


	//��ʾʱ��ļ����  

	const int nBufSize = 256;  

	TCHAR chBuf[nBufSize];  

	wsprintf(chBuf,_T(" %u:%u:%u"),              

		stLocal.wHour, stLocal.wMinute, stLocal.wSecond);  

	return chBuf;

}


BOOL KillProcessFromName(CString strProcessName)  
{  
	//�������̿���(TH32CS_SNAPPROCESS��ʾ�������н��̵Ŀ���)  
	HANDLE hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);  

	//PROCESSENTRY32���̿��յĽṹ��  
	PROCESSENTRY32 pe;  

	//ʵ������ʹ��Process32First��ȡ��һ�����յĽ���ǰ�����ĳ�ʼ������  
	pe.dwSize = sizeof(PROCESSENTRY32);  


	//�����IFЧ��ͬ:  
	//if(hProcessSnap == INVALID_HANDLE_VALUE)   ��Ч�ľ��  
	if(!Process32First(hSnapShot,&pe))  
	{  
		return FALSE;  
	}  

	//���ַ���ת��ΪСд  
	strProcessName.MakeLower();  

	//��������Ч  ��һֱ��ȡ��һ�����ѭ����ȥ  
	while (Process32Next(hSnapShot,&pe))  
	{  

		//pe.szExeFile��ȡ��ǰ���̵Ŀ�ִ���ļ�����  
		CString scTmp = pe.szExeFile;  


		//����ִ���ļ���������Ӣ����ĸ�޸�ΪСд  
		scTmp.MakeLower();  

		//�Ƚϵ�ǰ���̵Ŀ�ִ���ļ����ƺʹ��ݽ������ļ������Ƿ���ͬ  
		//��ͬ�Ļ�Compare����0  
		if(!scTmp.Compare(strProcessName))  
		{  

			//�ӿ��ս����л�ȡ�ý��̵�PID(������������е�PID)  
			DWORD dwProcessID = pe.th32ProcessID;  
			HANDLE hProcess = ::OpenProcess(PROCESS_TERMINATE,FALSE,dwProcessID);  
			::TerminateProcess(hProcess,0);  
			CloseHandle(hProcess);  
			return TRUE;  
		}  
		scTmp.ReleaseBuffer();  
	}  
	strProcessName.ReleaseBuffer();  
	return FALSE;  
}  


CString GetApplicationVersion()
{
	TCHAR szFullPath[MAX_PATH];
	DWORD dwVerInfoSize = 0;
	DWORD dwVerHnd;
	VS_FIXEDFILEINFO * pFileInfo;
	CString strVersion="";
	GetModuleFileName(NULL, szFullPath, sizeof(szFullPath));
	dwVerInfoSize = GetFileVersionInfoSize(szFullPath, &dwVerHnd);
	if (dwVerInfoSize)
	{
		// If we were able to get the information, process it:
		HANDLE  hMem;
		LPVOID  lpvMem;
		unsigned int uInfoSize = 0;

		hMem = GlobalAlloc(GMEM_MOVEABLE, dwVerInfoSize);
		lpvMem = GlobalLock(hMem);
		GetFileVersionInfo(szFullPath, dwVerHnd, dwVerInfoSize, lpvMem);
		::VerQueryValue(lpvMem, (LPTSTR)_T("\\"),(void**)&pFileInfo, &uInfoSize);
		int ret = GetLastError();
		WORD m_nProdVersion[4];
		// Product version from the FILEVERSION of the version info resource 
		m_nProdVersion[0] = HIWORD(pFileInfo->dwProductVersionMS); 
		m_nProdVersion[1] = LOWORD(pFileInfo->dwProductVersionMS);
		m_nProdVersion[2] = HIWORD(pFileInfo->dwProductVersionLS);
		m_nProdVersion[3] = LOWORD(pFileInfo->dwProductVersionLS); 

		
		strVersion.Format(_T("%d.%d.%d.%d"),m_nProdVersion[0],
			m_nProdVersion[1],m_nProdVersion[2],m_nProdVersion[3]);

		GlobalUnlock(hMem);
		GlobalFree(hMem);

		//AfxMessageBox(strVersion);
		
	}
	return strVersion;
} 


unsigned int GetUnixTimer(void)
{
	const time_t t = time(NULL);

	return t;
}

CString GetDateTimeStringByUnixTimestame(unsigned int timestamp)
{
	CTime tm(timestamp);
	CString str=tm.Format("%Y-%m-%d : %H:%M:%S ");
	return str;
}



CString EncryTeleNum(CString strTeleNum)
{
	char buf[256]={0};
	strcpy(buf,(LPCSTR)strTeleNum);
	int len=strlen(buf);
	for(int i=0;i<len;i++)
	{
		if(buf[i]>='0'&&buf[i]<='9')
			buf[i]=buf[i]+17;
	}
	CString strResult;
	strResult=buf;
	return strResult;
}

CString DecryTeleNum(CString strEncryTeleNum)
{
	char buf[256]={0};
	strcpy(buf,(LPCSTR)strEncryTeleNum);
	int len=strlen(buf);
	for(int i=0;i<len;i++)
	{
		if(buf[i]>='A'&&buf[i]<='J')
			buf[i]=buf[i]-17;
	}
	CString strResult;
	strResult=buf;
	return strResult;

}


int getMAC(char * mac)     //��NetAPI����ȡ����MAC��ַ  
{       
	NCB ncb;     //����һ��NCB(������ƿ�)���͵Ľṹ�����ncb  
	typedef struct _ASTAT_     //�Զ���һ���ṹ��_ASTAT_  
	{  
		ADAPTER_STATUS   adapt;   
		NAME_BUFFER   NameBuff   [30];       
	}ASTAT, *PASTAT;  
	ASTAT Adapter;     

	typedef struct _LANA_ENUM     //�Զ���һ���ṹ��_ASTAT_  
	{  
		UCHAR length;   
		UCHAR lana[MAX_LANA];     //�������MAC��ַ   
	}LANA_ENUM;       
	LANA_ENUM lana_enum;     

	//   ȡ��������Ϣ�б�       
	UCHAR uRetCode;       
	memset(&ncb, 0, sizeof(ncb));     //���ѿ����ڴ�ռ�ncb ��ֵ����Ϊֵ 0  
	memset(&lana_enum, 0, sizeof(lana_enum));     //���һ���ṹ���͵ı���lana_enum����ֵΪ0  
	//�Խṹ�����ncb��ֵ  
	ncb.ncb_command = NCBENUM;     //ͳ��ϵͳ������������  
	ncb.ncb_buffer = (unsigned char *)&lana_enum; //ncb_buffer��Աָ����LANA_ENUM�ṹ���Ļ�����  
	ncb.ncb_length = sizeof(LANA_ENUM);     
	//����������NCBENUM����Ի�ȡ��ǰ������������Ϣ�����ж��ٸ�������ÿ�������ı�ţ�MAC��ַ��   
	uRetCode = Netbios(&ncb); //����netbois(ncb)��ȡ�������к�      
	if(uRetCode != NRC_GOODRET)       
		return uRetCode;       

	//��ÿһ�������������������Ϊ�����ţ���ȡ��MAC��ַ     
	for(int lana=0; lana<lana_enum.length; lana++)       
	{  
		ncb.ncb_command = NCBRESET;   //����������NCBRESET������г�ʼ��  
		ncb.ncb_lana_num = lana_enum.lana[lana];   
		uRetCode = Netbios(&ncb);     
	}   
	if(uRetCode != NRC_GOODRET)  
		return uRetCode;       

	//   ׼��ȡ�ýӿڿ���״̬��ȡ��MAC��ַ  
	memset(&ncb, 0, sizeof(ncb));   
	ncb.ncb_command = NCBASTAT;    //����������NCBSTAT�����ȡ������Ϣ  
	ncb.ncb_lana_num = lana_enum.lana[0];     //ָ�������ţ��������ָ����һ��������ͨ��Ϊ��������   
	strcpy((char*)ncb.ncb_callname, "*");     //Զ��ϵͳ����ֵΪ*  
	ncb.ncb_buffer = (unsigned char *)&Adapter; //ָ�����ص���Ϣ��ŵı���  
	ncb.ncb_length = sizeof(Adapter);  
	//���ŷ���NCBASTAT�����Ի�ȡ��������Ϣ  
	uRetCode = Netbios(&ncb);   
	//   ȡ����������Ϣ����������������������Ļ������ر�׼��ð�ŷָ���ʽ��     
	if(uRetCode != NRC_GOODRET)     
		return uRetCode;     
	//������MAC��ַ��ʽת��Ϊ���õ�16������ʽ,������ַ���mac��   
	sprintf(mac,"%02X-%02X-%02X-%02X-%02X-%02X",       
		Adapter.adapt.adapter_address[0],       
		Adapter.adapt.adapter_address[1],       
		Adapter.adapt.adapter_address[2],       
		Adapter.adapt.adapter_address[3],       
		Adapter.adapt.adapter_address[4],       
		Adapter.adapt.adapter_address[5]   
	);   
	return 0;     
}  




