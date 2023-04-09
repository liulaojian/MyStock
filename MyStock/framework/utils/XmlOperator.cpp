#include "XmlOperator.h"

CXmlOperator::CXmlOperator()
{


}

CXmlOperator::~CXmlOperator()
{


}

/*! 
	*  /brief 获取xml文件的声明。 
	* 
	*  /param XmlFile xml文件全路径。 
	*  /param strVersion  Version属性值 
	*  /param strStandalone Standalone属性值 
	*  /param strEncoding Encoding属性值 
	*  /return 是否成功。true为成功，false表示失败。 
	*/  
bool CXmlOperator::GetXmlDeclare(std::string XmlFile, std::string &strVersion,  std::string &strStandalone,  std::string &strEncoding)
{  
	// 定义一个TiXmlDocument类指针  
	TiXmlDocument *pDoc = new TiXmlDocument();  
	if (NULL==pDoc)  
	{  
		return false;  
	}  
	pDoc->LoadFile(XmlFile);  
	TiXmlNode* pXmlFirst = pDoc->FirstChild();     
	if (NULL != pXmlFirst)    
	{    
		TiXmlDeclaration* pXmlDec = pXmlFirst->ToDeclaration();    
		if (NULL != pXmlDec)    
		{    
			strVersion = pXmlDec->Version();  
			strStandalone = pXmlDec->Standalone();  
			strEncoding = pXmlDec->Encoding();  
		}  
	}  
	return true;  
}  



	/*! 
	*  /brief 通过根节点和节点名获取节点指针。 
	* 
	*  /param pRootEle   xml文件的根节点。 
	*  /param strNodeName  要查询的节点名 
	*  /param Node      需要查询的节点指针 
	*  /return 是否找到。true为找到相应节点指针，false表示没有找到相应节点指针。 
	*/  
bool CXmlOperator::GetNodePointerByName(TiXmlElement* pRootEle,std::string &strNodeName,TiXmlElement* &Node)  
{  
	// 假如等于根节点名，就退出  
	if (strNodeName==pRootEle->Value())  
	{  
		Node = pRootEle;  
		return true;  
	}  
	TiXmlElement* pEle = pRootEle;    
	for (pEle = pRootEle->FirstChildElement(); pEle; pEle = pEle->NextSiblingElement())    
	{    
		//递归处理子节点，获取节点指针  
		if(CXmlOperator::GetNodePointerByName(pEle,strNodeName,Node))  
			return true;  
	}    
	return false;  
}   


//通过根节点和节点名以及属性名和值获取节点指针
bool CXmlOperator::GetNodePointerByName(TiXmlElement* pRootEle,std::string &strNodeName,std::string &strAttrName,std::string &strAttrValue,TiXmlElement* &Node)  
{
	// 假如等于根节点名，就退出  
	if (strNodeName==pRootEle->Value())  
	{  
		TiXmlAttribute* pAttr = NULL;   
		for (pAttr = pRootEle->FirstAttribute(); pAttr; pAttr = pAttr->Next())    
		{    
			std::string AttName = pAttr->Name();  
			std::string AttValue = pAttr->Value();  
			if(AttName==strAttrName && AttValue==strAttrValue)
			{
				Node = pRootEle;  
				return true;  
			}
		}    
	}  
	TiXmlElement* pEle = pRootEle;    
	for (pEle = pRootEle->FirstChildElement(); pEle; pEle = pEle->NextSiblingElement())    
	{    
		//递归处理子节点，获取节点指针  
		if(CXmlOperator::GetNodePointerByName(pEle,strNodeName,strAttrName,strAttrValue,Node))  
			return true;  
	}    
	return false;  
}


/*! 
			*  /brief 通过节点查询。 
			* 
			*  /param XmlFile   xml文件全路径。 
			*  /param strNodeName  要查询的节点名 
			*  /param strText      要查询的节点文本 
			*  /return 是否成功。true为成功，false表示失败。 
			*/  
