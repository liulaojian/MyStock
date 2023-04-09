#include "stdafx.h"
#include "KLineDataBean.h"
#include "CommonMacro.h"
#include "Convert.h"
#include "StockDataMgr.h"

CKLineDataBean::CKLineDataBean()
{

}

CKLineDataBean::~CKLineDataBean()
{

}



//将股票日数据转换为 K线基础数据 strDate 是 日期，mNums日期 向前mNums个 （包括strDate)
KLineBaseData * CKLineDataBean::ConvStockDayDataToArithmeticBaseData(CStockDayTable *pStockDayTable,CString strDate,int mNums)
{
	KLineBaseData * pKLineBaseData=NULL;

	int mLastPos=pStockDayTable->GetStockDayIndex(strDate);

	if(mLastPos==-1)
		return NULL;

	if(mLastPos<mNums)
		return NULL;
	int mBeginPos=(mLastPos-mNums)+1;
	Vec_StockDayData vecStockDayData;
	vecStockDayData=pStockDayTable->GetStockDayDataList();
	CStockDayData *pStockDayData=NULL;
	pKLineBaseData =new KLineBaseData();
	pKLineBaseData->m_length=mNums;
	pKLineBaseData->m_type=K_LINE_DAY;

	for(int i=mBeginPos;i<=mLastPos;i++)
	{
		pStockDayData=vecStockDayData[i];
		pKLineBaseData->vec_open_price.push_back(pStockDayData->GetBeginPrice());
		pKLineBaseData->vec_high_price.push_back(pStockDayData->GetMaxPrice());
		pKLineBaseData->vec_low_price.push_back(pStockDayData->GetMinPrice());
		pKLineBaseData->vec_close_price.push_back(pStockDayData->GetEndPrice());
		double f_avg_val=(pStockDayData->GetMaxPrice()+pStockDayData->GetMinPrice()+pStockDayData->GetEndPrice())/3.0;
		pKLineBaseData->vec_avg_price.push_back(f_avg_val);
		CTime time=ConverStringToCTime(pStockDayData->GetDate());
		long m_time=time.GetTime();
		pKLineBaseData->vec_time.push_back(m_time);
		pKLineBaseData->vec_volume.push_back(pStockDayData->GetTotalVolume());
		pKLineBaseData->vec_volume_price.push_back(pStockDayData->GetTotalPrice());

	}

	return pKLineBaseData;
}


//将股票5分钟数据转换为 K线基础数据(5分钟) strDate 是 日期，mNums日期 向前mNums个 （包括strDate)
KLineBaseData * CKLineDataBean::ConvStockDayDataToArithmeticBaseDataMin5(CStockMin5Table *pStockMin5Table,CString strDateTime,int mNums)
{
	KLineBaseData * pKLineBaseData=NULL;

	int mLastPos=pStockMin5Table->GetStockMin5Index(strDateTime);
	if(mLastPos==-1)
		return NULL;

	if(mLastPos<mNums)
		return NULL;
	int mBeginPos=(mLastPos-mNums)+1;

	Vec_StockMin5Data vecStockMin5Data;
	CStockMin5Data *pStockMin5Data=NULL;
	
	pStockMin5Table->LockData();
	vecStockMin5Data=pStockMin5Table->GetStockMin5DataList();
	pStockMin5Table->UnlockData();

	pKLineBaseData =new KLineBaseData();
	pKLineBaseData->m_length=mNums;
	pKLineBaseData->m_type=K_LINE_5IN;


	pStockMin5Table->LockData();
	for(int i=mBeginPos;i<=mLastPos;i++)
	{
		pStockMin5Data=vecStockMin5Data[i];
		ASSERT(pStockMin5Data!=NULL);
		pKLineBaseData->vec_open_price.push_back(pStockMin5Data->GetBeginPrice());
		pKLineBaseData->vec_high_price.push_back(pStockMin5Data->GetMaxPrice());
		pKLineBaseData->vec_low_price.push_back(pStockMin5Data->GetMinPrice());
		pKLineBaseData->vec_close_price.push_back(pStockMin5Data->GetEndPrice());
		double f_avg_val=(pStockMin5Data->GetMaxPrice()+pStockMin5Data->GetMinPrice()+pStockMin5Data->GetEndPrice())/3.0;
		pKLineBaseData->vec_avg_price.push_back(f_avg_val);
		
		CString strTempDateTime=pStockMin5Data->GetDate();
		strTempDateTime+=" ";
		strTempDateTime+=pStockMin5Data->GetTime();
		CTime time=ConverDateTimeStringToCTime(strTempDateTime);
		long m_time=time.GetTime();
		pKLineBaseData->vec_time.push_back(m_time);
		pKLineBaseData->vec_volume.push_back(pStockMin5Data->GetTotalVolume());
		pKLineBaseData->vec_volume_price.push_back(pStockMin5Data->GetTotalPrice());
	}
	pStockMin5Table->UnlockData();
	return pKLineBaseData;
}


