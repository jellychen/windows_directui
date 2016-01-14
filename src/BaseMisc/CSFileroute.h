#pragma once

#include "Include/Def/Require.h"
#include "Include/Util/Utiltpl.h"
#include "Include/Common/ISService.h"
#include "Include/Common/ICStruct.h"
#include "Include/BaseMisc/ISFileroute.h"
#include "Include/BaseMisc/ISPackage.h"
#include <map>
#include <set>

[
	default(ISFileroute) ,
	threading(free) ,
	uuid("500070EA-5470-461a-B589-64BB5235ECCD") ,
	coclass
]
class ATL_NO_VTABLE CSFileroute 
	: public TCustomServiceImpl<ISFileroute>
{
public:
	DECLARE_PROTECT_FINAL_CONSTRUCT() ;
	CSFileroute() ;
	virtual ~CSFileroute() ;

public:
	HRESULT _call OnInit				() ;
	HRESULT _call OnUnInit				() ;
	HRESULT _call AddSymbol             (BSTR bstrSymbol, BSTR bstrRoute) ;
	HRESULT _call DelSymbol             (BSTR bstrSymbol) ;
	HRESULT _call GetSymbol             (BSTR bstrSymbol, BSTR* pbstrRoute) ;
	HRESULT _call Convert               (BSTR bstrRoute, BSTR* pbstrRoute) ;
	HRESULT _call AddPackageSymbol      (BSTR bstrSymbol) ;
	HRESULT _call DelPackageSymbol      (BSTR bstrSymbol) ;

	HRESULT _call FileExists            (BSTR bstrFile, BOOL* pbExists) ;
	HRESULT _call ReadWholeFile         (BSTR bstrFile, ICVarBuffer* pComBuffer) ;

private:
	BOOL    FileInSystem                (CString& strFile, CString& strFileInSystem) ;

private:
	typedef std::map<CString, CString>  MAP_SYMBOL_POOL ;
	typedef std::set<CString>           SET_SYMBOL_PACKAGE ;

private:
	MAP_SYMBOL_POOL                     m_mapSymbolPool ;
	SET_SYMBOL_PACKAGE                  m_setSymbolPool ;
	CString                             m_cstrCurrentRoute ;
	CWeakPtr<ISPackage>					m_pPackageService ;
} ;