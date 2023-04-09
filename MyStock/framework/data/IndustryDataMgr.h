#pragma once

//��ҵ�������
#include <vector>
#include <string>

typedef struct
{
	std::string  strIndustryCode;
	std::string  strIndustryName;
	std::vector<std::string> vecIndustryCfg;		//�ð��ɷֹ�	
}IndustryData;

typedef	std::vector<IndustryData* > Vec_IndustryDataList;



class CIndustryDataMgr
{
public:
	CIndustryDataMgr();
	virtual ~CIndustryDataMgr();

public:
	static CIndustryDataMgr* GetInstance();

	bool Init(void);

	std::vector<std::string> FindIndustryByStockCode(std::string strCode);

	Vec_IndustryDataList GetIndustryDataList(void) { return vecIndustryDataList; }

	std::vector<std::string> GetIndustryNameList(void);
	//��ȡ��ҵ������
	int GetIndustryStockNums(std::string strIndustryName);
private:
	bool LoadIndustryDataList(void);

private:
	static CIndustryDataMgr* s_pIntance;
	Vec_IndustryDataList vecIndustryDataList;
	bool bInited = false;

};

#define IndustryDataMgr()	CIndustryDataMgr::GetInstance()