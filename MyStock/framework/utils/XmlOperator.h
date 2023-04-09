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
	*  /brief 获取xml文件的声明。 
	* 
	*  /param XmlFile xml文件全路径。 
	*  /param strVersion  Version属性值 
	*  /param strStandalone Standalone属性值 
	*  /param strEncoding Encoding属性值 
	*  /return 是否成功。true为成功，false表示失败。 
	*/  
	static	bool GetXmlDeclare(std::string XmlFile, std::string &strVersion,  std::string &strStandalone,  std::string &strEncoding);



	/*! 
	*  /brief 通过根节点和节点名获取节点指针。 
	* 
	*  /param pRootEle   xml文件的根节点。 
	*  /param strNodeName  要查询的节点名 
	*  /param Node      需要查询的节点指针 
	*  /return 是否找到。true为找到相应节点指针，false表示没有找到相应节点指针。 
	*/  
	static bool GetNodePointerByName(TiXmlElement* pRootEle,std::string &strNodeName,TiXmlElement* &Node)  ;

	//通过根节点和节点名以及属性名和值获取节点指针
	static bool GetNodePointerByName(TiXmlElement* pRootEle,std::string &strNodeName,std::string &strAttrName,std::string &strAttrValue,TiXmlElement* &Node)  ;


	  /*! 
			*  /brief 通过节点查询。 
			* 
			*  /param XmlFile   xml文件全路径。 
			*  /param strNodeName  要查询的节点名 
			*  /param strText      要查询的节点文本 
			*  /return 是否成功。true为成功，false表示失败。 
			*/  
	static	bool QueryNode_Text(std::string XmlFile,std::string strNodeName,std::string &strText) ;

	/*! 
	*  /brief 通过节点查询属性。 
	* 
	*  /param XmlFile   xml文件全路径。 
	*  /param strNodeName  要查询的节点名 
	*  /param AttMap      要查询的属性值，这是一个map，前一个为属性名，后一个为属性值 
	*  /return 是否成功。true为成功，false表示失败。 
	*/  
	static	bool QueryNode_Attribute(std::string XmlFile,std::string strNodeName,std::map<std::string,std::string> &AttMap)  ;

	// 按节点名和某一属性 查询该节点所有属性
	static	bool QueryNode_Attribute(std::string XmlFile,std::string strNodeName,std::string strAttrName,std::string strAttrValue,std::map<std::string,std::string> &AttMap)  ;

	
	static VecTiXmlElement QueryNode_Element(std::string XmlFile,std::string strNodeName,std::string strSubNodeName);

	static bool QueryNode_AttributeText(std::string XmlFile,std::string strNodeName,std::string strSubNodeName,std::string strAttrName,std::string &strText);
	/*! 
	*  /brief 删除指定节点的值。 
	* 
	*  /param XmlFile xml文件全路径。 
	*  /param strNodeName 指定的节点名。 
	*  /return 是否成功。true为成功，false表示失败。 
	*/  
	static bool DelNode(std::string XmlFile,std::string strNodeName) ;


	/*! 
	*  /brief 修改指定节点的文本。 
	* 
	*  /param XmlFile xml文件全路径。 
	*  /param strNodeName 指定的节点名。 
	*  /param strText 重新设定的文本的值 
	*  /return 是否成功。true为成功，false表示失败。 
	*/  
	static bool ModifyNode_Text(std::string XmlFile,std::string strNodeName,std::string strText)  ;


	/*! 
	*  /brief 修改指定节点的属性值。 
	* 
	*  /param XmlFile xml文件全路径。 
	*  /param strNodeName 指定的节点名。 
	*  /param AttMap 重新设定的属性值，这是一个map，前一个为属性名，后一个为属性值 
	*  /return 是否成功。true为成功，false表示失败。 
	*/  
	static bool ModifyNode_Attribute(std::string XmlFile,std::string strNodeName, std::map<std::string,std::string> &AttMap);

	//根据节点名 属性名和值 得到节点并修改其的属性值
	static bool ModifyNode_Attribute(std::string XmlFile,std::string strNodeName,std::string strAttrName,std::string strAttrValue, std::map<std::string,std::string> &AttMap);

	/*! 
	*  /brief 增加指定节点的文本。 
	* 
	*  /param XmlFile xml文件全路径。 
	*  /param strParNodeName 要增加的节点的父节点。 
	*  /param strNodeName 指定的节点名。 
	*  /param strText 要增加的文本 
	*  /return 是否成功。true为成功，false表示失败。 
	*/  
	static bool AddNode_Text(std::string XmlFile,std::string strParNodeName,std::string strNodeName,std::string strText)  ;


	/*! 
	*  /brief 增加节点。 
	* 
	*  /param XmlFile xml文件全路径。 
	*  /param strParNodeName 要增加的节点的父节点。 
	*  /param strNodeName 指定的节点名。 
	*  /param AttMap 要增加的节点设定的属性值，这是一个map，前一个为属性名，后一个为属性值 
	*  /return 是否成功。true为成功，false表示失败。 
	*/  
	static bool AddNode_Attribute(std::string XmlFile,std::string strParNodeName,std::string strNodeName,std::map<std::string,std::string> &AttMap)  ;
	
};