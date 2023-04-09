// DlgCalcu.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MyStock.h"
#include "DlgCalcu.h"
#include "afxdialogex.h"
#include "DlgCalcuInfo.h"
#include "CommonMacro.h"
// CDlgCalcu �Ի���

IMPLEMENT_DYNAMIC(CDlgCalcu, CDialogEx)

CDlgCalcu::CDlgCalcu(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgCalcu::IDD, pParent)
{

}

CDlgCalcu::~CDlgCalcu()
{
}

void CDlgCalcu::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_CALCU_DATA, mCaluDataListCtrl);
	DDX_Control(pDX, IDC_MENUBTN_CALCU, mMenuBtnCalcu);
}


BEGIN_MESSAGE_MAP(CDlgCalcu, CDialogEx)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BTN_DO_CALCU, &CDlgCalcu::OnBnClickedBtnDoCalcu)
	ON_BN_CLICKED(IDC_BTN_EXPORT_DATA, &CDlgCalcu::OnBnClickedBtnExportData)
	ON_COMMAND(IDR_MENU_CALCU_DATA_INFO, &CDlgCalcu::OnMenuCalcuDataInfo)
	ON_NOTIFY(NM_RCLICK, IDC_LIST_CALCU_DATA, &CDlgCalcu::OnRclickListCalcuData)
	ON_BN_CLICKED(IDC_MENUBTN_CALCU, &CDlgCalcu::OnBnClickedMenubtnCalcu)
END_MESSAGE_MAP()


// CDlgCalcu ��Ϣ�������


BOOL CDlgCalcu::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	mCaluDataListCtrl.ModifyStyle(LVS_ICON | LVS_SMALLICON | LVS_LIST, LVS_REPORT ); //���ñ�����


	mCaluDataListCtrl.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES); 

	mCaluDataListCtrl.InsertColumn( CALCUDATA_COLUMN_ID, "˳��ID��", LVCFMT_LEFT, 80 );
	mCaluDataListCtrl.InsertColumn( CALCUDATA_COLUMN_STOCK_DATETIME, "��������", LVCFMT_LEFT, 90 );

	mCaluDataListCtrl.InsertColumn( CALCUDATA_COLUMN_INFO, "������Ϣ", LVCFMT_LEFT, 200 );
	mCaluDataListCtrl.InsertColumn( CALCUDATA_COLUMN_EXP_STATUS, "ָ��״̬", LVCFMT_LEFT, 80 );
	mCaluDataListCtrl.InsertColumn( CALCUDATA_COLUMN_RESULT, "������", LVCFMT_LEFT, 300 );
	
	
	pCalcuMenu=new CMenu;
	pCalcuMenu->LoadMenu(IDR_MENU_BTN_CALCU);
	mMenuBtnCalcu.m_hMenu = pCalcuMenu->GetSubMenu(0)->GetSafeHmenu();


	SetTimer(CALCUDATAEVENT_REFRESH_DATA,300,0);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CDlgCalcu:: CopyCalcuData(Vec_CalcuData vecData)
{
	//DEBUG_TRY
	vecCalcuData.clear();

	vecCalcuData.assign(vecData.begin(),vecData.end());

	/*for(int i=0;i<vecCalcuData.size();i++)
	{
		vecCalcuData[i]->vec_exp_rsi_1_value.assign(vecData[i]->vec_exp_rsi_1_value.begin(),vecData[i]->vec_exp_rsi_1_value.end());
		vecCalcuData[i]->vec_exp_rsi_2_value.assign(vecData[i]->vec_exp_rsi_2_value.begin(),vecData[i]->vec_exp_rsi_2_value.end());
		vecCalcuData[i]->vec_exp_rsi_3_value.assign(vecData[i]->vec_exp_rsi_3_value.begin(),vecData[i]->vec_exp_rsi_3_value.end());
		vecCalcuData[i]->vecTanAngleData.assign(vecData[i]->vecTanAngleData.begin(),vecData[i]->vecTanAngleData.end());
		for(int j=0;j<vecCalcuData[i]->vecTanAngleData.size();j++)
		{
			vecCalcuData[i]->vecTanAngleData[j]->vec_rsi_1=vecData[i]->vecTanAngleData[j]->vec_rsi_1;
		}
	}*/
	//DEBUG_CATCH2("%s", __FUNCTION__);
}

