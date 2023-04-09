// DlgCalcRiskLevel.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MyStock.h"
#include "DlgCalcRiskLevel.h"
#include "afxdialogex.h"
#include "StockDataMgr.h"
#include "Convert.h"

// CDlgCalcRiskLevel �Ի���

IMPLEMENT_DYNAMIC(CDlgCalcRiskLevel, CDialogEx)

CDlgCalcRiskLevel::CDlgCalcRiskLevel(CString strCode,CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgCalcRiskLevel::IDD, pParent)
{
	strStockCode=strCode;
	pStockDayTable=NULL;
	bAutoCalcPrePoint=TRUE;
}

CDlgCalcRiskLevel::~CDlgCalcRiskLevel()
{
}

void CDlgCalcRiskLevel::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DATETIMEPICKER_PARA_0, mRef0DateTimeCtrl);
	DDX_Control(pDX, IDC_DATETIMEPICKER_PARA_100, mRef100DateTimeCtrl);
	DDX_Control(pDX, IDC_DATETIMEPICKER_HIGH, mHighDateTimeCtrl);
	DDX_Control(pDX, IDC_DATETIMEPICKER_LOW, mLowDateTimeCtrl);
	DDX_Control(pDX, IDC_EDIT_Y_BASE, mEditYAxisBase);
	DDX_Control(pDX, IDC_EDIT_X_BASE, mEditXAxisBase);
	DDX_Control(pDX, IDC_EDIT_RESULT, mEditResult);
	DDX_Control(pDX, IDC_DATETIMEPICKER_CALC, mCalcDateTimeCtrl);
	DDX_Control(pDX, IDC_EDIT_INCREASE, mEditIncrease);
	DDX_Control(pDX, IDC_DATETIMEPICKER_PREPOINT, mPrePointDataTimeCtrl);
	DDX_Control(pDX, IDC_CHECK_AUTO_CALC_PREPOINT, mCheckAutoCalcPrePoint);
	DDX_Control(pDX, IDC_EDIT_ROL_ADJ_RATE, mEditRolAdjRate);
	DDX_Control(pDX, IDC_SPIN_ROL_ADJ_ROTE, mSpinRolAdjRate);
}


BEGIN_MESSAGE_MAP(CDlgCalcRiskLevel, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_CALC, &CDlgCalcRiskLevel::OnBnClickedBtnCalc)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_ROL_ADJ_ROTE, &CDlgCalcRiskLevel::OnDeltaposSpinRolAdjRote)
END_MESSAGE_MAP()


// CDlgCalcRiskLevel ��Ϣ�������


BOOL CDlgCalcRiskLevel::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	pStockDayTable=StockDataMgr()->GetStockDayTable(strStockCode);

	if(!pStockDayTable)
		return FALSE;

	f_sh_exp_axis_para=3062.74;
	
	CString strStockName=StockDataMgr()->GetStockName(strStockCode);
	CString strInfo;
	strInfo.Format("%s  %s",strStockName,strStockCode);
	GetDlgItem(IDC_STATIC_STOCK)->SetWindowText(strInfo);

	strRef0Date="2014/03/12";
	strRef100Date="2015/06/12";

	CTime mRef0Date=ConverStringToCTime(strRef0Date);
	CTime mRef100Date=ConverStringToCTime(strRef100Date);
	mRef0DateTimeCtrl.SetTime(&mRef0Date);
	mRef100DateTimeCtrl.SetTime(&mRef100Date);


	

	strHighDate="2018/01/29";
	strLowDate="2018/02/09";

	CTime mHighDate=ConverStringToCTime(strHighDate);
	CTime mLowDate=ConverStringToCTime(strLowDate);
	mHighDateTimeCtrl.SetTime(&mHighDate);
	mLowDateTimeCtrl.SetTime(&mLowDate);


	f_y_axis_base=0.2598;
	f_x_axis_base=2.1;
	f_role_adjust_rate=2.0;
	
	strInfo.Format("%.4f",f_y_axis_base);
	mEditYAxisBase.SetWindowText(strInfo);

	strInfo.Format("%.4f",f_x_axis_base);
	mEditXAxisBase.SetWindowText(strInfo);

	strInfo.Format("%.2f",f_role_adjust_rate);
	mEditRolAdjRate.SetWindowText(strInfo);


	if(bAutoCalcPrePoint)
	{
		strPrePointDate=CalcPrePointDate();
		CTime mPrePointDate=ConverStringToCTime(strPrePointDate);
		mPrePointDataTimeCtrl.SetTime(&mPrePointDate);
		mCheckAutoCalcPrePoint.SetCheck(BST_CHECKED);

	}
	
	//mEditPrePointDate.SetWindowText(strPrePointDate);

	strCalcDate=pStockDayTable->GetLastStockDate();
	
	CTime mCalcDate=ConverStringToCTime(strCalcDate);
	mCalcDateTimeCtrl.SetTime(&mCalcDate);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

