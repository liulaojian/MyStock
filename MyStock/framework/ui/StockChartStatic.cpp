#include "stdafx.h"
#include "StockChartStatic.h"
#include "Log.h"
#include "Convert.h"
#include "CommonMacro.h"
#include "ConceptDataMgr.h"
#include "IndustryDataMgr.h"
#include "StockDataMgr.h"
IMPLEMENT_DYNAMIC(CStockChartStatic, CStatic)

CStockChartStatic::CStockChartStatic():pStockDayTable(NULL)
{
	mPreExtendNums=0;
	mAftExtendNums=0;
	bWaitRefresh=FALSE;
}

CStockChartStatic::~CStockChartStatic()
{
	if (!bmpBg.DeleteObject())
	{
		
	}
	dcMem.DeleteDC();
	if (pStockKDJData)
	{
		SAFE_DELETE(pStockKDJData);
		pStockKDJData = NULL;
	}
}


BEGIN_MESSAGE_MAP(CStockChartStatic, CStatic)
	ON_WM_CREATE()
	ON_WM_ERASEBKGND()
	ON_WM_MOUSEMOVE()
	ON_WM_TIMER()
	ON_WM_KEYDOWN()
	ON_WM_GETDLGCODE()
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_COMMAND(ID_MENU_SAVE_BMP, &CStockChartStatic::OnMenuSaveBmp)
END_MESSAGE_MAP()


void CStockChartStatic::DrawItem(LPDRAWITEMSTRUCT /*lpDrawItemStruct*/)
{

	/*CRect rcWnd;  
	GetWindowRect(&rcWnd);  
	ScreenToClient(&rcWnd);  
	dcMem.SelectObject(&bmpBg);  
	dcMem.SelectObject(&font);  
	dcMem.SetBkMode(TRANSPARENT);  
	dcMem.SetTextColor(RGB(255,255,255));  


	COLORREF col ;
	col= RGB(0,0,255);
	CPen pen(PS_SOLID,2,col);
	dcMem.SelectObject(&pen);
	dcMem.SelectStockObject(NULL_BRUSH);//空心的笔
	dcMem.Rectangle(rcWnd);

	pdc->BitBlt(0,0,rcWnd.Width(),rcWnd.Height(),&dcMem,0,0,SRCCOPY);  
	*/

	

	DrowOutLineUI(pdc);
	DrawScaleUI(pdc);
	DrawStockKLine(pdc);
	
	//DrawStockLine(pdc);
	//DrawTips(pdc);
	DrawVolumeOutLineUI(pdc);
	DrawVolumeLine(pdc);

	DrawStockM5Line(pdc);
	DrawStockM10Line(pdc);
	DrawStockM20Line(pdc);
	DrawStockM60Line(pdc);

	DrawSelStockInfo(pdc);

	//DrawEnviron(pdc);
}

#define BEGIN_X  82
#define BEGIN_Y  35

#define ROW_NUMS	18
#define COL_NUMS     4

void CStockChartStatic::DrowOutLineUI(CDC* pDC)
{
	CRect rect;	
	GetClientRect (&rect);
	pDC->SetBkMode(OPAQUE);
	pDC->SetBkColor(RGB(0,0,0));
	pDC->SelectStockObject(BLACK_BRUSH);
	pDC->Rectangle(&rect);

	CPen      redpen(PS_SOLID,2,RGB(153,0,0));
	CPen      whitepen(PS_SOLID, 1, RGB(255, 255, 255));
	CPen      redDotpen(PS_DOT, 1, RGB(153, 0, 0));
	CPen      redThinPen(PS_SOLID, 1, RGB(153, 0, 0));
	


	pDC->SelectObject(&redpen);

	//画左上角公共的边框
	pDC->MoveTo(2, 2);
	pDC->LineTo(rect.right-2, 2);
	pDC->LineTo(rect.right-2, rect.bottom-2);
	pDC->LineTo(2, rect.bottom-2);
	pDC->LineTo(2, 2);

	m_interMinH = (rect.bottom - 270)/ ROW_NUMS;
	m_interMinW = (rect.right - 250)/ COL_NUMS;

	//以下是画那个外面的方框，为保证每份均等，所以要求interH和interW
	pDC->MoveTo(BEGIN_X, BEGIN_Y);
	pDC->LineTo(BEGIN_X +m_interMinW* COL_NUMS, BEGIN_Y);
	pDC->LineTo(BEGIN_X +m_interMinW* COL_NUMS, BEGIN_Y +m_interMinH* ROW_NUMS);
	pDC->LineTo(BEGIN_X, BEGIN_Y +m_interMinH* ROW_NUMS);
	pDC->LineTo(BEGIN_X, BEGIN_Y);
	

	pDC->SelectObject(&redDotpen);
	for(int h = BEGIN_Y +m_interMinH; h < BEGIN_Y +m_interMinH*18; h += m_interMinH)
	{
		pDC->MoveTo(BEGIN_X, h);
		pDC->LineTo(BEGIN_X +m_interMinW* COL_NUMS, h);
	}
	
	

}

#define TX_DATE_BEGIN_X  50
#define TX_DATE_BEGIN_Y  42

#define SCALE_BEGIN_X  23
#define SCALE_BEGIN_Y  23