BOOL CDlgCalcu::RefreshData(void)
{

	CString strConv,strTemp;
	int nRow;
	mCaluDataListCtrl.DeleteAllItems();
	int i=0;
	CalcuData *pCalcuData=NULL;
	for(i=0;i<vecCalcuData.size();i++)
	{
		pCalcuData=vecCalcuData[i];
		if(!pCalcuData)
			continue;
		strConv.Format("%4d",i+1);
		nRow=i;
		if(nRow>=mCaluDataListCtrl.GetItemCount())
			mCaluDataListCtrl.InsertItem(i,strConv);
		else
			mCaluDataListCtrl.SetItemText(nRow, CALCUDATA_COLUMN_ID,strConv);

		mCaluDataListCtrl.SetItemText(nRow, CALCUDATA_COLUMN_STOCK_DATETIME,pCalcuData->strDateTime);

		CString strInfo;
		int mUpNums=0;
		for(int j=0;j<pCalcuData->vecTanAngleData.size();j++)
		{
			if(pCalcuData->vecTanAngleData[j]->mNextGrow>0)
				mUpNums++;
		}
		strInfo.Format("�ܹ�Ʊ�� %d  �������պ��� %d",pCalcuData->vecTanAngleData.size(),mUpNums);
		mCaluDataListCtrl.SetItemText(nRow, CALCUDATA_COLUMN_INFO,strInfo);
		printf("%s\n",strInfo);
		int mExpDynamicStatus=pCalcuData->mStockExpStatus;
		switch(mExpDynamicStatus)
		{
		case CALCUDATA_EXP_STATUS_NULL:
			strInfo="��״̬";
			break;
		case CALCUDATA_EXP_STATUS_LOW:
			strInfo="��λ";
			break;

		case CALCUDATA_EXP_STATUS_SUB_LOW:
			strInfo="ƫ��";
			break;

		case CALCUDATA_EXP_STATUS_HIGH:
			strInfo="��λ";
			break;

		case CALCUDATA_EXP_STATUS_SUB_HIGH:
			strInfo="ƫ��λ";
			break;
		case CALCUDATA_EXP_STATUS_SUPER_HIGH:
			strInfo="����λ";
			break;
		case CALCUDATA_EXP_STATUS_MIDDLE:
			strInfo="��λ";
			break;
		}
		printf("%s\n",strInfo);
		mCaluDataListCtrl.SetItemText(nRow, CALCUDATA_COLUMN_EXP_STATUS,strInfo);
		mCaluDataListCtrl.SetItemText(nRow, CALCUDATA_COLUMN_RESULT,pCalcuData->strResult);
		
		mCaluDataListCtrl.SetItemData(nRow,reinterpret_cast<DWORD_PTR>(pCalcuData));
	}
	if(i<mCaluDataListCtrl.GetItemCount())
	{
		for(int j=i;j<mCaluDataListCtrl.GetItemCount();j++)
			mCaluDataListCtrl.DeleteItem(j);
	}
	return TRUE;
}


void CDlgCalcu::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if(nIDEvent==CALCUDATAEVENT_REFRESH_DATA)
	{
		KillTimer(CALCUDATAEVENT_REFRESH_DATA);
		RefreshData();
	}
	CDialogEx::OnTimer(nIDEvent);
}

//��������
void CDlgCalcu::OnBnClickedBtnDoCalcu()
{
	doCalcu();
	SetTimer(CALCUDATAEVENT_REFRESH_DATA,300,0);
}

//��������
void CDlgCalcu::OnBnClickedBtnExportData()
{
	
}

#define RSI_LOW_THRESHOLD		20.0

#define RSI_HIGH_THRESHOLD		80.0

#define RSI_HIGH_HIGH_THRESHOLD		90.0

#define RSI_SUB_HIGH_THRESHOLD		70.0

