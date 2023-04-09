#pragma once

#include "StockDayTable.h"
#include <vector>
#include <thread>
#include <map>
#include <string>
#include "T_Queue.h"
#include "TanAngleAlg.h"
typedef struct
{
	CString  strInfo;
}BackFlowInfo;

typedef struct
{
	CString  strStockCode;
	double     fHoldNums;
	double   fStockPrice;
}HoldStockInfo;

typedef std::vector<HoldStockInfo*>  VecHoldStockInfo;


typedef std::vector<CString>  VecStockTempInfo;

enum
{
	EVENT_BACKFLOW_INFO = 0x1020,
};

enum
{
	FIRST_FILTTER_TAN4 = 0,
	FIRST_FILTTER_TAN6,
	FIRST_FILTTER_TAN9,
	FIRST_FILTTER_TAN3,
	FIRST_FILTTER_USERVALUE,
};

enum
{
	SECOND_FILTTER_NONE = 0,
	SECOND_FILTTER_HIGH_ONE,
	SECOND_FILTTER_AVE_LINE_BW_MIDDLE,
};

#define BUY_SALE_DAY  3

class CDlgBackFlow : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgBackFlow)

public:
	CDlgBackFlow(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CDlgBackFlow();

	bool doBackFlow(void);
private:
	CStockDayTable* pExpStockDayTable;
	CString strBeginDate;
	CString strEndDate;
	int mBeginPos = 0;
	int mEndPos = 0;

	double fTotalMoney = 100000.0;
	CString strTotalInfo = "";
	std::map<std::string, int > industyMapAllNum;

	std::thread t_backflow;
	CQueue<BackFlowInfo*> quQueueBackFlowInfo;
	CRITICAL_SECTION backFlowInfoLock;

	inline void TryLockBackFlowInfo()
	{
		::TryEnterCriticalSection(&backFlowInfoLock);
	}
	inline void LockBackFlowInfo()
	{
		::EnterCriticalSection(&backFlowInfoLock);
	}
	inline void UnlockBackFlowInfo()
	{
		::LeaveCriticalSection(&backFlowInfoLock);
	}


	void AddBackFlowInfo(CString strInfo);
	void PushBackFlowInfo(BackFlowInfo* Info);

	BackFlowInfo* PopBackFlowInfo(void);

	bool doHandleBackFlowInfo(void);


	bool doOneBackFlow(void);

	CString CalcNowDate(void);

	int mBackFlowNums = 0;

	int mFirstSelMode = 0;
	int mSecondSelMode = 0;
	int mNowPassPos = 0;
	double f_Tan_Per = 0.0;
	std::vector<double> vecTanPer;

	VecStockTempInfo DoFilterTanMatch4(Vec_TanAngleData& vecTanAngleData);

	VecStockTempInfo DoFilterTanMatch6(Vec_TanAngleData& vecTanAngleData);

	VecStockTempInfo DoFilterKLineBadFilter(VecStockTempInfo& vecStockTempInfo, CTime mNowDate);

	VecStockTempInfo DoFilterKLineNineTurn(VecStockTempInfo& vecStockTempInfo, CTime mNowDate);

	VecStockTempInfo DoFilterTanMatch9(Vec_TanAngleData& vecTanAngleData);

	VecStockTempInfo DoFilterKLinePregnant(Vec_TanAngleData& vecTanAngleData);

	VecStockTempInfo DoFilterUserValue(Vec_TanAngleData& vecTanAngleData);

	bool BuyStock(VecStockTempInfo& vecResult, CString strDate);

	double  SaleStock(CString strDate);

	bool IsTanPerContiLow(void);
	bool IsTanPerContiHigh(void);
	VecHoldStockInfo  vecHoldStockInfo;
	// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_BACKFLOW };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CDateTimeCtrl mBeginDateCtrl;
	CDateTimeCtrl mEndDateCtrl;
	CListBox mListBackFlow;
	afx_msg void OnBnClickedBtnBackflow();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	CComboBox mCmbFirst;
	CComboBox mCmbSecond;
	afx_msg void OnBnClickedBtnSave();
};