bool CXmlOperator::QueryNode_Text(std::string XmlFile,std::string strNodeName,std::string &strText) 
{  
	// 定义一个TiXmlDocument类指针  
	TiXmlDocument *pDoc = new TiXmlDocument();  
	if (NULL==pDoc)  
	{  
		return false;  
	}  
	pDoc->LoadFile(XmlFile);  
	TiXmlElement *pRootEle = pDoc->RootElement();  
	if (NULL==pRootEle)  
	{  
		return false;  
	}  
	TiXmlElement *pNode = NULL;  
	CXmlOperator::GetNodePointerByName(pRootEle,strNodeName,pNode);  
	if (NULL!=pNode)  
	{  
		strText = pNode->GetText();   
		return true;  
	}  
	else  
	{  
		return false;  
	}  

}  

	/*! 
	*  /brief 通过节点查询属性。 
	* 
	*  /param XmlFile   xml文件全路径。 
	*  /param strNodeName  要查询的节点名 
	*  /param AttMap      要查询的属性值，这是一个map，前一个为属性名，后一个为属性值 
	*  /return 是否成功。true为成功，false表示失败。 
	*/  
bool CXmlOperator::QueryNode_Attribute(std::string XmlFile,std::string strNodeName,std::map<std::string,std::string> &AttMap)  
{  
	// 定义一个TiXmlDocument类指针  
	typedef std::pair <std::string,std::string> String_Pair;  
	TiXmlDocument *pDoc = new TiXmlDocument();  
	if (NULL==pDoc)  
	{  
		return false;  
	}  
	pDoc->LoadFile(XmlFile);  
	TiXmlElement *pRootEle = pDoc->RootElement();  
	if (NULL==pRootEle)  
	{  
		return false;  
	}  
	TiXmlElement *pNode = NULL;  

	VecTiXmlElement vecTiXmlElement;

	CXmlOperator::GetNodePointerByName(pRootEle,strNodeName,pNode);  

	if (NULL!=pNode)  
	{  
		TiXmlAttribute* pAttr = NULL;   
		for (pAttr = pNode->FirstAttribute(); pAttr; pAttr = pAttr->Next())    
		{    
			std::string strAttName = pAttr->Name();  
			std::string strAttValue = pAttr->Value();  
			AttMap.insert(String_Pair(strAttName,strAttValue));  
		}    
		return true;  
	}  
	else  
	{  
		return false;  
	}  
	return true;  
}  

// 按节点名和某一属性 查询该节点所有属性
bool CXmlOperator::QueryNode_Attribute(std::string XmlFile,std::string strNodeName,std::string strAttrName,std::string strAttrValue,std::map<std::string,std::string> &AttMap)  
{

	typedef std::pair <std::string,std::string> String_Pair;  
	TiXmlDocument *pDoc = new TiXmlDocument();  
	if (NULL==pDoc)  
	{  
		return false;  
	}  
	pDoc->LoadFile(XmlFile);  
	TiXmlElement *pRootEle = pDoc->RootElement();  
	if (NULL==pRootEle)  
	{  
		return false;  
	}  
	TiXmlElement *pNode = NULL;  

	VecTiXmlElement vecTiXmlElement;

	CXmlOperator::GetNodePointerByName(pRootEle,strNodeName,strAttrName,strAttrValue,pNode);  

	if (NULL!=pNode)  
	{  
		TiXmlAttribute* pAttr = NULL;   
		for (pAttr = pNode->FirstAttribute(); pAttr; pAttr = pAttr->Next())    
		{    
			std::string strAttName = pAttr->Name();  
			std::string strAttValue = pAttr->Value();  
			AttMap.insert(String_Pair(strAttName,strAttValue));  
		}    
		return true;  
	}  
	else  
	{  
		return false;  
	}  
	return true;  

}