//����ָ��״̬
int CDlgCalcu::CalcExpStatus(CalcuData *pCalcuData)
{
	std::vector<double> vec_rsi_1;
	std::vector<double> vec_rsi_2;
	std::vector<double> vec_rsi_3;		
	vec_rsi_1=pCalcuData->vec_exp_rsi_1_value;
	vec_rsi_2=pCalcuData->vec_exp_rsi_2_value;
	vec_rsi_3=pCalcuData->vec_exp_rsi_3_value;

	int size=vec_rsi_1.size();


	double f_now_rsi1=vec_rsi_1[size-1];



	/*Vec_RsiData vecFirst8HightHightRsi;		//��ȥ8���ڳ���rsi����

	Vec_RsiData vecFirst8SubHightRsi;		//��ȥ8���ڴθ�rsi����

	Vec_RsiData vecFirst8HightRsi;		//��ȥ8���ڸ�rsi����

	Vec_RsiData vecFirst8LowRsi;		//��ȥ8���ڵ�rsi����

	//���ж�8�������ڣ��ж���HIGH Or Low rsi
	for(int i=size-8;i<size;i++)
	{
		if(vec_rsi_1[i]>=RSI_HIGH_HIGH_THRESHOLD)
		{
			RsiData *pRsiData=new RsiData();
			pRsiData->fRsi1=vec_rsi_1[i];
			pRsiData->mIndex=size-1-i;
			vecFirst8HightHightRsi.push_back(pRsiData);
		}

		if(vec_rsi_1[i]>=RSI_HIGH_THRESHOLD  && vec_rsi_1[i]<RSI_HIGH_HIGH_THRESHOLD)
		{
			RsiData *pRsiData=new RsiData();
			pRsiData->fRsi1=vec_rsi_1[i];
			pRsiData->mIndex=size-1-i;
			vecFirst8HightRsi.push_back(pRsiData);

		}
		if(vec_rsi_1[i]>=RSI_SUB_HIGH_THRESHOLD && vec_rsi_1[i]<RSI_HIGH_THRESHOLD)
		{
			RsiData *pRsiData=new RsiData();
			pRsiData->fRsi1=vec_rsi_1[i];
			pRsiData->mIndex=size-1-i;
			vecFirst8SubHightRsi.push_back(pRsiData);
		}

		if(vec_rsi_1[i]<=RSI_LOW_THRESHOLD)
		{
			RsiData *pRsiData=new RsiData();
			pRsiData->fRsi1=vec_rsi_1[i];
			pRsiData->mIndex=size-1-i;
			vecFirst8LowRsi.push_back(pRsiData);
		}
			
		
	}
	*/
	int mNowRsiStatus=0;

	if(f_now_rsi1<=20.0)
		mNowRsiStatus=CALCUDATA_EXP_STATUS_LOW;
	else if(f_now_rsi1>20.0&&f_now_rsi1<=30.0)
		mNowRsiStatus=CALCUDATA_EXP_STATUS_SUB_LOW;
	else if(f_now_rsi1>30.0&&f_now_rsi1<=70.0)
		mNowRsiStatus=CALCUDATA_EXP_STATUS_MIDDLE;
	else if(f_now_rsi1>70.0&&f_now_rsi1<=80.0)
		mNowRsiStatus=CALCUDATA_EXP_STATUS_SUB_HIGH;
	else if(f_now_rsi1>80.0&&f_now_rsi1<=90.0)
		mNowRsiStatus=CALCUDATA_EXP_STATUS_HIGH;
	else
		mNowRsiStatus=CALCUDATA_EXP_STATUS_SUPER_HIGH;




	return mNowRsiStatus;
}

//��������
BOOL  CDlgCalcu::doCalcu(void)
{
	int i=0;
	CalcuData *pCalcuData=NULL;
	for(i=0;i<vecCalcuData.size();i++)
	{
		pCalcuData=vecCalcuData[i];
		if(!pCalcuData)
			continue;
		int mStatus=CalcExpStatus(pCalcuData);
		pCalcuData->mStockExpStatus=mStatus;
		pCalcuData->strResult=doCalcuMethod(pCalcuData,0);
	}
	return 0;
}