void CStockChartStatic::DrawScaleUI(CDC* pDC)
{
	CRect rect;	
	GetClientRect (&rect);
	pDC->SetTextColor(RGB(255, 255, 255));	
	pDC->TextOut(TX_DATE_BEGIN_X, TX_DATE_BEGIN_Y +m_interMinH* ROW_NUMS, (LPCSTR)strDrawBeginDate,strDrawBeginDate.GetLength());
	pDC->TextOut(TX_DATE_BEGIN_X +m_interMinW* COL_NUMS, TX_DATE_BEGIN_Y +m_interMinH* ROW_NUMS, strDrawEndDate, strDrawEndDate.GetLength());


	CString strMinVal;
	strMinVal.Format("%.2f",f_draw_min_val);
	strMinVal=AlignStringBySpace(strMinVal,7);
	pDC->TextOut(SCALE_BEGIN_X, SCALE_BEGIN_Y +m_interMinH* ROW_NUMS, (LPCSTR)strMinVal,strMinVal.GetLength());

	CString strVal;
	float f_val;
	for(int i= ROW_NUMS-1;i>0;i--)
	{
		f_val = ((ROW_NUMS - i) * (f_draw_max_val - f_draw_min_val)) / (double)ROW_NUMS + f_draw_min_val;
		strVal.Format("%.2f",f_val);
		strVal=AlignStringBySpace(strVal,7);
		pDC->TextOut(SCALE_BEGIN_X, SCALE_BEGIN_Y +m_interMinH*i, (LPCSTR)strVal,strVal.GetLength());
	}

	CString strMaxVal;
	strMaxVal.Format("%.2f",f_draw_max_val);
	strMaxVal=AlignStringBySpace(strMaxVal,7);
	pDC->TextOut(SCALE_BEGIN_X, SCALE_BEGIN_Y, (LPCSTR)strMaxVal,strMaxVal.GetLength());
	
}

void CStockChartStatic::DrawStockLine(CDC* pDC)
{
	CPen      whitepen(PS_SOLID, 1, RGB(255, 255, 255));
	CPen      greenpen(PS_SOLID, 1, RGB(0, 255, 0));
	pDC->SelectObject(&whitepen);
	int mXNums=mDrawEndPos-mDrawBeginPos;

	float fYRange=f_draw_max_val-f_draw_min_val;

	int x,y;
	CStockDayData *pStockDayData=NULL;
	for(int i=0;i< vecDrawStockDayData.size();i++)
	{
		pStockDayData=vecDrawStockDayData[i];
		if((i+mDrawBeginPos)>=mBeginPos  && (i+mDrawBeginPos)<=mEndPos)
			pDC->SelectObject(&greenpen);
		else
			pDC->SelectObject(&whitepen);
		x=(i*m_interMinW*4)/mXNums;
		
		y=m_interMinH*18-((pStockDayData->GetEndPrice()-f_draw_min_val)*m_interMinH*18)/fYRange;
		if(i==0)
			pDC->MoveTo(82+x,35+y);
		else
			pDC->LineTo(82+x,35+y);
	}
	
}

//画股票K线
void CStockChartStatic::DrawStockKLine(CDC* pDC)
{
	

	int mXNums = mDrawEndPos - mDrawBeginPos+1;

	float fYRange = f_draw_max_val - f_draw_min_val;

	int x, y, w, h;

	int mDrawWidth=m_interMinW* COL_NUMS;
	int mDrawHeight = m_interMinH* ROW_NUMS;

	int mKLineWidth = mDrawWidth / mXNums;

	int mKLineHeight;

	
	CStockDayData* pStockDayData = NULL;
	for (int i = 0; i < vecDrawStockDayData.size(); i++)
	{
		pStockDayData = vecDrawStockDayData[i];
		
		float fStockRang = pStockDayData->GetMaxPrice() - pStockDayData->GetMinPrice();

		mKLineHeight = (fStockRang * mDrawHeight / fYRange) ;
		x = BEGIN_X + (double)i / (double)mXNums * mDrawWidth;
	
		//要镜像
		y = BEGIN_Y + mDrawHeight- mKLineHeight-((pStockDayData->GetMinPrice() - f_draw_min_val) * mDrawHeight / fYRange );

		mKLineWidth = mDrawWidth / mXNums;
		x = x + mKLineWidth / 6;
		mKLineWidth = mKLineWidth * 2 / 3;

		KLineAreaData* pKLineAreaData = new KLineAreaData();
		pKLineAreaData->pStockDayData = pStockDayData;
		if (i == 0)
			pKLineAreaData->pLastStockDayData = NULL;
		else
			pKLineAreaData->pLastStockDayData=vecDrawStockDayData[i-1];
		pKLineAreaData->x0 = x;
		pKLineAreaData->y0 = y;
		pKLineAreaData->x1 = x + mKLineWidth;
		pKLineAreaData->y1 = y + mKLineHeight;
		vecKLineAreaData.push_back(pKLineAreaData);

		DrawStockSingleKLine(pDC, pStockDayData, x, y, mKLineWidth, mKLineHeight);
	}


}


