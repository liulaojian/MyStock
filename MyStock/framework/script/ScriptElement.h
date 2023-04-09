#pragma once
#ifndef __SCRIPTELEMENT_H__
#define __SCRIPTELEMENT_H__


class CScriptElement
{
public:
	static CScriptElement* GetInstance();
public:
	CScriptElement(void);
	~CScriptElement(void);
public:
	
	//��½�Ա�
	int LoginTaobao(CString strAccount,CString strPassword);

	//ת��ָ��Url
	int GotoUrl(CString Url);
	
	//�ƶ���ָ��λ�ò����
	int GotoClick(int x,int y);
	
	//���������Ϲ�
	int WhellUp(void);

	//���������¹�
	int WhellDown(void);

	//����Ӣ���ַ���
	int InputString(CString strInput);

	//���뺺���ַ���
	int InputHZString(CString strInput);

	//����ͼƬ
	int FindPic(int x0,int y0,int x1 ,int y1,CString strPicFileName,CString strdelta_color, double sim,int *x,int *y);


	//������ɫ
	int FindColor(int x0,int y0,int x1,int y1,CString strColor,double sim,int *x,int *y);
	
	//��ȡ��Ļָ������ɫ����
	long GetScreenData(int x0,int y0,int x1,int y1);

	//�����ֿ��ļ�
	long  SetDict(int index,CString strFile);

	//�����ַ���
	long FindStr(int x0,int y0,int x1, int y1,CString strString,CString strColor_format,double sim,int *x,int *y);

	//�����ַ���ͨ��ָ��ϵͳ����
	long FindStrWithFont(int x0,int y0,int x1, int y1,CString strString,CString strColor_format,double sim,CString strFont_name, int font_size,int flag,int *x,int *y);
	
	//ocrָ�����򷵻��ַ��� 
	CString Ocr(int x0,int y0,int x1, int y1,CString strColor_format,double sim);
	
	//ocrָ�����򷵻��ַ��� 
	CString OcrEx(int x0,int y0,int x1, int y1,CString strColor_format,double sim);

	//��ָ�����ֿ������һ���ֿ���Ϣ.
	long AddDict(int index,CString dict_info);

	//���ָ�����ֿ�.
	long ClearDict(int index);

	//����ָ���ķ�Χ,�Լ�ָ������ɫ��������ȡ������Ϣ�������ڴ�Į������ĵ�����ȡ.
	CString FetchWord(int x0,int y0,int x1, int y1, CString color, CString word);

	//����ָ�������֣��Լ�ָ����ϵͳ�ֿ���Ϣ����ȡ�ֿ�������Ϣ.
	CString GetDictInfo(CString str,CString font_name,int font_size,int flag);

	//��ʾʹ���ĸ��ֿ��ļ�����ʶ��(index��Χ:0-9)
	long UseDict(int index);

	//����ȫ��·��
	long SetPath(CString path);
	

	//����ҳ�湺��  url �����ҳ��  type ��ʱͳһΪ 0  num ��������  additional ����ĸ��� �� | �ָ� ��Ҫ�ǿ�ʽ 
	short BuyIng(LPCTSTR url, short type, short num, LPCTSTR additional);

	//���ù���ʱ���õĵ�ַ
	short SetBuyIngAddr(LPCTSTR person,  LPCTSTR addr);

	//push ��Ϣ������Ӧ��
	short  PushOuterMsg(short MsgType,LPCTSTR MsgStr);
private:
	static CScriptElement* s_pIntance;	

};


#endif