//���㷽��1
CString  CDlgCalcu::doCalcuMethod(CalcuData *pCalcuData,int mMethod)
{
	TanAngleData *pTanAngleData=NULL;
	Vec_TanAngleData vecTanAngleData;
	vecTanAngleData=pCalcuData->vecTanAngleData;
	
	for(int i=0;i<vecTanAngleData.size();i++)
	{
		pTanAngleData=vecTanAngleData[i];
		if(mMethod==0)
		{
			if(doCalcuDataMethod(pTanAngleData))
			{
				pTanAngleData->mCalcuSel=1;
			}
			else
			{
				pTanAngleData->mCalcuSel=0;

			}
		}
		else if(mMethod==1)
		{
			if(doCalcuDataMethod_1(pTanAngleData))
			{
				pTanAngleData->mCalcuSel=1;
			}
			else
			{
				pTanAngleData->mCalcuSel=0;

			}

		}
		else if(mMethod==2)
		{
			if(doCalcuDataMethod_2(pTanAngleData))
			{
				pTanAngleData->mCalcuSel=1;
			}
			else
			{
				pTanAngleData->mCalcuSel=0;

			}

		}
		else if(mMethod==3)
		{
			if(doCalcuDataMethod_3(pTanAngleData))
			{
				pTanAngleData->mCalcuSel=1;
			}
			else
			{
				pTanAngleData->mCalcuSel=0;

			}

		}

	}

	for(int i=0;i<vecTanAngleData.size();i++)
	{
		pTanAngleData=vecTanAngleData[i];
		if(pTanAngleData->mCalcuSel>0)
		{
			if(pTanAngleData->mNextGrow>0)
				pTanAngleData->bCalcuOk=TRUE;
			else
				pTanAngleData->bCalcuOk=FALSE;
		}
		else
		{
			if(pTanAngleData->mNextGrow>0)
				pTanAngleData->bCalcuOk=FALSE;
			else
				pTanAngleData->bCalcuOk=TRUE;
		}
	}

	int mSelectOkNums=0;
	int mGrowNums=0;
	int mSelectNums=0;
	for(int i=0;i<vecTanAngleData.size();i++)
	{
		pTanAngleData=vecTanAngleData[i];
		if(pTanAngleData->mCalcuSel>0)
		{
			mSelectNums++;
			if(pTanAngleData->mNextGrow>0)
				mSelectOkNums++;
		}
		if(pTanAngleData->mNextGrow>0)
			mGrowNums++;
	}

	CString strResult;
	strResult.Format("���� %d,���ǵ���%d,����ѡ�����%d,����ѡ�е���%d",vecTanAngleData.size(),mGrowNums,mSelectNums,mSelectOkNums);


	return strResult;
}

