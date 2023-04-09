// DlgIndustryInfo.cpp: 实现文件
//

#include "stdafx.h"
#include "MyStock.h"
#include "DlgIndustryInfo.h"
#include "afxdialogex.h"
#include "TanAngleAlg.h"
#include "StockKDJArithmetic.h"
#include "StockRSIArithmetic.h"
#include "resource.h"
#include "Convert.h"
#include "CommonMacro.h"
#include "Global.h"
#include "StockKDJArithmetic.h"
#include "IndustryDataMgr.h"
// CDlgIndustryInfo 对话框

IMPLEMENT_DYNAMIC(CDlgIndustryInfo, CDialogEx)

CDlgIndustryInfo::CDlgIndustryInfo(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DLG_INDUSTRY_INFO, pParent)
{

}

CDlgIndustryInfo::~CDlgIndustryInfo()
{
}

void CDlgIndustryInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CMB_PERIOD, mCmbPeriod);
	DDX_Control(pDX, IDC_CMB_PER_LOW, mCmbPerLow);
	DDX_Control(pDX, IDC_CMB_PER_HIGH, mCmbPerHigh);
	DDX_Control(pDX, IDC_CMB_INDUSTRY, mCmbIndustry);
}


BEGIN_MESSAGE_MAP(CDlgIndustryInfo, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_FIND, &CDlgIndustryInfo::OnBnClickedBtnFind)
	ON_BN_CLICKED(IDC_BTN_SHOW, &CDlgIndustryInfo::OnBnClickedBtnShow)
	ON_BN_CLICKED(IDC_BTN_FIND2, &CDlgIndustryInfo::OnBnClickedBtnFind2)
	ON_BN_CLICKED(IDC_BTN_FIND3, &CDlgIndustryInfo::OnBnClickedBtnFind3)
END_MESSAGE_MAP()


// CDlgIndustryInfo 消息处理程序


BOOL CDlgIndustryInfo::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	mCmbPeriod.ResetContent();

	int ret = mCmbPeriod.AddString("5交易日");
	mCmbPeriod.SetItemData(ret, 5);
	
	ret = mCmbPeriod.AddString("10交易日");
	mCmbPeriod.SetItemData(ret, 10);

	ret = mCmbPeriod.AddString("15交易日");
	mCmbPeriod.SetItemData(ret, 15);

	ret = mCmbPeriod.AddString("20交易日");
	mCmbPeriod.SetItemData(ret, 20);

	ret = mCmbPeriod.AddString("25交易日");
	mCmbPeriod.SetItemData(ret, 25);

	ret = mCmbPeriod.AddString("30交易日");
	mCmbPeriod.SetItemData(ret, 30);


	ret = mCmbPeriod.AddString("35交易日");
	mCmbPeriod.SetItemData(ret, 35);

	ret = mCmbPeriod.AddString("40交易日");
	mCmbPeriod.SetItemData(ret, 40);


	mCmbPeriod.SetCurSel(2);



	mCmbPerLow.ResetContent();

	ret = mCmbPerLow.AddString("0%");
	mCmbPerLow.SetItemData(ret, 0);

	ret = mCmbPerLow.AddString("2%");
	mCmbPerLow.SetItemData(ret, 2);

	ret = mCmbPerLow.AddString("5%");
	mCmbPerLow.SetItemData(ret, 5);

	ret = mCmbPerLow.AddString("10%");
	mCmbPerLow.SetItemData(ret, 10);

	ret = mCmbPerLow.AddString("15%");
	mCmbPerLow.SetItemData(ret, 15);

	ret = mCmbPerLow.AddString("20%");
	mCmbPerLow.SetItemData(ret, 20);

	ret = mCmbPerLow.AddString("25%");
	mCmbPerLow.SetItemData(ret, 25);

	mCmbPerLow.SetCurSel(0);


	mCmbPerHigh.ResetContent();

	ret = mCmbPerHigh.AddString("5%");
	mCmbPerHigh.SetItemData(ret, 5);


	ret = mCmbPerHigh.AddString("8%");
	mCmbPerHigh.SetItemData(ret, 8);
	
	ret = mCmbPerHigh.AddString("10%");
	mCmbPerHigh.SetItemData(ret, 10);

	ret = mCmbPerHigh.AddString("15%");
	mCmbPerHigh.SetItemData(ret, 15);

	ret = mCmbPerHigh.AddString("20%");
	mCmbPerHigh.SetItemData(ret, 20);


	ret = mCmbPerHigh.AddString("25%");
	mCmbPerHigh.SetItemData(ret, 25);

	ret = mCmbPerHigh.AddString("30%");
	mCmbPerHigh.SetItemData(ret, 30);

	ret = mCmbPerHigh.AddString("40%");
	mCmbPerHigh.SetItemData(ret, 40);

	ret = mCmbPerHigh.AddString("50%");
	mCmbPerHigh.SetItemData(ret, 50);

	ret = mCmbPerHigh.AddString("70%");
	mCmbPerHigh.SetItemData(ret, 70);

	ret = mCmbPerHigh.AddString("90%");
	mCmbPerHigh.SetItemData(ret, 90);


	mCmbPerHigh.SetCurSel(1);


	mCmbIndustry.ResetContent();
	Vec_IndustryDataList vecIndustryDataList = IndustryDataMgr()->GetIndustryDataList();
	IndustryData* pIndustryData = NULL;
	for (int i = 0; i < vecIndustryDataList.size(); i++)
	{
		pIndustryData = vecIndustryDataList[i];
		ret = mCmbIndustry.AddString(pIndustryData->strIndustryName.c_str());
		mCmbIndustry.SetItemData(ret, reinterpret_cast<DWORD_PTR>(pIndustryData));
	}

	mCmbIndustry.SetCurSel(0);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


