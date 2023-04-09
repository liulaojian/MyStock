// DlgXLH.cpp : 实现文件
//

#include "stdafx.h"
#include <stdlib.h>
#include <stdio.h>

#include "MyStock.h"
#include "DlgXLH.h"
#include "afxdialogex.h"
#include "SystemMgr.h"

// CDlgXLH 对话框

IMPLEMENT_DYNAMIC(CDlgXLH, CDialogEx)

CDlgXLH::CDlgXLH(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgXLH::IDD, pParent)
{

}

CDlgXLH::~CDlgXLH()
{
}

void CDlgXLH::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_MACH_CODE, mEditMachCode);
	DDX_Control(pDX, IDC_EDIT_XULIEHAO, mEditXuliehao);
}


BEGIN_MESSAGE_MAP(CDlgXLH, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_MATCH, &CDlgXLH::OnBnClickedBtnMatch)
END_MESSAGE_MAP()


// CDlgXLH 消息处理程序


BOOL CDlgXLH::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	CString strMachCode;
	strMachCode.Format("%lu",SystemMgr()->GetVolumeSerialNumber());
	mEditMachCode.SetWindowText(strMachCode);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

//验证
void CDlgXLH::OnBnClickedBtnMatch()
{
	CString strXLHCode;
	mEditXuliehao.GetWindowText(strXLHCode);
	strXLHCode.Trim();
	const char *p=(LPCSTR)strXLHCode;
	DWORD mXLHCode=(DWORD)atof(p);

	DWORD mVolumeSerialNumber=SystemMgr()->GetVolumeSerialNumber();

	mVolumeSerialNumber^=0x12345678;

	if(mXLHCode==mVolumeSerialNumber)
	{
		SystemMgr()->SetXuLieHao(mXLHCode);
		EndDialog(IDOK); 
		return;
	}

	EndDialog(IDCANCEL); 
	
}
