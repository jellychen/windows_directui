#pragma once

#include "Include/Util/Utiltpl.h"
#include "Include/BaseMisc/ICXml.h"
#include "Include/BaseMisc/ISFileroute.h"
#include "Include/ThridParty/PugiXml/pugiconfig.hpp"
#include "Include/ThridParty/PugiXml/pugixml.hpp"


[
	default(ICXml) ,
	threading(free) ,
	uuid("766ADD9A-002C-4e51-9756-75ABEECD855B") ,
	coclass
]
class ATL_NO_VTABLE CCXml : public IDispatchImpl<ICXml>
{
public:
	DECLARE_PROTECT_FINAL_CONSTRUCT() ;
	CCXml() ;
	virtual ~CCXml() ;
	HRESULT FinalConstruct() ;

public:
	HRESULT _call LoadXmlFromFile       (BSTR bstrFile) ;
	HRESULT _call LoadXmlFromVarBuffer  (ICVarBuffer* pVarBuffer) ;
	HRESULT _call LoadXmlFromBuffer     (BYTE* pbBuffer, LONG lBufferLen) ;
	HRESULT _call GetXmlData            (ICVarData** pOutXmlData) ;
	HRESULT _call Clear                 () ;

private:
	HRESULT _parase_xml_data            (pugi::xml_node& _xml_node, ICVarData* pXmlData) ;

private:
	CComPtr<ICVarData>					m_pXmlData ;
	CWeakPtr<ISFileroute>				m_pFileroute ;
} ;