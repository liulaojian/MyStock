#include "stdafx.h"
#include "CurveSinCmpMethod.h"
#include "Log.h"
#include "Convert.h"
CCurveSinCmpMethod::CCurveSinCmpMethod(): CHistoryCmpMethod("CurveSin")
{
	f_x_scale=100.0;
	f_gate_percent=80.0;
	mEquGateNums=12;
}


CCurveSinCmpMethod::~CCurveSinCmpMethod()
{

}

BOOL CCurveSinCmpMethod::CreateAimStockDayDataVec(void)
{
	if(pStockDayTable==NULL)
		return FALSE;
	if(strBeginDate=="" || strEndDate=="")
		return FALSE;


	int mBeginPos=pStockDayTable->GetNearestStockDayIndex(strBeginDate);
	int mEndPos=pStockDayTable->GetNearestStockDayIndex(strEndDate);

	if(mBeginPos==-1 || mEndPos==-1 )
		return FALSE;

	if(mBeginPos>mEndPos)
		return FALSE;
	vecAimStockDayData.clear();
	Vec_StockDayData vecStockDayData;
	vecStockDayData=pStockDayTable->GetStockDayDataList();
	CStockDayData *pStockDayData=NULL;

	for(int i=mBeginPos;i<=mEndPos;i++)
	{
		pStockDayData=vecStockDayData[i];
		vecAimStockDayData.push_back(pStockDayData);

	}

	return TRUE;
}

Vec_StockDayData CCurveSinCmpMethod::CreateHistoryStockDayVec(CString strBegin,CString strEnd)
{
	Vec_StockDayData vecOutStockDayData;

	if(pStockDayTable==NULL)
		return vecOutStockDayData;

	if(strBeginDate=="" || strEndDate=="")
		return vecOutStockDayData;

	int mBeginPos=pStockDayTable->GetNearestStockDayIndex(strBegin);
	int mEndPos=pStockDayTable->GetNearestStockDayIndex(strEnd);

	if(mBeginPos==-1 || mEndPos==-1 )
		return vecOutStockDayData;

	if(mBeginPos>mEndPos)
		return vecOutStockDayData;

	vecOutStockDayData.clear();

	Vec_StockDayData vecStockDayData;
	vecStockDayData=pStockDayTable->GetStockDayDataList();
	CStockDayData *pStockDayData=NULL;

	for(int i=mBeginPos;i<=mEndPos;i++)
	{
		pStockDayData=vecStockDayData[i];
		vecOutStockDayData.push_back(pStockDayData);

	}
	return vecOutStockDayData;
}

BOOL CCurveSinCmpMethod::CreateAimSinValVec(void)
{
	if(vecAimStockDayData.size()<=1)
		return FALSE;
	vecAimSinVal.clear();

	double fBeginVal=vecAimStockDayData[0]->GetEndPrice();


	for(int i=1;i<vecAimStockDayData.size();i++)
	{
		double fVal=vecAimStockDayData[i]->GetEndPrice()-fBeginVal;

		double x_val=f_x_scale*i;

		double f_slope=sqrt(fVal*fVal+x_val*x_val);

		double f_sin=fVal/f_slope;
		
		vecAimSinVal.push_back(f_sin);
	}
	
	return TRUE;
}

std::vector<double> CCurveSinCmpMethod::CreateHistoryStockSinValVec(Vec_StockDayData vecStockDayData)
{
	std::vector<double> vecSinVal;
	if(vecStockDayData.size()<=1)
		return vecSinVal;
	vecSinVal.clear();
	double fBeginVal=vecStockDayData[0]->GetEndPrice();
	for(int i=1;i<vecStockDayData.size();i++)
	{
		
		double fVal=vecStockDayData[i]->GetEndPrice()-fBeginVal;

		double x_val=f_x_scale*i;

		double f_slope=sqrt(fVal*fVal+x_val*x_val);

		double f_sin=fVal/f_slope;
		vecSinVal.push_back(f_sin);
	}

	return vecSinVal;
}


