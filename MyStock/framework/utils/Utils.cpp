#include "stdafx.h"
#include <Wincrypt.h>

#include <winsock.h>
#include <Nb30.h>
#include "Log.h"
#include "tlhelp32.h"
#pragma comment(lib, "Ws2_32.lib")
#pragma comment (lib, "Version.lib")
#pragma comment(lib,"netapi32.lib")
//获取程序所在目录
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
	if (hFile==INVALID_HANDLE_VALUE)                                        //如果CreateFile调用失败  
	{   
		//提示CreateFile调用失败，并输出错误号。visual studio中可在“工具”>“错误查找”中利用错误号得到错误信息。  
		CloseHandle(hFile);
		return "";
	}
	HCRYPTPROV hProv=NULL;
	if(CryptAcquireContext(&hProv,NULL,NULL,PROV_RSA_FULL,CRYPT_VERIFYCONTEXT)==FALSE)       //获得CSP中一个密钥容器的句柄
		{
		return "";
	}
	HCRYPTPROV hHash=NULL;
	//初始化对数据流的hash，创建并返回一个与CSP的hash对象相关的句柄。这个句柄接下来将被    CryptHashData调用。
	if(CryptCreateHash(hProv,CALG_MD5,0,0,&hHash)==FALSE)
	{
		return "";
	}
	DWORD dwFileSize=GetFileSize(hFile,0);    //获取文件的大小
	if (dwFileSize==0xFFFFFFFF)               //如果获取文件大小失败  
	{
		return "";
	}
	byte* lpReadFileBuffer=new byte[dwFileSize];
	DWORD lpReadNumberOfBytes;
	if (ReadFile(hFile,lpReadFileBuffer,dwFileSize,&lpReadNumberOfBytes,NULL)==0)        //读取文件  
	{
		return "";
	}
	if(CryptHashData(hHash,lpReadFileBuffer,lpReadNumberOfBytes,0)==FALSE)      //hash文件  
	{
		return "";
	}
	delete[] lpReadFileBuffer;
	CloseHandle(hFile);          //关闭文件句柄
	BYTE *pbHash;
	DWORD dwHashLen=sizeof(DWORD);
	if (!CryptGetHashParam(hHash,HP_HASHVAL,NULL,&dwHashLen,0)) //我也不知道为什么要先这样调用CryptGetHashParam，这块是参照的msdn       
	{
		return "";
	}
	pbHash=(byte*)malloc(dwHashLen);
	TCHAR str[12]={0};
	if(CryptGetHashParam(hHash,HP_HASHVAL,pbHash,&dwHashLen,0))//获得md5值 
	{
		for(DWORD i=0;i<dwHashLen;i++)         //输出md5值 
		{
			memset(str,0,12);
			CString strFilePartM=_T("");
			_stprintf(str,_T("%02x"),pbHash[i]);
			strFileMd5+=str;
		}
	} 

		//善后工作
	if(CryptDestroyHash(hHash)==FALSE)          //销毁hash对象  
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
	if(!m_FileFind.FindFile(m_sFilePath))  //路径不存在则创建该路径
	{
		CreateDirectory(m_sFilePath,NULL);
		return TRUE;
	}

	return FALSE;
}

//获取文件名和扩展名
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



//获取当前时间的毫秒数
__int64 GetNowTime(void)
{
	CTime now = CTime::GetCurrentTime();			//获取 1970 到现在的秒数，所以后面要*1000
	__int64 time = now.GetTime();		
	return (time*1000);
}

//获取年月日时分秒
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



//获取本机ip地址列表
CString  GetHostIpList(void)
{
	CString strResult="";
	CString strTemp;
	WSADATA wsaData;  
	WORD sockVersion=MAKEWORD(2,2);  
	if (::WSAStartup (sockVersion,&wsaData)!=0)  
		return "";
	char szHost[256];  
	//取得本地主机名称  
	::gethostname(szHost,256);  
	hostent *pHost=::gethostbyname(szHost);  
	//打印出所有IP地址  
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
	//char host_name[256] = (LPCTSTR)strDomain;//注意这里不要加http://这些前缀  
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
	CTime t = CTime::GetCurrentTime(); //获取系统日期
	int d=t.GetDay(); //获得几号
	int y=t.GetYear(); //获取年份
	int m=t.GetMonth(); //获取当前月份
	int h=t.GetHour(); //获取当前为几时
	int mm=t.GetMinute(); //获取分钟
	int s=t.GetSecond(); //获取秒
	int w=t.GetDayOfWeek(); //获取星期几，注意1为星期天，7为星期六
	CString strResult;
	strResult.Format("%d%02d%02d",y, m, d);
	return strResult;
}

CString GetCurHourMinString(void)
{
	CTime t = CTime::GetCurrentTime(); //获取系统日期
	int d=t.GetDay(); //获得几号
	int y=t.GetYear(); //获取年份
	int m=t.GetMonth(); //获取当前月份
	int h=t.GetHour(); //获取当前为几时
	int mm=t.GetMinute(); //获取分钟
	int s=t.GetSecond(); //获取秒
	CString strResult;
	strResult.Format("%02d%02d", h, mm);
	return strResult;
}



