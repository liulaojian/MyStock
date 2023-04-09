// DlgXLH.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include <stdlib.h>
#include <stdio.h>

#include "MyStock.h"
#include "DlgXLH.h"
#include "afxdialogex.h"
#include "SystemMgr.h"

// CDlgXLH �Ի���

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


// CDlgXLH ��Ϣ�������


BOOL CDlgXLH::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	CString strMachCode;
	strMachCode.Format("%lu",SystemMgr()->GetVolumeSerialNumber());
	mEditMachCode.SetWindowText(strMachCode);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

//��֤
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