static UINT  doRunFindProc(LPVOID pParam)
{

	CDlgIndustryInfo* pDlg = (CDlgIndustryInfo*)pParam;


	pDlg->doRunFindInfo();



	return 0;
}


//查找
void CDlgIndustryInfo::OnBnClickedBtnFind()
{
	if (pThread)
		return;
	bIndustryFilter = true;
	bIndustryAllLow = false;
	bIndustryAllList = false;
	pThread = AfxBeginThread(doRunFindProc, (LPVOID)this, THREAD_PRIORITY_NORMAL, 0, 0, NULL);
}

typedef struct
{
	std::string  strIndustryName;
	int mAccordNums;
	int mTotalNums;
	float f_per;
	std::string  strTotalInfo;
}IndustryDataStat;
typedef	std::vector<IndustryDataStat* > Vec_IndustryDataStatList;


bool IsAccord(std::vector<double> vecPer)
{
	int size = vecPer.size();

	int pos = 0;
	int mNums = 0;
	while (true)
	{
		
		double now = vecPer[pos];
		double pre = vecPer[pos + 1];
		double f_per ;
		if (pre < 0.02)
			pre = 0.02;
		
		f_per = now / pre;
		bool bEqu = false;
		if (f_per > 0.98 && f_per < 1.02)
		{
			bEqu = true;
		}
		else
		{
			if (now <= pre)
				return false;
			mNums++;
			if (mNums >= 2)
				return true;
		}
		pos++;
		if (pos >=(size-1))
			break;
	}
	return false;
}

bool IsAccord2(std::vector<double> vecPer)
{
	int size = vecPer.size();

	int pos = 0;
	int mNums = 0;

	double f_now = vecPer[0];
	double f_pre= vecPer[1];

	if (f_now > 2.0 && f_pre > 2.0)
	{
		int nums = 0;
		for (int i = 2; i < size; i++)
		{
			if (vecPer[i] < 0.03)
			{
				nums++;
			}
			else
			{
				nums = 0;
			}

		}
		if (nums >= 6)
		{
			return true;
		}

	}

	return false;
}

