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
	STOCK_BOARD_ZS=0,		//指数
	STOCK_BOARD_SH,			//上海
	STOCK_BOARD_SZ,			//深圳
	STOCK_BOARD_CY,			//创业
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

	BOOL  LoadFromStockCodeXml(CString strXmlPath);			//从xml中加载股票种类数据


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

	//是否是指数
	BOOL  IsExpStock(CString strStockCode);
	
	CString GetStockName(CString strStockCode);

	CString GetStockCode(CString strStockName);


	CStockMin5Table* GetStockMin5Table(CString strStockCode);

	CString GetStockMin5BeginDateTime(CString strStockCode);

	CString GetStockMin5EndDateTime(CString strStockCode);

	
	//获取指数最近日期（可当作股票的最近日期）
	CString GetExpLastDayDate(void);

	//获取倒序指定的指数最近日期
	CString GetExpLastDayDateByReverse(int index);

	//获取倒序指定的日期前指定周期的日期
	CString GetExpPreDayDateByPreDateIndex(CString strDate,int preIndex);


	//指定时间，指数天数据是否存在
	BOOL IsExpDayDataExist(CString strDate);

	//获取指数最近5分钟日期（可当作股票的最近5分钟日期）
	CString GetExpLastMin5Date(void);

	//指定时间，指数5分钟数据是否存在
	BOOL IsExpMin5DataExist(CString strDateTime);

	//获取前一天的日期根据日期时间
	CString GetExpPreDayDateByDateTime(CString strDateTime);

	//获取股票板块类型
	int  GetStockBoard(CString strStockCode);

	//通过板块类型获取指数代码
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