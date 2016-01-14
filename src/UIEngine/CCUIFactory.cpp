#include "stdafx.h"
#include "CCUIFactory.h"

CCUIFactory::CCUIFactory()
{
}

CCUIFactory::~CCUIFactory()
{

}

HRESULT CCUIFactory::OnInit()
{
	Common::Util::GetService(&m_pFileroute)	;
	DEBUG_ASSERT(m_pFileroute) ;

	return S_OK ;
}

HRESULT CCUIFactory::SetTagIID(BSTR bstrTagName, REFIID iid)
{
	this->m_mapTagPool[bstrTagName] = iid ;
	return S_OK ;
}

HRESULT CCUIFactory::GetTagIID(BSTR bstrTagName, IID* piid)
{
	DEBUG_ASSERT(piid) ;
	IF_RETURN(NULL == piid, E_INVALIDARG) ;

	MAP_TAG_POOL::iterator _it = this->m_mapTagPool.find(bstrTagName) ;
	if (this->m_mapTagPool.end() != _it)
	{
		*piid = _it->second ;
		return S_OK ;
	}
	return E_FAIL ;
}

HRESULT CCUIFactory::DelTagIID(BSTR bstrTagName)
{
	MAP_TAG_POOL::iterator _it = this->m_mapTagPool.find(bstrTagName) ;
	if (this->m_mapTagPool.end() != _it)
	{
		this->m_mapTagPool.erase(_it) ;
	}
	return S_OK ;
}

HRESULT CCUIFactory::Clear()
{
	this->m_mapTagPool.clear() ;
	return S_OK ;
}

HRESULT CCUIFactory::LoadTagConfigFromFile(BSTR bstrFile)
{
	CComPtr<ICXml> _pXmlParser ;
	Common::Util::CreateObject(&_pXmlParser) ;
	IF_RETURN(NULL == _pXmlParser, E_FAIL) ;

	IF_RETURN(!SUCCEEDED(_pXmlParser->LoadXmlFromFile(bstrFile)), E_FAIL) ;
	CComPtr<ICVarData> _pXmlData ;
	IF_RETURN(!SUCCEEDED(_pXmlParser->GetXmlData(&_pXmlData)), E_FAIL) ;

	return this->_parse_factory_config(_pXmlData) ? S_OK : E_FAIL ;
}

HRESULT CCUIFactory::LoadTagConfigFromBuffer(BYTE* pBuffer, DWORD dwLen)
{
	DEBUG_ASSERT(pBuffer) ;
	IF_RETURN(NULL == pBuffer, E_FAIL) ;

	CComPtr<ICXml> _pXmlParser ;
	Common::Util::CreateObject(&_pXmlParser) ;
	IF_RETURN(NULL == _pXmlParser, E_FAIL) ;

	IF_RETURN(!SUCCEEDED(_pXmlParser->LoadXmlFromBuffer(pBuffer, dwLen)), E_FAIL) ;
	CComPtr<ICVarData> _pXmlData ;
	IF_RETURN(!SUCCEEDED(_pXmlParser->GetXmlData(&_pXmlData)), E_FAIL) ;

	return this->_parse_factory_config(_pXmlData) ? S_OK : E_FAIL ;
}

HRESULT CCUIFactory::LoadTagConfigFromVarBuffer(ICVarBuffer* pVarBuffer)
{
	DEBUG_ASSERT(pVarBuffer) ;
	IF_RETURN(NULL == pVarBuffer, E_FAIL) ;

	CComPtr<ICXml> _pXmlParser ;
	Common::Util::CreateObject(&_pXmlParser) ;
	IF_RETURN(NULL == _pXmlParser, E_FAIL) ;

	IF_RETURN(!SUCCEEDED(_pXmlParser->LoadXmlFromVarBuffer(pVarBuffer)), E_FAIL) ;
	CComPtr<ICVarData> _pXmlData ;
	IF_RETURN(!SUCCEEDED(_pXmlParser->GetXmlData(&_pXmlData)), E_FAIL) ;

	return this->_parse_factory_config(_pXmlData) ? S_OK : E_FAIL ;
}