/*
BOOL  CDlgCalcu::doCalcuDataMethod(TanAngleData *pTanAngleData)
{
	double f_ma5_angle=pTanAngleData->fPara0;
	double f_ma10_angle=pTanAngleData->fPara1;
	double f_ma20_angle=pTanAngleData->fPara2;
	double f_ma60_angle=pTanAngleData->fPara3;
	double f_max_volume_per=pTanAngleData->fPara4;
	double f_ave_volume_per=pTanAngleData->fPara5;
	double f_60_20_cross_price_increase=pTanAngleData->fPara6;
	double f_20_10_cross_price_increase=pTanAngleData->fPara7;
	double f_60_day_increase=pTanAngleData->fPara8;
	int m_10_big_20_nums=pTanAngleData->mPara6;
	int m_60_big_20_nums=pTanAngleData->mPara7;
	int m_continus_price_m10_up_nums=pTanAngleData->mPara8;
	int m_continus_price_m20_up_nums=pTanAngleData->mPara9;
	int m_continus_price_m60_up_nums=pTanAngleData->mPara10;
	int m_max_volume_distance=pTanAngleData->mMaxDis;
	int mContiDownNums=pTanAngleData->mContiDownNums;
	int mNowIsMaxPriceNums=pTanAngleData->mNowIsMaxPriceNums;
	int mNextGrow=pTanAngleData->mNextGrow;
	double fNextGrow=pTanAngleData->fNextGrow;
	double f_cur_rsi_1=pTanAngleData->fRsi1;
	std::vector<double> vec_rsi_1=pTanAngleData->vec_rsi_1;

	int rsi_size=vec_rsi_1.size();

	double f_max_rsi_1=0.0;
	for(int i=rsi_size-9;i<rsi_size;i++)
	{
		if(vec_rsi_1[i]>f_max_rsi_1)
		{
			f_max_rsi_1=vec_rsi_1[i];
		}

	}

	if(m_60_big_20_nums<10)
	{
		if(m_continus_price_m60_up_nums<25&&m_continus_price_m20_up_nums<25&&m_continus_price_m10_up_nums<25)
		{
			printf("f_max_rsi_1=%f\n",f_max_rsi_1);
			if(mNowIsMaxPriceNums>=115)
				return  TRUE;

		}
	}
	
	return FALSE;

#if 0
	BOOL bOk=FALSE;
	if(m_60_big_20_nums<=10)
	{
		if(m_10_big_20_nums<=15)
		{
			if(m_continus_price_m60_up_nums<25)
			{
				if(m_continus_price_m20_up_nums<20)
				{
					if(m_continus_price_m10_up_nums<20)
					{
						bOk=TRUE;
					}
				}
			}

		}

	}
	BOOL bOk2=FALSE;

	if(bOk)
	{
		if(f_ma60_angle<25.0)
		{
			if(f_ma20_angle<50.0)
				bOk2=TRUE;
		}
	}

	BOOL bOk3=FALSE;

	if(bOk2)
	{
		if(f_max_volume_per<2.0)
		{
			if(f_ave_volume_per<2.0)
			{
				if(mNowIsMaxPriceNums>115)
					bOk3=TRUE;
			}
		}

	}

	if(bOk3)
		return TRUE;


	return FALSE;
#endif

}*/

/*
BOOL  CDlgCalcu::doCalcuDataMethod(TanAngleData *pTanAngleData)
{
	double f_ma5_angle=pTanAngleData->fPara0;
	double f_ma10_angle=pTanAngleData->fPara1;
	double f_ma20_angle=pTanAngleData->fPara2;
	double f_ma60_angle=pTanAngleData->fPara3;
	double f_max_volume_per=pTanAngleData->fPara4;
	double f_ave_volume_per=pTanAngleData->fPara5;
	double f_60_20_cross_price_increase=pTanAngleData->fPara6;
	double f_20_10_cross_price_increase=pTanAngleData->fPara7;
	double f_60_day_increase=pTanAngleData->fPara8;
	int m_10_big_20_nums=pTanAngleData->mPara6;
	int m_60_big_20_nums=pTanAngleData->mPara7;
	int m_continus_price_m10_up_nums=pTanAngleData->mPara8;
	int m_continus_price_m20_up_nums=pTanAngleData->mPara9;
	int m_continus_price_m60_up_nums=pTanAngleData->mPara10;
	int m_max_volume_distance=pTanAngleData->mMaxDis;
	int mContiDownNums=pTanAngleData->mContiDownNums;
	int mNowIsMaxPriceNums=pTanAngleData->mNowIsMaxPriceNums;
	int mNextGrow=pTanAngleData->mNextGrow;
	double fNextGrow=pTanAngleData->fNextGrow;
	double f_cur_rsi_1=pTanAngleData->fRsi1;
	std::vector<double> vec_rsi_1=pTanAngleData->vec_rsi_1;

	int rsi_size=vec_rsi_1.size();

	double f_max_rsi_1=0.0;
	for(int i=rsi_size-9;i<rsi_size;i++)
	{
		if(vec_rsi_1[i]>f_max_rsi_1)
		{
			f_max_rsi_1=vec_rsi_1[i];
		}

	}

	double f_max_up=0.0;
	if(f_60_20_cross_price_increase>f_20_10_cross_price_increase)
		f_max_up=f_60_20_cross_price_increase;
	else
		f_max_up=f_20_10_cross_price_increase;

	if(f_ave_volume_per>10.0&&f_max_volume_per<4.0)
	{
		if(f_max_up<30.0)
			return TRUE;
	}

	return FALSE;
}
*/