//����ǰ������
CString CDlgCalcRiskLevel::CalcPrePointDate(void)
{
	int mHighPos=pStockDayTable->GetStockDayIndex(strHighDate);
	int mLowPos=pStockDayTable->GetStockDayIndex(strLowDate);

	if(mHighPos==-1 || mLowPos==-1)
	{
		return "";
	}

	if(mHighPos>=mLowPos)
	{
		return "";
	}

	if((mLowPos-mHighPos)<5)
	{
		return "";
	}
	Vec_StockDayData vecStockDayData;
	vecStockDayData=pStockDayTable->GetStockDayDataList();

	float f_min_val=vecStockDayData[mLowPos]->GetMinPrice();
	int mPrePointPos=-1;
	for(int i=mHighPos;i>=0;i--)
	{
		float f_val=vecStockDayData[i]->GetMinPrice();

		if(f_val<f_min_val)
		{
			mPrePointPos=i;
			break;
		}
	}

	if(mPrePointPos==-1)
		return "";

	return vecStockDayData[mPrePointPos]->GetDate();
}




BOOL  CDlgCalcRiskLevel::doCalcResult(void)
{

	int mRef0Pos=pStockDayTable->GetStockDayIndex(strRef0Date);
	int mRef100Pos=pStockDayTable->GetStockDayIndex(strRef100Date);

	if(mRef0Pos==-1 || mRef100Pos==-1)
	{
		AfxMessageBox("�ο���0��ο���100�����ڲ����ڹ�Ʊ����");
		return FALSE;
	}

	int mHighPos=pStockDayTable->GetStockDayIndex(strHighDate);
	int mLowPos=pStockDayTable->GetStockDayIndex(strLowDate);

	if(mHighPos==-1 || mLowPos==-1)
	{
		AfxMessageBox("�ߵ��͵�����ڲ����ڹ�Ʊ����");
		return FALSE;
	}

	if(mHighPos>=mLowPos)
	{
		AfxMessageBox("��֧�ָߵ��ڵ͵��ĸ�ʽ");
		return FALSE;
	}

	if((mLowPos-mHighPos)<5)
	{
		AfxMessageBox("�ߵ�͵�����������5��������");
		return FALSE;
	}

	int mCalcPos=pStockDayTable->GetStockDayIndex(strCalcDate);
	if(mCalcPos==-1)
	{
		AfxMessageBox("���������ڲ����ڹ�Ʊ����");
		return FALSE;
	}
	
	if((mCalcPos-mLowPos)<1)
	{
		AfxMessageBox("�����͵�����������1��������");
		return FALSE;
	}

	CStockDayData *pHighStockDayData=NULL;
	CStockDayData *pLowStockDayData=NULL;
	pHighStockDayData=pStockDayTable->GetStockDayDataByIndex(mHighPos);
	pLowStockDayData=pStockDayTable->GetStockDayDataByIndex(mLowPos);

	if(pHighStockDayData->GetEndPrice()<=pLowStockDayData->GetEndPrice())
	{
		AfxMessageBox("�ߵ�͵�۸񲻷��ϸߵ�,�ߵ��,�͵��");
		return FALSE;
	}

	
	
	if(strPrePointDate=="")
	{
		AfxMessageBox("�޷������ǰ������");
		return FALSE;
	}

	CStockDayData *pCalcStockDayData=NULL;
	pCalcStockDayData=pStockDayTable->GetStockDayDataByIndex(mCalcPos);


	int mPrePointPos=pStockDayTable->GetStockDayIndex(strPrePointDate);
	CStockDayData *pPrePointStockDayData=NULL;
	pPrePointStockDayData=pStockDayTable->GetStockDayDataByIndex(mPrePointPos);

	if(mHighPos-mPrePointPos<100)
	{
		CString strTemp;
		strTemp.Format("�ߵ��ǰ�����%d�������գ�С��100�����ܻ᲻����׼���Ƿ������",mHighPos-mPrePointPos);
		int result=AfxMessageBox(strTemp , MB_YESNO);
		if (IDNO == result )
		{
			return FALSE;
		}
	}

	

	Vec_StockDayData vecStockDayData;
	vecStockDayData=pStockDayTable->GetStockDayDataList();

	if((vecStockDayData.size()-mHighPos-1) > (mHighPos-mPrePointPos) )
	{
		CString strTemp;
		strTemp.Format("�ߵ㵽�����Ľ�����������ǰ�㵽�ߵ�Ľ��������������ƫ��,�Ƿ����������");
		int result=AfxMessageBox(strTemp , MB_YESNO);
		if (IDNO == result )
		{
			return FALSE;
		}
	}


	float f_max_val=-1.0;
	int mMaxPos=0;
	CStockDayData *pStockDayData=NULL;
	for(int i=mPrePointPos;i<=mHighPos;i++)
	{
		pStockDayData=vecStockDayData[i];
		if(!pStockDayData)
			continue;
		if(pStockDayData->GetMaxPrice()>=f_max_val)
		{
			f_max_val=pStockDayData->GetMaxPrice();
			mMaxPos=i;
		}

	}

	if(mMaxPos!=mHighPos)
	{
		pStockDayData=vecStockDayData[mMaxPos];
		CString strMaxValDate=pStockDayData->GetDate();
		CString strTemp;
		strTemp.Format("��ǰ�㵽�ߵ�Ľ������е���߼۸��ڸߵ㣬��%s,�Ƿ������",strMaxValDate);
		int result=AfxMessageBox(strTemp , MB_YESNO);
		if (IDNO == result )
		{
			return FALSE;
		}
	}


	float f_min_val=99999999.0;
	
	int mMinPos=0;
	for(int i=mHighPos;i<=mLowPos;i++)
	{
		pStockDayData=vecStockDayData[i];
		if(!pStockDayData)
			continue;
		if(pStockDayData->GetMinPrice()<f_min_val)
		{
			f_min_val=pStockDayData->GetMinPrice();
			mMinPos=i;
		}

	}

	if(mMinPos!=mLowPos)
	{
		pStockDayData=vecStockDayData[mMinPos];
		CString strMinValDate=pStockDayData->GetDate();
		CString strTemp;
		strTemp.Format("�Ӹߵ㵽�͵�Ľ������е͵�۸�����ͼ۸�,��͵���%s",strMinValDate);
		AfxMessageBox(strTemp);
		return FALSE;
	}

	f_min_val=99999999.0;
	mMinPos=0;
	pStockDayData=NULL;
	for(int i=mLowPos;i<vecStockDayData.size();i++)
	{
		pStockDayData=vecStockDayData[i];
		if(!pStockDayData)
			continue;
		if(pStockDayData->GetMinPrice()<f_min_val)
		{
			f_min_val=pStockDayData->GetMinPrice();
			mMinPos=i;
		}
	}

	if(mMinPos!=mLowPos)
	{
		int result=AfxMessageBox("�͵㵽������н����ռ۸���ڵ͵�۸񣬻�Ӱ�������Ƿ������" , MB_YESNO);
		if (IDNO == result )
		{
			return FALSE;
		}
	}


	f_axis_para=f_sh_exp_axis_para/pLowStockDayData->GetMinPrice();

	f_x_axis_base=f_x_axis_base*f_axis_para;
	f_y_axis_base=f_y_axis_base*f_axis_para;
	CString strInfo;
	strInfo.Format("%.4f",f_x_axis_base);
	mEditXAxisBase.SetWindowText(strInfo);
	strInfo.Format("%.4f",f_y_axis_base);
	mEditYAxisBase.SetWindowText(strInfo);


	float f_x_width=(mLowPos-mHighPos)+1;
	f_x_width=f_x_width*f_x_axis_base;

	float f_y_height=pHighStockDayData->GetMaxPrice()-pLowStockDayData->GetMinPrice();
	f_y_height=f_y_height*f_y_axis_base;

	//�ұ߽ǵ�cosֵ
	double f_right_rol_cos=f_x_width/sqrt(f_x_width*f_x_width+f_y_height*f_y_height);
	//�ұ߽ǵĶ���
	double f_right_rol_degree=(180.0/3.1415926)*acos(f_right_rol_cos);

	//ǰ�㵽��ߵ���
	float f_pre_x_width=(mHighPos-mPrePointPos)*f_x_axis_base;
	//��߽ǵ�cosֵ
	double f_left_rol_cos=f_pre_x_width/sqrt(f_pre_x_width*f_pre_x_width+f_y_height*f_y_height);
	//��߽ǵĶ���
	double f_left_rol_degree=(180.0/3.1415926)*acos(f_left_rol_cos);


	CStockDayData *pRef0StockDayData=NULL;
	CStockDayData *pRef100StockDayData=NULL;
	pRef0StockDayData=pStockDayTable->GetStockDayDataByIndex(mRef0Pos);
	pRef100StockDayData=pStockDayTable->GetStockDayDataByIndex(mRef100Pos);

	float f_ref0_min_val=pRef0StockDayData->GetMinPrice();
	float f_ref100_max_val=pRef100StockDayData->GetMaxPrice();

	float f_low_min_val=pLowStockDayData->GetMinPrice();
	float f_hight_max_val=pHighStockDayData->GetMaxPrice();

	float f_prepoint_min_val=pPrePointStockDayData->GetMinPrice();

	//ǰ��Σ�ն�
	double f_prepoint_danger_val=(f_prepoint_min_val-f_ref0_min_val)*100.0/(f_ref100_max_val-f_ref0_min_val);

	//�ߵ�Σ�ն�
	double f_high_danger_val=(f_hight_max_val-f_ref0_min_val)*100.0/(f_ref100_max_val-f_ref0_min_val);
	f_high_danger_val+=f_left_rol_degree;
	
	
	strInfo.Format("ǰ��Σ�ն� %.2f  , �ߵ�Σ�ն� %.2f",f_prepoint_danger_val,f_high_danger_val);
	GetDlgItem(IDC_STATIC_PARA_INFO)->SetWindowText(strInfo);
	double f_low_danger_val=f_high_danger_val-f_right_rol_degree;
	double f_adjust_para=f_right_rol_degree/f_high_danger_val;
	//�����
	float f_clac_x_width=(mCalcPos-mLowPos)+1;
	f_clac_x_width=f_clac_x_width*f_x_axis_base;
	float f_calc_y_height=pCalcStockDayData->GetMaxPrice()-pLowStockDayData->GetMinPrice();
	f_calc_y_height=f_calc_y_height*f_y_axis_base;
	//�������߽ǵ�cosֵ
	double f_calc_left_rol_cos=f_clac_x_width/sqrt(f_clac_x_width*f_clac_x_width+f_calc_y_height*f_calc_y_height);
	double f_calc_left_rol_degree=(180.0/3.1415926)*acos(f_calc_left_rol_cos);

	float f_calc_max_val=pCalcStockDayData->GetMaxPrice();
	
	double f_calc_danger_val=(f_calc_max_val-f_ref0_min_val)*100.0/(f_ref100_max_val-f_ref0_min_val);

	double f_muls_digree=f_calc_left_rol_degree/f_left_rol_degree;

	double f_muls_pow_para=pow(f_role_adjust_rate,f_muls_digree);		//2

	double f_calc_left_degree_effect=( (double)(mCalcPos-mLowPos+1)/ (double)( mHighPos-mPrePointPos+1) )*f_muls_pow_para;

	f_calc_left_degree_effect=f_calc_left_degree_effect*f_calc_left_rol_degree;

	f_calc_danger_val+=f_calc_left_degree_effect;

	/*if(f_adjust_para>=1.0)
	{
		f_adjust_para=(f_adjust_para-1.0)/f_muls_digree+1.0;
	}
	else
	{
		f_adjust_para=1.0-(1.0-f_adjust_para)/f_muls_digree;
	}

	f_calc_danger_val=f_calc_danger_val*f_adjust_para;
	*/
	
	strInfo.Format("%.2f",f_calc_danger_val);

	mEditResult.SetWindowText(strInfo);

	float f_esti_temp=(f_hight_max_val-f_low_min_val)*100.0/f_hight_max_val;
	f_esti_temp=f_esti_temp/(mLowPos-mHighPos);

	float f_esti_increase=(f_high_danger_val-f_calc_danger_val)/(f_high_danger_val-f_prepoint_danger_val)*f_esti_temp;


	strInfo.Format("�ٷ�֮%.2f",f_esti_increase);

	mEditIncrease.SetWindowText(strInfo);

	return TRUE;
}