HRESULT CCUIFactory::CreateFromFile(BSTR bstrFile, BSTR bstrTag, IUIElement** ppElement)
{
	DEBUG_ASSERT(ppElement) ;
    IF_RETURN(NULL == ppElement, E_INVALIDARG) ;
    *ppElement = NULL ;
    
    BOOL _bRet = this->_parse_xml_data(bstrFile) ;
    IF_RETURN(FALSE == _bRet, E_FAIL) ;

    CComPtr<ICVarData> _pNodeAttrData ;
    MAP_XML_DATA::iterator _it_xml = this->m_mapXmlData.find(CString(bstrFile)) ;
    if (this->m_mapXmlData.end() != _it_xml)
    {
        MAP_NODE_DATA::iterator _it_node = _it_xml->second.find(CString(bstrTag)) ;
        if (_it_xml->second.end() != _it_node)
        {
            _pNodeAttrData = _it_node->second ;
        }
    }
    IF_RETURN(NULL == _pNodeAttrData, E_FAIL) ;
    
    CComBSTR _bstrTagName ;
    _pNodeAttrData->GetString(CComBSTR(XML::XML_TAG), &_bstrTagName) ;
    CComPtr<IUIElement> _pElement ;
    _bRet = this->_build_ui_object(NULL, _bstrTagName, &_pElement, _pNodeAttrData, TRUE) ;
    if (_pElement && _bRet && ppElement)
    {
        return _pElement->QueryInterface(__uuidof(IUIElement), (VOID**)ppElement) ;
    }

    return E_FAIL ;
}

HRESULT CCUIFactory::CreateFromBuffer(BYTE* pBuffer, DWORD dwLen, BSTR bstrTag, IUIElement** ppElement)
{
	return S_OK ;
}

HRESULT CCUIFactory::CreateFromVarBuffer(ICVarBuffer* pVarBuffer, BSTR bstrTag, IUIElement** ppElement)
{
	return S_OK ;
}

HRESULT CCUIFactory::InitFromFile(BSTR bstrFile, BSTR bstrTag, IUIElement* pElement)
{
	return S_OK ;
}

HRESULT CCUIFactory::InitFromBuffer(BYTE* pBuffer, DWORD dwLen, BSTR bstrTag, IUIElement* pElement)
{
	return S_OK ;
}

HRESULT CCUIFactory::InitFromVarBuffer(ICVarBuffer* pVarBuffer, BSTR bstrTag, IUIElement* pElement)
{
	return S_OK ;
}

BOOL CCUIFactory::_parse_factory_config(ICVarData* pXmlData)
{
	DEBUG_ASSERT(pXmlData) ;
	IF_RETURN(NULL == pXmlData, FALSE) ;

	CComBSTR _bstrTopTagName ;
	pXmlData->GetString(CComBSTR(XML::XML_TAG), &_bstrTopTagName) ;
	IF_RETURN(CString(_bstrTopTagName) != CString(FACTORY::FACTORY_TOP_TAG), FALSE) ;

	CComPtr<ICVarArray> _pChildrenArray ;
	pXmlData->GetVarArray(CComBSTR(XML::XML_CHILDREN), &_pChildrenArray) ;
	IF_RETURN(NULL == _pChildrenArray, FALSE) ;

	LONG _nArrayCount = 0 ;
	_pChildrenArray->GetArrayCount(&_nArrayCount) ;
	for (INT i = 0; i < _nArrayCount; ++i)
	{
		CComPtr<ICVarData> _pChildData ;
		_pChildrenArray->GetVarData(i, &_pChildData) ;
		IF_CONTINUE(NULL == _pChildData) ;

		CComBSTR _bstrTagName ;
		_pChildData->GetString(CComBSTR(XML::XML_TAG), &_bstrTagName) ;
		CString _strTagName = _bstrTagName ;
		IF_CONTINUE(_strTagName != CString(FACTORY::FACTORY_TAG_TAG)) ;

		CComBSTR _bstrUITagName, _bstrUIIid ; IID _iid ;
		_pChildData->GetString(CComBSTR(FACTORY::FACTORY_TAG_NAME), &_bstrUITagName) ;
		_pChildData->GetString(CComBSTR(FACTORY::FACTORY_TAG_IID), &_bstrUIIid) ;
		::UuidFromString((RPC_WSTR)(BSTR)(_bstrUIIid), &_iid) ;

		this->SetTagIID(_bstrUITagName, _iid) ;
	}
	return TRUE ;
}