BOOL  CDlgCalcu::doCalcuDataMethod(TanAngleData *pTanAngleData)
{

	double f_ma5_angle=pTanAngleData->fPara0;
	double f_ma10_angle=pTanAngleData->fPara1;
	double f_ma20_angle=pTanAngleData->fPara2;
	double f_ma60_angle=pTanAngleData->fPara3;
	double f_max_volume_per=pTanAngleData->fPara4;
	double f_ave_volume_per=pTanAngleData->fPara5;
	double f_60_20_cross_price_increase=pTanAngleData->fPara6;
	double f_20_10_cross_price_increase=pTanAngleData->fPara7;
	double f_60_day_increase=pTanAngleData->fPara8;
	int m_10_big_20_nums=pTanAngleData->mPara6;
	int m_60_big_20_nums=pTanAngleData->mPara7;
	int m_continus_price_m10_up_nums=pTanAngleData->mPara8;
	int m_continus_price_m20_up_nums=pTanAngleData->mPara9;
	int m_continus_price_m60_up_nums=pTanAngleData->mPara10;
	int m_max_volume_distance=pTanAngleData->mMaxDis;
	int mContiDownNums=pTanAngleData->mContiDownNums;
	int mNowIsMaxPriceNums=pTanAngleData->mNowIsMaxPriceNums;
	int mNextGrow=pTanAngleData->mNextGrow;
	double fNextGrow=pTanAngleData->fNextGrow;
	double f_cur_rsi_1=pTanAngleData->fRsi1;
	std::vector<double> vec_rsi_1=pTanAngleData->vec_rsi_1;

	
	if(f_ma60_angle>40.0)
		return FALSE;

	double f_m10_m20_angle_per=fabs(f_ma10_angle-f_ma20_angle)*100.0/f_ma20_angle;

	double f_m5_m10_angle_per=fabs(f_ma5_angle-f_ma10_angle)*100.0/f_ma10_angle;

	if(f_m10_m20_angle_per<15.0 && f_m5_m10_angle_per<20.0)
		return TRUE;

	return FALSE;
}

//�Ҽ��˵���ϸ��Ϣ
void CDlgCalcu::OnMenuCalcuDataInfo()
{
	CalcuData *pCalcuData=NULL;
	for(uint16  i=0; i<mCaluDataListCtrl.GetItemCount(); i++)
	{
		if( mCaluDataListCtrl.GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED )
		{
			pCalcuData=reinterpret_cast<CalcuData *>(mCaluDataListCtrl.GetItemData(i));
			break;
		}
	}

	if(!pCalcuData)
		return;
	CDlgCalcuInfo dlg;
	dlg.SetCalcuData(pCalcuData);
	dlg.DoModal();
}


void CDlgCalcu::OnRclickListCalcuData(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	if(pNMItemActivate->iItem != -1)
	{
		DWORD dwPos = GetMessagePos();
		CPoint point( LOWORD(dwPos), HIWORD(dwPos) );
		CMenu menu;
		VERIFY( menu.LoadMenu( IDR_MENU_CALCU ) );
		CMenu* popup = menu.GetSubMenu(0);
		ASSERT( popup != NULL );
		popup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this );

	}
	*pResult = 0;
}

//����˵�
void CDlgCalcu::OnBnClickedMenubtnCalcu()
{
	int mMethod=0;
	if(mMenuBtnCalcu.m_nMenuResult == ID_MENU_BTN_CALCU_1)
		mMethod=1;
	else if(mMenuBtnCalcu.m_nMenuResult == ID_MENU_BTN_CALCU_2)
		mMethod=2;
	else if(mMenuBtnCalcu.m_nMenuResult == ID_MENU_BTN_CALCU_3)
		mMethod=3;
	int i=0;
	CalcuData *pCalcuData=NULL;
	for(i=0;i<vecCalcuData.size();i++)
	{
		pCalcuData=vecCalcuData[i];
		if(!pCalcuData)
			continue;
		int mStatus=CalcExpStatus(pCalcuData);
		pCalcuData->mStockExpStatus=mStatus;
		pCalcuData->strResult=doCalcuMethod(pCalcuData,mMethod);
	}

	SetTimer(CALCUDATAEVENT_REFRESH_DATA,300,0);
}

