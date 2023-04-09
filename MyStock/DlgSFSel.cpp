// DlgSFSel.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MyStock.h"
#include "DlgSFSel.h"
#include "afxdialogex.h"


// CDlgSFSel �Ի���

IMPLEMENT_DYNAMIC(CDlgSFSel, CDialogEx)

CDlgSFSel::CDlgSFSel(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgSFSel::IDD, pParent)
{

}

CDlgSFSel::~CDlgSFSel()
{
}

void CDlgSFSel::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_SF_SEL, mCmbSFSel);
}


BEGIN_MESSAGE_MAP(CDlgSFSel, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDlgSFSel::OnBnClickedOk)
END_MESSAGE_MAP()


// CDlgSFSel ��Ϣ�������


BOOL CDlgSFSel::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	mSFSel=0;
	mCmbSFSel.ResetContent();
	int ret;
	

	ret=mCmbSFSel.AddString("K�߷���-1");
	mCmbSFSel.SetItemData(ret,0);
	
	//ret=mCmbSFSel.AddString("����������");
	//mCmbSFSel.SetItemData(ret,1);

	ret=mCmbSFSel.AddString("����TAN�Ƕ�");
	mCmbSFSel.SetItemData(ret,2);


	ret=mCmbSFSel.AddString("TAN����(��չ����)");
	mCmbSFSel.SetItemData(ret,3);
	

	//ret=mCmbSFSel.AddString("���վ���TAN");
	//mCmbSFSel.SetItemData(ret,4);

	//ret=mCmbSFSel.AddString("TAN����2(�������)");
	//mCmbSFSel.SetItemData(ret,5);

	//ret=mCmbSFSel.AddString("RSI����");
	//mCmbSFSel.SetItemData(ret,6);


	//ret=mCmbSFSel.AddString("���վ���TAN");
	//mCmbSFSel.SetItemData(ret,7);


	//ret=mCmbSFSel.AddString("����������");
	//mCmbSFSel.SetItemData(ret,8);


	ret=mCmbSFSel.AddString("TAN����3(����M20�м�)");
	mCmbSFSel.SetItemData(ret,9);

	ret=mCmbSFSel.AddString("TAN����4(��������)");
	mCmbSFSel.SetItemData(ret,10);

	ret=mCmbSFSel.AddString("TAN����5(<10)"); //TAN����5  //(�ǶȾ���)
	mCmbSFSel.SetItemData(ret,11);

	ret=mCmbSFSel.AddString("TAN����6(ѡ����5)");
	mCmbSFSel.SetItemData(ret,12);

	//ret=mCmbSFSel.AddString("K�߷���-����");
	//mCmbSFSel.SetItemData(ret,13);

	ret=mCmbSFSel.AddString("TAN����7(������ͬ)");
	mCmbSFSel.SetItemData(ret,13);

	//ret=mCmbSFSel.AddString("TAN����8");
	//mCmbSFSel.SetItemData(ret,14);

	ret = mCmbSFSel.AddString("TAN����9(�����)");
	mCmbSFSel.SetItemData(ret, 15);

	ret = mCmbSFSel.AddString("TAN����10(��ҵѡ��)");
	mCmbSFSel.SetItemData(ret, 16);

#if 0
	ret=mCmbSFSel.AddString("ThreeLow");
	mCmbSFSel.SetItemData(ret,15);

	ret=mCmbSFSel.AddString("һ����");
	mCmbSFSel.SetItemData(ret,16);
#endif	


	mCmbSFSel.SetCurSel(1);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CDlgSFSel::OnBnClickedOk()
{
	
	int	iItem = mCmbSFSel.GetCurSel();
	if(iItem<0) return ;
	
	mSFSel=mCmbSFSel.GetItemData(iItem);
	
	CDialogEx::OnOK();
}
