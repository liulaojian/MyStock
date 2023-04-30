#include "stdafx.h"
#include "StockDMIAtithmetic.h"
#include "StockDataMgr.h"
#include "CommonMacro.h"
//#include "BaseIndicator.h"
CStockDMIArithmetic::CStockDMIArithmetic()
{


}


CStockDMIArithmetic::~CStockDMIArithmetic()
{

}

/*
static void calDMIMTR(std::vector<double>& pPRICE_h, std::vector<double>& pPRICE_l, std::vector<double>& pPRICE_o, std::vector<double>& pPRICE_c,
	const int count,
	const int N,
	const double smooth,
	double *pMTR)
{
	double *pclose = new double[count];	// [count] ;
	for (int i = 0; i < count; i++)
	{
		pclose[i] = pPRICE_c[i];
	}
	double *pmaxValue=new double[count];	//[count];
	for (int i = 0; i < count; i++)
	{
		double ref = calRef(pclose, count, i, 1);
		double maxArgs = fmax(pPRICE_h[i] - pPRICE_l[i], fabs(pPRICE_h[i] - ref));
		pmaxValue[i] = fmax(maxArgs, fabs(ref - pPRICE_l[i]));
	}

	calEXPMEMA(pmaxValue, count, N, smooth, pMTR);
	delete[]pclose;
	delete[]pmaxValue;
}


void calDMIHD(std::vector<double>& pPRICE_h, std::vector<double>& pPRICE_l, std::vector<double>& pPRICE_o, std::vector<double>& pPRICE_c,
    const int count,
    double *pHD)
{
    double *phigh = new double[count];
    for (int i = 0; i < count; i++)
    {
        phigh[i] = pPRICE_h[i];
    }

    for (int i = 0; i < count; i++)
    {
        pHD[i] = phigh[i] - calRef(phigh, count, i, 1);
    }
    delete[]phigh;
}

void calDMILD(std::vector<double>& pPRICE_h, std::vector<double>& pPRICE_l, std::vector<double>& pPRICE_o, std::vector<double>& pPRICE_c,
    const int count,
    double *pLD)
{
    double *plow = new double[count];
    for (int i = 0; i < count; i++)
    {
        plow[i] = pPRICE_l[i];
    }

    for (int i = 0; i < count; i++)
    {
        pLD[i] = calRef(plow, count, i, 1) - plow[i];
    }
    delete[]plow;
}

void calDMIDMP(std::vector<double>& pPRICE_h, std::vector<double>& pPRICE_l, std::vector<double>& pPRICE_o, std::vector<double>& pPRICE_c,
    const int count,
    const int N,
    const double smooth,
    const double *pHD,
    const double *pLD,
    double *pDMP)
{
    double *pdmpMiddle= new double[count];
    for (int i = 0; i < count; i++)
    {
        if ((pHD[i] > 0.f) && (pHD[i] > pLD[i]))
        {
            pdmpMiddle[i] = pHD[i];
        }
        else
        {
            pdmpMiddle[i] = 0.f;
        }
    }

    calEXPMEMA(pdmpMiddle, count, N, smooth, pDMP);
    delete[]pdmpMiddle;
}

void calDMIDMM(std::vector<double>& pPRICE_h, std::vector<double>& pPRICE_l, std::vector<double> & pPRICE_o, std::vector<double> &pPRICE_c,
    const int count,
    const int N,
    const double smooth,
    const double *pHD,
    const double *pLD,
    double *pDMM)
{
    double *pdmmMiddle= new double[count];
    for (int i = 0; i < count; i++)
    {
        if ((pLD[i] > 0.f) && (pLD[i] > pHD[i]))
        {
            pdmmMiddle[i] = pLD[i];
        }
        else
        {
            pdmmMiddle[i] = 0.f;
        }
    }

    calEXPMEMA(pdmmMiddle, count, N, smooth, pDMM);
    delete[]pdmmMiddle;
}

void calDMIPDI(const double *pDMP,
    const double *pMTR,
    const int count,
    double *pPDI)
{
    for (int i = 0; i < count; i++)
    {
        pPDI[i] = pDMP[i] * 100 / pMTR[i];
    }
}

void calDMIMDI(const double *pDMM,
    const double *pMTR,
    const int count,
    double *pMDI)
{
    for (int i = 0; i < count; i++)
    {
        pMDI[i] = pDMM[i] * 100 / pMTR[i];
    }
}

void calDMIADX(const double *pMDI,
    const double *pPDI,
    const int count,
    const int M,
    const double smooth,
    double *pADX)
{
    double *padxMiddle = new double[count];
    for (int i = 0; i < count; i++)
    {
        padxMiddle[i] = fabs(pMDI[i] - pPDI[i]) / (pMDI[i] + pPDI[i]) * 100;
    }

    calEXPMEMA(padxMiddle, count, M, smooth, pADX);
    delete[]padxMiddle;
}

void calDMIADXR(const double *pADX,
    const int count,
    const double smooth,
    const int M,
    double *pADXR)
{
    calEXPMEMA(pADX, count, M, smooth, pADXR);
}

void CalDMIIndicator(std::vector<double>& pPRICE_h, std::vector<double>& pPRICE_l, std::vector<double>& pPRICE_o, std::vector<double>& pPRICE_c,
    const int count,
    const int N,
    const int M,
    const double smooth,
    double *pPDI,
    double *pMDI,
    double *pADX,
    double *pADXR)
{
    double *pMTR= new double[count];
    double *pHD = new double[count];
    double *pLD = new double[count];
    calDMIMTR(pPRICE_h, pPRICE_l, pPRICE_o, pPRICE_c, count, N, smooth, pMTR);
    calDMIHD(pPRICE_h, pPRICE_l, pPRICE_o, pPRICE_c, count, pHD);
    calDMILD(pPRICE_h, pPRICE_l, pPRICE_o, pPRICE_c, count, pLD);

    double *pDMP = new double[count];
    double *pDMM = new double[count];
    calDMIDMP(pPRICE_h, pPRICE_l, pPRICE_o, pPRICE_c, count, N, smooth, pHD, pLD, pDMP);
    calDMIDMM(pPRICE_h, pPRICE_l, pPRICE_o, pPRICE_c, count, N, smooth, pHD, pLD, pDMM);

    calDMIPDI(pDMP, pMTR, count, pPDI);
    calDMIMDI(pDMM, pMTR, count, pMDI);
    calDMIADX(pMDI, pPDI, count, M, smooth, pADX);
    calDMIADXR(pADX, count, smooth, M, pADXR);

    delete[]pMTR;
    delete[]pHD;
    delete[]pLD;
    delete[]pDMP;
    delete[]pDMM;
}
*/