BOOL CCUIFactory::_parse_xml_data(BSTR bstrFile)
{
	MAP_XML_DATA::iterator _it = this->m_mapXmlData.find(CString(bstrFile)) ;
	IF_RETURN(_it != this->m_mapXmlData.end(), TRUE) ;

	CComPtr<ICXml> _pXmlParser ;
	Common::Util::CreateObject(&_pXmlParser) ;
	DEBUG_ASSERT(_pXmlParser) ;
	IF_RETURN(NULL == _pXmlParser || !(this->m_pFileroute), FALSE) ;

	CComPtr<ICVarData> _pXmlData ;
	_pXmlParser->LoadXmlFromFile(bstrFile) ;
	_pXmlParser->GetXmlData(&_pXmlData) ;
	IF_RETURN(NULL == _pXmlData, FALSE) ;

	CComPtr<ICVarArray> _pXmlChildren ;
	_pXmlData->GetVarArray(CComBSTR(XML::XML_CHILDREN), &_pXmlChildren) ;
	IF_RETURN(NULL == _pXmlChildren, FALSE) ;
	LONG _nChildrenCount = 0 ;
	_pXmlChildren->GetArrayCount(&_nChildrenCount) ;
	for (INT i = 0; i < _nChildrenCount; ++i)
	{
		CComPtr<ICVarData> _pChildData ;
		_pXmlChildren->GetVarData(i, &_pChildData) ;
		IF_CONTINUE(NULL == _pChildData) ;

		CComBSTR _bstrName ;
		_pChildData->GetString(CComBSTR(UIXML::XML_NODE_PART), &_bstrName) ;
		if (0 != CString(_bstrName).GetLength())
		{
			this->m_mapXmlData[CString(bstrFile)][CString(_bstrName)] = _pChildData ;
		}
	}
	return TRUE ;
}

BOOL CCUIFactory::_parse_attribute(ICVarData* pXmlData, ICVarData* pOutAttr)
{
	IF_RETURN(!pXmlData || !pOutAttr, FALSE) ;

	CComPtr<ICVarArray> _pChildrenArray ;
	pXmlData->GetVarArray(CComBSTR(XML::XML_CHILDREN), &_pChildrenArray) ;
	IF_RETURN(NULL == _pChildrenArray, FALSE) ;

	LONG _lChildrenCount = 0 ;
	_pChildrenArray->GetArrayCount(&_lChildrenCount) ;
	for (INT i = 0; i < _lChildrenCount; ++i)
	{
		CComPtr<ICVarData> _pChildData ;
		_pChildrenArray->GetVarData(i, &_pChildData) ;
		IF_CONTINUE(NULL == _pChildData) ;

		CComBSTR _bstrAttrName ;
		_pChildData->GetString(CComBSTR(XML::XML_TAG), &_bstrAttrName) ;

		CComPtr<ICVarArray> _pAttrChildrenArray ;
		_pChildData->GetVarArray(CComBSTR(XML::XML_CHILDREN), &_pAttrChildrenArray) ;
		IF_CONTINUE(NULL == _pAttrChildrenArray) ;

		CComPtr<ICVarData> _pAttrData ;
		_pAttrChildrenArray->GetVarData(0, &_pAttrData) ;
		IF_CONTINUE(NULL == _pAttrData) ;

		CComBSTR _bstrAttrTagName ;
		_pAttrData->GetString(CComBSTR(XML::XML_TAG), &_bstrAttrTagName) ;
		MAP_TAG_POOL::iterator it = this->m_mapTagPool.find(CString(_bstrAttrTagName)) ;
		if (this->m_mapTagPool.end() == it)
		{
			DEBUG_ASSERT_MSG(FALSE, _T("UnKnown Attr Tag Name ¡¾%s¡¿"), _bstrAttrTagName) ;
			continue ;
		}

		CComPtr<IUnknown> _pAttrUnknow ;
		Common::Util::CreateObjectByIid(it->second, (VOID**)&_pAttrUnknow, NULL) ;
		CComQIPtr<IUIAttribute> _pAttrInterface = _pAttrUnknow ;
		IF_CONTINUE(NULL == _pAttrUnknow) ;

		if (_pAttrInterface)
		{
			do
			{
				CComPtr<ICVarArray> _pChildrenArray ;
				_pAttrData->GetVarArray(CComBSTR(XML::XML_CHILDREN), &_pChildrenArray) ;
				IF_BREAK(NULL == _pChildrenArray) ;

				LONG _lChildrenCount = 0 ;
				_pChildrenArray->GetArrayCount(&_lChildrenCount) ;
				for (INT i = 0; i < _lChildrenCount; ++i)
				{
					CComPtr<ICVarData> _pChildData ;
					_pChildrenArray->GetVarData(i, &_pChildData) ;
					IF_CONTINUE(NULL == _pChildData) ;

					CComBSTR _bstrChildTagName ;
					_pChildData->GetString(CComBSTR(XML::XML_TAG), &_bstrChildTagName) ;

					if (CString(_bstrChildTagName) == UIXML::XML_NODE_ATTR)
					{
						CComPtr<ICVarData> _pAttrData ;
						Common::Util::CreateObject(&_pAttrData) ;
						this->_parse_attribute(_pChildData, _pAttrData) ;
						_pAttrInterface->SetAttribute(_pAttrData) ;
					}
				}

			}while(FALSE) ;

			_pAttrInterface->SetAttribute(_pAttrData) ;
		}

		pOutAttr->SetInterface(_bstrAttrName, _pAttrUnknow) ;
	}
	return TRUE ;
}