VecTiXmlElement CXmlOperator::QueryNode_Element(std::string XmlFile,std::string strNodeName,std::string strSubNodeName)
{
	VecTiXmlElement vecTiXmlElement;
	vecTiXmlElement.clear();

	TiXmlDocument *pDoc = new TiXmlDocument();  
	if (NULL==pDoc)  
	{  
		return vecTiXmlElement;  
	}  

	pDoc->LoadFile(XmlFile);  
	TiXmlElement *pRootEle = pDoc->RootElement();  
	if (NULL==pRootEle)  
	{  
		return vecTiXmlElement;  
	}  

	TiXmlElement *pNode = NULL;  

	CXmlOperator::GetNodePointerByName(pRootEle,strNodeName,pNode);  
	if (NULL!=pNode)  
	{
		TiXmlElement* pEle = pNode;    
		for (pEle = pNode->FirstChildElement(); pEle; pEle = pEle->NextSiblingElement())    
		{    
			if(pEle->Value()==strSubNodeName)
			{
				vecTiXmlElement.push_back(pEle);
			}

		}    
	}
	return vecTiXmlElement;  
}

bool CXmlOperator::QueryNode_AttributeText(std::string XmlFile,std::string strNodeName,std::string strSubNodeName,std::string strAttrName,std::string &strText)
{

	TiXmlDocument *pDoc = new TiXmlDocument();  
	if (NULL==pDoc)  
	{  
		return false;  
	}  

	pDoc->LoadFile(XmlFile);  
	TiXmlElement *pRootEle = pDoc->RootElement();  
	if (NULL==pRootEle)  
	{  
		return false;  
	}  

	TiXmlElement *pNode = NULL;  

	CXmlOperator::GetNodePointerByName(pRootEle,strNodeName,pNode);  
	if (NULL!=pNode)  
	{
		TiXmlElement* pEle = pNode;    
		for (pEle = pNode->FirstChildElement(); pEle; pEle = pEle->NextSiblingElement())    
		{    
			if(pEle->Value()==strSubNodeName)
			{
				
				TiXmlAttribute* pAttr = NULL;   
				for (pAttr = pEle->FirstAttribute(); pAttr; pAttr = pAttr->Next())    
				{    
					std::string strName = pAttr->Name();  
					std::string strValue = pAttr->Value();  
					if(strName==strAttrName)
					{
						strText=strValue;
						return true;
					}
				}

			}

		}    
	}
	return true;
}

	/*! 
	*  /brief 删除指定节点的值。 
	* 
	*  /param XmlFile xml文件全路径。 
	*  /param strNodeName 指定的节点名。 
	*  /return 是否成功。true为成功，false表示失败。 
	*/  
bool CXmlOperator::DelNode(std::string XmlFile,std::string strNodeName) 
{  
	// 定义一个TiXmlDocument类指针  
	TiXmlDocument *pDoc = new TiXmlDocument();  
	if (NULL==pDoc)  
	{  
		return false;  
	}  
	pDoc->LoadFile(XmlFile);  
	TiXmlElement *pRootEle = pDoc->RootElement();  
	if (NULL==pRootEle)  
	{  
		return false;  
	}  
	TiXmlElement *pNode = NULL;  
	CXmlOperator::GetNodePointerByName(pRootEle,strNodeName,pNode);  
	// 假如是根节点  
	if (pRootEle==pNode)  
	{  
		if(pDoc->RemoveChild(pRootEle))  
		{  
			pDoc->SaveFile(XmlFile);  
			return true;  
		}  
		else   
			return false;  
	}  
	// 假如是其它节点  
	if (NULL!=pNode)  
	{  
		TiXmlNode *pParNode =  pNode->Parent();  
		if (NULL==pParNode)  
		{  
			return false;  
		}  

		TiXmlElement* pParentEle = pParNode->ToElement();  
		if (NULL!=pParentEle)  
		{  
			if(pParentEle->RemoveChild(pNode))  
				pDoc->SaveFile(XmlFile);  
			else  
				return false;  
		}  
	}  
	else  
	{  
		return false;  
	}  
	return false;  
}  


	/*! 
	*  /brief 修改指定节点的文本。 
	* 
	*  /param XmlFile xml文件全路径。 
	*  /param strNodeName 指定的节点名。 
	*  /param strText 重新设定的文本的值 
	*  /return 是否成功。true为成功，false表示失败。 
	*/  