BOOL CCurveSinCmpMethod::JudgeSinVal(std::vector<double> vecSinVal)
{
	if(vecSinVal.size()!=vecAimSinVal.size())
		return FALSE;

	double fAimVal;
	double fVal;
	int mOkNums=0;
	for(int i=0;i<vecSinVal.size();i++)
	{
		fAimVal=vecAimSinVal[i];
		fVal=vecSinVal[i];

		if(fAimVal>=0.0 && fVal>=0.0)
		{
			double fTemp=abs(fVal-fAimVal);

			double fDif=(fTemp/fAimVal)*100.0;
			if(fDif<f_gate_percent)
				mOkNums++;
		}
		else if(fAimVal<0.0 && fVal<0.0)
		{
			double fTemp=abs(fVal-fAimVal);
			double fDif=(fTemp/abs(fAimVal))*100.0;
			if(fDif<f_gate_percent)
				mOkNums++;
		}
		else if(fAimVal<0.0 && fVal>=0.0)
		{
			double fTemp=abs(fVal-fAimVal);
			double fDif=(fTemp/abs(fAimVal))*100.0;
			if(fDif<f_gate_percent)
				mOkNums++;
		}
		else if(fAimVal>=0.0 && fVal<0.0)
		{
			double fTemp=abs(fVal-fAimVal);
			double fDif=(fTemp/fAimVal)*100.0;
			if(fDif<f_gate_percent)
				mOkNums++;
		}
	}

	if(mOkNums>=12)
		PrintfDebug("mOkNums=%d,mEquGateNums=%d\n",mOkNums,mEquGateNums);
	if(mOkNums>=mEquGateNums)	//vecSinVal.size()
		return TRUE;
	return FALSE;
}

BOOL  CCurveSinCmpMethod::ParseCmpMethodParas(void)
{
	if(pStockDayTable==NULL)
		return FALSE;
	if(strBeginDate=="" || strEndDate=="")
		return FALSE;

	int mBeginPos=pStockDayTable->GetNearestStockDayIndex(strBeginDate);
	int mEndPos=pStockDayTable->GetNearestStockDayIndex(strEndDate);

	if(mBeginPos==-1 || mEndPos==-1 )
		return FALSE;

	if(mBeginPos>mEndPos)
		return FALSE;

	CString strXScale=mapCmpMethodParas["XScale"];
	if(strXScale!="")
		f_x_scale=atof((LPCSTR)strXScale);
	else
		f_x_scale=100.0f;
	CString strGatePercent=mapCmpMethodParas["GatePercent"];
	if(strGatePercent!="")
		f_gate_percent=atof((LPCSTR)strGatePercent);
	else
		f_gate_percent=50.0f;

	CString strEquGateNums=mapCmpMethodParas["EquGateNums"];
	if(strEquGateNums!="")
		mEquGateNums=atoi((LPCSTR)strEquGateNums);
	else
		mEquGateNums=(mEndPos-mBeginPos)*3/4;


	return TRUE;
}

BOOL CCurveSinCmpMethod::Init(void)
{

	if(pStockDayTable==NULL)
		return FALSE;
	if(strBeginDate=="" || strEndDate=="")
		return FALSE;
	ParseCmpMethodParas();
	CreateAimStockDayDataVec();
	CreateAimSinValVec();

	return TRUE;
}
	

BOOL CCurveSinCmpMethod::TraverseData(void)
{
	if(pStockDayTable==NULL)
		return FALSE;
	if(strBeginDate=="" || strEndDate=="")
		return FALSE;

	int mBeginPos=pStockDayTable->GetNearestStockDayIndex(strBeginDate);
	int mEndPos=pStockDayTable->GetNearestStockDayIndex(strEndDate);

	if(mBeginPos==-1 || mEndPos==-1 )
		return FALSE;

	if(mBeginPos>mEndPos)
		return FALSE;
	
	if(vecHistoryResultList.size()>0)
		vecHistoryResultList.clear();

	int mDataNums=(mEndPos-mBeginPos)+1;

	Vec_StockDayData vecStockDayData;
	vecStockDayData=pStockDayTable->GetStockDayDataList();
	CStockDayData *pStockDayData=NULL;

	for(int i=0;i<vecStockDayData.size();i++)
	{
		if((i+mDataNums)<=vecStockDayData.size())
		{
			CString strBegin=vecStockDayData[i]->GetDate();
			CString strEnd=vecStockDayData[i+mDataNums-1]->GetDate();

			int mCmpDays=CmpTwoDate(strEnd,strEndDate);
			if(mCmpDays>0)
				break;

			Vec_StockDayData vecHistoryStockDayData;

			vecHistoryStockDayData=CreateHistoryStockDayVec(strBegin,strEnd);

			std::vector<double> vecSinVal;
			vecSinVal=CreateHistoryStockSinValVec(vecHistoryStockDayData);

			BOOL bOK1=JudgeSinVal(vecSinVal);
			if( bOK1)	
			{
				i+=mDataNums;
				HistoryResult * pHistoryResult=new HistoryResult();
				pHistoryResult->strBeginDate=strBegin;
				pHistoryResult->strEndDate=strEnd;
				PrintfDebug("%s  %s push \n",strBegin,strEnd);
				vecHistoryResultList.push_back(pHistoryResult);
			}
		}
	}

	

	return TRUE;
}