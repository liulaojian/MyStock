// DlgKLineModeSel.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MyStock.h"
#include "DlgKLineModeSel.h"
#include "afxdialogex.h"


// CDlgKLineModeSel �Ի���

IMPLEMENT_DYNAMIC(CDlgKLineModeSel, CDialogEx)

CDlgKLineModeSel::CDlgKLineModeSel(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgKLineModeSel::IDD, pParent)
{

}

CDlgKLineModeSel::~CDlgKLineModeSel()
{
}

void CDlgKLineModeSel::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_MODE, mCmbKLineMode);
}


BEGIN_MESSAGE_MAP(CDlgKLineModeSel, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDlgKLineModeSel::OnBnClickedOk)
END_MESSAGE_MAP()


// CDlgKLineModeSel ��Ϣ�������


BOOL CDlgKLineModeSel::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	mKLineMode=0;
	mCmbKLineMode.ResetContent();
	int ret=mCmbKLineMode.AddString("��ͷǿͻģʽ");
	mCmbKLineMode.SetItemData(ret,0);
	ret=mCmbKLineMode.AddString("���۾���ģʽ");
	mCmbKLineMode.SetItemData(ret,1);
	ret=mCmbKLineMode.AddString("������");
	mCmbKLineMode.SetItemData(ret,2);
	ret=mCmbKLineMode.AddString("������");
	mCmbKLineMode.SetItemData(ret,3);

	ret=mCmbKLineMode.AddString("������");
	mCmbKLineMode.SetItemData(ret,4);

	mCmbKLineMode.SetCurSel(0);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CDlgKLineModeSel::OnBnClickedOk()
{
	int	iItem = mCmbKLineMode.GetCurSel();
	if(iItem<0) return ;

	mKLineMode=mCmbKLineMode.GetItemData(iItem);
	CDialogEx::OnOK();
}