bool CXmlOperator::ModifyNode_Text(std::string XmlFile,std::string strNodeName,std::string strText)  
{  
	// 定义一个TiXmlDocument类指针  
	TiXmlDocument *pDoc = new TiXmlDocument();  
	if (NULL==pDoc)  
	{  
		return false;  
	}  
	pDoc->LoadFile(XmlFile);  
	TiXmlElement *pRootEle = pDoc->RootElement();  
	if (NULL==pRootEle)  
	{  
		return false;  
	}  
	TiXmlElement *pNode = NULL;  
	CXmlOperator::GetNodePointerByName(pRootEle,strNodeName,pNode);  
	if (NULL!=pNode)  
	{  
		pNode->Clear();  // 首先清除所有文本  
		// 然后插入文本，保存文件  
		TiXmlText *pValue = new TiXmlText(strText);  
		pNode->LinkEndChild(pValue);  
		pDoc->SaveFile(XmlFile);  
		return true;  
	}  
	else  
		return false;  
}  


/*! 
	*  /brief 修改指定节点的属性值。 
	* 
	*  /param XmlFile xml文件全路径。 
	*  /param strNodeName 指定的节点名。 
	*  /param AttMap 重新设定的属性值，这是一个map，前一个为属性名，后一个为属性值 
	*  /return 是否成功。true为成功，false表示失败。 
	*/  
bool CXmlOperator::ModifyNode_Attribute(std::string XmlFile,std::string strNodeName, std::map<std::string,std::string> &AttMap)
{  
	typedef std::pair <std::string,std::string> String_Pair;  
	// 定义一个TiXmlDocument类指针  
	TiXmlDocument *pDoc = new TiXmlDocument();  
	if (NULL==pDoc)  
	{  
		return false;  
	}  
	pDoc->LoadFile(XmlFile);  
	TiXmlElement *pRootEle = pDoc->RootElement();  
	if (NULL==pRootEle)  
	{  
		return false;  
	}  

	TiXmlElement *pNode = NULL;  
	CXmlOperator::GetNodePointerByName(pRootEle,strNodeName,pNode);  
	if (NULL!=pNode)  
	{  
		TiXmlAttribute* pAttr = NULL;   
		std::string strAttName = "";  
		std::string strAttValue = "";  
		for (pAttr = pNode->FirstAttribute(); pAttr; pAttr = pAttr->Next())    
		{    
			strAttName = pAttr->Name();  
			std::map<std::string,std::string>::iterator iter;  
			for (iter=AttMap.begin();iter!=AttMap.end();iter++)  
			{  
				if (strAttName==iter->first)  
				{  
					pAttr->SetValue(iter->second);  
				}  
			}  
		}    
		pDoc->SaveFile(XmlFile);  
		return true;  
	}  
	else  
	{  
		return false;  
	}  
}  


//根据节点名 属性名和值 得到节点并修改其的属性值
bool CXmlOperator::ModifyNode_Attribute(std::string XmlFile,std::string strNodeName,std::string strAttrName,std::string strAttrValue, std::map<std::string,std::string> &AttMap)
{
	typedef std::pair <std::string,std::string> String_Pair;  
	// 定义一个TiXmlDocument类指针  
	TiXmlDocument *pDoc = new TiXmlDocument();  
	if (NULL==pDoc)  
	{  
		return false;  
	}  
	pDoc->LoadFile(XmlFile);  
	TiXmlElement *pRootEle = pDoc->RootElement();  
	if (NULL==pRootEle)  
	{  
		return false;  
	}  

	TiXmlElement *pNode = NULL;  
	CXmlOperator::GetNodePointerByName(pRootEle,strNodeName,strAttrName,strAttrValue,pNode);  
	if (NULL!=pNode)  
	{  
		TiXmlAttribute* pAttr = NULL;   
		std::string strAttName = "";  
		std::string strAttValue = "";  
		for (pAttr = pNode->FirstAttribute(); pAttr; pAttr = pAttr->Next())    
		{    
			strAttName = pAttr->Name();  
			std::map<std::string,std::string>::iterator iter;  
			for (iter=AttMap.begin();iter!=AttMap.end();iter++)  
			{  
				if (strAttName==iter->first)  
				{  
					pAttr->SetValue(iter->second);  
				}  
			}  
		}    
		pDoc->SaveFile(XmlFile);  
		return true;  
	}  
	else  
	{  
		return false;  
	}  

}

	/*! 
	*  /brief 增加指定节点的文本。 
	* 
	*  /param XmlFile xml文件全路径。 
	*  /param strParNodeName 要增加的节点的父节点。 
	*  /param strNodeName 指定的节点名。 
	*  /param strText 要增加的文本 
	*  /return 是否成功。true为成功，false表示失败。 
	*/  
