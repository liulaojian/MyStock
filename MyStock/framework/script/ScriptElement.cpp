#include "StdAfx.h"
#include "ScriptElement.h"

CScriptElement* CScriptElement::s_pIntance = NULL;

CScriptElement::CScriptElement(void)
{
	
}

CScriptElement::~CScriptElement(void)
{
	
}

CScriptElement* CScriptElement::GetInstance()
{
	if (s_pIntance == NULL)
	{
		s_pIntance = new CScriptElement();
		
	}
	
	return s_pIntance;
}

//��½�Ա�

int CScriptElement::LoginTaobao(CString strAccount,CString strPassword)
{
	
	return 0;
}

//ת��ָ��Url
int CScriptElement::GotoUrl(CString Url)
{
	
	return 0;
}

//�ƶ���ָ��λ�ò����
int CScriptElement::GotoClick(int x,int y)
{

	return 0;
}

//���������Ϲ�
int CScriptElement::WhellUp(void)
{

	return 0;
}

//���������¹�
int CScriptElement::WhellDown(void)
{

	return 0;
}
//����Ӣ���ַ���
int CScriptElement::InputString(CString strInput)
{

	return 0;
}
//���뺺���ַ���
int CScriptElement::InputHZString(CString strInput)
{

	return 0;
}
//����ͼƬ
int CScriptElement::FindPic(int x0,int y0,int x1 ,int y1,CString strPicFileName,CString strdelta_color, double sim,int *x,int *y)
{

	return 0;
}

//������ɫ
int CScriptElement::FindColor(int x0,int y0,int x1,int y1,CString strColor,double sim,int *x,int *y)
{

	return 0;
}

//��ȡ��Ļָ������ɫ����
long CScriptElement::GetScreenData(int x0,int y0,int x1,int y1)
{

	return 0;
}

//�����ֿ��ļ�
long  CScriptElement::SetDict(int index,CString strFile)
{

	return 0;
}

//�����ַ���
long CScriptElement::FindStr(int x0,int y0,int x1, int y1,CString strString,CString strColor_format,double sim,int *x,int *y)
{

	return 0;
}

//�����ַ���ͨ��ָ��ϵͳ����
long CScriptElement::FindStrWithFont(int x0,int y0,int x1, int y1,CString strString,CString strColor_format,double sim,CString strFont_name, int font_size,int flag,int *x,int *y)
{

	return 0;
}

//ocrָ�����򷵻��ַ��� 
CString CScriptElement::Ocr(int x0,int y0,int x1, int y1,CString strColor_format,double sim)
{

	return "";
}

//ocrָ�����򷵻��ַ��� 
CString CScriptElement::OcrEx(int x0,int y0,int x1, int y1,CString strColor_format,double sim)
{

	return "";
}

//��ָ�����ֿ������һ���ֿ���Ϣ.
long CScriptElement::AddDict(int index,CString dict_info)
{

	return 0;
}
//���ָ�����ֿ�.
long CScriptElement::ClearDict(int index)
{

	return 0;
}

//����ָ���ķ�Χ,�Լ�ָ������ɫ��������ȡ������Ϣ�������ڴ�Į������ĵ�����ȡ.
CString CScriptElement::FetchWord(int x0,int y0,int x1, int y1, CString color, CString word)
{

	return "";
}

//����ָ�������֣��Լ�ָ����ϵͳ�ֿ���Ϣ����ȡ�ֿ�������Ϣ.
CString CScriptElement::GetDictInfo(CString str,CString font_name,int font_size,int flag)
{

	return "";
}

//��ʾʹ���ĸ��ֿ��ļ�����ʶ��(index��Χ:0-9)
long CScriptElement::UseDict(int index)
{

	return 0;
}

//����ȫ��·��
long CScriptElement::SetPath(CString path)
{

	return 0;
}

//����ҳ�湺��  url �����ҳ��  type ��ʱͳһΪ 0  num ��������  additional ����ĸ��� �� | �ָ� ��Ҫ�ǿ�ʽ 
short CScriptElement::BuyIng(LPCTSTR url, short type, short num, LPCTSTR additional)
{

	return 0;
}


//���ù���ʱ���õĵ�ַ
short CScriptElement::SetBuyIngAddr(LPCTSTR person,  LPCTSTR addr)
{
	
	return 0;
}

short  CScriptElement:: PushOuterMsg(short MsgType,LPCTSTR MsgStr)
{

	return 0;
}