CStockDMIData* CStockDMIArithmetic::CalcDMIData(CString strStockCode, CString strDateTime, int mNums, int mType, int mN1, int mN2)
{
	KLineBaseData* pKLineBaseData = NULL;

	int mRelNums = mNums+mN1;
	if (mType == K_LINE_DAY)
	{
		CStockDayTable* pStockDayTable;
		pStockDayTable = StockDataMgr()->GetStockDayTable(strStockCode);
		if (!pStockDayTable)
			return NULL;

		pKLineBaseData = CKLineDataBean::ConvStockDayDataToArithmeticBaseData(pStockDayTable, strDateTime, mRelNums);

	}
	else if (mType == K_LINE_5IN)
	{
		CStockMin5Table* pStockMin5Table;
		pStockMin5Table = StockDataMgr()->GetStockMin5Table(strStockCode);
		if (!pStockMin5Table)
			return NULL;
		pKLineBaseData = CKLineDataBean::ConvStockDayDataToArithmeticBaseDataMin5(pStockMin5Table, strDateTime, mRelNums);

	}
	else if (mType == K_LINE_15IN)
	{
		CStockMin5Table* pStockMin5Table;
		pStockMin5Table = StockDataMgr()->GetStockMin5Table(strStockCode);
		if (!pStockMin5Table)
			return NULL;
		pKLineBaseData = CKLineDataBean::ConvStockDayDataToArithmeticBaseDataMin15(pStockMin5Table, strDateTime, mRelNums);
	}
	else if (mType == K_LINE_30IN)
	{
		CStockMin5Table* pStockMin5Table;
		pStockMin5Table = StockDataMgr()->GetStockMin5Table(strStockCode);
		if (!pStockMin5Table)
			return NULL;
		pKLineBaseData = CKLineDataBean::ConvStockDayDataToArithmeticBaseDataMin30(pStockMin5Table, strDateTime, mRelNums);
	}
	else if (mType == K_LINE_60MIN)
	{
		CStockMin5Table* pStockMin5Table;
		pStockMin5Table = StockDataMgr()->GetStockMin5Table(strStockCode);
		if (!pStockMin5Table)
			return NULL;
		pKLineBaseData = CKLineDataBean::ConvStockDayDataToArithmeticBaseDataMin60(pStockMin5Table, strDateTime, mRelNums);
	}

	if (!pKLineBaseData)
		return NULL;

    int size = pKLineBaseData->vec_close_price.size();

   /* double PDI[125 + 14];
    double MDI[125 + 14];
    double ADX[125 + 14];
    double ADXR[125 + 14];




    CalDMIIndicator(pKLineBaseData->vec_high_price, pKLineBaseData->vec_low_price, pKLineBaseData->vec_open_price, pKLineBaseData->vec_close_price,
        size, 14, 6, 0.0, PDI, MDI, ADX, ADXR);*/


    /*
    TR = SUM(MAX(MAX(HIGH - LOW, ABS(HIGH - REF(CLOSE, 1))), ABS(LOW - REF(CLOSE, 1))), M1)
    HD = HIGH - REF(HIGH, 1);     LD = REF(LOW, 1) - LOW
    DMP = SUM(IF((HD > 0) & (HD > LD), HD, 0), M1)
    DMM = SUM(IF((LD > 0) & (LD > HD), LD, 0), M1)
    PDI = DMP * 100 / TR;         MDI = DMM * 100 / TR
    ADX = MA(ABS(MDI - PDI) / (PDI + MDI) * 100, M2)
    ADXR = (ADX + REF(ADX, M2)) / 2
    */
    int n = mN1;

    std::vector<float> vec_pdi;
    std::vector<float> vec_mdi;
    for (int i = n; i < size; i++)
    {
      
      
        double mtr = 0.0;
        double dmp = 0.0;
        double dmm = 0.0;

        for (int j = i - n + 1; j <= i; j++)
        {
            double preclose = pKLineBaseData->vec_close_price[j - 1];
            double high = pKLineBaseData->vec_high_price[j];
            double prehigh = pKLineBaseData->vec_high_price[j - 1];
            double low = pKLineBaseData->vec_low_price[j];
            double prelow = pKLineBaseData->vec_low_price[j - 1];

            double f_temp1 = fabs(high - preclose);
            double f_temp2 = fmax(high - low, f_temp1);
            double f_temp3 = fabs(preclose - low);
            double f_temp4 = fmax(f_temp2, f_temp3);
            mtr += f_temp4;

            double hd = high - prehigh;
            double ld = prelow - low;

            if (hd > 0.0 && hd > ld)
                dmp += hd;
            if (ld > 0.0 && ld > hd)
                dmm += ld;

        }

      
        double pdi = dmp * 100.0 / mtr;
        double mdi = dmm * 100.0 / mtr;
        vec_pdi.push_back(pdi);
        vec_mdi.push_back(mdi);

    }
    
    std::vector<float> vec_adx_pre;
    size = vec_pdi.size();
    for (int i = 0; i < size; i++)
    {
        double f_temp = fabs(vec_mdi[i] - vec_pdi[i]) / (vec_pdi[i] + vec_mdi[i]) * 100.0;
        vec_adx_pre.push_back(f_temp);
    }
    std::vector<float> vec_adx = CStockDMIArithmetic::CalcMA(mN2, vec_adx_pre);

    size = vec_adx.size();
    std::vector<float> vec_adxr;
    for (int i = 0; i < mN2; i++)
        vec_adxr.push_back(0.0);

    for (int i = mN2; i < size; i++)
    {
        double f_temp = (vec_adx[i]+vec_adx[i - mN2])/2.0;
        vec_adxr.push_back(f_temp);

    }


    CStockDMIData* pCStockDMIData;
    pCStockDMIData = new CStockDMIData();
    pCStockDMIData->vec_open_price.assign(pKLineBaseData->vec_open_price.begin() + mN1, pKLineBaseData->vec_open_price.end());
    pCStockDMIData->vec_high_price.assign(pKLineBaseData->vec_high_price.begin() + mN1, pKLineBaseData->vec_high_price.end());
    pCStockDMIData->vec_low_price.assign(pKLineBaseData->vec_low_price.begin() + mN1, pKLineBaseData->vec_low_price.end());
    pCStockDMIData->vec_close_price.assign(pKLineBaseData->vec_close_price.begin() + mN1, pKLineBaseData->vec_close_price.end());
    pCStockDMIData->vec_avg_price.assign(pKLineBaseData->vec_avg_price.begin() + mN1, pKLineBaseData->vec_avg_price.end());
    pCStockDMIData->vec_time.assign(pKLineBaseData->vec_time.begin() + mN1, pKLineBaseData->vec_time.end());
    pCStockDMIData->vec_volume.assign(pKLineBaseData->vec_volume.begin() + mN1, pKLineBaseData->vec_volume.end());
    pCStockDMIData->vec_volume_price.assign(pKLineBaseData->vec_volume_price.begin() + mN1, pKLineBaseData->vec_volume_price.end());
    pCStockDMIData->vec_pdi = vec_pdi;
    pCStockDMIData->m_length = vec_pdi.size();
    pCStockDMIData->vec_mdi = vec_mdi;
    pCStockDMIData->vec_adx = vec_adx;
    pCStockDMIData->vec_adxr = vec_adxr;
    pCStockDMIData->m_type = pKLineBaseData->m_type;
    pCStockDMIData->mN1 = mN1;
    pCStockDMIData->mN2 = mN2;
    pCStockDMIData->strStockCode = strStockCode;
    SAFE_DELETE(pKLineBaseData);
    return pCStockDMIData;

	

}


std::vector<float> CStockDMIArithmetic::CalcMA(int n, std::vector<float> veccr)
{
	std::vector<float> vecma_value;
	double ma;
	double closeSum = 0.0;
	int period;
	for (int i = 0; i < veccr.size(); i++) {
		closeSum += veccr[i];
		if (i >= (n - 1)) {
			period = i - n;
			if (period >= 0) {
				closeSum -= veccr[period];
			}
			ma = (double)closeSum / n;
			vecma_value.push_back(ma);
		}
		else
		{
			vecma_value.push_back(0.0);
		}
	}

	return vecma_value;
}