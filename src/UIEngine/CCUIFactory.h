#pragma once
#include "Include/Def/Require.h"
#include "Include/Util/Utiltpl.h"
#include "Include/Common/ISService.h"
#include "Include/BaseMisc/ICXml.h"
#include "Include/BaseMisc/ISFileroute.h"
#include "Include/UIEngine/IUIAttribute.h"
#include "Include/UIEngine/IUIFactory.h"
#include <map>

typedef std::map<CString, IID>					MAP_TAG_POOL ;
typedef std::map<CString, CComPtr<ICVarData>>	MAP_NODE_DATA ;
typedef std::map<CString, MAP_NODE_DATA>		MAP_XML_DATA ;

namespace FACTORY
{
	const TCHAR FACTORY_TOP_TAG[]                   = _T("Tags") ;
	const TCHAR FACTORY_TAG_TAG[]                   = _T("Tag") ;
	const TCHAR FACTORY_TAG_NAME[]                  = _T("Name") ;
	const TCHAR FACTORY_TAG_IID[]                   = _T("IID") ;
}

namespace UIXML
{
	const TCHAR XML_NODE_PART[]                     = _T("Node") ;
	const TCHAR XML_NODE_OBJECT[]					= _T("Object") ;
	const TCHAR XML_NODE_OBJECT_IID[]				= _T("ObjectIID") ;
	const TCHAR XML_NODE_ATTR[]                     = _T("Attribute") ;
	const TCHAR XML_NODE_INCLUDE[]                  = _T("Include") ;
	const TCHAR XML_NODE_INCLUDE_FILE[]             = _T("File") ;
	const TCHAR XML_NODE_INCLUDE_NAME[]             = _T("Node") ;
}

[
	default(IUIFactory) ,
	threading(free) ,
	uuid("66B68817-907D-43ce-9DE0-0FB566E02303") ,
	coclass
]
class ATL_NO_VTABLE CCUIFactory
	: public TCustomServiceImpl<IUIFactory>
{
public:
	DECLARE_PROTECT_FINAL_CONSTRUCT() ;
	CCUIFactory() ;
	virtual ~CCUIFactory() ;

public:
	HRESULT _call OnInit					() ;
	HRESULT _call SetTagIID					(BSTR bstrTagName, REFIID iid) ;
	HRESULT _call GetTagIID					(BSTR bstrTagName, IID* piid) ;
	HRESULT _call DelTagIID					(BSTR bstrTagName) ;
	HRESULT _call Clear						() ;
	HRESULT _call LoadTagConfigFromFile		(BSTR bstrFile) ;
	HRESULT _call LoadTagConfigFromBuffer	(BYTE* pBuffer, DWORD dwLen) ;
	HRESULT _call LoadTagConfigFromVarBuffer(ICVarBuffer* pVarBuffer) ;
	HRESULT _call CreateFromFile			(BSTR bstrFile, BSTR bstrTag, IUIElement** ppElement) ;
	HRESULT _call CreateFromBuffer			(BYTE* pBuffer, DWORD dwLen, BSTR bstrTag, IUIElement** ppElement) ;
	HRESULT _call CreateFromVarBuffer		(ICVarBuffer* pVarBuffer, BSTR bstrTag, IUIElement** ppElement) ;
	HRESULT _call InitFromFile				(BSTR bstrFile, BSTR bstrTag, IUIElement* pElement) ;
	HRESULT _call InitFromBuffer			(BYTE* pBuffer, DWORD dwLen, BSTR bstrTag, IUIElement* pElement) ;
	HRESULT _call InitFromVarBuffer			(ICVarBuffer* pVarBuffer, BSTR bstrTag, IUIElement* pElement) ;

private:
	BOOL	_parse_factory_config			(ICVarData* pXmlData) ;
	BOOL	_parse_xml_data					(BSTR bstrFile) ;
	BOOL	_parse_attribute				(ICVarData* pXmlData, ICVarData* pOutAttr) ;
	BOOL    _build_ui_object				(IUIElement* pParent, BSTR bstrName, IUIElement** ppElement, 
												ICVarData* pObjectAttr, BOOL bRootElement = FALSE) ;
private:
	MAP_TAG_POOL							m_mapTagPool ;
	MAP_XML_DATA							m_mapXmlData ;
	CWeakPtr<ISFileroute>					m_pFileroute ;
} ;