//将股票倍数5分钟数据转换为 K线基础数据(倍数分钟) strDate 是 日期，mNums日期 向前mNums个倍数分钟数据（5分钟的N倍) （包括strDate)
KLineBaseData * CKLineDataBean::ConvStockDayDataToArithmeticBaseDataMulMin5(CStockMin5Table *pStockMin5Table,CString strDateTime,int mNums,int mPerNums,int mType)
//KLineBaseData * CKLineDataBean::ConvStockDayDataToArithmeticBaseDataMin60(CStockMin5Table *pStockMin5Table,CString strDateTime,int mNums)
{

	/*
	KLineBaseData * pKLineBaseData=NULL;

	


	int mLastPos=pStockMin5Table->GetStockMin5Index(strDateTime);
	if(mLastPos==-1)
		return NULL;

	if(mLastPos<mNums*mPerNums)
		return NULL;
	
	int mBeginPos=(mLastPos-mNums*mPerNums)+1;

	Vec_StockMin5Data vecStockMin5Data;
	CStockMin5Data *pStockMin5Data=NULL;
	vecStockMin5Data=pStockMin5Table->GetStockMin5DataList();

	pKLineBaseData =new KLineBaseData();
	pKLineBaseData->m_length=mNums;
	pKLineBaseData->m_type=mType;


	for(int i=mBeginPos;i<=mLastPos;i+=mPerNums)
	{
		//ASSERT(pStockMin5Data!=NULL);
		
		double f_end_val,f_begin_val,f_max_val=-1.0,f_min_val=99999999.0,f_avg_val=0.0;
		f_end_val=vecStockMin5Data[i+mPerNums-1]->GetEndPrice();
		f_begin_val=vecStockMin5Data[i]->GetBeginPrice();

		CString strTempDateTime=vecStockMin5Data[i+mPerNums-1]->GetDate();
		strTempDateTime+=" ";
		strTempDateTime+=vecStockMin5Data[i+mPerNums-1]->GetTime();
		CTime time=ConverDateTimeStringToCTime(strTempDateTime);
		long m_time=time.GetTime();

		long m_volume=0;
		double f_volume_price=0.0;
		for(int j=0;j<mPerNums;j++)
		{
			pStockMin5Data=vecStockMin5Data[i+j];
			if(f_max_val<pStockMin5Data->GetMaxPrice())
				f_max_val=pStockMin5Data->GetMaxPrice();

			if(f_min_val>pStockMin5Data->GetMinPrice())
				f_min_val=pStockMin5Data->GetMinPrice();
			m_volume+=pStockMin5Data->GetTotalVolume();
			f_volume_price+=pStockMin5Data->GetTotalPrice();
			
		}
		
		f_avg_val=(f_max_val+f_min_val+f_end_val)/3.0;
		pKLineBaseData->vec_open_price.push_back(f_begin_val);
		pKLineBaseData->vec_high_price.push_back(f_max_val);
		pKLineBaseData->vec_low_price.push_back(f_min_val);
		pKLineBaseData->vec_close_price.push_back(f_end_val);
		pKLineBaseData->vec_avg_price.push_back(f_avg_val);

		pKLineBaseData->vec_time.push_back(m_time);
		pKLineBaseData->vec_volume.push_back(m_volume);
		pKLineBaseData->vec_volume_price.push_back(f_volume_price);

		
	}

	return pKLineBaseData;*/


	CString strTime="";
	CString strDate="";
	CStringArray arryVal;
	StringSplit(strDateTime,arryVal,' ');
	if(arryVal.GetSize()==2)
	{
		strDate=arryVal.GetAt(0);
		strTime=arryVal.GetAt(1);
	}
	else
		return NULL;

	

	CString strTemp=strTime.Left(2);
	int mHour=atoi((LPCSTR)strTemp);
	strTemp=strTime.Right(2);
	int mMin=atoi((LPCSTR)strTemp);

	 
	
	int  mKLineMin;

	if(mType==K_LINE_5IN)
		mKLineMin=5;
	else if(mType==K_LINE_15IN)
		mKLineMin=15;
	else if(mType==K_LINE_30IN)
		mKLineMin=30;
	else if(mType==K_LINE_60MIN)
		mKLineMin=60;


	int mTotalMin;

	if(mHour>=9 && mHour<=11)
	{
		mTotalMin=mHour*60+mMin-(9*60+30);

	}
	else
	{
		mTotalMin=(mHour-13)*60+mMin+120;
	}

	if(mTotalMin<0)
		return NULL;

	int mSubMin=mTotalMin%mKLineMin;

	int mMainMin=(mTotalMin/mKLineMin)*mKLineMin;


	int mNewNums=mNums;
	if(mSubMin>0)
		mNewNums--;
	CString strNewTime;
	
	if(mMainMin==0)
	{
		strDate=StockDataMgr()->GetExpPreDayDateByDateTime(strDateTime);
		strNewTime="1500";
	}
	else if(mMainMin<=120)
	{
		int mTMin=9*60+30+mMainMin;

		int mH=mTMin/60;
		int mM=mTMin%60;
		strNewTime.Format("%02d%02d",mH,mM);
	}
	else
	{
		int mTMin=13*60+(mMainMin-120);

		int mH=mTMin/60;
		int mM=mTMin%60;
		strNewTime.Format("%02d%02d",mH,mM);

	}
	
	CString strNewDateTime;
	strNewDateTime=strDate;

	strNewDateTime=strDate;
	strNewDateTime+=" ";
	strNewDateTime+=strNewTime;
	

	KLineBaseData * pKLineBaseData=NULL;

	


	int mNewLastPos;

	mNewLastPos=pStockMin5Table->GetStockMin5Index(strNewDateTime);
	if(mNewLastPos==-1)
	{
		return NULL;
	}
	if(mNewLastPos<mNewNums*mPerNums)
		return NULL;

	int mBeginPos=(mNewLastPos-mNewNums*mPerNums)+1;

	Vec_StockMin5Data vecStockMin5Data;
	CStockMin5Data *pStockMin5Data=NULL;
	pStockMin5Table->LockData();
	vecStockMin5Data=pStockMin5Table->GetStockMin5DataList();
	pStockMin5Table->UnlockData();
	pKLineBaseData =new KLineBaseData();
	pKLineBaseData->m_length=mNewNums;
	pKLineBaseData->m_type=K_LINE_30IN;

	pStockMin5Table->LockData();
	for(int i=mBeginPos;i<=mNewLastPos;i+=mPerNums)
	{
		//ASSERT(pStockMin5Data!=NULL);

		double f_end_val,f_begin_val,f_max_val=-1.0,f_min_val=99999999.0,f_avg_val=0.0;
		f_end_val=vecStockMin5Data[i+mPerNums-1]->GetEndPrice();
		f_begin_val=vecStockMin5Data[i]->GetBeginPrice();

		CString strTempDateTime=vecStockMin5Data[i+mPerNums-1]->GetDate();
		strTempDateTime+=" ";
		strTempDateTime+=vecStockMin5Data[i+mPerNums-1]->GetTime();
		CTime time=ConverDateTimeStringToCTime(strTempDateTime);
		long m_time=time.GetTime();

		long m_volume=0;
		double f_volume_price=0.0;
		for(int j=0;j<mPerNums;j++)
		{
			pStockMin5Data=vecStockMin5Data[i+j];
			if(f_max_val<pStockMin5Data->GetMaxPrice())
				f_max_val=pStockMin5Data->GetMaxPrice();

			if(f_min_val>pStockMin5Data->GetMinPrice())
				f_min_val=pStockMin5Data->GetMinPrice();
			m_volume+=pStockMin5Data->GetTotalVolume();
			f_volume_price+=pStockMin5Data->GetTotalPrice();

		}

		f_avg_val=(f_max_val+f_min_val+f_end_val)/3.0;
		pKLineBaseData->vec_open_price.push_back(f_begin_val);
		pKLineBaseData->vec_high_price.push_back(f_max_val);
		pKLineBaseData->vec_low_price.push_back(f_min_val);
		pKLineBaseData->vec_close_price.push_back(f_end_val);
		pKLineBaseData->vec_avg_price.push_back(f_avg_val);

		pKLineBaseData->vec_time.push_back(m_time);
		pKLineBaseData->vec_volume.push_back(m_volume);
		pKLineBaseData->vec_volume_price.push_back(f_volume_price);


	}

	int mLastPos=pStockMin5Table->GetStockMin5Index(strDateTime);

	if(mLastPos>mNewLastPos)
	{
		int mStep=(mLastPos-mNewLastPos);
		for(int i=mNewLastPos+1;i<=mLastPos;i+=mStep)
		{
			double f_end_val,f_begin_val,f_max_val=-1.0,f_min_val=99999999.0,f_avg_val=0.0;
			f_end_val=vecStockMin5Data[i+mStep-1]->GetEndPrice();
			f_begin_val=vecStockMin5Data[i]->GetBeginPrice();

			CString strTempDateTime=vecStockMin5Data[i+mStep-1]->GetDate();
			strTempDateTime+=" ";
			strTempDateTime+=vecStockMin5Data[i+mStep-1]->GetTime();
			CTime time=ConverDateTimeStringToCTime(strTempDateTime);
			long m_time=time.GetTime();

			long m_volume=0;
			double f_volume_price=0.0;
			for(int j=0;j<mStep;j++)
			{
				pStockMin5Data=vecStockMin5Data[i+j];
				if(f_max_val<pStockMin5Data->GetMaxPrice())
					f_max_val=pStockMin5Data->GetMaxPrice();

				if(f_min_val>pStockMin5Data->GetMinPrice())
					f_min_val=pStockMin5Data->GetMinPrice();
				m_volume+=pStockMin5Data->GetTotalVolume();
				f_volume_price+=pStockMin5Data->GetTotalPrice();

			}

			f_avg_val=(f_max_val+f_min_val+f_end_val)/3.0;
			pKLineBaseData->vec_open_price.push_back(f_begin_val);
			pKLineBaseData->vec_high_price.push_back(f_max_val);
			pKLineBaseData->vec_low_price.push_back(f_min_val);
			pKLineBaseData->vec_close_price.push_back(f_end_val);
			pKLineBaseData->vec_avg_price.push_back(f_avg_val);

			pKLineBaseData->vec_time.push_back(m_time);
			pKLineBaseData->vec_volume.push_back(m_volume);
			pKLineBaseData->vec_volume_price.push_back(f_volume_price);
		}

		pKLineBaseData->m_length++;
	}
	pStockMin5Table->UnlockData();
	return pKLineBaseData;
}



