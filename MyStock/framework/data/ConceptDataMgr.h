#pragma once

//概念板块数据
#include <vector>
#include <string>

typedef struct
{
	std::string  strConceptCode;
	std::string  strConceptName;
	std::vector<std::string> vecConceptCfg;		//该板块成分股	
}ConceptData;


typedef	std::vector<ConceptData* > Vec_ConceptDataList;


class CConceptDataMgr
{
public:
	CConceptDataMgr();
	virtual ~CConceptDataMgr();

public:
	static CConceptDataMgr* GetInstance();

	bool Init(void);

	std::vector<std::string> FindConceptByStockCode(std::string strCode);

private:
	bool LoadConceptDataList(void);

private:
	static CConceptDataMgr* s_pIntance;
	Vec_ConceptDataList vecConceptDataList;
	bool bInited = false;

};

#define ConceptDataMgr()	CConceptDataMgr::GetInstance()