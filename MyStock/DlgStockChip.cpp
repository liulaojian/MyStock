// DlgStockChip.cpp : 实现文件
//

#include "stdafx.h"
#include "MyStock.h"
#include "DlgStockChip.h"
#include "afxdialogex.h"


// CDlgStockChip 对话框

IMPLEMENT_DYNAMIC(CDlgStockChip, CDialogEx)

CDlgStockChip::CDlgStockChip(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgStockChip::IDD, pParent)
{

}

CDlgStockChip::~CDlgStockChip()
{
}

void CDlgStockChip::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_CHIP_LOW, mEditChipLow);
	DDX_Control(pDX, IDC_SPIN_CHIP_LOW, mSpinChipLow);
	DDX_Control(pDX, IDC_EDIT_CHIP_HIGH, mEditChipHigh);
	DDX_Control(pDX, IDC_SPIN_CHIP_HIGH, mSpinChipHigh);
	DDX_Control(pDX, IDC_EDIT_CHIP_CONTI, mEditChipConti);
	DDX_Control(pDX, IDC_SPIN_CHIP_CONTI, mSpinConti);
}


BEGIN_MESSAGE_MAP(CDlgStockChip, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDlgStockChip::OnBnClickedOk)
END_MESSAGE_MAP()


// CDlgStockChip 消息处理程序


BOOL CDlgStockChip::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_StockChipLow=0; //70
	mSpinChipLow.SetBuddy(&mEditChipLow);
	mSpinChipLow.SetRange(0, 90);
	mSpinChipLow.SetPos(m_StockChipLow);

	m_StockChipHigh=100;
	mSpinChipHigh.SetBuddy(&mEditChipHigh);
	mSpinChipHigh.SetRange(5, 100);
	mSpinChipHigh.SetPos(m_StockChipHigh);

	m_StockChipConti=1;	//14;
	mSpinConti.SetBuddy(&mEditChipConti);
	mSpinConti.SetRange(1, 20);
	mSpinConti.SetPos(m_StockChipConti);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CDlgStockChip::OnBnClickedOk()
{
	CString strVal;
	mEditChipLow.GetWindowText(strVal);
	int temp=atoi(strVal);
	m_StockChipLow=temp;

	mEditChipHigh.GetWindowText(strVal);
	temp=atoi(strVal);
	m_StockChipHigh=temp;

	mEditChipConti.GetWindowText(strVal);
	temp=atoi(strVal);
	m_StockChipConti=temp;

	if(m_StockChipLow>=m_StockChipHigh)
	{
		AfxMessageBox("低值不能等于大于高值");
		return;
	}

	CDialogEx::OnOK();
}
