#pragma once
#include "Include/Def/Require.h"
#include "Include/Util/Utiltpl.h"
#include "Include/Common/ISService.h"
#include "Include/BaseMisc/ICXml.h"
#include "Include/BaseMisc/ISConfig.h"

namespace CONFIG
{
	const TCHAR CONFIG_TOP_TAG[]                    = _T("common_config") ;

	namespace OBJECT
	{
		const TCHAR CONFIG_OBJECT[]                 = _T("objects") ;
		const TCHAR CONFIG_OBJECT_TAG[]             = _T("object") ;
		const TCHAR CONFIG_OBJECT_IID[]             = _T("iid") ;
		const TCHAR CONFIG_OBJECT_CLSID[]           = _T("clsid") ;
		const TCHAR CONFIG_OBJECT_MODULE[]          = _T("module") ;
	}

	namespace SERVICE
	{
		const TCHAR CONFIG_SERVICE[]                = _T("services") ;
		const TCHAR CONFIG_SERVICE_TAG[]            = _T("service") ;
		const TCHAR CONFIG_SERVICE_IID[]            = _T("iid") ;
		const TCHAR CONFIG_SERVICE_CLSID[]			= _T("clsid") ;
		const TCHAR CONFIG_SERVICE_MODULE[]			= _T("module") ;
	}

	enum
	{
		TYPE_OBJECT                                 = 0 ,
		TYPE_SERVICE                                = 1 ,
	}   ;
}


[
	default(ISConfig) ,
	threading(free) ,
	uuid("D9CF0CF0-11C4-400c-8D74-F4E2B0A1831A") ,
	coclass
]
class ATL_NO_VTABLE CSConfig
	: public TCustomServiceImpl<ISConfig>
{
public:
	DECLARE_PROTECT_FINAL_CONSTRUCT() ;
	CSConfig() ;
	virtual ~CSConfig() ;

public:
	HRESULT _call OnInit					() ;
	HRESULT _call LoadConfigFromFile		(BSTR bstrFile) ;
	HRESULT _call LoadConfigFromVarBuffer	(ICVarBuffer* pVarBuffer) ;
	HRESULT _call LoadConfigFromBuffer		(BYTE* pbBuffer, LONG lBufferLen) ;

private:
	BOOL    _parse_config                   (ICVarData* pXmlData) ;
	BOOL    _parse_config_detail            (ICVarData* pXmlData, INT nType) ;
} ;