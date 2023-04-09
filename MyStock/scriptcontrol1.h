#pragma once

// 计算机生成了由 Microsoft Visual C++ 创建的 IDispatch 包装类

// 注意: 不要修改此文件的内容。如果此类由
//  Microsoft Visual C++ 重新生成，您的修改将被覆盖。

/////////////////////////////////////////////////////////////////////////////
// CScriptcontrol1 包装类

class CScriptcontrol1 : public CWnd
{
protected:
	DECLARE_DYNCREATE(CScriptcontrol1)
public:
	CLSID const& GetClsid()
	{
		static CLSID const clsid
			= { 0xE59F1D5, 0x1FBE, 0x11D0, { 0x8F, 0xF2, 0x0, 0xA0, 0xD1, 0x0, 0x38, 0xBC } };
		return clsid;
	}
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle,
						const RECT& rect, CWnd* pParentWnd, UINT nID, 
						CCreateContext* pContext = NULL)
	{ 
		return CreateControl(GetClsid(), lpszWindowName, dwStyle, rect, pParentWnd, nID); 
	}

    BOOL Create(LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, 
				UINT nID, CFile* pPersist = NULL, BOOL bStorage = FALSE,
				BSTR bstrLicKey = NULL)
	{ 
		return CreateControl(GetClsid(), lpszWindowName, dwStyle, rect, pParentWnd, nID,
		pPersist, bStorage, bstrLicKey); 
	}

// 特性
public:
enum
{
    Initialized = 0,
    Connected = 1
}ScriptControlStates;


// 操作
public:

// IScriptControl

// Functions
//

	CString get_Language()
	{
		CString result;
		InvokeHelper(0x5dc, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	void put_Language(LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x5dc, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_State()
	{
		long result;
		InvokeHelper(0x5dd, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_State(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x5dd, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	void put_SitehWnd(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x5de, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_SitehWnd()
	{
		long result;
		InvokeHelper(0x5de, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	long get_Timeout()
	{
		long result;
		InvokeHelper(0x5df, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_Timeout(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x5df, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	BOOL get_AllowUI()
	{
		BOOL result;
		InvokeHelper(0x5e0, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void put_AllowUI(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL ;
		InvokeHelper(0x5e0, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	BOOL get_UseSafeSubset()
	{
		BOOL result;
		InvokeHelper(0x5e1, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void put_UseSafeSubset(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL ;
		InvokeHelper(0x5e1, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	LPDISPATCH get_Modules()
	{
		LPDISPATCH result;
		InvokeHelper(0x5e2, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_Error()
	{
		LPDISPATCH result;
		InvokeHelper(0x5e3, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_CodeObject()
	{
		LPDISPATCH result;
		InvokeHelper(0x3e8, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_Procedures()
	{
		LPDISPATCH result;
		InvokeHelper(0x3e9, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	void _AboutBox()
	{
		InvokeHelper(DISPID_ABOUTBOX, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void AddObject(LPCTSTR Name, LPDISPATCH Object, BOOL AddMembers)
	{
		static BYTE parms[] = VTS_BSTR VTS_DISPATCH VTS_BOOL ;
		InvokeHelper(0x9c4, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Name, Object, AddMembers);
	}
	void Reset()
	{
		InvokeHelper(0x9c5, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void AddCode(LPCTSTR Code)
	{
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x7d0, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Code);
	}
	VARIANT Eval(LPCTSTR Expression)
	{
		VARIANT result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x7d1, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms, Expression);
		return result;
	}
	void ExecuteStatement(LPCTSTR Statement)
	{
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x7d2, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Statement);
	}
	VARIANT Run(LPCTSTR ProcedureName, SAFEARRAY * * Parameters)
	{
		VARIANT result;
		static BYTE parms[] = VTS_BSTR VTS_UNKNOWN ;
		InvokeHelper(0x7d3, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms, ProcedureName, Parameters);
		return result;
	}

// Properties
//



};
