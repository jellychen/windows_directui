#include "stdafx.h"
#include "CSConfig.h"

CSConfig::CSConfig()
{
}

CSConfig::~CSConfig()
{
}

HRESULT CSConfig::OnInit()
{
	return S_OK ;
}

HRESULT CSConfig::LoadConfigFromFile(BSTR bstrFile)
{
	CComPtr<ICXml> pXmlParser ;
	Common::Util::CreateObject(&pXmlParser) ;
	DEBUG_ASSERT(pXmlParser) ;
	IF_RETURN(NULL == pXmlParser, E_FAIL) ;
	IF_RETURN(!SUCCEEDED(pXmlParser->LoadXmlFromFile(bstrFile)), E_FAIL) ;
	CComPtr<ICVarData> pXmlData ;
	IF_RETURN(!SUCCEEDED(pXmlParser->GetXmlData(&pXmlData)), E_FAIL) ;
	return this->_parse_config(pXmlData) ? S_OK : E_FAIL ;
}

HRESULT CSConfig::LoadConfigFromVarBuffer(ICVarBuffer* pVarBuffer)
{
	CComPtr<ICXml> pXmlParser ;
	Common::Util::CreateObject(&pXmlParser) ;
	DEBUG_ASSERT(pXmlParser) ;
	IF_RETURN(NULL == pXmlParser, E_FAIL) ;
	IF_RETURN(!SUCCEEDED(pXmlParser->LoadXmlFromVarBuffer(pVarBuffer)), E_FAIL) ;
	CComPtr<ICVarData> pXmlData ;
	IF_RETURN(!SUCCEEDED(pXmlParser->GetXmlData(&pXmlData)), E_FAIL) ;
	return this->_parse_config(pXmlData) ? S_OK : E_FAIL ;
}

HRESULT CSConfig::LoadConfigFromBuffer(BYTE* pbBuffer, LONG lBufferLen)
{
	CComPtr<ICXml> pXmlParser ;
	Common::Util::CreateObject(&pXmlParser) ;
	DEBUG_ASSERT(pXmlParser) ;
	IF_RETURN(NULL == pXmlParser, E_FAIL) ;
	IF_RETURN(!SUCCEEDED(pXmlParser->LoadXmlFromBuffer(pbBuffer, lBufferLen)), E_FAIL) ;
	CComPtr<ICVarData> pXmlData ;
	IF_RETURN(!SUCCEEDED(pXmlParser->GetXmlData(&pXmlData)), E_FAIL) ;
	return this->_parse_config(pXmlData) ? S_OK : E_FAIL ;
}

BOOL CSConfig::_parse_config(ICVarData* pXmlData)
{
	DEBUG_ASSERT(pXmlData) ;
	IF_RETURN(NULL == pXmlData, FALSE) ;

	CComBSTR bstrTopTagName ;
	pXmlData->GetString(CComBSTR(XML::XML_TAG), &bstrTopTagName) ;
	IF_RETURN(CString(CONFIG::CONFIG_TOP_TAG) != CString(bstrTopTagName), FALSE) ;
	
	CComPtr<ICVarArray> pVarChildrenArray ;
	pXmlData->GetVarArray(CComBSTR(XML::XML_CHILDREN), &pVarChildrenArray) ;
	IF_RETURN(NULL == pVarChildrenArray, FALSE) ;

	LONG lArrayCount = 0 ;
	pVarChildrenArray->GetArrayCount(&lArrayCount) ;
	for (INT i = 0; i < lArrayCount; ++i)
	{
		CComPtr<ICVarData> pChildData ;
		pVarChildrenArray->GetVarData(i, &pChildData) ;
		IF_CONTINUE(NULL == pChildData) ;

		CComBSTR bstrTagName ;
		pChildData->GetString(CComBSTR(XML::XML_TAG), &bstrTagName) ;
		CString strTagName = bstrTagName ;

		if (0 == strTagName.CompareNoCase(CONFIG::OBJECT::CONFIG_OBJECT))
		{
			this->_parse_config_detail(pChildData, CONFIG::TYPE_OBJECT) ;
		}
		else if (0 == strTagName.CompareNoCase(CONFIG::SERVICE::CONFIG_SERVICE))
		{
			this->_parse_config_detail(pChildData, CONFIG::TYPE_SERVICE) ;
		}
		else
		{
			DEBUG_ASSERT_MSG(FALSE, _T("Config Unknow Tag %s ..."), strTagName) ;
		}
	}
	return TRUE ;
}

BOOL CSConfig::_parse_config_detail(ICVarData* pXmlData, INT nType)
{
	DEBUG_ASSERT(pXmlData) ;
	IF_RETURN(NULL == pXmlData, FALSE) ;

	CComPtr<ICVarArray> pVarChildrenArray ;
	pXmlData->GetVarArray(CComBSTR(XML::XML_CHILDREN), &pVarChildrenArray) ;
	IF_RETURN(NULL == pVarChildrenArray, E_FAIL) ;

	LONG lArrayCount = 0 ;
	pVarChildrenArray->GetArrayCount(&lArrayCount) ;
	for (INT i = 0; i < lArrayCount; ++i)
	{
		CComPtr<ICVarData> pXmlChildData ;
		pVarChildrenArray->GetVarData(i, &pXmlChildData) ;
		IF_CONTINUE(NULL == pXmlChildData) ;

		CComBSTR bstrTagName ;
		pXmlChildData->GetString(CComBSTR(XML::XML_TAG), &bstrTagName) ;

		if (CONFIG::TYPE_OBJECT == nType)
		{
			IF_CONTINUE(CString(bstrTagName) != CString(CONFIG::OBJECT::CONFIG_OBJECT_TAG)) ;
			CComBSTR bstrIID, bstrCLSID, bstrModule ;
			pXmlChildData->GetString(CComBSTR(CONFIG::OBJECT::CONFIG_OBJECT_IID), &bstrIID) ;
			pXmlChildData->GetString(CComBSTR(CONFIG::OBJECT::CONFIG_OBJECT_CLSID), &bstrCLSID) ;
			pXmlChildData->GetString(CComBSTR(CONFIG::OBJECT::CONFIG_OBJECT_MODULE), &bstrModule) ;
			Common::Util::RegisterComponentString(bstrIID, bstrCLSID, bstrModule) ;
		}

		else if (CONFIG::TYPE_SERVICE == nType)
		{
			IF_CONTINUE(CString(bstrTagName) != CString(CONFIG::SERVICE::CONFIG_SERVICE_TAG)) ;
			CComBSTR bstrIID, bstrCLSID, bstrModule ;
			pXmlChildData->GetString(CComBSTR(CONFIG::SERVICE::CONFIG_SERVICE_IID), &bstrIID) ;
			pXmlChildData->GetString(CComBSTR(CONFIG::SERVICE::CONFIG_SERVICE_CLSID), &bstrCLSID) ;
			pXmlChildData->GetString(CComBSTR(CONFIG::SERVICE::CONFIG_SERVICE_MODULE), &bstrModule) ;
			Common::Util::RegisterServiceString(bstrIID, bstrCLSID, bstrModule) ;
		}
	}
	return S_OK ;
}