#pragma once


#include <vector>

#include "StockDayTable.h"
#include "StockMin5Table.h"

//股票标准算法 数据类

enum
{
	K_LINE_DAY=0,				//ID
	K_LINE_5IN=1,
	K_LINE_15IN=2,
	K_LINE_30IN=3,
	K_LINE_60MIN=4,
};


class KLineBaseData
{
public:
	KLineBaseData() {}
	virtual ~KLineBaseData() {}
	std::vector<long> vec_time;			//时间
	std::vector<double> vec_open_price;	//开盘价 
	std::vector<double> vec_high_price;	//最高价
	std::vector<double> vec_low_price;	//最低价
	std::vector<double> vec_close_price;	//结束价
	std::vector<double> vec_avg_price;	//平均价格
	std::vector<long> vec_volume;	//交易量
	std::vector<double> vec_volume_price;	////交易总价格
	int m_length;	//长度
	int m_type;		//类型 
} ;
typedef std::vector<KLineBaseData *> Vec_KLineBaseData;

class CKLineDataBean
{
public:
	CKLineDataBean();
	virtual ~CKLineDataBean();

	//将股票日数据转换为 K线基础数据 strDate 是 日期，mNums日期 向前mNums个 （包括strDate)
	static KLineBaseData * ConvStockDayDataToArithmeticBaseData(CStockDayTable *pStockDayTable,CString strDate,int mNums);

	//将股票5分钟数据转换为 K线基础数据(5分钟) strDate 是 日期，mNums日期 向前mNums个 （包括strDate)
	static KLineBaseData * ConvStockDayDataToArithmeticBaseDataMin5(CStockMin5Table *pStockMin5Table,CString strDateTime,int mNums);

	//将股票倍数5分钟数据转换为 K线基础数据(倍数分钟) strDate 是 日期，mNums日期 向前mNums个倍数分钟数据（5分钟的N倍) （包括strDate)
	static KLineBaseData * ConvStockDayDataToArithmeticBaseDataMulMin5(CStockMin5Table *pStockMin5Table,CString strDateTime,int mNums,int mPerNums,int mType);


	//将股票15分钟数据转换为 K线基础数据(15分钟) strDate 是 日期，mNums日期 向前mNums个 （5分钟的3倍)（包括strDate)
	static KLineBaseData * ConvStockDayDataToArithmeticBaseDataMin15(CStockMin5Table *pStockMin5Table,CString strDateTime,int mNums);

	//将股票30分钟数据转换为 K线基础数据(30分钟) strDate 是 日期，mNums日期 向前mNums个 （5分钟的6倍)（包括strDate)
	static KLineBaseData * ConvStockDayDataToArithmeticBaseDataMin30(CStockMin5Table *pStockMin5Table,CString strDateTime,int mNums);

	//将股票30分钟数据转换为 K线基础数据(60分钟) strDate 是 日期，mNums日期 向前mNums个 （5分钟的12倍)（包括strDate)
	static KLineBaseData * ConvStockDayDataToArithmeticBaseDataMin60(CStockMin5Table *pStockMin5Table,CString strDateTime,int mNums);

	static KLineBaseData *NewKLineBaseData(int mArithType);

	//最后的值要根据日期修正（主要是 最后的日期不是 15 30 60 这样的整的
	static double CalcDateTimeCorrect(CString strDateTime,int mType,std::vector<double> vec_value);


	//计算能量值
	static BOOL CalcPowerValue(std::vector<double> vec_close,std::vector<double> vec_volume_price,int mN,double & f_power_val);
};