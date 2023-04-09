#pragma once

#include "resource.h"

#include "StockDayTable.h"
#include "EnvDataMgr.h"
#include "StockKDJArithmetic.h"

#include <vector>

enum
{
	CHART_TIMER_EVENT_REFRESH=0x2100,
	CHART_TIMER_EVENT_SEL,
};

typedef struct
{
	CStockDayData* pStockDayData;
	CStockDayData* pLastStockDayData;
	int x0;
	int y0;
	int x1;
	int y1;
} KLineAreaData;

typedef std::vector<KLineAreaData*> Vec_KLineAreaData;

class CStockChartStatic : public CStatic
{
	DECLARE_DYNAMIC(CStockChartStatic)
public:
	CStockChartStatic();
	virtual ~CStockChartStatic();

public:
	CStockDayTable * GetStockDayTable(void) {return pStockDayTable;}
	void SetStockDayTable(CStockDayTable * pTable) {pStockDayTable=pTable;}
	void SetBeginDate(CString strVal) {strBeginDate=strVal;}
	void SetEndDate(CString strVal) {strEndDate=strVal;}
public:
	void DrowOutLineUI(CDC* pDC);		//外框线
	void DrawScaleUI(CDC* pDC);			//刻度
	void DrawStockLine(CDC* pDC);		//画股票线

	void DrawStockKLine(CDC* pDC);		//画股票K线
	void DrawStockM5Line(CDC* pDC);		//画股票5日K线
	void DrawStockM10Line(CDC* pDC);		//画股票10日K线
	void DrawStockM20Line(CDC* pDC);		//画股票20日K线
	void DrawStockM60Line(CDC* pDC);		//画股票60日K线

	//画单个股票K线
	void DrawStockSingleKLine(CDC* pDC, CStockDayData* pStockDayData,int x,int y,int w,int h);		

	void DrawTips(CDC* pDC);			//画提示

	void DrawVolumeOutLineUI(CDC* pDC);		//交易额外框线
	void DrawVolumeLine(CDC* pDC);			//画交易额线

	//画选中股票的信息
	void DrawSelStockInfo(CDC* pDC);		

	void DrawEnviron(CDC* pDC);			//画环境（加息 准备金等)
public:
	
	BOOL Init(void);
private:
	CDC *pdc;
	CDC dcMem;   
	CFont font;   
	CBitmap bmpBg;  
	CStockKDJData* pStockKDJData = NULL;
	Vec_KLineAreaData vecKLineAreaData;
	KLineAreaData* pNowKLineAreaData = NULL;
private:
	CStockDayTable *pStockDayTable;
	CString  strBeginDate;
	CString  strEndDate;

	CString  strDrawBeginDate;
	CString  strDrawEndDate;

	float   f_draw_min_val;
	float   f_draw_max_val;



	int mBeginPos;
	int mEndPos;

	int mDrawBeginPos;
	int mDrawEndPos;


	int mPreExtendNums;
	int mAftExtendNums;

	float   f_draw_min_volume;
	float   f_draw_max_volume;

	Vec_StockDayData vecDrawStockDayData;

	Vec_EnvInterestDataList vecEnvInterestBwDatesDataList;
	Vec_EnvReserveDataList  vecEnvReserveBwDatesDataList;
	
	BOOL bWaitRefresh;

private:

	double		m_interMinH;	//分时线间隔高度
	double		m_interMinW;	//分时线间隔宽度

	double      m_volumeInterH;		//交易量间隔高度
	double      m_volumeInterW;		//交易量间隔宽带

	double      m_volumeBeginY;

	BOOL        bDrawTips;
	CString     strDrawTips;
	
	void JudgeDrawTips(UINT nFlags, CPoint point);

protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void DrawItem(LPDRAWITEMSTRUCT /*lpDrawItemStruct*/);
	virtual void PreSubclassWindow();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg UINT OnGetDlgCode();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMenuSaveBmp();
};

