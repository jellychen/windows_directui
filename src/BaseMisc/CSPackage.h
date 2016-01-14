#pragma once

#include "Include/Def/Require.h"
#include "Include/Util/Utiltpl.h"
#include "Include/Common/ISService.h"
#include "Include/BaseMisc/ISPackage.h"
#include "Include/BaseMisc/ISFileroute.h"
#include "CSPackageDef.h"

[
	default(ISPackage) ,
	threading(free) ,
	uuid("2C2DBD63-62DC-4ecd-B221-2D4374D8066A") ,
	coclass
]
class ATL_NO_VTABLE CSPackage
	: public TCustomServiceImpl<ISPackage>
{
public:
	DECLARE_PROTECT_FINAL_CONSTRUCT() ;
	CSPackage() ;
	virtual ~CSPackage() ;

public:
	HRESULT _call OnInit			() ;
	HRESULT _call OnUnInit			() ;
	HRESULT _call AddPackage        (BSTR bstrName, BSTR bstrPackage) ;
	HRESULT _call DelPackage        (BSTR bstrName) ;
	HRESULT _call FileExists        (BSTR bstrFile, BOOL* pbExists) ;
	HRESULT _call ReadWholeFile     (BSTR bstrFile, ICVarBuffer* pComBuffer) ;
private:
	size_t  _string_hash            (CString cstrKey) ;
	BOOL    _load_file_list         (CString cstrSymbol, CString cstrFile, UINT32 un32Offset) ;
private:
	MAP_PACKAGE_POOL                m_mapPackagePool ;
	CWeakPtr<ISFileroute>			m_pFilerouteService ;
} ;