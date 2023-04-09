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
		if (c==0) break;  //如果到字符串尾则说明该字符串没有中文字符
		if (c&0x80)        //如果字符高位为1且下一字符高位也是1则有中文字符
			if (*str & 0x80) return true;
	}
	return false;
}