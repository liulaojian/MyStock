#include "XmlOperator.h"

CXmlOperator::CXmlOperator()
{


}

CXmlOperator::~CXmlOperator()
{


}

/*! 
	*  /brief ��ȡxml�ļ��������� 
	* 
	*  /param XmlFile xml�ļ�ȫ·���� 
	*  /param strVersion  Version����ֵ 
	*  /param strStandalone Standalone����ֵ 
	*  /param strEncoding Encoding����ֵ 
	*  /return �Ƿ�ɹ���trueΪ�ɹ���false��ʾʧ�ܡ� 
	*/  
bool CXmlOperator::GetXmlDeclare(std::string XmlFile, std::string &strVersion,  std::string &strStandalone,  std::string &strEncoding)
{  
	// ����һ��TiXmlDocument��ָ��  
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
	*  /brief ͨ�����ڵ�ͽڵ�����ȡ�ڵ�ָ�롣 
	* 
	*  /param pRootEle   xml�ļ��ĸ��ڵ㡣 
	*  /param strNodeName  Ҫ��ѯ�Ľڵ��� 
	*  /param Node      ��Ҫ��ѯ�Ľڵ�ָ�� 
	*  /return �Ƿ��ҵ���trueΪ�ҵ���Ӧ�ڵ�ָ�룬false��ʾû���ҵ���Ӧ�ڵ�ָ�롣 
	*/  
bool CXmlOperator::GetNodePointerByName(TiXmlElement* pRootEle,std::string &strNodeName,TiXmlElement* &Node)  
{  
	// ������ڸ��ڵ��������˳�  
	if (strNodeName==pRootEle->Value())  
	{  
		Node = pRootEle;  
		return true;  
	}  
	TiXmlElement* pEle = pRootEle;    
	for (pEle = pRootEle->FirstChildElement(); pEle; pEle = pEle->NextSiblingElement())    
	{    
		//�ݹ鴦���ӽڵ㣬��ȡ�ڵ�ָ��  
		if(CXmlOperator::GetNodePointerByName(pEle,strNodeName,Node))  
			return true;  
	}    
	return false;  
}   


//ͨ�����ڵ�ͽڵ����Լ���������ֵ��ȡ�ڵ�ָ��
bool CXmlOperator::GetNodePointerByName(TiXmlElement* pRootEle,std::string &strNodeName,std::string &strAttrName,std::string &strAttrValue,TiXmlElement* &Node)  
{
	// ������ڸ��ڵ��������˳�  
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
		//�ݹ鴦���ӽڵ㣬��ȡ�ڵ�ָ��  
		if(CXmlOperator::GetNodePointerByName(pEle,strNodeName,strAttrName,strAttrValue,Node))  
			return true;  
	}    
	return false;  
}


/*! 
			*  /brief ͨ���ڵ��ѯ�� 
			* 
			*  /param XmlFile   xml�ļ�ȫ·���� 
			*  /param strNodeName  Ҫ��ѯ�Ľڵ��� 
			*  /param strText      Ҫ��ѯ�Ľڵ��ı� 
			*  /return �Ƿ�ɹ���trueΪ�ɹ���false��ʾʧ�ܡ� 
			*/  
