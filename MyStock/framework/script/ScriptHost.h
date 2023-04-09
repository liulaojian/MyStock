#if !defined(AFX_SCRIPTHOST_H__E0E5EE8A_8855_4BDB_9C00_FF3E60B6A1CB__INCLUDED_)
#define AFX_SCRIPTHOST_H__E0E5EE8A_8855_4BDB_9C00_FF3E60B6A1CB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ScriptHost.h : header file
//


#include "ScriptElement.h"
/////////////////////////////////////////////////////////////////////////////
// CScriptHost command target

class CScriptHost : public CCmdTarget
{
	DECLARE_DYNCREATE(CScriptHost)

	CScriptHost();           // protected constructor used by dynamic creation

// Attributes
public:
	CScriptElement *p_ScriptElement;
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CScriptHost)
	public:
	virtual void OnFinalRelease();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CScriptHost();

	// Generated message map functions
	//{{AFX_MSG(CScriptHost)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
	DECLARE_OLECREATE(CScriptHost)

	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CScriptHost)
	afx_msg long Test(LPCTSTR strT1, long t);
	afx_msg short Test2(LPCTSTR strA);
	afx_msg short LoginTaobao(LPCTSTR Account, LPCTSTR Password);
	afx_msg short GotoUrl(LPCTSTR Url);
	afx_msg short GotoClick(short x, short y);
	afx_msg short WhellUp();
	afx_msg short WhellDown();
	afx_msg short InputString(LPCTSTR Input);
	afx_msg short InputHZString(LPCTSTR Input);
	afx_msg short FindPic(short x0, short y0, short x1, short y1, LPCTSTR PicFileName, LPCTSTR delta_color, double sim, short FAR* x, short FAR* y);
	afx_msg short FindColor(short x0, short y0, short x1, short y1, LPCTSTR Color, double sim, short FAR* x, short FAR* y);
	afx_msg long GetScreenData(short x0, short y0, short x1, short y1);
	afx_msg long SetDict(short index, LPCTSTR file);
	afx_msg long FindStr(short x0, short y0, short x1, short y1, LPCTSTR strString, LPCTSTR color_format, double sim, short FAR* x, short FAR* y);
	afx_msg long FindStrWithFont(short x0, short y0, short x1, short y1, LPCTSTR strString, LPCTSTR color_format, double sim, LPCTSTR font_name, short font_size, short flag, short FAR* x, short FAR* y);
	afx_msg BSTR Ocr(short x0, short y0, short x1, short y1, LPCTSTR color_format, double sim);
	afx_msg BSTR OcrEx(short x0, short y0, short x1, short y1, LPCTSTR color_format, double sim);
	afx_msg long AddDict(short index, LPCTSTR dict_info);
	afx_msg long ClearDict(short index);
	afx_msg BSTR FetchWord(short x0, short y0, short x1, short y1, LPCTSTR color, LPCTSTR word);
	afx_msg BSTR GetDictInfo(LPCTSTR str, LPCTSTR font_name, short font_size, short flag);
	afx_msg long UseDict(short index);
	afx_msg long SetPath(LPCTSTR path);

	afx_msg short BuyIng(LPCTSTR url, short type, short num, LPCTSTR additional);	//进入购买页面
	
	afx_msg short SetBuyIngAddr(LPCTSTR person,  LPCTSTR addr);		//设置购买的账号密码 


	afx_msg short PushOuterMsg(short MsgType,LPCTSTR MsgStr);		//push 信息 给不同应用

	//afx_msg short BuyIngHandleAddtion(LPCTSTR additional);			//处理购买页面那些颜色尺寸等额外信息


	//afx_msg short GetBuyingUrlType();								//获取当前购买类型 0 表示淘宝  1 表示天猫 -1 表示错误



	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SCRIPTHOST_H__E0E5EE8A_8855_4BDB_9C00_FF3E60B6A1CB__INCLUDED_)