void  CDlgIndustryInfo::doRunFindInfo(void)
{
	int	iItem = mCmbPeriod.GetCurSel();
	if (iItem < 0) return;

	mPeridNums = mCmbPeriod.GetItemData(iItem);

	vecIndustryInfoDataList.clear();

	CString strExpStockCode = "SH000001";
	CStockDayTable* pExpStockDayTable = NULL;
	pExpStockDayTable = StockDataMgr()->GetStockDayTable(strExpStockCode);

	int mPreIndex = 0;
	int mNowIndex = 0;
	IndustryInfoData* pIndustryInfoData = new IndustryInfoData();

	pIndustryInfoData->strStockDate = pExpStockDayTable->GetNearestStockDayDate(mStockDateTime);
	mNowIndex = pExpStockDayTable->GetStockDayIndex(pIndustryInfoData->strStockDate);
	mPreIndex = mNowIndex - 1;
	vecIndustryInfoDataList.push_back(pIndustryInfoData);

	int nums = 1;

	while (nums <= mPeridNums)
	{
		pIndustryInfoData = new IndustryInfoData();
		pIndustryInfoData->strStockDate = pExpStockDayTable->GetStockDayDateByIndex(mPreIndex);
		mPreIndex--;
		vecIndustryInfoDataList.push_back(pIndustryInfoData);
		nums++;
	}

	//std::map<std::string, int > stocknumsMap;

	Vec_TanAngleData vecTanAngleData;

	int mBackDays = 5;
	int mMaxAngle = 90;
	double f_max_volume_multiple = 10.0;
	bool bIgnoreM5 = false;
	bool bUseM120 = false;
	bool bUseAllUp = false;
	int mMaxInsBack = 5;
	double f_max_ins_thes = 6.0;
	CTime mDate;
	CTanAngleAlg* pTanAngleAlg;
	int mStockCodeSize = StockDataMgr()->GetStockCodeListSize();

	for (int i = 0; i < vecIndustryInfoDataList.size(); i++)
	{
		pIndustryInfoData = vecIndustryInfoDataList[i];
		mDate = ConverStringToCTime(pIndustryInfoData->strStockDate);

		for (int j = 0; j < vecTanAngleData.size(); j++)
			SAFE_DELETE(vecTanAngleData[j]);
		vecTanAngleData.clear();
		pTanAngleAlg = new CTanAngleAlg();
		mBackDays = 5;
		vecTanAngleData = pTanAngleAlg->doFilter(mDate, mBackDays, mMaxAngle, f_max_volume_multiple, bIgnoreM5, bUseM120, bUseAllUp, mMaxInsBack, f_max_ins_thes);
		
		std::map<std::string, std::vector<std::string> > industyMap;


		for (int j = 0; j < vecTanAngleData.size(); j++)
		{
			CString strStockCode = vecTanAngleData[j]->strStockCode;
			CString strStockName = vecTanAngleData[j]->strStockName;

		//	std::string stockcode = (LPCSTR)strStockCode;
		//	stocknumsMap[stockcode]++;

			std::vector<std::string> vecIndusty = IndustryDataMgr()->FindIndustryByStockCode((LPCSTR)strStockCode);
			for (int n = 0; n < vecIndusty.size(); n++)
			{
				industyMap[vecIndusty[n]].push_back((LPCSTR)strStockCode);
			}
		}

		
		std::map<std::string, std::vector<std::string> >::iterator iter;
		IndustryDataStat *pIndustryDataStat = NULL;
		iter = industyMap.begin();
		while (iter != industyMap.end())
		{
			int mStockNums = IndustryDataMgr()->GetIndustryStockNums(iter->first);
			double  f_per = (double)iter->second.size() * 100.0 / (double)mStockNums;
			pIndustryInfoData->mapIndustryInfo[iter->first] = f_per;
			iter++;
		}

		

	}

	/*std::map<std::string, int >::iterator iter2;
	iter2 = stocknumsMap.begin();
	while (iter2 != stocknumsMap.end())
	{
		int nums = iter2->second;
		if (nums >= 15)
		{
			printf("%s %d\n", iter2->first.c_str(), nums);
		}
		iter2++;
	}*/


	if (bIndustryAllList)
	{
		IndustryData* pIndustryData = NULL;
		int size = mCmbIndustry.GetCount();
		std::vector<double> vecPer;
		for (int i = 0; i < size; i++)
		{
			vecPer.clear();
			pIndustryData = reinterpret_cast<IndustryData*>(mCmbIndustry.GetItemData(i));
			std::string  strIndustryName = pIndustryData->strIndustryName;
			
			
			for (int i = 0; i < vecIndustryInfoDataList.size(); i++)
			{
				pIndustryInfoData = vecIndustryInfoDataList[i];

				double f_per = pIndustryInfoData->mapIndustryInfo[strIndustryName];
				vecPer.push_back(f_per);
				//printf("日期 %s  板块  %s  per=%.2f\n", (LPCSTR)pIndustryInfoData->strStockDate, strIndustryName.c_str(), f_per);

			}

			bool bFound = false;
			int perSize = vecPer.size();
			double f_now_per = vecPer[0];
			double f_p1_per = vecPer[1];
			double f_p2_per = vecPer[2];

			bFound = IsAccord(vecPer);
			if (!bFound)
			{
				bFound = IsAccord2(vecPer); 
			}
			/*if (f_now_per > f_p1_per)
			{
				if (f_p1_per > f_p2_per)
				{
					bFound = true;
				}
			}*/
			/*if (!bFound)
			{
				if (f_now_per > 0.0 && f_now_per < 5.0)
				{
					if (f_p1_per < 0.2)
					{
						bFound = true;
					}
				}
			}
			if (!bFound)
			{
				bool bNext = false;
				for (int j = 0; j < perSize; j++)
				{
					if (vecPer[j] > 60.0)
					{
						bNext = true;
						break;
					}
				}
				if (bNext)
				{
					if (f_now_per < 0.2 && f_p1_per < 0.2)
					{
						bFound = true;
					}
				}
			}*/

			if (bFound)
			{
				for (int i = 0; i < vecIndustryInfoDataList.size(); i++)
				{
					pIndustryInfoData = vecIndustryInfoDataList[i];

					double f_per = pIndustryInfoData->mapIndustryInfo[strIndustryName];
					printf("日期 %s  板块  %s  per=%.2f\n", (LPCSTR)pIndustryInfoData->strStockDate, strIndustryName.c_str(), f_per);

				}
				printf("------------------------------------------------\n");
			}


		}


		pThread = NULL;

		return;

	}

	if (!bIndustryFilter)
	{
		int	iItem = mCmbIndustry.GetCurSel();
		if (iItem < 0) return;
		IndustryData* pIndustryData = reinterpret_cast<IndustryData*>(mCmbIndustry.GetItemData(iItem));

		std::string  strIndustryName = pIndustryData->strIndustryName;

		for (int i = 0; i < vecIndustryInfoDataList.size(); i++)
		{
			pIndustryInfoData = vecIndustryInfoDataList[i];
			
			double f_per = pIndustryInfoData->mapIndustryInfo[strIndustryName];
		
			printf("日期 %s  板块  %s  per=%.2f\n", (LPCSTR)pIndustryInfoData->strStockDate, strIndustryName.c_str(), f_per);
		
		}

		pThread = NULL;

		return;
	}

	iItem = mCmbPerHigh.GetCurSel();
	if (iItem < 0) return;

	double fHighThrehold = mCmbPerHigh.GetItemData(iItem);


	iItem = mCmbPerLow.GetCurSel();
	if (iItem < 0) return;

	double fLowThrehold = mCmbPerLow.GetItemData(iItem);

	

	std::vector<std::string> vecIndustryList = IndustryDataMgr()->GetIndustryNameList();
	int mSize = vecIndustryInfoDataList.size();
	pIndustryInfoData = vecIndustryInfoDataList[0];

	if (bIndustryAllLow)
	{
		for (int i = 0; i < vecIndustryList.size(); i++)
		{
			double f_per = pIndustryInfoData->mapIndustryInfo[vecIndustryList[i]];
			if (f_per< fLowThrehold)
			{
				int mLowNums = 1;
				std::string strLowIndustryName = vecIndustryList[i];

				for (int j = 1; j < mSize; j++)
				{
					IndustryInfoData* pIndustryInfoData2 = vecIndustryInfoDataList[j];

					double f_per2 = pIndustryInfoData2->mapIndustryInfo[strLowIndustryName];
					if (f_per2 <= fLowThrehold)
					{
						mLowNums++;
					}

				}

				if (mLowNums >= (mSize - 2))
				{

					for (int j = 1; j < mSize; j++)
					{
						IndustryInfoData* pIndustryInfoData2 = vecIndustryInfoDataList[j];

						double f_per2 = pIndustryInfoData2->mapIndustryInfo[strLowIndustryName];

						if (j == 1)
						{
							printf("日期 %s  板块  %s  per=%.2f\n", (LPCSTR)pIndustryInfoData->strStockDate, strLowIndustryName.c_str(), f_per);
						}
						printf("日期 %s  板块  %s  per=%.2f\n", (LPCSTR)pIndustryInfoData2->strStockDate, strLowIndustryName.c_str(), f_per2);
					}
					printf("------------------------------------------------\n");
				}

			}


		}
		pThread = NULL;
		return;

	}



	

	//Vec_IndustryFilterData vecIndustryFilterData;
	
	std::vector<std::string> vecHighList;
	for (int i = 0; i < vecIndustryList.size(); i++)
	{
		double f_per = pIndustryInfoData->mapIndustryInfo[vecIndustryList[i]];
		if (f_per <= fHighThrehold)
		{
			//IndustryFilterData* pIndustryFilterData = new IndustryFilterData();
			//pIndustryFilterData->strIndustryName= vecIndustryList[i].c_str();
			//IndustryFilterDayData* pIndustryFilterDayData = new IndustryFilterDayData();

			//IndustryFilterDayData* pIndustryFilterDayData = new IndustryFilterDayData();
			//pIndustryFilterDayData->strStockDate = pIndustryInfoData->strStockDate;
			//pIndustryFilterDayData->f_per = f_per;
			//pIndustryFilterData->vecIndustryFilterDayData.push_back(pIndustryFilterDayData);

			//printf("日期 %s  板块  %s  per=%.2f\n", (LPCSTR)pIndustryInfoData->strStockDate, vecIndustryList[i].c_str(),f_per);
			//vecHighList.push_back(vecIndustryList[i]);
			std::string strHighIndustryName = vecIndustryList[i];
			//
			//printf("High %s \n", strHighIndustryName.c_str());
			bool bLowOk = false;
			int mNums = 0;
			for (int j = 1; j < mSize; j++)
			{
				IndustryInfoData* pIndustryInfoData2 = vecIndustryInfoDataList[j];

				double f_per2 = pIndustryInfoData2->mapIndustryInfo[strHighIndustryName];
				//printf("Low %s  f_per2=%.2f\n", strHighIndustryName.c_str(), f_per2);
				if (f_per2 >= fLowThrehold && f_per2<= fHighThrehold)
				{
					//printf("Low %s  f_per2=%.2f mNums=%d\n", strHighIndustryName.c_str(), f_per2, mNums);
					mNums++;
				}
					
			}
			//printf("High %s mNums %d\n", strHighIndustryName.c_str(), mNums);
			
			if (mNums >= (mSize - 1))
			{
				bLowOk = true;
			}

			if (bLowOk)
			{
				for (int j = 1; j < mSize; j++)
				{
					IndustryInfoData* pIndustryInfoData2 = vecIndustryInfoDataList[j];

					double f_per2 = pIndustryInfoData2->mapIndustryInfo[strHighIndustryName];
					
					if (j==1)
					{
						printf("1日期 %s  板块  %s  per=%.2f\n", (LPCSTR)pIndustryInfoData->strStockDate, strHighIndustryName.c_str(), f_per);
					}
					printf("1日期 %s  板块  %s  per=%.2f\n", (LPCSTR)pIndustryInfoData2->strStockDate, strHighIndustryName.c_str(), f_per2);
				}

				printf("------------------------------------------------\n");

			}
			

		}
	}
	
	pThread = NULL;
	
}


void CDlgIndustryInfo::OnBnClickedBtnShow()
{
	if (pThread)
		return;
	bIndustryFilter = false;
	bIndustryAllLow = false;
	bIndustryAllList = false;
	pThread = AfxBeginThread(doRunFindProc, (LPVOID)this, THREAD_PRIORITY_NORMAL, 0, 0, NULL);
}


void CDlgIndustryInfo::OnBnClickedBtnFind2()
{
	if (pThread)
		return;
#if 0
	bIndustryFilter = true;
	bIndustryAllLow = true;
	bIndustryAllList = false;
#else
	bIndustryFilter = false;
	bIndustryAllLow = false;
	bIndustryAllList = true;
#endif
	pThread = AfxBeginThread(doRunFindProc, (LPVOID)this, THREAD_PRIORITY_NORMAL, 0, 0, NULL);
}


void CDlgIndustryInfo::OnBnClickedBtnFind3()
{
	if (pThread)
		return;
	bIndustryFilter = true;
	bIndustryAllLow = true;
	bIndustryAllList = false;
	pThread = AfxBeginThread(doRunFindProc, (LPVOID)this, THREAD_PRIORITY_NORMAL, 0, 0, NULL);
}
