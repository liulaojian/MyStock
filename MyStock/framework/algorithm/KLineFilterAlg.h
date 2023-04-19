#pragma once
#include "StockDataMgr.h"
#include "afxwin.h"
#include "afxdtctl.h"
#include "Algorithm.h"
#include <vector>
#include "DataType.h"


class CKLineFilterAlg
{

public:
	CKLineFilterAlg();
	virtual ~CKLineFilterAlg();

public:
	Vec_KLineFilterData  doFilter(CTime mDropOffTime,Vec_DropOffData & vecDropOffData);
	Vec_KLineFilterData2  doFilter2(CString strStockCode, CString strStockName, CTime mNowTime);

	KLineContinusMNData  doCalcMNPriceContiUp(CString strStockCode, CString strStockName, CTime mNowTime);


	int CalcBollType(double f_boll_up,double f_boll_middle,double f_boll_bottom,double f_close,double f_begin,double f_high,double f_low);

	//K�� 4���� ��ת
	static BOOL IsKLineFourDownFilter(Vec_KLineFilterData2& vecKLineFilterData2);
	
	//ʮ���Ƿ�ת
	//��ʮ���� �ڶ������߰���������ʮ����
	static BOOL  IsCrossStartRevertFilter(Vec_KLineFilterData2& vecKLineFilterData2, KLineContinusMNData & mKLineContinusMNData);
	
	//�Ƿ�K�������߻�
	static BOOL IsKLineBadTrend(Vec_KLineFilterData2& vecKLineFilterData2);

	//K����ҵ
	static BOOL IsKLineIndustry(Vec_KLineFilterData2& vecKLineFilterData2);

	//�����תDown
	static BOOL IsKLineNineTurn(Vec_KLineFilterData2& vecKLineFilterData2);
	//�����תUp
	static BOOL IsKLineNineTurnUp(Vec_KLineFilterData2& vecKLineFilterData2);


	//�Ƿ�K�߾���Ok
	static BOOL IsKLineAveLineOk(Vec_KLineFilterData2& vecKLineFilterData2);


	//��������K������
	static CString AnalyzeSingleKLineTrend(Vec_KLineFilterData2& vecKLineFilterData2);

	static void FreeVecKLineFilterData2(Vec_KLineFilterData2& vecKLineFilterData2);


	//������K��
	static BOOL IsKLineReverse(CString strStockCode, CString strStockName,CTime mNowTime);

};