//画单个股票K线
void CStockChartStatic::DrawStockSingleKLine(CDC* pDC, CStockDayData* pStockDayData, int x, int y, int w, int h)
{
	CPen      redpen(PS_SOLID, 1, RGB(255, 0, 0));
	CPen      greenpen(PS_SOLID, 1, RGB(0, 255, 0));
	if (pStockDayData->GetEndPrice() > pStockDayData->GetBeginPrice())
		pDC->SelectObject(&redpen);
	else
		pDC->SelectObject(&greenpen);

	bool bUp = false;

	if (pStockDayData->GetEndPrice() > pStockDayData->GetBeginPrice())
		bUp = true;

	double f_rang = pStockDayData->GetMaxPrice() - pStockDayData->GetMinPrice();

	double f_body_rang = fabs(pStockDayData->GetEndPrice() - pStockDayData->GetBeginPrice());

	double f_up_rang;
	if (bUp)
	{
		f_up_rang = pStockDayData->GetMaxPrice() - pStockDayData->GetEndPrice();
	}
	else
	{
		f_up_rang = pStockDayData->GetMaxPrice() - pStockDayData->GetBeginPrice();
	}
	
	double f_down_rang;
	if (bUp)
	{
		f_down_rang = pStockDayData->GetBeginPrice() - pStockDayData->GetMinPrice();
	}
	else
	{
		f_down_rang= pStockDayData->GetEndPrice()- pStockDayData->GetMinPrice();
	}
	
	int bodyH = f_body_rang * h / f_rang;
	if (bodyH == 0)
		bodyH = 1;
	int bodyY;
	
	bodyY = y + (f_up_rang * h / f_rang) ;
	
	if (bUp)
	{
		RECT rect;
		rect.left = x;
		rect.top = bodyY;
		rect.right = x + w;
		rect.bottom = bodyY + bodyH;
		pDC->FillSolidRect(&rect, RGB(255, 0, 0));
	}
	else
	{
		RECT rect;
		rect.left = x;
		rect.top = bodyY;
		rect.right = x + w;
		rect.bottom = bodyY + bodyH;
		pDC->FillSolidRect(&rect, RGB(0, 255, 0));
	}


	int upH = f_up_rang * h / f_rang;
	
	
	int x0 = x + (w / 2);
	int y0 = y;
	int x1 = x0;
	int y1 = y0 + (f_up_rang * h / f_rang);
	pDC->MoveTo(x0, y0);
	pDC->LineTo(x1, y1);
	
	
	int downH = f_down_rang * h / f_rang;

	x0= x + (w / 2);
	y0 = y+ (f_up_rang * h / f_rang)+ (f_body_rang * h / f_rang);
	x1 = x0;
	y1 = y + h;
	pDC->MoveTo(x0, y0);
	pDC->LineTo(x1, y1);

}

//画股票5日K线
void CStockChartStatic::DrawStockM5Line(CDC* pDC)
{
	std::vector<double> vec_price_ma5;
	vec_price_ma5 = CStockKDJArithmetic::CalcMA(5, pStockKDJData->vec_close_price);
	int mXNums = mDrawEndPos - mDrawBeginPos + 1;

	float fYRange = f_draw_max_val - f_draw_min_val;

	int size = vec_price_ma5.size();

	CPen      whitepen(PS_SOLID, 1, RGB(255, 255, 255));
	pDC->SelectObject(&whitepen);

	int mDrawWidth = m_interMinW * COL_NUMS;
	int mDrawHeight = m_interMinH * ROW_NUMS;

	int mKLineWidth = mDrawWidth / mXNums;

	for (int i = size - mXNums; i <= size - 1; i++)
	{
		int n = (i - (size - mXNums));
		int x = (n * m_interMinW * COL_NUMS) / mXNums+ mKLineWidth/2;

		int y = m_interMinH * ROW_NUMS - ((vec_price_ma5[i] - f_draw_min_val) * m_interMinH * ROW_NUMS) / fYRange;
		if (n == 0)
			pDC->MoveTo(BEGIN_X + x, BEGIN_Y + y);
		else
			pDC->LineTo(BEGIN_X + x, BEGIN_Y + y);
	}

}

//画股票10日K线
void CStockChartStatic::DrawStockM10Line(CDC* pDC)
{
	std::vector<double> vec_price_ma10;
	vec_price_ma10 = CStockKDJArithmetic::CalcMA(10, pStockKDJData->vec_close_price);
	int mXNums = mDrawEndPos - mDrawBeginPos + 1;

	float fYRange = f_draw_max_val - f_draw_min_val;

	int size = vec_price_ma10.size();

	CPen      pen(PS_SOLID, 1, RGB(255, 255, 0));
	pDC->SelectObject(&pen);

	int mDrawWidth = m_interMinW * COL_NUMS;
	int mDrawHeight = m_interMinH * ROW_NUMS;

	int mKLineWidth = mDrawWidth / mXNums;

	for (int i = size - mXNums; i <= size - 1; i++)
	{
		int n = (i - (size - mXNums));
		int x = (n * m_interMinW * COL_NUMS) / mXNums + mKLineWidth / 2;

		int y = m_interMinH * ROW_NUMS - ((vec_price_ma10[i] - f_draw_min_val) * m_interMinH * ROW_NUMS) / fYRange;
		if (n == 0)
			pDC->MoveTo(BEGIN_X + x, BEGIN_Y + y);
		else
			pDC->LineTo(BEGIN_X + x, BEGIN_Y + y);
	}
}
//画股票20日K线
void CStockChartStatic::DrawStockM20Line(CDC* pDC)
{
	std::vector<double> vec_price_ma20;
	vec_price_ma20 = CStockKDJArithmetic::CalcMA(20, pStockKDJData->vec_close_price);
	int mXNums = mDrawEndPos - mDrawBeginPos + 1;

	float fYRange = f_draw_max_val - f_draw_min_val;

	int size = vec_price_ma20.size();

	CPen      pen(PS_SOLID, 1, RGB(255, 0, 255));
	pDC->SelectObject(&pen);

	int mDrawWidth = m_interMinW * COL_NUMS;
	int mDrawHeight = m_interMinH * ROW_NUMS;

	int mKLineWidth = mDrawWidth / mXNums;

	for (int i = size - mXNums; i <= size - 1; i++)
	{
		int n = (i - (size - mXNums));
		int x = (n * m_interMinW * COL_NUMS) / mXNums + mKLineWidth / 2;

		int y = m_interMinH * ROW_NUMS - ((vec_price_ma20[i] - f_draw_min_val) * m_interMinH * ROW_NUMS) / fYRange;
		if (n == 0)
			pDC->MoveTo(BEGIN_X + x, BEGIN_Y + y);
		else
			pDC->LineTo(BEGIN_X + x, BEGIN_Y + y);
	}
}