bool CXmlOperator::AddNode_Text(std::string XmlFile,std::string strParNodeName,std::string strNodeName,std::string strText)  
{  
	// 定义一个TiXmlDocument类指针  
	TiXmlDocument *pDoc = new TiXmlDocument();  
	if (NULL==pDoc)  
	{  
		return false;  
	}  
	pDoc->LoadFile(XmlFile);  
	TiXmlElement *pRootEle = pDoc->RootElement();  
	if (NULL==pRootEle)  
	{  
		return false;  
	}  
	TiXmlElement *pNode = NULL;  
	CXmlOperator::GetNodePointerByName(pRootEle,strParNodeName,pNode);  
	if (NULL!=pNode)  
	{  
		// 生成子节点：pNewNode  
		TiXmlElement *pNewNode = new TiXmlElement(strNodeName);  
		if (NULL==pNewNode)  
		{  
			return false;  
		}  
		// 设置节点文本，然后插入节点  
		TiXmlText *pNewValue = new TiXmlText(strText);  
		pNewNode->LinkEndChild(pNewValue);  
		pNode->InsertEndChild(*pNewNode);  
		pDoc->SaveFile(XmlFile);  
		return true;  
	}  
	else  
		return false;  

}  


	/*! 
	*  /brief 增加节点。 
	* 
	*  /param XmlFile xml文件全路径。 
	*  /param strParNodeName 要增加的节点的父节点。 
	*  /param strNodeName 指定的节点名。 
	*  /param AttMap 要增加的节点设定的属性值，这是一个map，前一个为属性名，后一个为属性值 
	*  /return 是否成功。true为成功，false表示失败。 
	*/  
bool CXmlOperator::AddNode_Attribute(std::string XmlFile,std::string strParNodeName,std::string strNodeName,std::map<std::string,std::string> &AttMap)  
{  
	// 定义一个TiXmlDocument类指针  
	TiXmlDocument *pDoc = new TiXmlDocument();  
	if (NULL==pDoc)  
	{  
		return false;  
	}  
	pDoc->LoadFile(XmlFile);  
	TiXmlElement *pRootEle = pDoc->RootElement();  
	if (NULL==pRootEle)  
	{  
		return false;  
	}  
	TiXmlElement *pNode = NULL;  
	CXmlOperator::GetNodePointerByName(pRootEle,strParNodeName,pNode);  
	if (NULL!=pNode)  
	{  
		// 生成子节点：pNewNode  
		TiXmlElement *pNewNode = new TiXmlElement(strNodeName);  
		if (NULL==pNewNode)  
		{  
			return false;  
		}  
		// 设置节点的属性值，然后插入节点  
		std::map<std::string,std::string>::iterator iter;  
		for (iter=AttMap.begin();iter!=AttMap.end();iter++)  
		{  
			pNewNode->SetAttribute(iter->first,iter->second);  
		}  
		pNode->InsertEndChild(*pNewNode);  
		pDoc->SaveFile(XmlFile);  
		return true;  
	}  
	else  
		return false;  
}  