bool IsDirectoryExists(CString const& path)
{ 
	//判断是否存在
	if(!PathFileExists(path))
		return false;
	//判断是否为目录
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


	//显示时间的间隔。  

	const int nBufSize = 256;  

	TCHAR chBuf[nBufSize];  

	wsprintf(chBuf,_T(" %u:%u:%u"),              

		stLocal.wHour, stLocal.wMinute, stLocal.wSecond);  

	return chBuf;

}


BOOL KillProcessFromName(CString strProcessName)  
{  
	//创建进程快照(TH32CS_SNAPPROCESS表示创建所有进程的快照)  
	HANDLE hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);  

	//PROCESSENTRY32进程快照的结构体  
	PROCESSENTRY32 pe;  

	//实例化后使用Process32First获取第一个快照的进程前必做的初始化操作  
	pe.dwSize = sizeof(PROCESSENTRY32);  


	//下面的IF效果同:  
	//if(hProcessSnap == INVALID_HANDLE_VALUE)   无效的句柄  
	if(!Process32First(hSnapShot,&pe))  
	{  
		return FALSE;  
	}  

	//将字符串转换为小写  
	strProcessName.MakeLower();  

	//如果句柄有效  则一直获取下一个句柄循环下去  
	while (Process32Next(hSnapShot,&pe))  
	{  

		//pe.szExeFile获取当前进程的可执行文件名称  
		CString scTmp = pe.szExeFile;  


		//将可执行文件名称所有英文字母修改为小写  
		scTmp.MakeLower();  

		//比较当前进程的可执行文件名称和传递进来的文件名称是否相同  
		//相同的话Compare返回0  
		if(!scTmp.Compare(strProcessName))  
		{  

			//从快照进程中获取该进程的PID(即任务管理器中的PID)  
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


int getMAC(char * mac)     //用NetAPI来获取网卡MAC地址  
{       
	NCB ncb;     //定义一个NCB(网络控制块)类型的结构体变量ncb  
	typedef struct _ASTAT_     //自定义一个结构体_ASTAT_  
	{  
		ADAPTER_STATUS   adapt;   
		NAME_BUFFER   NameBuff   [30];       
	}ASTAT, *PASTAT;  
	ASTAT Adapter;     

	typedef struct _LANA_ENUM     //自定义一个结构体_ASTAT_  
	{  
		UCHAR length;   
		UCHAR lana[MAX_LANA];     //存放网卡MAC地址   
	}LANA_ENUM;       
	LANA_ENUM lana_enum;     

	//   取得网卡信息列表       
	UCHAR uRetCode;       
	memset(&ncb, 0, sizeof(ncb));     //将已开辟内存空间ncb 的值均设为值 0  
	memset(&lana_enum, 0, sizeof(lana_enum));     //清空一个结构类型的变量lana_enum，赋值为0  
	//对结构体变量ncb赋值  
	ncb.ncb_command = NCBENUM;     //统计系统中网卡的数量  
	ncb.ncb_buffer = (unsigned char *)&lana_enum; //ncb_buffer成员指向由LANA_ENUM结构填充的缓冲区  
	ncb.ncb_length = sizeof(LANA_ENUM);     
	//向网卡发送NCBENUM命令，以获取当前机器的网卡信息，如有多少个网卡，每个网卡的编号（MAC地址）   
	uRetCode = Netbios(&ncb); //调用netbois(ncb)获取网卡序列号      
	if(uRetCode != NRC_GOODRET)       
		return uRetCode;       

	//对每一个网卡，以其网卡编号为输入编号，获取其MAC地址     
	for(int lana=0; lana<lana_enum.length; lana++)       
	{  
		ncb.ncb_command = NCBRESET;   //对网卡发送NCBRESET命令，进行初始化  
		ncb.ncb_lana_num = lana_enum.lana[lana];   
		uRetCode = Netbios(&ncb);     
	}   
	if(uRetCode != NRC_GOODRET)  
		return uRetCode;       

	//   准备取得接口卡的状态块取得MAC地址  
	memset(&ncb, 0, sizeof(ncb));   
	ncb.ncb_command = NCBASTAT;    //对网卡发送NCBSTAT命令，获取网卡信息  
	ncb.ncb_lana_num = lana_enum.lana[0];     //指定网卡号，这里仅仅指定第一块网卡，通常为有线网卡   
	strcpy((char*)ncb.ncb_callname, "*");     //远程系统名赋值为*  
	ncb.ncb_buffer = (unsigned char *)&Adapter; //指定返回的信息存放的变量  
	ncb.ncb_length = sizeof(Adapter);  
	//接着发送NCBASTAT命令以获取网卡的信息  
	uRetCode = Netbios(&ncb);   
	//   取得网卡的信息，并且如果网卡正常工作的话，返回标准的冒号分隔格式。     
	if(uRetCode != NRC_GOODRET)     
		return uRetCode;     
	//把网卡MAC地址格式转化为常用的16进制形式,输出到字符串mac中   
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




