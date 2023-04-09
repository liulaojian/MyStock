#pragma once
#include "afxcmn.h"

#include "StockDataMgr.h"
#include "afxwin.h"
#include "afxdtctl.h"

#include "StockProfitLossArithmetic.h"
#include "afxmenubutton.h"
#include "TanAngleAlg.h"
// CDlgCalcu �Ի���


enum
{
	CALCUDATA_COLUMN_ID=0,				//ID
	CALCUDATA_COLUMN_STOCK_DATETIME,			
	CALCUDATA_COLUMN_INFO,
	CALCUDATA_COLUMN_EXP_STATUS,
	CALCUDATA_COLUMN_RESULT,
};

enum
{
	CALCUDATAEVENT_REFRESH_DATA=0x3000,
};

enum
{
	CALCUDATA_EXP_STATUS_NULL=0,			//ָ��״̬  ��
	CALCUDATA_EXP_STATUS_LOW=1,				//ָ��״̬ ��λ <20
	CALCUDATA_EXP_STATUS_SUB_LOW=2,			//ָ��״̬ ƫ��20-30

	CALCUDATA_EXP_STATUS_HIGH=3,			//ָ��״̬ ��λ 80-90
	CALCUDATA_EXP_STATUS_SUB_HIGH=4,		//ָ��״̬ ƫ��λ 70-80
	CALCUDATA_EXP_STATUS_SUPER_HIGH=5,		//ָ��״̬ ����λ 90-100

	CALCUDATA_EXP_STATUS_MIDDLE=6,			//ָ��״̬ ��λ	30-70  

};

enum
{
	CALCUDATA_EXP_DYNAMIC_STATUS_NULL=0,			//��
	CALCUDATA_EXP_DYNAMIC_STATUS_LOW_TO_HIGH=1,		//��λ����λ
	CALCUDATA_EXP_DYNAMIC_STATUS_LOW_SHOCK=2,		//��λ��
	CALCUDATA_EXP_DYNAMIC_STATUS_HIGH_TO_LOW=3,		//��λ����λ
	CALCUDATA_EXP_DYNAMIC_STATUS_HIGH_SHOCK=4,		//��λ��
	CALCUDATA_EXP_DYNAMIC_STATUS_SUPER_HIGH_SHOCK=5, //����λ��
	CALCUDATA_EXP_DYNAMIC_STATUS_MIDDLE_SHOCK=6,	//��λ��
};

typedef struct
{
	int mIndex;
	double fRsi1;
} RsiData;
typedef std::vector<RsiData *> Vec_RsiData;

class CDlgCalcu : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgCalcu)

public:
	CDlgCalcu(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgCalcu();

// �Ի�������
	enum { IDD = IDD_DLG_CALCU };

public:
	void  CopyCalcuData(Vec_CalcuData vecData);
	BOOL RefreshData(void);
private:
	Vec_CalcuData  vecCalcuData;
	int CalcExpStatus(CalcuData *pCalcuData);		//����ָ��״̬

	BOOL doCalcu(void);		//��������

	CString doCalcuMethod(CalcuData *pCalcuData,int mMethod);	//���㷽��1

	BOOL  doCalcuDataMethod(TanAngleData *pTanAngleData);
	BOOL  doCalcuDataMethod_1(TanAngleData *pTanAngleData);
	BOOL  doCalcuDataMethod_2(TanAngleData *pTanAngleData);
	BOOL  doCalcuDataMethod_3(TanAngleData *pTanAngleData);
private:
	CMenu* pCalcuMenu;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CListCtrl mCaluDataListCtrl;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedBtnDoCalcu();
	afx_msg void OnBnClickedBtnExportData();
	afx_msg void OnMenuCalcuDataInfo();
	afx_msg void OnRclickListCalcuData(NMHDR *pNMHDR, LRESULT *pResult);
	CMFCMenuButton mMenuBtnCalcu;
	afx_msg void OnBnClickedMenubtnCalcu();
};
