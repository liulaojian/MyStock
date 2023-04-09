#pragma once

#include <string>


std::wstring StringToWString(const std::string &str);
std::string WStringToString(const std::wstring &wstr);

void StringSplit(CString source, CStringArray& dest, char division)  ;


std::string int_to_string(int d);
int string_to_int(std::string str);
std::string hex_to_string(unsigned char c);

CString UnixTimerToDateTime(unsigned int  timestamp);
unsigned int DateTimeToUnixTimer(CString strDateTime);
void ConvertGBKToUtf8(CString& strGBK) ;
CString UnixTimerToDate(unsigned int  timestamp);
CTime ConverStringToCTime(CString strDate);
// 2018/09/09 0909
CTime ConverDateTimeStringToCTime(CString strDate);

CString ConverCTimeToString(CTime mTime);
//2018/09/09 0909
CString ConverCTimeToDateTimeString(CTime mTime);


CString AlignStringBySpace(CString strInfo,int mAlignNums);

int CmpTwoDate(CString strDate1,CString strDate2);

std::string FloatConvrtString(float fVal);