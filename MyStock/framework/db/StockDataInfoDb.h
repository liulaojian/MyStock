#pragma once
#include <string>
#include <vector>
#include "zbTypeDef.h"
#include "sqlite.h"

#include "StockDayTable.h"
#include "StockMin5Table.h"

#define STOCKDATA_DATABASE 			"stockdata.db"


typedef struct
{
	std::string		strDate;
	float  fBeginPrice;		//开盘价格
	float  fMaxPrice;		//最高价格
	float  fMinPrice;		//最低价格
	float  fEndPrice;		//收盘价格
	long   mTotalVolume;		//成交量
	float  fTotalPrice;		//成交金额
} DbStockDayData;
typedef std::vector<DbStockDayData *> Vec_DbStockDayData;

typedef struct
{
	CString strStockCode;
	Vec_DbStockDayData  vecDbStockDayData;
} DbStockDayTable;
typedef std::vector<DbStockDayTable *> Vec_DbStockDayTable;


typedef struct
{
	std::string	 strDateTime;
	float  fBeginPrice;		//开盘价格
	float  fMaxPrice;		//最高价格
	float  fMinPrice;		//最低价格
	float  fEndPrice;		//收盘价格
	long   mTotalVolume;		//成交量
	float  fTotalPrice;		//成交金额
} DbStock5MinData;
typedef std::vector<DbStock5MinData *> Vec_DbStock5MinData;

typedef struct
{
	CString strStockCode;
	Vec_DbStock5MinData  vecDbStock5MinData;
} DbStock5MinTable;
typedef std::vector<DbStock5MinTable *> Vec_DbStock5MinTable;

class CStockDataInfoDb
{
public:
	CStockDataInfoDb();
	virtual ~CStockDataInfoDb();

public:
	static CStockDataInfoDb* GetInstance();
	
	CString GetStockDayTableName(CString strStockCode);
	CString GetStockMin5TableName(CString strStockCode);

	//打开数据库
	bool DataBaseOpen(void);
	
	//关闭数据库
	bool DataBaseClose(void);

	//数据库日表是否存在
	BOOL IsDbDayTableExist(CString strStockCode);

	//数据库5分钟表是否存在
	BOOL IsDbMin5TableExist(CString strStockCode);

	BOOL  IsDatabaseOpe(void) {return bDatabaseOpen;}

	//创建日表
	bool CreateDayTable(std::string strTableName);

	//创建5分钟表
	bool CreateMin5Table(std::string strTableName);

	//创建表
	bool CreateTable(void);

	//日数据批量插入
	bool StockDay_Table_InsertVec(CString strStockCode,Vec_DbStockDayData vecDbStockDayData);

	//日数据查询
	bool StockDay_Table_Query(CString strStockCode, Vec_DbStockDayData &vecDbStockDayData);

	//日数据删除
	bool StockDay_Table_Delete(CString strStockCode,CString strDate);

	//日数据更新
	bool StockDay_Table_Update(CString strStockCode,DbStockDayData * pDbStockDayData);

	//5分钟数据批量插入
	bool StockMin5_Table_InsertVec(CString strStockCode,Vec_DbStock5MinData vecDbStock5MinData);

	//5分钟数据查询
	bool StockMin5_Table_Query(CString strStockCode, Vec_DbStock5MinData &vecDbStock5MinData);

	//5分钟数据删除
	bool StockMin5_Table_Delete(CString strStockCode,CString strDateTime);

	//5分钟数据更新
	bool StockMin5_Table_Update(CString strStockCode,DbStock5MinData * pDbStock5MinData);

	//将Vec_StockDayData 天数据列表 转换为  Vec_DbStockDayData 天数据库列表
	Vec_DbStockDayData  ConvertVecStockDayDataToVecDbStockDayData(Vec_StockDayData vecStockDayData );

	//将Vec_StockMin5Data 天数据列表 转换为  Vec_DbStock5MinData 天数据库列表
	Vec_DbStock5MinData ConvertVecStockMin5DataToVecDbStock5MinData(Vec_StockMin5Data vecStockMin5Data);
	
private:
	static CStockDataInfoDb* s_pIntance;
	
	Sqlite mDatabase;

	BOOL bDatabaseOpen;

};


#define StockDataInfoDb()	CStockDataInfoDb::GetInstance()