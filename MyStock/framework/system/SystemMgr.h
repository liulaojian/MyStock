#pragma once

#define MYSTOCK_INI	"mystock.ini"

class CSystemMgr
{
public:
	CSystemMgr();
	virtual ~CSystemMgr();

public:
	static CSystemMgr* GetInstance();


	//从股票数据导出目录中产生股票xml文件信息
	CString BuildStockXmlInfo(void);
	BOOL  SaveStockXmlInfo(CString strStockInfo);
	CString BuildSingleFileStockXmlInfo(CString strFileDir,CString strFileName);


	void SetMyStockXmlFile(CString strFilePath);

	CString DoGetMyStockXmlFile(void);

	CString GetMyStockXmlFile(void) {return strStockXmlFile;}

	CString GetTitle(void) {return strTitle;}

	CString DoGetTitle(void);

	void SetTitle(CString strVal);

	BOOL DoGetXuLieHao(void);

	void SetXuLieHao(DWORD xuliehao);

	unsigned long GetXuLieHao(void) {return mXuLiehao;}

	BOOL  CheckXuLieHao(void);
	DWORD GetVolumeSerialNumber(void);

	BOOL IsFakeMode(void) {return bFakeMode;}
	void SetFakeMode(BOOL val) {bFakeMode=val;}
private:
	static CSystemMgr* s_pIntance;

	CString strStockXmlFile;

	CString strTitle;

	unsigned long mXuLiehao;
	DWORD mVolumeSerialNumber;

	BOOL bFakeMode;
};


#define SystemMgr()	CSystemMgr::GetInstance()