#pragma once

#include "tinyxml.h"
#include <string>
#include <map>
#include <vector>

typedef std::vector <TiXmlElement * > VecTiXmlElement;

class CXmlOperator
{
public:
	CXmlOperator();
	virtual ~CXmlOperator();

	

	/*! 
	*  /brief ��ȡxml�ļ��������� 
	* 
	*  /param XmlFile xml�ļ�ȫ·���� 
	*  /param strVersion  Version����ֵ 
	*  /param strStandalone Standalone����ֵ 
	*  /param strEncoding Encoding����ֵ 
	*  /return �Ƿ�ɹ���trueΪ�ɹ���false��ʾʧ�ܡ� 
	*/  
	static	bool GetXmlDeclare(std::string XmlFile, std::string &strVersion,  std::string &strStandalone,  std::string &strEncoding);



	/*! 
	*  /brief ͨ�����ڵ�ͽڵ�����ȡ�ڵ�ָ�롣 
	* 
	*  /param pRootEle   xml�ļ��ĸ��ڵ㡣 
	*  /param strNodeName  Ҫ��ѯ�Ľڵ��� 
	*  /param Node      ��Ҫ��ѯ�Ľڵ�ָ�� 
	*  /return �Ƿ��ҵ���trueΪ�ҵ���Ӧ�ڵ�ָ�룬false��ʾû���ҵ���Ӧ�ڵ�ָ�롣 
	*/  
	static bool GetNodePointerByName(TiXmlElement* pRootEle,std::string &strNodeName,TiXmlElement* &Node)  ;

	//ͨ�����ڵ�ͽڵ����Լ���������ֵ��ȡ�ڵ�ָ��
	static bool GetNodePointerByName(TiXmlElement* pRootEle,std::string &strNodeName,std::string &strAttrName,std::string &strAttrValue,TiXmlElement* &Node)  ;


	  /*! 
			*  /brief ͨ���ڵ��ѯ�� 
			* 
			*  /param XmlFile   xml�ļ�ȫ·���� 
			*  /param strNodeName  Ҫ��ѯ�Ľڵ��� 
			*  /param strText      Ҫ��ѯ�Ľڵ��ı� 
			*  /return �Ƿ�ɹ���trueΪ�ɹ���false��ʾʧ�ܡ� 
			*/  
	static	bool QueryNode_Text(std::string XmlFile,std::string strNodeName,std::string &strText) ;

	/*! 
	*  /brief ͨ���ڵ��ѯ���ԡ� 
	* 
	*  /param XmlFile   xml�ļ�ȫ·���� 
	*  /param strNodeName  Ҫ��ѯ�Ľڵ��� 
	*  /param AttMap      Ҫ��ѯ������ֵ������һ��map��ǰһ��Ϊ����������һ��Ϊ����ֵ 
	*  /return �Ƿ�ɹ���trueΪ�ɹ���false��ʾʧ�ܡ� 
	*/  
	static	bool QueryNode_Attribute(std::string XmlFile,std::string strNodeName,std::map<std::string,std::string> &AttMap)  ;

	// ���ڵ�����ĳһ���� ��ѯ�ýڵ���������
	static	bool QueryNode_Attribute(std::string XmlFile,std::string strNodeName,std::string strAttrName,std::string strAttrValue,std::map<std::string,std::string> &AttMap)  ;

	
	static VecTiXmlElement QueryNode_Element(std::string XmlFile,std::string strNodeName,std::string strSubNodeName);

	static bool QueryNode_AttributeText(std::string XmlFile,std::string strNodeName,std::string strSubNodeName,std::string strAttrName,std::string &strText);
	/*! 
	*  /brief ɾ��ָ���ڵ��ֵ�� 
	* 
	*  /param XmlFile xml�ļ�ȫ·���� 
	*  /param strNodeName ָ���Ľڵ����� 
	*  /return �Ƿ�ɹ���trueΪ�ɹ���false��ʾʧ�ܡ� 
	*/  
	static bool DelNode(std::string XmlFile,std::string strNodeName) ;


	/*! 
	*  /brief �޸�ָ���ڵ���ı��� 
	* 
	*  /param XmlFile xml�ļ�ȫ·���� 
	*  /param strNodeName ָ���Ľڵ����� 
	*  /param strText �����趨���ı���ֵ 
	*  /return �Ƿ�ɹ���trueΪ�ɹ���false��ʾʧ�ܡ� 
	*/  
	static bool ModifyNode_Text(std::string XmlFile,std::string strNodeName,std::string strText)  ;


	/*! 
	*  /brief �޸�ָ���ڵ������ֵ�� 
	* 
	*  /param XmlFile xml�ļ�ȫ·���� 
	*  /param strNodeName ָ���Ľڵ����� 
	*  /param AttMap �����趨������ֵ������һ��map��ǰһ��Ϊ����������һ��Ϊ����ֵ 
	*  /return �Ƿ�ɹ���trueΪ�ɹ���false��ʾʧ�ܡ� 
	*/  
	static bool ModifyNode_Attribute(std::string XmlFile,std::string strNodeName, std::map<std::string,std::string> &AttMap);

	//���ݽڵ��� ��������ֵ �õ��ڵ㲢�޸��������ֵ
	static bool ModifyNode_Attribute(std::string XmlFile,std::string strNodeName,std::string strAttrName,std::string strAttrValue, std::map<std::string,std::string> &AttMap);

	/*! 
	*  /brief ����ָ���ڵ���ı��� 
	* 
	*  /param XmlFile xml�ļ�ȫ·���� 
	*  /param strParNodeName Ҫ���ӵĽڵ�ĸ��ڵ㡣 
	*  /param strNodeName ָ���Ľڵ����� 
	*  /param strText Ҫ���ӵ��ı� 
	*  /return �Ƿ�ɹ���trueΪ�ɹ���false��ʾʧ�ܡ� 
	*/  
	static bool AddNode_Text(std::string XmlFile,std::string strParNodeName,std::string strNodeName,std::string strText)  ;


	/*! 
	*  /brief ���ӽڵ㡣 
	* 
	*  /param XmlFile xml�ļ�ȫ·���� 
	*  /param strParNodeName Ҫ���ӵĽڵ�ĸ��ڵ㡣 
	*  /param strNodeName ָ���Ľڵ����� 
	*  /param AttMap Ҫ���ӵĽڵ��趨������ֵ������һ��map��ǰһ��Ϊ����������һ��Ϊ����ֵ 
	*  /return �Ƿ�ɹ���trueΪ�ɹ���false��ʾʧ�ܡ� 
	*/  
	static bool AddNode_Attribute(std::string XmlFile,std::string strParNodeName,std::string strNodeName,std::map<std::string,std::string> &AttMap)  ;
	
};