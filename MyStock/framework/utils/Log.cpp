#include "StdAfx.h"
#include "Log.h"
#include "Util.h"
CStdioFile fileError;
CStdioFile fileDebug;
BOOL bFileErrorOpen=FALSE;
BOOL bFileDebugOpen=FALSE;

CRITICAL_SECTION mLogLock;


#define DEBUG_LEVEL_DEBUG	1
#define DEBUG_LEVEL_DEBUG2	2
#define DEBUG_LEVEL_DEBUG3	4
#define DEBUG_LEVEL_DEBUG4	8
#define DEBUG_LEVEL_WARNING 16
#define DEBUG_LEVEL_ERROR	32



static int mCurLevel=DEBUG_LEVEL_DEBUG|DEBUG_LEVEL_DEBUG2|DEBUG_LEVEL_DEBUG3|DEBUG_LEVEL_DEBUG4;

void TryLockLogDebug() 
{ 
	::TryEnterCriticalSection(&mLogLock); 
}

void LockLogDebug() 
{ 
	::EnterCriticalSection(&mLogLock); 
}

void UnlockLogDebug() 
{ 
	::LeaveCriticalSection(&mLogLock); 
}


void PrintfDebug(const char *format, ... )
{
	va_list ap;
	va_start(ap, format);
	PrintfInfo(format, DEBUG_LEVEL_DEBUG,ap);
	va_end(ap);
}

void PrintfDebug2(const char *format, ... )
{
	va_list ap;
	va_start(ap, format);
	PrintfInfo(format, DEBUG_LEVEL_DEBUG2,ap);
	va_end(ap);

}
void PrintfDebug3(const char *format, ... )
{

	va_list ap;
	va_start(ap, format);
	PrintfInfo(format, DEBUG_LEVEL_DEBUG3,ap);
	va_end(ap);

}
void PrintfDebug4(const char *format, ... )
{
	va_list ap;
	va_start(ap, format);
	PrintfInfo(format, DEBUG_LEVEL_DEBUG4,ap);
	va_end(ap);

}


void PrintfWarning(const char *format, ... )
{
	va_list ap;
	va_start(ap, format);
	PrintfInfo(format, DEBUG_LEVEL_WARNING,ap);
	va_end(ap);
}


void PrintfDebugError(const char *format, ... )
{

	va_list ap;
	va_start(ap, format);
	PrintfInfo(format, DEBUG_LEVEL_ERROR,ap);
	va_end(ap);
}


void PrintfInfo(const char *format, int level, va_list argp )
{
	if(!(level&mCurLevel))
		return;
	char buf[1024];
	vsnprintf(buf, 1024, format, argp);
	if(bFileDebugOpen&&fileDebug)
		fileDebug.WriteString( buf );	
	//printf("%s",buf);

}

void PrintfError(const char *format, ...)
{
	va_list ap;
	char buf[1024];
	va_start(ap, format);
	vsnprintf(buf, 1024, format, ap);
	va_end(ap);
	if(bFileErrorOpen&&fileError)
		fileError.WriteString( buf );	
	
}

void LogFileOpen(void)
{
	CString strPath;
	
		
	strPath=GetReturnPath();
	strPath+="\\log\\";
	strPath+="ErrorLog";
	strPath+=GetYMDHMS();
	strPath+=".txt";
	fileError.Open(strPath,CFile::modeCreate|CFile::modeWrite|CFile::typeText);
	bFileErrorOpen=TRUE;

	strPath=GetReturnPath();
	strPath+="\\log\\";
	strPath+="DebugLog";
	strPath+=GetYMDHMS();
	strPath+=".txt";
	fileDebug.Open(strPath,CFile::modeCreate|CFile::modeWrite|CFile::typeText);
	bFileDebugOpen=TRUE;
}


void LogFileClose(void)
{
	bFileErrorOpen=FALSE;
	bFileDebugOpen=FALSE;
	fileDebug.Close();
	
	fileError.Close();
	
}

void LogInit(void)
{
	::InitializeCriticalSection(&mLogLock);
}

void LogUnInit(void)
{
	::DeleteCriticalSection(&mLogLock);
}