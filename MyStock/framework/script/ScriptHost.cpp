// ScriptHost.cpp : implementation file
//

#include "stdafx.h"

#include "ScriptHost.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CScriptHost

IMPLEMENT_DYNCREATE(CScriptHost, CCmdTarget)

CScriptHost::CScriptHost()
{
	EnableAutomation();
	
	// To keep the application running as long as an OLE automation 
	//	object is active, the constructor calls AfxOleLockApp.
	
	AfxOleLockApp();
}

CScriptHost::~CScriptHost()
{
	// To terminate the application when all objects created with
	// 	with OLE automation, the destructor calls AfxOleUnlockApp.
	
	AfxOleUnlockApp();
}


void CScriptHost::OnFinalRelease()
{
	// When the last reference for an automation object is released
	// OnFinalRelease is called.  The base class will automatically
	// deletes the object.  Add additional cleanup required for your
	// object before calling the base class.

	CCmdTarget::OnFinalRelease();
}


BEGIN_MESSAGE_MAP(CScriptHost, CCmdTarget)
	//{{AFX_MSG_MAP(CScriptHost)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CScriptHost, CCmdTarget)
	//{{AFX_DISPATCH_MAP(CScriptHost)
	DISP_FUNCTION(CScriptHost, "Test", Test, VT_I4, VTS_BSTR VTS_I4)
	DISP_FUNCTION(CScriptHost, "Test2", Test2, VT_I2, VTS_BSTR)
	DISP_FUNCTION(CScriptHost, "LoginTaobao", LoginTaobao, VT_I2, VTS_BSTR VTS_BSTR)
	DISP_FUNCTION(CScriptHost, "GotoUrl", GotoUrl, VT_I2, VTS_BSTR)
	DISP_FUNCTION(CScriptHost, "GotoClick", GotoClick, VT_I2, VTS_I2 VTS_I2)
	DISP_FUNCTION(CScriptHost, "WhellUp", WhellUp, VT_I2, VTS_NONE)
	DISP_FUNCTION(CScriptHost, "WhellDown", WhellDown, VT_I2, VTS_NONE)
	DISP_FUNCTION(CScriptHost, "InputString", InputString, VT_I2, VTS_BSTR)
	DISP_FUNCTION(CScriptHost, "InputHZString", InputHZString, VT_I2, VTS_BSTR)
	DISP_FUNCTION(CScriptHost, "FindPic", FindPic, VT_I2, VTS_I2 VTS_I2 VTS_I2 VTS_I2 VTS_BSTR VTS_BSTR VTS_R8 VTS_PI2 VTS_PI2)
	DISP_FUNCTION(CScriptHost, "FindColor", FindColor, VT_I2, VTS_I2 VTS_I2 VTS_I2 VTS_I2 VTS_BSTR VTS_R8 VTS_PI2 VTS_PI2)
	DISP_FUNCTION(CScriptHost, "GetScreenData", GetScreenData, VT_I4, VTS_I2 VTS_I2 VTS_I2 VTS_I2)
	DISP_FUNCTION(CScriptHost, "SetDict", SetDict, VT_I4, VTS_I2 VTS_BSTR)
	DISP_FUNCTION(CScriptHost, "FindStr", FindStr, VT_I4, VTS_I2 VTS_I2 VTS_I2 VTS_I2 VTS_BSTR VTS_BSTR VTS_R8 VTS_PI2 VTS_PI2)
	DISP_FUNCTION(CScriptHost, "FindStrWithFont", FindStrWithFont, VT_I4, VTS_I2 VTS_I2 VTS_I2 VTS_I2 VTS_BSTR VTS_BSTR VTS_R8 VTS_BSTR VTS_I2 VTS_I2 VTS_PI2 VTS_PI2)
	DISP_FUNCTION(CScriptHost, "Ocr", Ocr, VT_BSTR, VTS_I2 VTS_I2 VTS_I2 VTS_I2 VTS_BSTR VTS_R8)
	DISP_FUNCTION(CScriptHost, "OcrEx", OcrEx, VT_BSTR, VTS_I2 VTS_I2 VTS_I2 VTS_I2 VTS_BSTR VTS_R8)
	DISP_FUNCTION(CScriptHost, "AddDict", AddDict, VT_I4, VTS_I2 VTS_BSTR)
	DISP_FUNCTION(CScriptHost, "ClearDict", ClearDict, VT_I4, VTS_I2)
	DISP_FUNCTION(CScriptHost, "FetchWord", FetchWord, VT_BSTR, VTS_I2 VTS_I2 VTS_I2 VTS_I2 VTS_BSTR VTS_BSTR)
	DISP_FUNCTION(CScriptHost, "GetDictInfo", GetDictInfo, VT_BSTR, VTS_BSTR VTS_BSTR VTS_I2 VTS_I2)
	DISP_FUNCTION(CScriptHost, "UseDict", UseDict, VT_I4, VTS_I2)
	DISP_FUNCTION(CScriptHost, "SetPath", SetPath, VT_I4, VTS_BSTR)
	DISP_FUNCTION(CScriptHost, "BuyIng", BuyIng, VT_I2, VTS_BSTR VTS_I2 VTS_I2 VTS_BSTR)
	DISP_FUNCTION(CScriptHost, "SetBuyIngAddr", SetBuyIngAddr, VT_I2, VTS_BSTR VTS_BSTR)
	DISP_FUNCTION(CScriptHost, "PushOuterMsg", PushOuterMsg, VT_I2, VTS_I2 VTS_BSTR)


	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// Note: we add support for IID_IScriptHost to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.