//将股票15分钟数据转换为 K线基础数据(15分钟) strDate 是 日期，mNums日期 向前mNums个 （5分钟的3倍)（包括strDate)
KLineBaseData *  CKLineDataBean::ConvStockDayDataToArithmeticBaseDataMin15(CStockMin5Table *pStockMin5Table,CString strDateTime,int mNums)
{
	return ConvStockDayDataToArithmeticBaseDataMulMin5(pStockMin5Table,strDateTime,mNums,3,K_LINE_15IN);
}

//将股票30分钟数据转换为 K线基础数据(30分钟) strDate 是 日期，mNums日期 向前mNums个 （5分钟的6倍)（包括strDate)
KLineBaseData * CKLineDataBean::ConvStockDayDataToArithmeticBaseDataMin30(CStockMin5Table *pStockMin5Table,CString strDateTime,int mNums)
{

	/*
	CString strTime="";
	CString strDate="";
	CStringArray arryVal;
	StringSplit(strDateTime,arryVal,' ');
	if(arryVal.GetSize()==2)
	{
		strDate=arryVal.GetAt(0);
		strTime=arryVal.GetAt(1);
	}
	else
		return NULL;

	CString strTemp=strTime.Left(2);
	int mHour=atoi((LPCSTR)strTemp);
	strTemp=strTime.Right(2);
	int mMin=atoi((LPCSTR)strTemp);

	int mSubMin=mMin%30;

	int mNewNums=mNums;
	if(mSubMin>0)
		mNewNums--;


	int m30MinNums=mMin/30;

	CString strNewTime;
	strNewTime.Format("%02d%02d",mHour,m30MinNums*30);
	CString strNewDateTime;
	strNewDateTime=strDate;
	strNewDateTime+=" ";
	strNewDateTime+=strNewTime;

	int  mPerNums=6;

	KLineBaseData * pKLineBaseData=NULL;

	int mNewLastPos=pStockMin5Table->GetStockMin5Index(strNewDateTime);
	if(mNewLastPos==-1)
		return NULL;

	if(mNewLastPos<mNewNums*mPerNums)
		return NULL;

	int mBeginPos=(mNewLastPos-mNewNums*mPerNums)+1;

	Vec_StockMin5Data vecStockMin5Data;
	CStockMin5Data *pStockMin5Data=NULL;
	vecStockMin5Data=pStockMin5Table->GetStockMin5DataList();

	pKLineBaseData =new KLineBaseData();
	pKLineBaseData->m_length=mNewNums;
	pKLineBaseData->m_type=K_LINE_30IN;


	for(int i=mBeginPos;i<=mNewLastPos;i+=mPerNums)
	{
		//ASSERT(pStockMin5Data!=NULL);

		double f_end_val,f_begin_val,f_max_val=-1.0,f_min_val=99999999.0,f_avg_val=0.0;
		f_end_val=vecStockMin5Data[i+mPerNums-1]->GetEndPrice();
		f_begin_val=vecStockMin5Data[i]->GetBeginPrice();

		CString strTempDateTime=vecStockMin5Data[i+mPerNums-1]->GetDate();
		strTempDateTime+=" ";
		strTempDateTime+=vecStockMin5Data[i+mPerNums-1]->GetTime();
		CTime time=ConverDateTimeStringToCTime(strTempDateTime);
		long m_time=time.GetTime();

		long m_volume=0;
		double f_volume_price=0.0;
		for(int j=0;j<mPerNums;j++)
		{
			pStockMin5Data=vecStockMin5Data[i+j];
			if(f_max_val<pStockMin5Data->GetMaxPrice())
				f_max_val=pStockMin5Data->GetMaxPrice();

			if(f_min_val>pStockMin5Data->GetMinPrice())
				f_min_val=pStockMin5Data->GetMinPrice();
			m_volume+=pStockMin5Data->GetTotalVolume();
			f_volume_price+=pStockMin5Data->GetTotalPrice();

		}

		f_avg_val=(f_max_val+f_min_val+f_end_val)/3.0;
		pKLineBaseData->vec_open_price.push_back(f_begin_val);
		pKLineBaseData->vec_high_price.push_back(f_max_val);
		pKLineBaseData->vec_low_price.push_back(f_min_val);
		pKLineBaseData->vec_close_price.push_back(f_end_val);
		pKLineBaseData->vec_avg_price.push_back(f_avg_val);

		pKLineBaseData->vec_time.push_back(m_time);
		pKLineBaseData->vec_volume.push_back(m_volume);
		pKLineBaseData->vec_volume_price.push_back(f_volume_price);


	}

	int mLastPos=pStockMin5Table->GetStockMin5Index(strDateTime);

	if(mLastPos>mNewLastPos)
	{
		int mStep=(mLastPos-mNewLastPos);
		for(int i=mNewLastPos+1;i<=mLastPos;i+=mStep)
		{
			double f_end_val,f_begin_val,f_max_val=-1.0,f_min_val=99999999.0,f_avg_val=0.0;
			f_end_val=vecStockMin5Data[i+mStep-1]->GetEndPrice();
			f_begin_val=vecStockMin5Data[i]->GetBeginPrice();

			CString strTempDateTime=vecStockMin5Data[i+mStep-1]->GetDate();
			strTempDateTime+=" ";
			strTempDateTime+=vecStockMin5Data[i+mStep-1]->GetTime();
			CTime time=ConverDateTimeStringToCTime(strTempDateTime);
			long m_time=time.GetTime();

			long m_volume=0;
			double f_volume_price=0.0;
			for(int j=0;j<mStep;j++)
			{
				pStockMin5Data=vecStockMin5Data[i+j];
				if(f_max_val<pStockMin5Data->GetMaxPrice())
					f_max_val=pStockMin5Data->GetMaxPrice();

				if(f_min_val>pStockMin5Data->GetMinPrice())
					f_min_val=pStockMin5Data->GetMinPrice();
				m_volume+=pStockMin5Data->GetTotalVolume();
				f_volume_price+=pStockMin5Data->GetTotalPrice();

			}

			f_avg_val=(f_max_val+f_min_val+f_end_val)/3.0;
			pKLineBaseData->vec_open_price.push_back(f_begin_val);
			pKLineBaseData->vec_high_price.push_back(f_max_val);
			pKLineBaseData->vec_low_price.push_back(f_min_val);
			pKLineBaseData->vec_close_price.push_back(f_end_val);
			pKLineBaseData->vec_avg_price.push_back(f_avg_val);

			pKLineBaseData->vec_time.push_back(m_time);
			pKLineBaseData->vec_volume.push_back(m_volume);
			pKLineBaseData->vec_volume_price.push_back(f_volume_price);
		}

		pKLineBaseData->m_length++;
	}

	return pKLineBaseData;
	*/
	return ConvStockDayDataToArithmeticBaseDataMulMin5(pStockMin5Table,strDateTime,mNums,6,K_LINE_30IN);
}

