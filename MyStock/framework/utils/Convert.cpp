#include "StdAfx.h"
#include "Convert.h"

std::wstring StringToWString(const std::string &str)
{
	std::wstring wstr(str.length(),L' ');
	std::copy(str.begin(), str.end(), wstr.begin());
	return wstr; 
}


std::string WStringToString(const std::wstring &wstr)
{
	std::string str(wstr.length(), ' ');
	std::copy(wstr.begin(), wstr.end(), str.begin());
	return str; 
}

void StringSplit(CString source, CStringArray& dest, char division)     
{     
	if(source.IsEmpty())  
	{  

	}  
	else  
	{  
		int pos = source.Find(division);  
		if(pos == -1)  
		{  
			dest.Add(source);  
		}  
		else  
		{  
			dest.Add(source.Left(pos));  
			source = source.Mid(pos+1);  
			StringSplit(source,dest,division);  
		}  
	}  
}  



std::string int_to_string(int d)
{
	char buf[20]={0};
	sprintf(buf, "%d", d);
	std::string b = buf;
	return b;
}


int string_to_int(std::string str)
{
	int n = atoi(str.c_str());
	return n;
}

std::string hex_to_string(unsigned char c)
{
	std::string s;
	unsigned char buf[3]={0};
	buf[0]=c/0x10;
	buf[1]=c%0x10;
	if(buf[0]>=10)
	{
		buf[0]='a'+(buf[0]-10);
	}
	else
	{
		buf[0]='0'+buf[0];
	}

	if(buf[1]>=10)
	{
		buf[1]='a'+(buf[1]-10);
	}
	else
	{
		buf[1]='0'+buf[1];
	}
	s.assign((const char*)buf);
	return s;

}

CString UnixTimerToDateTime(unsigned int  timestamp)
{

	struct tm tm;
	char s[100]={0};
	time_t t=(time_t)timestamp;

	tm = *localtime(&t);
	strftime(s, sizeof(s), "%Y-%m-%d %H:%M:%S", &tm);
	//printf("%d: %s\n", (int)tick, s);

	CString strResult;
	strResult=s;
	return strResult;
}


unsigned int DateTimeToUnixTimer(CString strDateTime)
{

	//CString s("2001-8-29 19:06:23");
	int nYear, nMonth, nDate, nHour, nMin, nSec;
	sscanf(strDateTime, "%d-%d-%d %d:%d:%d", &nYear, &nMonth, &nDate, &nHour, &nMin, &nSec);
	CTime t(nYear, nMonth, nDate, nHour, nMin, nSec);

	return t.GetTime();
}

CString UnixTimerToDate(unsigned int  timestamp)
{

	struct tm tm;
	char s[100]={0};
	time_t t=(time_t)timestamp;

	tm = *localtime(&t);
	strftime(s, sizeof(s), "%Y/%m/%d", &tm);
	CString strResult;
	strResult=s;
	return strResult;
}

// 2018/09/09 0909
CTime ConverDateTimeStringToCTime(CString strDate)
{
	int nYear, nMonth, nDate,mHour,mMin;

	CStringArray arryVal;
	StringSplit(strDate,arryVal,' ');
	ASSERT(arryVal.GetSize()==2);
	if(arryVal.GetSize()==2)
	{
		CString strDate=arryVal.GetAt(0);
		sscanf(strDate,"%d/%d/%d", &nYear, &nMonth, &nDate);

		CString strTime=arryVal.GetAt(1);

		CString strTemp=strTime.Left(2);
		mHour=atoi((LPCSTR)strTemp);
		strTemp=strTime.Right(2);
		mMin=atoi((LPCSTR)strTemp);
		CTime t(nYear, nMonth, nDate,mHour,mMin,0);
		return t;
	}
	else
	{
		
		CTime t(0, 0, 0,0,0,0);
		return t;
	}

	//sscanf(strDate,"%d/%d/%d %d:%d", &nYear, &nMonth, &nDate,&mHour,&mMin);
	//CTime t(nYear, nMonth, nDate,mHour,mMin,0);
	//return t;
}

CTime ConverStringToCTime(CString strDate)
{
	int nYear, nMonth, nDate;

	/*CStringArray arryVal;
	StringSplit(strDate,arryVal,'/');
	if(arryVal.GetSize()==3)
	{
		nYear=atoi((LPCSTR)arryVal.GetAt(0));
		nMonth=atoi((LPCSTR)arryVal.GetAt(1));
		nDate=atoi((LPCSTR)arryVal.GetAt(2));
	}
	*/

	sscanf(strDate,"%d/%d/%d", &nYear, &nMonth, &nDate);
	CTime t(nYear, nMonth, nDate,0,0,0);

	return t;
}

CString ConverCTimeToString(CTime mTime)
{
	int nYear, nMonth, nDay;
	nYear=mTime.GetYear();
	nMonth=mTime.GetMonth();
	nDay=mTime.GetDay();
	CString strResult;
	strResult.Format("%d/%02d/%02d",nYear,nMonth,nDay);
	return strResult;
}

//2018/09/09 0909
CString ConverCTimeToDateTimeString(CTime mTime)
{
	int nYear, nMonth, nDay,nHour,nMin;
	nYear=mTime.GetYear();
	nMonth=mTime.GetMonth();
	nDay=mTime.GetDay();
	nHour=mTime.GetHour();
	nMin=mTime.GetMinute();

	CString strResult;
	strResult.Format("%d/%02d/%02d %02d%02d",nYear,nMonth,nDay,nHour,nMin);
	return strResult;
}

int CmpTwoDate(CString strDate1,CString strDate2)
{
	CTime time1,time2;
	time1=ConverStringToCTime(strDate1);
	time2=ConverStringToCTime(strDate2);
	CTimeSpan span=time1-time2;
	int iDay=span.GetDays(); 

	return iDay;

}

void ConvertGBKToUtf8(CString& strGBK) 
{
	int len = MultiByteToWideChar(CP_ACP, 0, (LPCTSTR)strGBK, -1, NULL, 0);
	WCHAR *wszUtf8 = new WCHAR[len+1];
	memset(wszUtf8, 0, len*2+2);
	MultiByteToWideChar(CP_ACP, 0, (LPCTSTR)strGBK, -1, wszUtf8, len);

	len = WideCharToMultiByte(CP_UTF8, 0, wszUtf8, -1, NULL, 0, NULL, NULL);
	char *szUtf8 = new char[len+1];
	memset(szUtf8, 0, len+1);
	WideCharToMultiByte(CP_UTF8, 0, wszUtf8, -1, szUtf8, len, NULL, NULL);

	strGBK = szUtf8;
	delete[] szUtf8;
	delete[] wszUtf8;
}

CString AlignStringBySpace(CString strInfo,int mAlignNums)
{

	int length=strInfo.GetLength();

	if(length>=mAlignNums)
		return strInfo;
	
	int mNum=mAlignNums-length;
	CString strTemp="";
	for(int i=0;i<mNum;i++)
	{
		 strTemp += _T(' ');
	}
	strTemp+=strInfo;
	
	return strTemp;

}



std::string FloatConvrtString(float fVal)
{
	CString strVal;
	strVal.Format("%.2f",fVal);
	return (LPCSTR)strVal;
}