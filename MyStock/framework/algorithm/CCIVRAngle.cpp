#include "stdafx.h"
#include "CCIVRAngle.h"
#include  "StockCCIArithmetic.h"
#include "CommonMacro.h"

CCIVRAngle::CCIVRAngle()
{

}


CCIVRAngle::~CCIVRAngle()
{

}


CCIVRAngleData CCIVRAngle::CalcCCIVRAngle(CString strStockCode, CString strDate, std::vector<float>& vec_vr, int m_prenum)
{
	
	CStockCCIData* pCStockCCIData = CStockCCIArithmetic::CalcCCIData(strStockCode, strDate, 125, K_LINE_DAY, 14);

	int m_cci_size = pCStockCCIData->vec_cci_value.size();

	int m_vr_size = vec_vr.size();

	float f_max_cci_value=-99999.0;
	int m_max_cci_num = -1;
	for (int i = m_cci_size - m_prenum; i < m_cci_size; i++)
	{
		if (pCStockCCIData->vec_cci_value[i] > f_max_cci_value)
		{
			f_max_cci_value = pCStockCCIData->vec_cci_value[i];
			m_max_cci_num = m_cci_size - i;
		}
	}

	int m_cci_up_100_index = -1;
	for (int i = m_cci_size - 1; i >= m_cci_size - m_prenum; i--)
	{
		float nowvalue = pCStockCCIData->vec_cci_value[i];
		float prevalue = pCStockCCIData->vec_cci_value[i - 1];
		if (prevalue < 100.0 && nowvalue>100.0)
		{
			m_cci_up_100_index =  i;
			break;
		}
	}

	float f_max_cci_value_after_up_100 = -99999.0;
	int  m_max_cci_value_after_up_100_num = -1;

	if (m_cci_up_100_index > 0)
	{
		for (int i = m_cci_up_100_index; i < m_cci_size; i++)
		{
			if (pCStockCCIData->vec_cci_value[i] > f_max_cci_value_after_up_100)
			{
				f_max_cci_value_after_up_100 = pCStockCCIData->vec_cci_value[i];
				m_max_cci_value_after_up_100_num = m_cci_size - i;
			}
		}
	}


	int m_cci_up_100_num=-1;
	for (int i = m_cci_size - 1; i >= m_cci_size - m_prenum; i--)
	{
		float nowvalue= pCStockCCIData->vec_cci_value[i];
		float prevalue= pCStockCCIData->vec_cci_value[i-1];
		if (prevalue < 100.0 && nowvalue>100.0)
		{
			m_cci_up_100_num= m_cci_size - i;
			break;
		}
	}

	int m_cci_down_100_num=-1;
	for (int i = m_cci_size - 1; i >= m_cci_size - m_prenum; i--)
	{
		float nowvalue = pCStockCCIData->vec_cci_value[i];
		float prevalue = pCStockCCIData->vec_cci_value[i - 1];
		if (prevalue > 100.0 && nowvalue<100.0)
		{
			m_cci_down_100_num = m_cci_size - i;
			break;
		}
	}

	float f_now_cci_value= pCStockCCIData->vec_cci_value[m_cci_size-1];
	float f_now_vr_value = vec_vr[m_vr_size - 1];

	float f_max_cci_index_cr_value = 0.0;

	if (m_max_cci_num >= 0)
	{
		f_max_cci_index_cr_value = vec_vr[m_vr_size - m_max_cci_num];
	}

	float f_cci_up_100_index_cr_value = 0.0;
	if (m_cci_up_100_num >= 0)
	{
		f_cci_up_100_index_cr_value = vec_vr[m_vr_size - m_cci_up_100_num];
	}

	float f_cci_down_100_index_cr_value=0.0;
	if (m_cci_down_100_num >= 0)
	{
		f_cci_down_100_index_cr_value= vec_vr[m_vr_size - m_cci_down_100_num];
	}

	int m_nums_bw_up100_max=-1;
	float f_vr_per_increase_bw_up100_max = 0.0;

	if (m_cci_up_100_num >0 && m_max_cci_num > 0)
	{
		m_nums_bw_up100_max =  m_cci_up_100_num - m_max_cci_num;
		f_vr_per_increase_bw_up100_max = (f_max_cci_index_cr_value - f_cci_up_100_index_cr_value)/ m_nums_bw_up100_max;
	}


	int m_nums_bw_up100_now = -1;

	float f_vr_per_increase_bw_up100_now = 0.0;

	if (m_cci_up_100_num > 0)
	{
		m_nums_bw_up100_now = m_cci_up_100_num ;
		f_vr_per_increase_bw_up100_now = (f_now_vr_value - f_cci_up_100_index_cr_value) / m_nums_bw_up100_now;
	}



	CCIVRAngleData mCCIVRAngleData ;
	mCCIVRAngleData.strStockCode = pCStockCCIData->strStockCode;

	mCCIVRAngleData.f_max_cci_value = f_max_cci_value;
	
	mCCIVRAngleData.m_max_cci_num = m_max_cci_num;


	mCCIVRAngleData.f_max_cci_value_after_up_100 = f_max_cci_value_after_up_100;
	mCCIVRAngleData.m_max_cci_value_after_up_100_num = m_max_cci_value_after_up_100_num;


	mCCIVRAngleData.m_cci_up_100_num = m_cci_up_100_num;

	mCCIVRAngleData.m_cci_down_100_num = m_cci_down_100_num;

	mCCIVRAngleData.f_now_cci_value = f_now_cci_value;

	mCCIVRAngleData.f_max_cci_index_cr_value = f_max_cci_index_cr_value;

	mCCIVRAngleData.f_cci_up_100_index_cr_value = f_cci_up_100_index_cr_value;

	mCCIVRAngleData.f_cci_down_100_index_cr_value = f_cci_down_100_index_cr_value;
	
	mCCIVRAngleData.f_vr_per_increase_bw_up100_max = f_vr_per_increase_bw_up100_max;
	mCCIVRAngleData.m_nums_bw_up100_max = m_nums_bw_up100_max;
	mCCIVRAngleData.f_vr_per_increase_bw_up100_now = f_vr_per_increase_bw_up100_now;
	mCCIVRAngleData.m_nums_bw_up100_now = m_nums_bw_up100_now;


	SAFE_DELETE(pCStockCCIData);

	return mCCIVRAngleData;
}