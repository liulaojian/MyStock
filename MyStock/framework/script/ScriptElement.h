#pragma once
#ifndef __SCRIPTELEMENT_H__
#define __SCRIPTELEMENT_H__


class CScriptElement
{
public:
	static CScriptElement* GetInstance();
public:
	CScriptElement(void);
	~CScriptElement(void);
public:
	
	//登陆淘宝
	int LoginTaobao(CString strAccount,CString strPassword);

	//转到指定Url
	int GotoUrl(CString Url);
	
	//移动到指定位置并点击
	int GotoClick(int x,int y);
	
	//鼠标滚轮向上滚
	int WhellUp(void);

	//鼠标滚轮向下滚
	int WhellDown(void);

	//输入英文字符串
	int InputString(CString strInput);

	//输入汉字字符串
	int InputHZString(CString strInput);

	//查找图片
	int FindPic(int x0,int y0,int x1 ,int y1,CString strPicFileName,CString strdelta_color, double sim,int *x,int *y);


	//查找颜色
	int FindColor(int x0,int y0,int x1,int y1,CString strColor,double sim,int *x,int *y);
	
	//获取屏幕指定点颜色数据
	long GetScreenData(int x0,int y0,int x1,int y1);

	//设置字库文件
	long  SetDict(int index,CString strFile);

	//查找字符串
	long FindStr(int x0,int y0,int x1, int y1,CString strString,CString strColor_format,double sim,int *x,int *y);

	//查找字符串通过指定系统字体
	long FindStrWithFont(int x0,int y0,int x1, int y1,CString strString,CString strColor_format,double sim,CString strFont_name, int font_size,int flag,int *x,int *y);
	
	//ocr指定区域返回字符串 
	CString Ocr(int x0,int y0,int x1, int y1,CString strColor_format,double sim);
	
	//ocr指定区域返回字符串 
	CString OcrEx(int x0,int y0,int x1, int y1,CString strColor_format,double sim);

	//给指定的字库中添加一条字库信息.
	long AddDict(int index,CString dict_info);

	//清空指定的字库.
	long ClearDict(int index);

	//根据指定的范围,以及指定的颜色描述，提取点阵信息，类似于大漠工具里的单独提取.
	CString FetchWord(int x0,int y0,int x1, int y1, CString color, CString word);

	//根据指定的文字，以及指定的系统字库信息，获取字库描述信息.
	CString GetDictInfo(CString str,CString font_name,int font_size,int flag);

	//表示使用哪个字库文件进行识别(index范围:0-9)
	long UseDict(int index);

	//设置全局路径
	long SetPath(CString path);
	

	//购买页面购买  url 购买的页面  type 暂时统一为 0  num 购买数量  additional 购买的附加 以 | 分割 主要是款式 
	short BuyIng(LPCTSTR url, short type, short num, LPCTSTR additional);

	//设置购买时所用的地址
	short SetBuyIngAddr(LPCTSTR person,  LPCTSTR addr);

	//push 信息给其他应用
	short  PushOuterMsg(short MsgType,LPCTSTR MsgStr);
private:
	static CScriptElement* s_pIntance;	

};


#endif