BOOL  CDlgCalcu::doCalcuDataMethod_1(TanAngleData *pTanAngleData)
{
	double f_ma5_angle=pTanAngleData->fPara0;
	double f_ma10_angle=pTanAngleData->fPara1;
	double f_ma20_angle=pTanAngleData->fPara2;
	double f_ma60_angle=pTanAngleData->fPara3;
	double f_max_volume_per=pTanAngleData->fPara4;
	double f_ave_volume_per=pTanAngleData->fPara5;
	double f_60_20_cross_price_increase=pTanAngleData->fPara6;
	double f_20_10_cross_price_increase=pTanAngleData->fPara7;
	double f_60_day_increase=pTanAngleData->fPara8;
	int m_10_big_20_nums=pTanAngleData->mPara6;
	int m_60_big_20_nums=pTanAngleData->mPara7;
	int m_continus_price_m10_up_nums=pTanAngleData->mPara8;
	int m_continus_price_m20_up_nums=pTanAngleData->mPara9;
	int m_continus_price_m60_up_nums=pTanAngleData->mPara10;
	int m_max_volume_distance=pTanAngleData->mMaxDis;
	int mContiDownNums=pTanAngleData->mContiDownNums;
	int mNowIsMaxPriceNums=pTanAngleData->mNowIsMaxPriceNums;
	int mNextGrow=pTanAngleData->mNextGrow;
	double fNextGrow=pTanAngleData->fNextGrow;
	double f_cur_rsi_1=pTanAngleData->fRsi1;
	std::vector<double> vec_rsi_1=pTanAngleData->vec_rsi_1;


	if(f_ma60_angle>20.0)
		return FALSE;
	if(f_ma20_angle>35.0)
		return FALSE;
	if(f_ma10_angle>50.0)
		return FALSE;
	if(f_ma5_angle>50.0)
		return FALSE;

	double f_max_per=0.0;
	if(f_60_20_cross_price_increase>f_20_10_cross_price_increase)
		f_max_per=f_60_20_cross_price_increase;
	else
		f_max_per=f_20_10_cross_price_increase;

	if(f_max_per>14.0)
		return FALSE;

	if(m_continus_price_m60_up_nums>20||m_continus_price_m60_up_nums<10)
		return FALSE;

	if(m_continus_price_m20_up_nums>20||m_continus_price_m20_up_nums<10)
		return FALSE;
	
	if(m_continus_price_m10_up_nums>20||m_continus_price_m10_up_nums<10)
		return FALSE;


	return TRUE;


}


BOOL  CDlgCalcu::doCalcuDataMethod_2(TanAngleData *pTanAngleData)
{
	double f_ma5_angle=pTanAngleData->fPara0;
	double f_ma10_angle=pTanAngleData->fPara1;
	double f_ma20_angle=pTanAngleData->fPara2;
	double f_ma60_angle=pTanAngleData->fPara3;
	double f_max_volume_per=pTanAngleData->fPara4;
	double f_ave_volume_per=pTanAngleData->fPara5;
	double f_60_20_cross_price_increase=pTanAngleData->fPara6;
	double f_20_10_cross_price_increase=pTanAngleData->fPara7;
	double f_60_day_increase=pTanAngleData->fPara8;
	int m_10_big_20_nums=pTanAngleData->mPara6;
	int m_60_big_20_nums=pTanAngleData->mPara7;
	int m_continus_price_m10_up_nums=pTanAngleData->mPara8;
	int m_continus_price_m20_up_nums=pTanAngleData->mPara9;
	int m_continus_price_m60_up_nums=pTanAngleData->mPara10;
	int m_max_volume_distance=pTanAngleData->mMaxDis;
	int mContiDownNums=pTanAngleData->mContiDownNums;
	int mNowIsMaxPriceNums=pTanAngleData->mNowIsMaxPriceNums;
	int mNextGrow=pTanAngleData->mNextGrow;
	double fNextGrow=pTanAngleData->fNextGrow;
	double f_cur_rsi_1=pTanAngleData->fRsi1;
	std::vector<double> vec_rsi_1=pTanAngleData->vec_rsi_1;


	

	if(f_ma60_angle>35.0)
		return FALSE;
	if(f_cur_rsi_1<50.0)
		return FALSE;

	double f_max_angle=f_ma60_angle;
	if(f_ma20_angle>f_max_angle)
		f_max_angle=f_ma20_angle;

	if(f_ma10_angle>f_max_angle)
		f_max_angle=f_ma10_angle;

	if(f_ma5_angle>f_max_angle)
		f_max_angle=f_ma5_angle;

	if(f_max_angle<30.0)
		return FALSE;

	double f_max_up=f_60_20_cross_price_increase;
	if(f_max_up<f_20_10_cross_price_increase)
		f_max_up=f_20_10_cross_price_increase;
	if(f_max_up<12.0)
		return FALSE;

	double f_20_60_angle_per=f_ma20_angle/f_ma60_angle;
	if(f_20_60_angle_per>2.5||f_20_60_angle_per<1.3)
		return FALSE;

	double f_10_20_angle_per=f_ma10_angle/f_ma20_angle;

	if(f_10_20_angle_per<0.9||f_10_20_angle_per>1.2)
		return FALSE;

	double f_5_10_angle_per=f_ma5_angle/f_ma10_angle;
	if(f_5_10_angle_per<0.9||f_5_10_angle_per>1.2)
		return FALSE;
	return TRUE;
}