//画股票60日K线
void CStockChartStatic::DrawStockM60Line(CDC* pDC)
{
	std::vector<double> vec_price_ma60;
	vec_price_ma60 = CStockKDJArithmetic::CalcMA(60, pStockKDJData->vec_close_price);
	int mXNums = mDrawEndPos - mDrawBeginPos + 1;

	float fYRange = f_draw_max_val - f_draw_min_val;

	int size = vec_price_ma60.size();

	CPen      pen(PS_SOLID, 1, RGB(84, 255, 255));
	pDC->SelectObject(&pen);

	int mDrawWidth = m_interMinW * COL_NUMS;
	int mDrawHeight = m_interMinH * ROW_NUMS;

	int mKLineWidth = mDrawWidth / mXNums;

	for (int i = size - mXNums; i <= size - 1; i++)
	{
		int n = (i - (size - mXNums));
		int x = (n * m_interMinW * COL_NUMS) / mXNums + mKLineWidth / 2;

		int y = m_interMinH * ROW_NUMS - ((vec_price_ma60[i] - f_draw_min_val) * m_interMinH * ROW_NUMS) / fYRange;
	
		if (n == 0)
			pDC->MoveTo(BEGIN_X + x, BEGIN_Y + y);
		else
			pDC->LineTo(BEGIN_X + x, BEGIN_Y + y);
		
		
	}
}

//画选中股票的信息
void CStockChartStatic::DrawSelStockInfo(CDC* pDC)
{
	CStockDayData* pNowStockDayData = NULL;
	if (!pNowKLineAreaData)
		return;
	pNowStockDayData = pNowKLineAreaData->pStockDayData;
	CPen      whitepen(PS_SOLID, 1, RGB(255, 255, 255));
	pDC->SelectObject(&whitepen);
	pDC->SetTextColor(RGB(255, 255, 255));
	pDC->SetBkColor(RGB(0, 0, 0));
	CRect rect;
	GetClientRect(&rect);

	int x = rect.right - 240;

	int y = BEGIN_Y;

	CString strInfo;

	strInfo = pNowStockDayData->GetDate();

	pDC->TextOut(x+75, 15+ y , (LPCSTR)strInfo, strInfo.GetLength());

	strInfo.Format("开始价格 %.2f", pNowStockDayData->GetBeginPrice());
	pDC->TextOut(x + 75, 15 + y+25, (LPCSTR)strInfo, strInfo.GetLength());

	strInfo.Format("结束价格 %.2f", pNowStockDayData->GetEndPrice());
	pDC->TextOut(x + 75, 15 + y + 50, (LPCSTR)strInfo, strInfo.GetLength());

	strInfo.Format("最低价格 %.2f", pNowStockDayData->GetMinPrice());
	pDC->TextOut(x + 75, 15 + y + 75, (LPCSTR)strInfo, strInfo.GetLength());


	strInfo.Format("最高价格 %.2f", pNowStockDayData->GetMaxPrice());
	pDC->TextOut(x + 75, 15 + y + 100, (LPCSTR)strInfo, strInfo.GetLength());

	double f_rang = (pNowStockDayData->GetMaxPrice() - pNowStockDayData->GetMinPrice()) * 100.0 / pNowStockDayData->GetMinPrice();

	strInfo.Format("振幅 %.2f", f_rang);
	pDC->TextOut(x + 75, 15 + y + 125, (LPCSTR)strInfo, strInfo.GetLength());

	strInfo.Format("成交金额 %.2f万", pNowStockDayData->GetTotalPrice()/10000.0);
	pDC->TextOut(x + 75, 15 + y + 150, (LPCSTR)strInfo, strInfo.GetLength());

	if (pNowKLineAreaData->pLastStockDayData)
	{
		double f_last_close_price = pNowKLineAreaData->pLastStockDayData->GetEndPrice();

		double f_per = (pNowStockDayData->GetEndPrice() - f_last_close_price) * 100.0 / f_last_close_price;

		double f_now_per = (pNowStockDayData->GetEndPrice() - pNowStockDayData->GetBeginPrice()) * 100.0 / f_last_close_price;

		strInfo.Format("当日涨幅 %.2f", f_now_per);
		pDC->TextOut(x + 75, 15 + y + 175, (LPCSTR)strInfo, strInfo.GetLength());

		strInfo.Format("隔日涨幅 %.2f", f_per);
		pDC->TextOut(x + 75, 15 + y + 200, (LPCSTR)strInfo, strInfo.GetLength());

	}

}

