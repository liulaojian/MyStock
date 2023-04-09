#include "StdAfx.h"
#include "Verify.h"
#include "Convert.h"
#include <regex>  

using namespace std;  
using namespace std::tr1;




bool IsIpAddr(std::string strIpAddr)
{
	std::wstring wstrIpaddr;
	wstrIpaddr=StringToWString(strIpAddr);
	std::regex_constants::syntax_option_type fl = std::regex_constants::icase;  
	std::wregex pattern(L"((?:(?:25[0-5]|2[0-4]\\d|((1\\d{2})|([1-9]?\\d)))\\.){3}(?:25[0-5]|2[0-4]\\d|((1\\d{2})|([1-9]?\\d))))", fl);  
	std::wsmatch result;  
	std::wstring tmpStr = wstrIpaddr;  

	if( std::regex_search( tmpStr, result, pattern) )  
	{
		if( result.size() >0 )  
		{
			return true;
		}

	}

	return false;
}


bool IsIncludeChinese(LPCTSTR str)
{
	char c;
	while(true)
	{
		c=*str++;
		if (c==0) break;  //������ַ���β��˵�����ַ���û�������ַ�
		if (c&0x80)        //����ַ���λΪ1����һ�ַ���λҲ��1���������ַ�
			if (*str & 0x80) return true;
	}
	return false;
}