// {913716BC-9859-4F33-86DC-C2554D487F8E}
static const IID IID_IScriptHost =
{ 0x913716bc, 0x9859, 0x4f33, { 0x86, 0xdc, 0xc2, 0x55, 0x4d, 0x48, 0x7f, 0x8e } };

BEGIN_INTERFACE_MAP(CScriptHost, CCmdTarget)
	INTERFACE_PART(CScriptHost, IID_IScriptHost, Dispatch)
END_INTERFACE_MAP()

// {8C38CF57-9DD3-4EF7-9144-67185C2279EF}
IMPLEMENT_OLECREATE(CScriptHost, "tbauto.ScriptHost", 0x8c38cf57, 0x9dd3, 0x4ef7, 0x91, 0x44, 0x67, 0x18, 0x5c, 0x22, 0x79, 0xef)

/////////////////////////////////////////////////////////////////////////////
// CScriptHost message handlers

long CScriptHost::Test(LPCTSTR strT1, long t) 
{
	// TODO: Add your dispatch handler code here
	if(t==1)
		AfxGetMainWnd()->MessageBox("show","提示");
	else
		AfxGetMainWnd()->MessageBox(strT1,"提示");
	return 0;
}

short CScriptHost::Test2(LPCTSTR strA) 
{
	// TODO: Add your dispatch handler code here
	AfxGetMainWnd()->MessageBox(strA,strA);
	return 0;
}



short CScriptHost::LoginTaobao(LPCTSTR Account, LPCTSTR Password) 
{
	// TODO: Add your dispatch handler code here
	p_ScriptElement->LoginTaobao(Account,Password);
	return 0;
}

short CScriptHost::GotoUrl(LPCTSTR Url) 
{
	// TODO: Add your dispatch handler code here
	p_ScriptElement->GotoUrl(Url);
	return 0;
}

short CScriptHost::GotoClick(short x, short y) 
{
	// TODO: Add your dispatch handler code here

	return 0;
}

short CScriptHost::WhellUp() 
{
	// TODO: Add your dispatch handler code here

	return 0;
}

short CScriptHost::WhellDown() 
{
	// TODO: Add your dispatch handler code here

	return 0;
}

short CScriptHost::InputString(LPCTSTR Input) 
{
	// TODO: Add your dispatch handler code here

	return 0;
}

short CScriptHost::InputHZString(LPCTSTR Input) 
{
	// TODO: Add your dispatch handler code here

	return 0;
}

short CScriptHost::FindPic(short x0, short y0, short x1, short y1, LPCTSTR PicFileName, LPCTSTR delta_color, double sim, short FAR* x, short FAR* y) 
{
	// TODO: Add your dispatch handler code here

	return 0;
}

short CScriptHost::FindColor(short x0, short y0, short x1, short y1, LPCTSTR Color, double sim, short FAR* x, short FAR* y) 
{
	// TODO: Add your dispatch handler code here

	return 0;
}

long CScriptHost::GetScreenData(short x0, short y0, short x1, short y1) 
{
	// TODO: Add your dispatch handler code here

	return 0;
}

long CScriptHost::SetDict(short index, LPCTSTR file) 
{
	// TODO: Add your dispatch handler code here

	return 0;
}

long CScriptHost::FindStr(short x0, short y0, short x1, short y1, LPCTSTR strString, LPCTSTR color_format, double sim, short FAR* x, short FAR* y) 
{
	// TODO: Add your dispatch handler code here

	return 0;
}

long CScriptHost::FindStrWithFont(short x0, short y0, short x1, short y1, LPCTSTR strString, LPCTSTR color_format, double sim, LPCTSTR font_name, short font_size, short flag, short FAR* x, short FAR* y) 
{
	// TODO: Add your dispatch handler code here

	return 0;
}

BSTR CScriptHost::Ocr(short x0, short y0, short x1, short y1, LPCTSTR color_format, double sim) 
{
	CString strResult;
	// TODO: Add your dispatch handler code here

	return strResult.AllocSysString();
}

BSTR CScriptHost::OcrEx(short x0, short y0, short x1, short y1, LPCTSTR color_format, double sim) 
{
	CString strResult;
	// TODO: Add your dispatch handler code here

	return strResult.AllocSysString();
}

long CScriptHost::AddDict(short index, LPCTSTR dict_info) 
{
	// TODO: Add your dispatch handler code here

	return 0;
}

long CScriptHost::ClearDict(short index) 
{
	// TODO: Add your dispatch handler code here

	return 0;
}

BSTR CScriptHost::FetchWord(short x0, short y0, short x1, short y1, LPCTSTR color, LPCTSTR word) 
{
	CString strResult;
	// TODO: Add your dispatch handler code here

	return strResult.AllocSysString();
}

BSTR CScriptHost::GetDictInfo(LPCTSTR str, LPCTSTR font_name, short font_size, short flag) 
{
	CString strResult;
	// TODO: Add your dispatch handler code here

	return strResult.AllocSysString();
}

long CScriptHost::UseDict(short index) 
{
	// TODO: Add your dispatch handler code here

	return 0;
}

long CScriptHost::SetPath(LPCTSTR path) 
{
	// TODO: Add your dispatch handler code here

	return 0;
}

short CScriptHost::BuyIng(LPCTSTR url, short type, short num, LPCTSTR additional) 
{
	// TODO: Add your dispatch handler code here
	p_ScriptElement->BuyIng(url,type,num,additional);
	return 0;
}

short CScriptHost::SetBuyIngAddr(LPCTSTR person,  LPCTSTR addr)
{
	p_ScriptElement->SetBuyIngAddr(person,addr);
	return 0;
}


short  CScriptHost::PushOuterMsg(short MsgType,LPCTSTR MsgStr)
{
	return p_ScriptElement->PushOuterMsg(MsgType,MsgStr);
}