bool CXmlOperator::QueryNode_Text(std::string XmlFile,std::string strNodeName,std::string &strText) 
{  
	// ����һ��TiXmlDocument��ָ��  
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
	*  /brief ͨ���ڵ��ѯ���ԡ� 
	* 
	*  /param XmlFile   xml�ļ�ȫ·���� 
	*  /param strNodeName  Ҫ��ѯ�Ľڵ��� 
	*  /param AttMap      Ҫ��ѯ������ֵ������һ��map��ǰһ��Ϊ����������һ��Ϊ����ֵ 
	*  /return �Ƿ�ɹ���trueΪ�ɹ���false��ʾʧ�ܡ� 
	*/  
bool CXmlOperator::QueryNode_Attribute(std::string XmlFile,std::string strNodeName,std::map<std::string,std::string> &AttMap)  
{  
	// ����һ��TiXmlDocument��ָ��  
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

// ���ڵ�����ĳһ���� ��ѯ�ýڵ���������
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
	*  /brief ɾ��ָ���ڵ��ֵ�� 
	* 
	*  /param XmlFile xml�ļ�ȫ·���� 
	*  /param strNodeName ָ���Ľڵ����� 
	*  /return �Ƿ�ɹ���trueΪ�ɹ���false��ʾʧ�ܡ� 
	*/  
bool CXmlOperator::DelNode(std::string XmlFile,std::string strNodeName) 
{  
	// ����һ��TiXmlDocument��ָ��  
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
	// �����Ǹ��ڵ�  
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
	// �����������ڵ�  
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
	*  /brief �޸�ָ���ڵ���ı��� 
	* 
	*  /param XmlFile xml�ļ�ȫ·���� 
	*  /param strNodeName ָ���Ľڵ����� 
	*  /param strText �����趨���ı���ֵ 
	*  /return �Ƿ�ɹ���trueΪ�ɹ���false��ʾʧ�ܡ� 
	*/  
bool CXmlOperator::ModifyNode_Text(std::string XmlFile,std::string strNodeName,std::string strText)  
{  
	// ����һ��TiXmlDocument��ָ��  
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
		pNode->Clear();  // ������������ı�  
		// Ȼ������ı��������ļ�  
		TiXmlText *pValue = new TiXmlText(strText);  
		pNode->LinkEndChild(pValue);  
		pDoc->SaveFile(XmlFile);  
		return true;  
	}  
	else  
		return false;  
}  


/*! 
	*  /brief �޸�ָ���ڵ������ֵ�� 
	* 
	*  /param XmlFile xml�ļ�ȫ·���� 
	*  /param strNodeName ָ���Ľڵ����� 
	*  /param AttMap �����趨������ֵ������һ��map��ǰһ��Ϊ����������һ��Ϊ����ֵ 
	*  /return �Ƿ�ɹ���trueΪ�ɹ���false��ʾʧ�ܡ� 
	*/  
bool CXmlOperator::ModifyNode_Attribute(std::string XmlFile,std::string strNodeName, std::map<std::string,std::string> &AttMap)
{  
	typedef std::pair <std::string,std::string> String_Pair;  
	// ����һ��TiXmlDocument��ָ��  
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


//���ݽڵ��� ��������ֵ �õ��ڵ㲢�޸��������ֵ
bool CXmlOperator::ModifyNode_Attribute(std::string XmlFile,std::string strNodeName,std::string strAttrName,std::string strAttrValue, std::map<std::string,std::string> &AttMap)
{
	typedef std::pair <std::string,std::string> String_Pair;  
	// ����һ��TiXmlDocument��ָ��  
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
	*  /brief ����ָ���ڵ���ı��� 
	* 
	*  /param XmlFile xml�ļ�ȫ·���� 
	*  /param strParNodeName Ҫ���ӵĽڵ�ĸ��ڵ㡣 
	*  /param strNodeName ָ���Ľڵ����� 
	*  /param strText Ҫ���ӵ��ı� 
	*  /return �Ƿ�ɹ���trueΪ�ɹ���false��ʾʧ�ܡ� 
	*/  
bool CXmlOperator::AddNode_Text(std::string XmlFile,std::string strParNodeName,std::string strNodeName,std::string strText)  
{  
	// ����һ��TiXmlDocument��ָ��  
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
		// �����ӽڵ㣺pNewNode  
		TiXmlElement *pNewNode = new TiXmlElement(strNodeName);  
		if (NULL==pNewNode)  
		{  
			return false;  
		}  
		// ���ýڵ��ı���Ȼ�����ڵ�  
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
	*  /brief ���ӽڵ㡣 
	* 
	*  /param XmlFile xml�ļ�ȫ·���� 
	*  /param strParNodeName Ҫ���ӵĽڵ�ĸ��ڵ㡣 
	*  /param strNodeName ָ���Ľڵ����� 
	*  /param AttMap Ҫ���ӵĽڵ��趨������ֵ������һ��map��ǰһ��Ϊ����������һ��Ϊ����ֵ 
	*  /return �Ƿ�ɹ���trueΪ�ɹ���false��ʾʧ�ܡ� 
	*/  
bool CXmlOperator::AddNode_Attribute(std::string XmlFile,std::string strParNodeName,std::string strNodeName,std::map<std::string,std::string> &AttMap)  
{  
	// ����һ��TiXmlDocument��ָ��  
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
		// �����ӽڵ㣺pNewNode  
		TiXmlElement *pNewNode = new TiXmlElement(strNodeName);  
		if (NULL==pNewNode)  
		{  
			return false;  
		}  
		// ���ýڵ������ֵ��Ȼ�����ڵ�  
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