BOOL CStockChartStatic::Init(void)
{
	
	if(pStockDayTable==NULL)
		return FALSE;
	if(strBeginDate=="" || strEndDate=="")
		return FALSE;


	mBeginPos=pStockDayTable->GetNearestStockDayIndex(strBeginDate);
	mEndPos=pStockDayTable->GetNearestStockDayIndex(strEndDate);

	if(mBeginPos==-1 || mEndPos==-1 )
		return FALSE;

	if(mBeginPos>mEndPos)
		return FALSE;

	if(mPreExtendNums==0)
		mPreExtendNums=(mEndPos-mBeginPos)*1;
	
	if(mAftExtendNums==0)
		mAftExtendNums=(mEndPos-mBeginPos)*1;


	int mNums = mEndPos - mBeginPos;

	strDrawBeginDate = strBeginDate;//pStockDayTable->GetStockDayDatePreOfIndex(strBeginDate,mPreExtendNums);
	strDrawEndDate = strEndDate;//pStockDayTable->GetStockDayDateAftOfIndex(strEndDate,mAftExtendNums);
	mDrawBeginPos=pStockDayTable->GetNearestStockDayIndex(strDrawBeginDate);
	mDrawEndPos=pStockDayTable->GetNearestStockDayIndex(strDrawEndDate);


	float f_min_val=pStockDayTable->GetMinLowPriceBwDates(strDrawBeginDate,strDrawEndDate);
	float f_max_val=pStockDayTable->GetMaxHighPriceBwDates(strDrawBeginDate,strDrawEndDate);
	f_draw_min_val = f_min_val;// f_min_val - ((f_max_val - f_min_val) * 5) / 100.0;
	f_draw_max_val = f_max_val;// f_max_val + ((f_max_val - f_min_val) * 5) / 100.0;

	vecDrawStockDayData=pStockDayTable->GetStockDayDataListBwDates(strDrawBeginDate,strDrawEndDate);


	float f_min_volume=pStockDayTable->GetMinVolumeBwDates(strDrawBeginDate,strDrawEndDate);
	float f_max_volume=pStockDayTable->GetMaxVolumeBwDates(strDrawBeginDate,strDrawEndDate);
	
	f_draw_min_volume = f_min_volume-((f_max_volume-f_min_volume)*5)/100.0;
	f_draw_max_volume = f_max_volume + ((f_max_volume - f_min_volume) * 5) / 100.0;


	pStockKDJData = CStockKDJArithmetic::CalcKDJData(pStockDayTable->GetStockCode(), strEndDate, mNums+70, K_LINE_DAY, 9, 3, 3);//

	std::vector<double> vec_price_ma5, vec_price_ma10, vec_price_ma20,vec_price_ma60;
	vec_price_ma5= CStockKDJArithmetic::CalcMA(5, pStockKDJData->vec_close_price);
	vec_price_ma10 = CStockKDJArithmetic::CalcMA(10, pStockKDJData->vec_close_price);
	vec_price_ma20 = CStockKDJArithmetic::CalcMA(20, pStockKDJData->vec_close_price);
	vec_price_ma60 = CStockKDJArithmetic::CalcMA(60, pStockKDJData->vec_close_price);

	double f_min_ma = 99999999999.0;
	double f_max_ma = 0.0;
	int mXNums = mDrawEndPos - mDrawBeginPos + 1;

	for (int i = vec_price_ma5.size()- mXNums; i < vec_price_ma5.size();i++)
	{
		if (vec_price_ma5[i] > 0.2)
		{
			if (vec_price_ma5[i] < f_min_ma)
				f_min_ma = vec_price_ma5[i];
		}
	}
	for (int i = vec_price_ma5.size() - mXNums; i < vec_price_ma5.size(); i++)
	{
		if (vec_price_ma5[i] > 0.2)
		{
			if (vec_price_ma5[i] > f_max_ma)
				f_max_ma = vec_price_ma5[i];
		}
	}



	for (int i = vec_price_ma5.size() - mXNums; i < vec_price_ma10.size(); i++)
	{
		if (vec_price_ma10[i] > 0.2)
		{
			if (vec_price_ma10[i] < f_min_ma)
				f_min_ma = vec_price_ma10[i];
		}
	}
	for (int i = vec_price_ma5.size() - mXNums; i < vec_price_ma10.size(); i++)
	{
		if (vec_price_ma10[i] > 0.2)
		{
			if (vec_price_ma10[i] > f_max_ma)
				f_max_ma = vec_price_ma10[i];
		}
	}


	for (int i = vec_price_ma5.size() - mXNums; i < vec_price_ma20.size(); i++)
	{
		if (vec_price_ma20[i] > 0.2)
		{
			if (vec_price_ma20[i] < f_min_ma)
				f_min_ma = vec_price_ma20[i];
		}
	}
	for (int i = vec_price_ma5.size() - mXNums; i < vec_price_ma20.size(); i++)
	{
		if (vec_price_ma20[i] > 0.2)
		{
			if (vec_price_ma20[i] > f_max_ma)
				f_max_ma = vec_price_ma20[i];
		}
	}

	for (int i = vec_price_ma5.size() - mXNums; i < vec_price_ma60.size(); i++)
	{
		if (vec_price_ma60[i] > 0.2)
		{
			if (vec_price_ma60[i] < f_min_ma)
				f_min_ma = vec_price_ma60[i];
		}
	}
	for (int i = vec_price_ma5.size() - mXNums; i < vec_price_ma60.size(); i++)
	{
		if (vec_price_ma60[i] > 0.2)
		{
			if (vec_price_ma60[i] > f_max_ma)
				f_max_ma = vec_price_ma60[i];
		}
	}

	if(f_min_ma < f_min_val)
		f_draw_min_val = f_min_ma;

	if(f_max_ma > f_max_val)
		f_draw_max_val = f_max_ma;
	
	
	vecEnvInterestBwDatesDataList=EnvDataMgr()->GetEnvInterestDataListOfPreDate(strDrawEndDate,5);
	vecEnvReserveBwDatesDataList=EnvDataMgr()->GetEnvReserveDataListOfPreDate(strDrawEndDate,5);

	CString strStockName;
	strStockName = StockDataMgr()->GetStockName(pStockDayTable->GetStockCode());

	CString strTitle;
	strTitle.Format("%s  %s  %s--%s  ",pStockDayTable->GetStockCode(), strStockName,strDrawBeginDate,strDrawEndDate);
	
	CString strInfo;

	std::vector<std::string> strIndustryList= IndustryDataMgr()->FindIndustryByStockCode((LPCSTR)pStockDayTable->GetStockCode());

	std::vector<std::string> strConceptList = ConceptDataMgr()->FindConceptByStockCode((LPCSTR)pStockDayTable->GetStockCode());

	

	strInfo = "板块: ";
	for (int i = 0; i < strIndustryList.size(); i++)
	{
		strInfo += strIndustryList[i].c_str();
		strInfo += "   ";

	}
	strInfo += "  概念: ";
	for (int i = 0; i < strConceptList.size(); i++)
	{
		strInfo += strConceptList[i].c_str();
		strInfo += "   ";

	}
	strTitle += "  ";
	strTitle += strInfo;

	GetParent()->SetWindowText(strTitle);

	bDrawTips=FALSE;
	strDrawTips="";

	return TRUE;
}

