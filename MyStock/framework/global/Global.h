#pragma once




class CGlobalMgr
{
public:
	CGlobalMgr();
	virtual ~CGlobalMgr();

public:
	static CGlobalMgr* GetInstance();

	void SetGlobalInfo(int info) { mGlobalInfo = info; }

	int GetGlobalInfo(void) {return mGlobalInfo;}
private:
	static CGlobalMgr* s_pIntance;


	int mGlobalInfo = 0;
};


#define GlobalMgr()	CGlobalMgr::GetInstance()