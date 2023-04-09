#pragma once

#include "StockDayTable.h"
#include "StockMin5Table.h"
#include "zbTypeDef.h"
typedef struct 
{
	CString  strStockCode;
	CString  strStockName;
	CString  strStockDayFilePath;
	CString  strStockMinFilePath;
}StockCode;

typedef std::vector<StockCode *> Vec_StockCodeList;

typedef	std::vector<CStockDayTable * > Vec_StockDayTableList;

typedef	std::vector<CStockMin5Table * > Vec_StockMin5TableList;

enum
{
	STOCK_BOARD_ZS=0,		//ָ��
	STOCK_BOARD_SH,			//�Ϻ�
	STOCK_BOARD_SZ,			//����
	STOCK_BOARD_CY,			//��ҵ
};

#define  STOCK_CODE_XML_NAME  "StockCode.xml"
//#define  STOCK_CODE_XML_NAME  "StockCode300.xml"

class CStockDataMgr
{
public:
	CStockDataMgr();
	virtual ~CStockDataMgr();

public:
	static CStockDataMgr* GetInstance();

	BOOL  Init(void);

	BOOL  LoadFromStockCodeXml(CString strXmlPath);			//��xml�м��ع�Ʊ��������


	BOOL InitStockTableList(void);

	Vec_CString GetStockCodeStringList(void);

	Vec_StockCodeList  GetStockCodeList(void) {return vecStockCodeList;}
	int          GetStockCodeListSize(void){return vecStockCodeList.size();}

	BOOL  IsStockInCodeList(CString strStockCode);
 
	CStockDayTable* GetStockDayTable(CString strStockCode);

	int GetStockDayTableIndex(CString strStockCode);

	CString GetStockDayBeginDate(CString strStockCode);

	CString GetStockDayEndDate(CString strStockCode);

	CString GetStockDayDateReverseIndex(CString strStockCode,int index);

	CString GetStockDayDatePreOfIndex(CString strStockCode,CString strDate,int prenums);

	CString GetStockDayDateAftOfIndex(CString strStockCode,CString strDate,int aftnums);

	//�Ƿ���ָ��
	BOOL  IsExpStock(CString strStockCode);
	
	CString GetStockName(CString strStockCode);

	CString GetStockCode(CString strStockName);


	CStockMin5Table* GetStockMin5Table(CString strStockCode);

	CString GetStockMin5BeginDateTime(CString strStockCode);

	CString GetStockMin5EndDateTime(CString strStockCode);

	
	//��ȡָ��������ڣ��ɵ�����Ʊ��������ڣ�
	CString GetExpLastDayDate(void);

	//��ȡ����ָ����ָ���������
	CString GetExpLastDayDateByReverse(int index);

	//��ȡ����ָ��������ǰָ�����ڵ�����
	CString GetExpPreDayDateByPreDateIndex(CString strDate,int preIndex);


	//ָ��ʱ�䣬ָ���������Ƿ����
	BOOL IsExpDayDataExist(CString strDate);

	//��ȡָ�����5�������ڣ��ɵ�����Ʊ�����5�������ڣ�
	CString GetExpLastMin5Date(void);

	//ָ��ʱ�䣬ָ��5���������Ƿ����
	BOOL IsExpMin5DataExist(CString strDateTime);

	//��ȡǰһ������ڸ�������ʱ��
	CString GetExpPreDayDateByDateTime(CString strDateTime);

	//��ȡ��Ʊ�������
	int  GetStockBoard(CString strStockCode);

	//ͨ��������ͻ�ȡָ������
	CString GetExpCodeByBoardType(int  mType);

	inline void TryLockDayTable() 
	{ ::TryEnterCriticalSection(&dayTableLock); }
	inline void LockDayTable() 
	{ ::EnterCriticalSection(&dayTableLock); }
	inline void UnlockDayTable() 
	{ ::LeaveCriticalSection(&dayTableLock); }


	inline void TryLockMin5Table() 
	{ ::TryEnterCriticalSection(&min5TableLock); }
	inline void LockMin5Table() 
	{ ::EnterCriticalSection(&min5TableLock); }
	inline void UnlockMin5Table() 
	{ ::LeaveCriticalSection(&min5TableLock); }


	inline void TryLockStockList() 
	{ ::TryEnterCriticalSection(&stockListLock); }
	inline void LockStockList() 
	{ ::EnterCriticalSection(&stockListLock); }
	inline void UnlockStockList() 
	{ ::LeaveCriticalSection(&stockListLock); }

private:
	static CStockDataMgr* s_pIntance;

	Vec_StockCodeList vecStockCodeList;

	Vec_StockDayTableList  vecStockDayTableList;

	Vec_StockMin5TableList vecStockMin5TableList;

	CRITICAL_SECTION dayTableLock;
	CRITICAL_SECTION min5TableLock;
	CRITICAL_SECTION stockListLock;

	
};


#define StockDataMgr()	CStockDataMgr::GetInstance()