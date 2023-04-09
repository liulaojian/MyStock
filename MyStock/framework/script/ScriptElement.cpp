#include "StdAfx.h"
#include "ScriptElement.h"

CScriptElement* CScriptElement::s_pIntance = NULL;

CScriptElement::CScriptElement(void)
{
	
}

CScriptElement::~CScriptElement(void)
{
	
}

CScriptElement* CScriptElement::GetInstance()
{
	if (s_pIntance == NULL)
	{
		s_pIntance = new CScriptElement();
		
	}
	
	return s_pIntance;
}

//登陆淘宝

int CScriptElement::LoginTaobao(CString strAccount,CString strPassword)
{
	
	return 0;
}

//转到指定Url
int CScriptElement::GotoUrl(CString Url)
{
	
	return 0;
}

//移动到指定位置并点击
int CScriptElement::GotoClick(int x,int y)
{

	return 0;
}

//鼠标滚轮向上滚
int CScriptElement::WhellUp(void)
{

	return 0;
}

//鼠标滚轮向下滚
int CScriptElement::WhellDown(void)
{

	return 0;
}
//输入英文字符串
int CScriptElement::InputString(CString strInput)
{

	return 0;
}
//输入汉字字符串
int CScriptElement::InputHZString(CString strInput)
{

	return 0;
}
//查找图片
int CScriptElement::FindPic(int x0,int y0,int x1 ,int y1,CString strPicFileName,CString strdelta_color, double sim,int *x,int *y)
{

	return 0;
}

//查找颜色
int CScriptElement::FindColor(int x0,int y0,int x1,int y1,CString strColor,double sim,int *x,int *y)
{

	return 0;
}

//获取屏幕指定点颜色数据
long CScriptElement::GetScreenData(int x0,int y0,int x1,int y1)
{

	return 0;
}

//设置字库文件
long  CScriptElement::SetDict(int index,CString strFile)
{

	return 0;
}

//查找字符串
long CScriptElement::FindStr(int x0,int y0,int x1, int y1,CString strString,CString strColor_format,double sim,int *x,int *y)
{

	return 0;
}

//查找字符串通过指定系统字体
long CScriptElement::FindStrWithFont(int x0,int y0,int x1, int y1,CString strString,CString strColor_format,double sim,CString strFont_name, int font_size,int flag,int *x,int *y)
{

	return 0;
}

//ocr指定区域返回字符串 
CString CScriptElement::Ocr(int x0,int y0,int x1, int y1,CString strColor_format,double sim)
{

	return "";
}

//ocr指定区域返回字符串 
CString CScriptElement::OcrEx(int x0,int y0,int x1, int y1,CString strColor_format,double sim)
{

	return "";
}

//给指定的字库中添加一条字库信息.
long CScriptElement::AddDict(int index,CString dict_info)
{

	return 0;
}
//清空指定的字库.
long CScriptElement::ClearDict(int index)
{

	return 0;
}

//根据指定的范围,以及指定的颜色描述，提取点阵信息，类似于大漠工具里的单独提取.
CString CScriptElement::FetchWord(int x0,int y0,int x1, int y1, CString color, CString word)
{

	return "";
}

//根据指定的文字，以及指定的系统字库信息，获取字库描述信息.
CString CScriptElement::GetDictInfo(CString str,CString font_name,int font_size,int flag)
{

	return "";
}

//表示使用哪个字库文件进行识别(index范围:0-9)
long CScriptElement::UseDict(int index)
{

	return 0;
}

//设置全局路径
long CScriptElement::SetPath(CString path)
{

	return 0;
}

//购买页面购买  url 购买的页面  type 暂时统一为 0  num 购买数量  additional 购买的附加 以 | 分割 主要是款式 
short CScriptElement::BuyIng(LPCTSTR url, short type, short num, LPCTSTR additional)
{

	return 0;
}


//设置购买时所用的地址
short CScriptElement::SetBuyIngAddr(LPCTSTR person,  LPCTSTR addr)
{
	
	return 0;
}

short  CScriptElement:: PushOuterMsg(short MsgType,LPCTSTR MsgStr)
{

	return 0;
}