int CStockChartStatic::OnCreate(LPCREATESTRUCT lpCreateStruct)
{

	if (CStatic::OnCreate(lpCreateStruct) == -1)
		return -1;

	
	CRect rcWnd;  
	GetWindowRect(&rcWnd);  
	ScreenToClient(&rcWnd);  
	pdc = GetWindowDC(); 
	dcMem.CreateCompatibleDC(pdc);  
	bmpBg.CreateCompatibleBitmap(pdc,rcWnd.Width(),rcWnd.Height());  

	VERIFY(font.CreateFont(  
		16,                        // nHeight  
		0,                         // nWidth  
		0,                         // nEscapement  
		0,                         // nOrientation  
		FW_NORMAL,                 // nWeight  
		FALSE,                     // bItalic  
		FALSE,                     // bUnderline  
		0,                         // cStrikeOut  
		ANSI_CHARSET,              // nCharSet  
		OUT_DEFAULT_PRECIS,        // nOutPrecision  
		CLIP_DEFAULT_PRECIS,       // nClipPrecision  
		DEFAULT_QUALITY,           // nQuality  
		DEFAULT_PITCH | FF_SWISS,  // nPitchAndFamily  
		"宋体"));                 // lpszFacename  

	return 0;
}

void CStockChartStatic::PreSubclassWindow()
{
	// TODO: 在此添加专用代码和/或调用基类
	DWORD dwStyle = GetStyle();  
	SetWindowLong(GetSafeHwnd(),GWL_STYLE,dwStyle | SS_OWNERDRAW |SS_NOTIFY  );  
	CStatic::PreSubclassWindow();
}


BOOL CStockChartStatic::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if(pMsg->message==WM_RBUTTONDOWN)
	{
		CWnd * Parent = GetParent();
		if(Parent->GetSafeHwnd())
		{

		}
	}
	return CStatic::PreTranslateMessage(pMsg);
}



BOOL CStockChartStatic::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	return TRUE;
}

void CStockChartStatic::DrawTips(CDC* pDC)
{
	CPen      whitepen(PS_SOLID, 1, RGB(255, 255, 255));
	pDC->SelectObject(&whitepen);
	pDC->SetTextColor(RGB(255, 255, 255));	
	
	if(bDrawTips)
	{
		pDC->TextOut(400, 42+m_interMinH*18, (LPCSTR)strDrawTips,strDrawTips.GetLength());
	}
	else
	{
		CString strDraw="                       ";
		pDC->TextOut(400, 42+m_interMinH*18, (LPCSTR)strDraw,strDraw.GetLength());
	}
}


#define VOL_ROW_NUMS 6
#define VOL_COL_NUMS 4

//交易额外框线
void CStockChartStatic::DrawVolumeOutLineUI(CDC* pDC)
{
	CPen      redpen(PS_SOLID,2,RGB(153,0,0));
	CPen      redDotpen(PS_DOT, 1, RGB(153,0,0));
	CPen      whiteDotpen(PS_DOT, 1, RGB(153, 153, 153));
	CPen      whilepen(PS_SOLID, 2, RGB(153, 153, 153));


	m_volumeInterH=170/ VOL_ROW_NUMS;
	m_volumeInterW=m_interMinW;
	m_volumeBeginY=70+m_interMinH*ROW_NUMS;

	pDC->SelectObject(&whilepen);
	pDC->MoveTo(BEGIN_X, m_volumeBeginY);
	pDC->LineTo(BEGIN_X +m_volumeInterW* VOL_COL_NUMS, m_volumeBeginY);
	pDC->LineTo(BEGIN_X +m_volumeInterW* VOL_COL_NUMS, m_volumeBeginY+m_volumeInterH*6);
	pDC->LineTo(BEGIN_X, m_volumeBeginY+m_volumeInterH* VOL_ROW_NUMS);
	pDC->LineTo(BEGIN_X, m_volumeBeginY);

	pDC->SelectObject(&redDotpen);	


	for(int i=1;i< VOL_ROW_NUMS;i++)
	{
		pDC->MoveTo(BEGIN_X, m_volumeBeginY+m_volumeInterH*i);
		pDC->LineTo(BEGIN_X +m_volumeInterW* VOL_COL_NUMS, m_volumeBeginY+m_volumeInterH*i);
	}
}