BOOL  CDlgCalcu::doCalcuDataMethod_3(TanAngleData *pTanAngleData)
{
	double f_ma5_angle=pTanAngleData->fPara0;
	double f_ma10_angle=pTanAngleData->fPara1;
	double f_ma20_angle=pTanAngleData->fPara2;
	double f_ma60_angle=pTanAngleData->fPara3;
	double f_max_volume_per=pTanAngleData->fPara4;
	double f_ave_volume_per=pTanAngleData->fPara5;
	double f_60_20_cross_price_increase=pTanAngleData->fPara6;
	double f_20_10_cross_price_increase=pTanAngleData->fPara7;
	double f_60_day_increase=pTanAngleData->fPara8;
	int m_10_big_20_nums=pTanAngleData->mPara6;
	int m_60_big_20_nums=pTanAngleData->mPara7;
	int m_continus_price_m10_up_nums=pTanAngleData->mPara8;
	int m_continus_price_m20_up_nums=pTanAngleData->mPara9;
	int m_continus_price_m60_up_nums=pTanAngleData->mPara10;
	int m_max_volume_distance=pTanAngleData->mMaxDis;
	int mContiDownNums=pTanAngleData->mContiDownNums;
	int mNowIsMaxPriceNums=pTanAngleData->mNowIsMaxPriceNums;
	int mNextGrow=pTanAngleData->mNextGrow;
	int mBigIncreaseNums=pTanAngleData->mBigIncreaseNums;
	int mRsi1BigNums=pTanAngleData->mRsi1BigNums;
	double fNextGrow=pTanAngleData->fNextGrow;
	double f_cur_rsi_1=pTanAngleData->fRsi1;
	std::vector<double> vec_rsi_1=pTanAngleData->vec_rsi_1;
	std::vector<double>  vec_close_value=pTanAngleData->vec_close_value;
	std::vector<double>  vec_high_value=pTanAngleData->vec_high_value;
	std::vector<double>  vec_low_value=pTanAngleData->vec_low_value;
	std::vector<double> vec_price_m5=pTanAngleData->vec_price_m5;
	std::vector<double> vec_price_m10=pTanAngleData->vec_price_m10;


	double f_max_angle=0.0;

	if(f_ma60_angle>f_max_angle)
		f_max_angle=f_ma60_angle;
	if(f_ma20_angle>f_max_angle)
		f_max_angle=f_ma20_angle;
	if(f_ma10_angle>f_max_angle)
		f_max_angle=f_ma10_angle;
	if(f_ma5_angle>f_max_angle)
		f_max_angle=f_ma5_angle;

	if(f_max_angle<45.0)
		return FALSE;
	if(mBigIncreaseNums<1)
		return FALSE;

	
	return TRUE;

}