BOOL CCUIFactory::_build_ui_object(IUIElement* pParent, BSTR bstrName, 
								   IUIElement** ppElement, ICVarData* pObjectAttr, BOOL bRootElement)
{
	DEBUG_ASSERT(NULL != pParent || NULL != ppElement) ;
	IF_RETURN(NULL == pParent && NULL == ppElement, FALSE) ;

	if (ppElement)
	{
		*ppElement = NULL ;
	}

	CComPtr<IUIElement> _pElement ;
	MAP_TAG_POOL::iterator _it = this->m_mapTagPool.find(CString(bstrName)) ;
	if (this->m_mapTagPool.end() == _it)
	{
		DEBUG_ASSERT_MSG(FALSE, _T("UnKnown UI Tag Name ¡¾%s¡¿"), bstrName) ;
		return FALSE ;
	}

	Common::Util::CreateObjectByIid(_it->second, (VOID**)&_pElement, NULL) ;
	DEBUG_ASSERT_MSG(_pElement, _T("create ui¡¾%s¡¿failed"), bstrName) ;
	IF_RETURN(NULL == _pElement, FALSE) ;

	CComPtr<ICVarArray> _pChildrenArray ;
	pObjectAttr->GetVarArray(CComBSTR(XML::XML_CHILDREN), &_pChildrenArray) ;
	IF_RETURN(NULL == _pChildrenArray, TRUE) ;

	LONG _lChildrenCount = 0 ;
	_pChildrenArray->GetArrayCount(&_lChildrenCount) ;
	for (INT i = 0; i < _lChildrenCount; ++i)
	{
		CComPtr<ICVarData> _pChildData ;
		_pChildrenArray->GetVarData(i, &_pChildData) ;
		IF_CONTINUE(NULL == _pChildData) ;

		CComBSTR _bstrChildTagName ;
		_pChildData->GetString(CComBSTR(XML::XML_TAG), &_bstrChildTagName) ;
		IF_CONTINUE(NULL == _bstrChildTagName) ;

		if (CString(_bstrChildTagName) == UIXML::XML_NODE_INCLUDE)
		{
			CComBSTR _bstrIncludeFile ;
			_pChildData->GetString(CComBSTR(UIXML::XML_NODE_INCLUDE_FILE), &_bstrIncludeFile) ;
			CComBSTR _bstrIncludeNodeName ;
			_pChildData->GetString(CComBSTR(UIXML::XML_NODE_INCLUDE_NAME), &_bstrIncludeNodeName) ;

			CComPtr<IUIElement> _pIncludeElment ;
			this->CreateFromFile(_bstrIncludeFile, _bstrIncludeNodeName, &_pIncludeElment) ;
			if (_pIncludeElment && _pElement)
			{
				_pElement->AddChildBack(_pIncludeElment) ;
			}
		}
		else if (CString(_bstrChildTagName) == UIXML::XML_NODE_ATTR)
		{
			this->_parse_attribute(_pChildData, pObjectAttr) ;
		}
		else
		{
			this->_build_ui_object(_pElement, _bstrChildTagName, NULL, _pChildData) ;
		}
	}

	CComQIPtr<IUIAttribute> _pAttribute = _pElement ;
	if (_pAttribute)
	{
		_pAttribute->SetAttribute(pObjectAttr) ;
	}

	if (pParent)
	{
		pParent->AddChildBack(_pElement) ;
	}

	if (ppElement)
	{
		_pElement->QueryInterface(__uuidof(IUIElement), (VOID**)ppElement) ;
	}
	return TRUE ;
}