//画交易额线
void CStockChartStatic::DrawVolumeLine(CDC* pDC)
{

#if 0
	CPen      whitepen(PS_SOLID, 1, RGB(255, 255, 255));
	CPen      greenpen(PS_SOLID, 1, RGB(0, 255, 0));
	pDC->SelectObject(&whitepen);
	int mXNums=mDrawEndPos-mDrawBeginPos;

	float fYRange=f_draw_max_volume-f_draw_min_volume;

	int x,y;
	CStockDayData *pStockDayData=NULL;
	for(int i=0;i<vecDrawStockDayData.size();i++)
	{
		pStockDayData=vecDrawStockDayData[i];
		if((i+mDrawBeginPos)>=mBeginPos  && (i+mDrawBeginPos)<=mEndPos)
			pDC->SelectObject(&greenpen);
		else
			pDC->SelectObject(&whitepen);
		x=(i*m_volumeInterW*4)/mXNums;

		y=m_volumeInterH*6-((pStockDayData->GetTotalPrice()-f_draw_min_volume)*m_volumeInterH*6)/fYRange;
		if(i==0)
			pDC->MoveTo(82+x,m_volumeBeginY+y);
		else
			pDC->LineTo(82+x,m_volumeBeginY+y);
	}

#endif
	int mXNums = mDrawEndPos - mDrawBeginPos+1;

	float fYRange = f_draw_max_volume - f_draw_min_volume;

	int x, y;
	CStockDayData* pStockDayData = NULL;

	int mVolPerW= (m_volumeInterW * VOL_COL_NUMS) / mXNums;
	for (int i = 0; i < vecDrawStockDayData.size(); i++)
	{
		pStockDayData = vecDrawStockDayData[i];
		x = (i * m_volumeInterW * VOL_COL_NUMS) / mXNums;

		y = m_volumeInterH * VOL_ROW_NUMS - ((pStockDayData->GetTotalPrice() - f_draw_min_volume) * m_volumeInterH * VOL_ROW_NUMS) / fYRange;
	

		//


		RECT rect;
		rect.left = BEGIN_X+x+ mVolPerW/6;
		rect.top = m_volumeBeginY+y;
		rect.right = rect.left + mVolPerW*2/3;
		rect.bottom =  m_volumeBeginY + m_volumeInterH * VOL_ROW_NUMS;
		if (pStockDayData->GetEndPrice() > pStockDayData->GetBeginPrice())
			pDC->FillSolidRect(&rect, RGB(255, 0, 0));
		else
			pDC->FillSolidRect(&rect, RGB(0, 255, 0));

	}

}

//画环境（加息 准备金等)
void CStockChartStatic::DrawEnviron(CDC* pDC)
{
	CPen      blue_pen(PS_SOLID, 1, RGB(0, 0, 255));
	
	CString strEnvInterest;
	strEnvInterest="   加息: ";
	CEnvInterestData *pEnvInterestData=NULL;
	CString strTemp="";
	for(int i=0;i<vecEnvInterestBwDatesDataList.size();i++)
	{
		pEnvInterestData=vecEnvInterestBwDatesDataList[i];
		if(!pEnvInterestData)
			continue;
		strTemp.Format(" %s  %.2f ,",pEnvInterestData->GetDate(),pEnvInterestData->GetDepositRange());
		strEnvInterest+=strTemp;
	}
	if(vecEnvInterestBwDatesDataList.size()>0)
	{
		int Nums=vecEnvInterestBwDatesDataList.size()-1;
		strTemp.Format(" %.2f",vecEnvInterestBwDatesDataList[Nums]->GetDepositAfter());
		strEnvInterest+=strTemp;
	}

	CString strEnvReserve;
	strEnvReserve="准备金:";
	CEnvReserveData *pEnvReserveData=NULL;
	strTemp="";
	for(int i=0;i<vecEnvReserveBwDatesDataList.size();i++)
	{
		pEnvReserveData=vecEnvReserveBwDatesDataList[i];
		if(!pEnvReserveData)
			continue;
		strTemp.Format(" %s  %.2f ,",pEnvReserveData->GetDate(),pEnvReserveData->GetBigRange());
		strEnvReserve+=strTemp;
	}
	if(vecEnvReserveBwDatesDataList.size()>0)
	{
		int Nums=vecEnvReserveBwDatesDataList.size()-1;
		strTemp.Format(" %.2f",vecEnvReserveBwDatesDataList[Nums]->GetBigAfter());
		strEnvReserve+=strTemp;
	}

//	pDC->SelectObject(&blue_pen);
	pDC->SetTextColor(RGB(168, 168, 0));	
	pDC->TextOut(20, 15+m_volumeBeginY+m_volumeInterH*6, (LPCSTR)strEnvInterest,strEnvInterest.GetLength());
	pDC->SetTextColor(RGB(0, 168, 168));	
	pDC->TextOut(20, 45+m_volumeBeginY+m_volumeInterH*6, (LPCSTR)strEnvReserve,strEnvReserve.GetLength());
}

void CStockChartStatic::JudgeDrawTips(UINT nFlags, CPoint point)
{
	int x,y;
	x=point.x;
	y=point.y;

	if(x>82 && x<(82+m_interMinW*4))
	{
		if(y>35  && y<(35+m_interMinH*18))
		{
			bDrawTips=TRUE;
			

			int mXNums=mDrawEndPos-mDrawBeginPos;
			int pos=(x-82)/((m_interMinW*4)/mXNums);

			pos=pos+mDrawBeginPos;
			Vec_StockDayData vecStockDayData;

			vecStockDayData=pStockDayTable->GetStockDayDataList();
			CStockDayData *pStockDayData=NULL;
			pStockDayData=vecStockDayData[pos];
			
			
			float fEndVal=vecStockDayData[pos]->GetEndPrice();

			CString strDate=vecStockDayData[pos]->GetDate();

			strDrawTips.Format("%s   %.2f",strDate,fEndVal);

			SetTimer(CHART_TIMER_EVENT_REFRESH,200,0);
			bWaitRefresh=TRUE;
			return;
		
			
		}
	}

	if(bDrawTips)
	{
		SetTimer(CHART_TIMER_EVENT_REFRESH,200,0);
		bWaitRefresh=TRUE;
		strDrawTips="";
		bDrawTips=FALSE;
	}
	
	
	
}

void CStockChartStatic::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	/*int x,y;
	x=point.x;
	y=point.y;
	PrintfDebug("%d  %d  %d \n",x,y,nFlags);*/
	//JudgeDrawTips(nFlags,point);

	CStatic::OnMouseMove(nFlags, point);
}


