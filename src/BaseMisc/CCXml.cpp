#include "stdafx.h"
#include "CCXml.h"

CCXml::CCXml()
{
}

CCXml::~CCXml()
{
}

HRESULT CCXml::FinalConstruct()
{
	Common::Util::CreateObject(&m_pXmlData) ;
	DEBUG_ASSERT(m_pXmlData) ;

	Common::Util::GetService(&m_pFileroute) ;
	DEBUG_ASSERT(m_pFileroute) ;
	return S_OK ;
}

HRESULT CCXml::LoadXmlFromFile(BSTR bstrFile)
{
	DEBUG_ASSERT(this->m_pFileroute) ;
	IF_RETURN(NULL == this->m_pFileroute, E_FAIL) ;

	CComPtr<ICVarBuffer> pBuffer ;
	Common::Util::CreateObject(&pBuffer) ;
	this->m_pFileroute->ReadWholeFile(bstrFile, pBuffer) ;
	return this->LoadXmlFromVarBuffer(pBuffer) ;


	//    {
	//        IF_RETURN(NULL == this->m_pXmlData, E_FAIL) ;
	//        this->m_pXmlData->EraseAll() ;
	//
	//        pugi::xml_document      _doc ;
	//        pugi::xml_parse_result  _res = _doc.load_file(CComBSTR(bstrFile)) ;
	//        if (_res)
	//        {
	//            return this->_parase_xml_data(_doc.first_child(), this->m_pXmlData) ;
	//        }
	//#ifdef _DEBUG
	//        else
	//        {
	//            CString _str ;
	//            _str.Format(_T("XML parsed with errors, attr value: %S\n\
	//                           Error description: %S\n\
	//                           Error offset: %d\n")
	//                           , _doc.child(_T("node")).attribute(_T("attr")).value()
	//                           , _res.description()
	//                           , _res.offset) ;
	//            DEBUG_ASSERT_MSG(FALSE, _str) ;
	//        }
	//#endif//_DEBUG
	//        return E_FAIL ;
	//    }
	//    return E_FAIL ;
}

HRESULT CCXml::LoadXmlFromVarBuffer(ICVarBuffer* pVarBuffer)
{
	DEBUG_ASSERT(pVarBuffer) ;
	IF_RETURN(NULL == pVarBuffer, E_INVALIDARG) ;

	LPBYTE  pbBuffer = NULL ;
	DWORD   dwBufferLen = 0 ;
	pVarBuffer->GetBuffer(&pbBuffer) ;
	pVarBuffer->GetSize(&dwBufferLen) ;
	return this->LoadXmlFromBuffer(pbBuffer, (LONG)(dwBufferLen)) ;
}

HRESULT CCXml::LoadXmlFromBuffer(BYTE* pbBuffer, LONG lBufferLen)
{
	IF_RETURN(NULL == this->m_pXmlData, E_FAIL) ;
	this->m_pXmlData->Clear() ;

	pugi::xml_document      _doc ;
	pugi::xml_parse_result  _res = _doc.load_buffer_inplace(pbBuffer, (size_t)lBufferLen) ;
	if (_res)
	{
		return this->_parase_xml_data(_doc.first_child(), this->m_pXmlData) ;
	}
#ifdef _DEBUG
	else
	{

		CString _str ;
		_str.Format(_T("XML parsed with errors, attr value: %S\n\
					   Error description: %S\n\
					   Error offset: %d\n")
					   , _doc.child(_T("node")).attribute(_T("attr")).value()
					   , _res.description()
					   , _res.offset) ;
		DEBUG_ASSERT_MSG(FALSE, _str) ;
	}
#endif//_DEBUG
	return E_FAIL ;
}

HRESULT CCXml::GetXmlData(ICVarData** pOutXmlData)
{
	DEBUG_ASSERT(pOutXmlData) ;
	IF_RETURN(NULL == pOutXmlData, E_INVALIDARG) ;
	*pOutXmlData = NULL ;
	if (this->m_pXmlData)
	{
		return this->m_pXmlData->QueryInterface(__uuidof(ICVarData), (VOID**)pOutXmlData) ;
	}
	return E_FAIL ;
}

HRESULT CCXml::Clear()
{
	this->m_pXmlData = NULL ;
	return S_OK ;
}

HRESULT CCXml::_parase_xml_data(pugi::xml_node& _xml_node, ICVarData* pXmlData)
{
	DEBUG_ASSERT(pXmlData) ;
	IF_RETURN(NULL == pXmlData, E_INVALIDARG) ;
	if (_xml_node)
	{
		pXmlData->SetString(CComBSTR(XML::XML_TAG), CComBSTR(_xml_node.name())) ;
		pXmlData->SetString(CComBSTR(XML::XML_VALUE), CComBSTR(_xml_node.value())) ;

		for (pugi::xml_attribute _attr = _xml_node.first_attribute(); _attr; _attr = _attr.next_attribute())
		{
			pXmlData->SetString(CComBSTR(_attr.name()), CComBSTR(_attr.value())) ;
		}

		CComPtr<ICVarArray> pXmlChildrenArray ;
		
		pXmlData->SetNewVarArray(CComBSTR(XML::XML_CHILDREN), &pXmlChildrenArray) ;
		DEBUG_ASSERT(pXmlChildrenArray) ;
		IF_RETURN(NULL == pXmlChildrenArray, E_FAIL) ;

		for (pugi::xml_node _node = _xml_node.first_child(); _node; _node = _node.next_sibling())
		{
			IF_CONTINUE(!_node) ;

			CComPtr<ICVarData> pChildNodeData ;
			pXmlChildrenArray->AddNewVarData(&pChildNodeData) ;
			DEBUG_ASSERT(pChildNodeData) ;
			IF_CONTINUE(NULL == pChildNodeData) ;

			this->_parase_xml_data(_node, pChildNodeData) ;
		}
		
	}
	return S_OK ;
}