//将股票30分钟数据转换为 K线基础数据(60分钟) strDate 是 日期，mNums日期 向前mNums个 （5分钟的12倍)（包括strDate)
KLineBaseData * CKLineDataBean::ConvStockDayDataToArithmeticBaseDataMin60(CStockMin5Table *pStockMin5Table,CString strDateTime,int mNums)
{
	return ConvStockDayDataToArithmeticBaseDataMulMin5(pStockMin5Table,strDateTime,mNums,12,K_LINE_60MIN);
}



//最后的值要根据日期修正（主要是 最后的日期不是 15 30 60 这样的整的
double CKLineDataBean::CalcDateTimeCorrect(CString strDateTime,int mType,std::vector<double> vec_value)
{

	int length=vec_value.size();

	if(mType==K_LINE_DAY)
	{

		return vec_value[length-1];
	}
	else if(mType==K_LINE_5IN)
	{
		return vec_value[length-1];

	}

	CString strTime="";
	CString strDate="";
	CStringArray arryVal;
	StringSplit(strDateTime,arryVal,' ');
	if(arryVal.GetSize()==2)
	{
		strDate=arryVal.GetAt(0);
		strTime=arryVal.GetAt(1);
	}
	else
		return vec_value[length-1];

	CString strTemp=strTime.Left(2);
	int mHour=atoi((LPCSTR)strTemp);
	strTemp=strTime.Right(2);
	int mMin=atoi((LPCSTR)strTemp);

	int mSubMin;

	double f_val=vec_value[length-1];
	if(mType==K_LINE_15IN)
	{
		mSubMin=mMin%15;
		double f_mul_para=mSubMin/15.0;
		if(mSubMin==0)
			f_val=vec_value[length-1];
		else
			f_val=(vec_value[length-1]-vec_value[length-2])*f_mul_para+vec_value[length-2];

	}
	else if(mType==K_LINE_30IN)
	{
		mSubMin=mMin%30;
		double f_mul_para=mSubMin/30.0;

		if(mSubMin==0)
			f_val=vec_value[length-1];
		else
			f_val=(vec_value[length-1]-vec_value[length-2])*f_mul_para+vec_value[length-2];
	}
	else if(mType==K_LINE_60MIN)
	{
		mSubMin=mMin%60;
		double f_mul_para=mSubMin/60.0;
		if(mSubMin==0)
			f_val=vec_value[length-1];
		else
			f_val=(vec_value[length-1]-vec_value[length-2])*f_mul_para+vec_value[length-2];
	}

	return f_val;
}