void CStockChartStatic::OnTimer(UINT_PTR nIDEvent)
{
	if(CHART_TIMER_EVENT_REFRESH==nIDEvent)
	{
	//	bWaitRefresh=FALSE;
	//	Invalidate();
		KillTimer(CHART_TIMER_EVENT_REFRESH);
	}
	if (CHART_TIMER_EVENT_SEL == nIDEvent)
	{
		Invalidate();
		KillTimer(CHART_TIMER_EVENT_SEL);
	}
	CStatic::OnTimer(nIDEvent);
}


void CStockChartStatic::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	
	if(VK_LEFT==nChar && !bWaitRefresh)
	{
		mPreExtendNums++;
		Init();
		SetTimer(CHART_TIMER_EVENT_REFRESH,100,0);
		bWaitRefresh=TRUE;
	}
	else if(VK_RIGHT==nChar && !bWaitRefresh)
	{
		mAftExtendNums++;
		Init();
		SetTimer(CHART_TIMER_EVENT_REFRESH,100,0);
		bWaitRefresh=TRUE;
	}
	else if(VK_UP==nChar)
	{
		mPreExtendNums++;
		mAftExtendNums++;
		Init();
		SetTimer(CHART_TIMER_EVENT_REFRESH,100,0);
		bWaitRefresh=TRUE;
	}
	else if(VK_DOWN==nChar && !bWaitRefresh)
	{
		if( mPreExtendNums>(mEndPos-mBeginPos)*2  || mAftExtendNums>(mEndPos-mBeginPos)*2)
		{
			if( mPreExtendNums>(mEndPos-mBeginPos)*2)
				mPreExtendNums--;
			if(mAftExtendNums>(mEndPos-mBeginPos)*2)
				mAftExtendNums--;
			Init();
			SetTimer(CHART_TIMER_EVENT_REFRESH,100,0);
			bWaitRefresh=TRUE;
		}
	}

	CStatic::OnKeyDown(nChar, nRepCnt, nFlags);
}


UINT CStockChartStatic::OnGetDlgCode()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	UINT lRet = CStatic::OnGetDlgCode();  
	lRet |= DLGC_WANTARROWS;  
	return lRet; 
}


void CStockChartStatic::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	int x = point.x;
	int y = point.y;
	KLineAreaData* pKLineAreaData = NULL;
	for (int i = 0; i < vecKLineAreaData.size(); i++)
	{
		pKLineAreaData = vecKLineAreaData[i];
		if (x >= pKLineAreaData->x0 && x <= pKLineAreaData->x1)
		{
			if (y >= pKLineAreaData->y0 && y <= pKLineAreaData->y1)
			{
				pNowKLineAreaData = pKLineAreaData;
				SetTimer(CHART_TIMER_EVENT_SEL, 200, 0);
			}
		}


	}

	CStatic::OnLButtonDown(nFlags, point);
}


void CStockChartStatic::OnRButtonDown(UINT nFlags, CPoint point)
{
	int x = point.x;
	int y = point.y;
	CPoint point2(x, y);
	ClientToScreen(&point2);
	CMenu menu;
	VERIFY(menu.LoadMenu(IDR_MENU_SAVE_PIC));
	CMenu* popup = menu.GetSubMenu(0);
	ASSERT(popup != NULL);
	popup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point2.x, point2.y, this);

	CStatic::OnRButtonDown(nFlags, point);
}


void CStockChartStatic::OnMenuSaveBmp()
{
	CString strFileName = pStockDayTable->GetStockCode();
	strFileName += ".png";
	CString m_path;
	static TCHAR szFilter[] =
		_T("Png Files (*.png)|*.png|");

	CFileDialog hFileDlg(FALSE, "*.png", strFileName,
		OFN_FILEMUSTEXIST | OFN_READONLY | OFN_PATHMUSTEXIST,
		szFilter,
		NULL);
	if (hFileDlg.DoModal() == IDOK)
	{
		m_path = hFileDlg.GetPathName();
		UpdateData(FALSE);
	}

	HBITMAP hBitmap = NULL;
	if (pdc)
	{
		/**
		* 创建位图段
		*/
		BITMAPINFO bmi;
		LPBYTE pBits;
		ZeroMemory(&bmi, sizeof(bmi));
		CRect rcClient;
		GetClientRect(rcClient);
		bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
		bmi.bmiHeader.biWidth = rcClient.Width();
		bmi.bmiHeader.biHeight = rcClient.Height();
		bmi.bmiHeader.biPlanes = 1;
		bmi.bmiHeader.biBitCount = 24;
		bmi.bmiHeader.biCompression = BI_RGB;
		hBitmap = CreateDIBSection(pdc->m_hDC, &bmi, DIB_RGB_COLORS, (void**)&pBits, 0, 0);

		/**
		* 创建兼容dc并选择位图段
		*/
		CDC dcMem;
		dcMem.CreateCompatibleDC(pdc);
		dcMem.SelectObject(hBitmap);

		/**
		* 在内存dc上(即位图段上)绘图
		* 此函数你自己把你的绘制代码拿出来做成函数 void Paint( CDC *pDC)就行了
		*/
		dcMem.BitBlt(0, 0, rcClient.Width(), rcClient.Height(), pdc, 0, 0, SRCCOPY);

		/**
		* 释放dc
		*/
		ReleaseDC(pdc);
	}


	/**
	* 保存位图
	*/
	if (hBitmap)
	{
		CImage img;
		img.Attach(hBitmap);
		//img.Save("e:\\1.bmp");
		img.Save(m_path);
		DeleteObject(hBitmap);

		//AfxMessageBox("ok");
	}
}
