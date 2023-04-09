#pragma once
#include <vector>
#include "EnvInterestData.h"
#include "EnvReserveData.h"

typedef	std::vector<CEnvInterestData * > Vec_EnvInterestDataList;
typedef	std::vector<CEnvReserveData * > Vec_EnvReserveDataList;

#define  ENV_DATA_XML_NAME  "Envrion.xml"

class CEnvDataMgr
{
public:
	CEnvDataMgr();
	virtual ~CEnvDataMgr();

public:
	static CEnvDataMgr* GetInstance();

	BOOL  LoadEnvIntereDataFromXml(CString strXmlPath);
	BOOL  LoadEnvReserveDataFromXml(CString strXmlPath);

	BOOL  Init(void);

	Vec_EnvInterestDataList GetEnvInterestDataListOfPreDate(CString strDate,int mNums);
	Vec_EnvReserveDataList GetEnvReserveDataListOfPreDate(CString strDate,int mNums);

private:
	static CEnvDataMgr* s_pIntance;
	Vec_EnvInterestDataList vecEnvInterestDataList;
	Vec_EnvReserveDataList  vecEnvReserveDataList;
};

#define EnvDataMgr()	CEnvDataMgr::GetInstance()