//计算能量值
BOOL CKLineDataBean::CalcPowerValue(std::vector<double> vec_close,std::vector<double> vec_volume_price,int mN,double & f_power_val)
{
	if(vec_close.size()!=vec_volume_price.size())
		return FALSE;

	int mLength=vec_close.size();
	if(mLength<(mN+1))
		return FALSE;

	double f_total_sale_val=0.0;

	for(int i=mLength-mN;i<mLength;i++)
	{
		double f_range;
		double f_now_val=vec_close[i];
		double f_pre_val=vec_close[i-1];
		f_range=(f_now_val-f_pre_val)/f_pre_val;
		f_range=f_range/2.0;
		if(f_range<0.0)
		{
			double f_sale_val=vec_volume_price[i]*f_range;
			f_total_sale_val+=f_sale_val;
		}
	}

	double f_total_buy_val=0.0;

	for(int i=mLength-mN;i<mLength;i++)
	{
		double f_range;
		double f_now_val=vec_close[i];
		double f_pre_val=vec_close[i-1];
		f_range=(f_now_val-f_pre_val)/f_pre_val;
		f_range=f_range/2.0;
		if(f_range>=0.0)
		{
			double f_buy_val=vec_volume_price[i]*f_range;
			f_total_buy_val+=f_buy_val;
		}
	}

	if(f_total_buy_val>=abs(f_total_sale_val))
	{
		f_power_val=(f_total_buy_val+f_total_sale_val)*100.0/f_total_buy_val;
	}
	else
	{
		f_power_val=(f_total_sale_val+f_total_buy_val)*100.0/abs(f_total_sale_val);
	}
	return TRUE;
}