//����
void CDlgCalcRiskLevel::OnBnClickedBtnCalc()
{

	if(mCheckAutoCalcPrePoint.GetCheck()==BST_CHECKED)
	{
		bAutoCalcPrePoint=TRUE;
	}
	else
		bAutoCalcPrePoint=FALSE;

	CTime mRef0Date,mRef100Date;
	mRef0DateTimeCtrl.GetTime(mRef0Date);
	mRef100DateTimeCtrl.GetTime(mRef100Date);

	strRef0Date=ConverCTimeToString(mRef0Date);
	strRef100Date=ConverCTimeToString(mRef100Date);

	CTime mHighDate,mLowDate;
	mHighDateTimeCtrl.GetTime(mHighDate);
	mLowDateTimeCtrl.GetTime(mLowDate);

	strHighDate=ConverCTimeToString(mHighDate);
	strLowDate=ConverCTimeToString(mLowDate);


	if(!bAutoCalcPrePoint)
	{
		CTime mPrePointDate;
		mPrePointDataTimeCtrl.GetTime(mPrePointDate);
		strPrePointDate=ConverCTimeToString(mPrePointDate);
	}
	else
	{
		strPrePointDate=CalcPrePointDate();
		CTime mPrePointDate=ConverStringToCTime(strPrePointDate);
		mPrePointDataTimeCtrl.SetTime(&mPrePointDate);

	}

	CTime mCalcDate;
	mCalcDateTimeCtrl.GetTime(mCalcDate);
	strCalcDate=ConverCTimeToString(mCalcDate);





	/*CString strInfo;
	mEditYAxisBase.GetWindowText(strInfo);

	float f_val=atof((LPCSTR)strInfo);

	if(f_val<=0.0)
	{
		AfxMessageBox("Y������������");
		return;
	}
	f_y_axis_base=f_val;
	mEditXAxisBase.GetWindowText(strInfo);
	f_val=atof((LPCSTR)strInfo);

	if(f_val<=0.0)
	{
		AfxMessageBox("X������������");
		return;
	}
	f_x_axis_base=f_val;
	*/

	f_y_axis_base=0.2598;
	f_x_axis_base=2.1;

	doCalcResult();
}


void CDlgCalcRiskLevel::OnDeltaposSpinRolAdjRote(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	
	if(pNMUpDown->iDelta>0)  //Down
	{
		f_role_adjust_rate-=0.1;
		
		if(f_role_adjust_rate<0.2)
			f_role_adjust_rate=0.2;

		CString strInfo;
		strInfo.Format("%.2f",f_role_adjust_rate);
		mEditRolAdjRate.SetWindowText(strInfo);
	}

	if(pNMUpDown->iDelta<0)  //Up
	{
		
		f_role_adjust_rate+=0.1;

		CString strInfo;
		strInfo.Format("%.2f",f_role_adjust_rate);
		mEditRolAdjRate.SetWindowText(strInfo);
	}


	*pResult = 0;
}
