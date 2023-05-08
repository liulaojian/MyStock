#include "stdafx.h"
#include "CCIVRAngle.h"
#include  "StockCCIArithmetic.h"
#include "CommonMacro.h"
#include "Convert.h"
CCIVRAngle::CCIVRAngle()
{

}


CCIVRAngle::~CCIVRAngle()
{

}



CCIVRAngleData2 CCIVRAngle::CalcCCIVRAngle2(CString strStockCode, CString strDate, std::vector<float>& vec_vr, int m_prenum)
{
	CCIVRAngleData2 mCCIVRAngleData;

	CStockCCIData* pCStockCCIData = CStockCCIArithmetic::CalcCCIData(strStockCode, strDate, 125, K_LINE_DAY, 14);

	int m_cci_size = pCStockCCIData->vec_cci_value.size();

	int m_vr_size = vec_vr.size();

	float f_max_cci_value = -99999.0;
	int m_max_cci_num = -1;
	long m_max_cci_time = 0;
	int m_max_cci_index = -1;
	for (int i = m_cci_size - m_prenum; i < m_cci_size; i++)
	{
		if (pCStockCCIData->vec_cci_value[i] > f_max_cci_value)
		{
			f_max_cci_value = pCStockCCIData->vec_cci_value[i];
			m_max_cci_time = pCStockCCIData->vec_time[i];
			m_max_cci_num = m_cci_size - i;
			m_max_cci_index = i;
		}
	}

	float f_max_cci_vr_value=vec_vr[m_vr_size - m_max_cci_num];
	

	CciVrUnit mMaxUnit;
	mMaxUnit.f_cci_value = f_max_cci_value;
	mMaxUnit.f_vr_value = f_max_cci_vr_value;
	mMaxUnit.m_cci_num = m_max_cci_num;
	mMaxUnit.m_cci_time = m_max_cci_time;
	mMaxUnit.m_mode = 2;

	if (f_max_cci_value < 100.0)
	{
		CString strInfo = "CCI���ֵС��100.0,��������";
		mCCIVRAngleData.vecInfo.push_back(strInfo);
		SAFE_DELETE(pCStockCCIData);
		return mCCIVRAngleData;
	}
	else
	{
		
		CTime time(m_max_cci_time);
		CString strDate= ConverCTimeToString(time);

		CString strInfo;
		strInfo.Format("CCI���ֵ %.2f  %s  ���%d��  VRֵ %.2f", f_max_cci_value, (LPCSTR)strDate, m_max_cci_num, f_max_cci_vr_value);
		mCCIVRAngleData.vecInfo.push_back(strInfo);
	}

	float f_now_cci_value= pCStockCCIData->vec_cci_value[m_cci_size-1];
	int m_now_cci_num = 1;
	long m_now_cci_time = pCStockCCIData->vec_time[m_cci_size - 1];
	float f_now_vr_value= vec_vr[m_vr_size - 1];

	CciVrUnit mNowUnit;
	mNowUnit.f_cci_value = f_now_cci_value;
	mNowUnit.f_vr_value = f_now_vr_value;
	mNowUnit.m_cci_num = m_now_cci_num;
	mNowUnit.m_cci_time = m_now_cci_time;
	mNowUnit.m_mode = 3;
	CString strInfo;
	strInfo.Format("��ǰCCIֵ %.2f  VRֵ %.2f", f_now_cci_value, f_now_vr_value);
	mCCIVRAngleData.vecInfo.push_back(strInfo);


	float f_cci_up100_premax_value = 0.0;
	int m_cci_up100_premax_num = -1;
	long m_cci_up100_premax_time = 0;
	int m_cci_up100_premax_index = -1;
	float f_cci_up100_premax_vr_value = 0.0;

	for (int i = m_max_cci_index; i >= m_cci_size - m_prenum; i--)
	{
		float nowvalue = pCStockCCIData->vec_cci_value[i];
		float prevalue = pCStockCCIData->vec_cci_value[i - 1];
		if (prevalue < 100.0 && nowvalue>100.0)
		{
			m_cci_up100_premax_index = i;
			m_cci_up100_premax_num= m_cci_size - i;

			f_cci_up100_premax_value = pCStockCCIData->vec_cci_value[i];
			m_cci_up100_premax_time = pCStockCCIData->vec_time[i];

			break;
		}

	}

	CciVrUnit mCCiUp100BefMaxUnit;
	if (m_cci_up100_premax_num < 0)
	{
		CString strInfo;
		strInfo.Format("���CCIֵ֮ǰû��CCI�ϴ�100����");
		mCCIVRAngleData.vecInfo.push_back(strInfo);
	}
	else
	{
		f_cci_up100_premax_vr_value = vec_vr[m_vr_size - m_cci_up100_premax_num];
		
		mCCiUp100BefMaxUnit.f_cci_value = f_cci_up100_premax_value;
		mCCiUp100BefMaxUnit.f_vr_value = f_cci_up100_premax_vr_value;
		mCCiUp100BefMaxUnit.m_cci_num = m_cci_up100_premax_num;
		mCCiUp100BefMaxUnit.m_cci_time = m_cci_up100_premax_time;
		mCCiUp100BefMaxUnit.m_mode = 0;

		CTime time(m_cci_up100_premax_time);
		CString strDate = ConverCTimeToString(time);


		CString strInfo;
		strInfo.Format("CCI���ֵǰ�ϴ�100ʱ��CCIֵ %.2f  %s  ���%d��  VRֵ %.2f", f_cci_up100_premax_value, 
			(LPCSTR)strDate, m_cci_up100_premax_num, f_cci_up100_premax_vr_value);
		mCCIVRAngleData.vecInfo.push_back(strInfo);
	}

	for (int i = m_max_cci_index; i < m_cci_size ; i++)
	{
		float nowvalue = pCStockCCIData->vec_cci_value[i];
		float prevalue = pCStockCCIData->vec_cci_value[i - 1];

		if (prevalue < 100.0 && nowvalue>100.0)		//�ϴ�
		{

			CciVrUnit mCciVrUnit;
			mCciVrUnit.f_cci_value= pCStockCCIData->vec_cci_value[i];
			mCciVrUnit.m_cci_num= m_cci_size - i;
			mCciVrUnit.m_cci_time= pCStockCCIData->vec_time[i];
			mCciVrUnit.f_vr_value= vec_vr[m_vr_size - mCciVrUnit.m_cci_num];
			mCciVrUnit.m_mode = 0;
			mCCIVRAngleData.vecUpDown100AftMaxUnit.push_back(mCciVrUnit);

			CTime time(mCciVrUnit.m_cci_time);
			CString strDate = ConverCTimeToString(time);

			CString strInfo;
			strInfo.Format("%s CCI�ϴ�100ʱCCIֵ %.2f  ���%d��  VRֵ %.2f", (LPCSTR)strDate, mCciVrUnit.f_cci_value,
				mCciVrUnit.m_cci_num, mCciVrUnit.f_vr_value);
			mCCIVRAngleData.vecInfo.push_back(strInfo);
		}
		else if (prevalue > 100.0 && nowvalue < 100.0) //�´�
		{
			CciVrUnit mCciVrUnit;
			mCciVrUnit.f_cci_value = pCStockCCIData->vec_cci_value[i];
			mCciVrUnit.m_cci_num = m_cci_size - i;
			mCciVrUnit.m_cci_time = pCStockCCIData->vec_time[i];
			mCciVrUnit.f_vr_value = vec_vr[m_vr_size - mCciVrUnit.m_cci_num];
			mCciVrUnit.m_mode = 1;
			mCCIVRAngleData.vecUpDown100AftMaxUnit.push_back(mCciVrUnit);

			CTime time(mCciVrUnit.m_cci_time);
			CString strDate = ConverCTimeToString(time);

			CString strInfo;
			strInfo.Format("%s CCI�´�100ʱCCIֵ %.2f  ���%d��  VRֵ %.2f", (LPCSTR)strDate, mCciVrUnit.f_cci_value,
				mCciVrUnit.m_cci_num, mCciVrUnit.f_vr_value);
			mCCIVRAngleData.vecInfo.push_back(strInfo);

		}


	}

	mCCIVRAngleData.strStockCode = strStockCode;
	mCCIVRAngleData.mMaxUnit = mMaxUnit;
	mCCIVRAngleData.mNowUnit = mNowUnit;
	mCCIVRAngleData.mCCiUp100BefMaxUnit = mCCiUp100BefMaxUnit;
	SAFE_DELETE(pCStockCCIData);
	return mCCIVRAngleData;
}
