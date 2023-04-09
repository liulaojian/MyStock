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
	void DrowOutLineUI(CDC* pDC);		//�����
	void DrawScaleUI(CDC* pDC);			//�̶�
	void DrawStockLine(CDC* pDC);		//����Ʊ��

	void DrawStockKLine(CDC* pDC);		//����ƱK��
	void DrawStockM5Line(CDC* pDC);		//����Ʊ5��K��
	void DrawStockM10Line(CDC* pDC);		//����Ʊ10��K��
	void DrawStockM20Line(CDC* pDC);		//����Ʊ20��K��
	void DrawStockM60Line(CDC* pDC);		//����Ʊ60��K��

	//��������ƱK��
	void DrawStockSingleKLine(CDC* pDC, CStockDayData* pStockDayData,int x,int y,int w,int h);		

	void DrawTips(CDC* pDC);			//����ʾ

	void DrawVolumeOutLineUI(CDC* pDC);		//���׶������
	void DrawVolumeLine(CDC* pDC);			//�����׶���

	//��ѡ�й�Ʊ����Ϣ
	void DrawSelStockInfo(CDC* pDC);		

	void DrawEnviron(CDC* pDC);			//����������Ϣ ׼�����)
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

	double		m_interMinH;	//��ʱ�߼���߶�
	double		m_interMinW;	//��ʱ�߼�����

	double      m_volumeInterH;		//����������߶�
	double      m_volumeInterW;		//������������

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

