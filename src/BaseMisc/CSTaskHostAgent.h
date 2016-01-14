#pragma once

#include "Include/Def/Require.h"
#include "Include/Common/ISService.h"
#include "Include/BaseMisc/ISTaskHostAgent.h"
#include <map>

[
	default(ISTaskHostAgent) ,
	threading(free) ,
	uuid("1D4C62C4-06A6-4e20-A341-3AFAE98B9B18") ,
	coclass
]
class ATL_NO_VTABLE CSTaskHostAgent 
	: public TCustomServiceImpl<ISTaskHostAgent>
	, public CRITICAL_SECTION
{
public:
	DECLARE_PROTECT_FINAL_CONSTRUCT() ;
	CSTaskHostAgent() ;
	virtual ~CSTaskHostAgent() ;

public:
	HRESULT _call AddHostAgent		(INT nHostId, IUnknown* pHost) ;
	HRESULT _call DelHostAgent		(INT nHostId) ;
	HRESULT _call AddHostProtect	(INT nHostId) ;
	HRESULT _call DelHostProtect	(INT nHostId) ;

private:
	VOID	_lock	() ;
	VOID	_unlock	() ;

private:
	typedef struct _host_node
	{
		CComPtr<IUnknown>	pHostPtr ;
		DWORD				dwProtectThreadId ;
		DWORD				dwProtectCount ;
	} host_node ;

	typedef std::map<INT, CComPtr<IWeakAgent>>	MAP_PROTECT_WEAK ;
	MAP_PROTECT_WEAK							m_mapProtectWeak ;
	typedef std::map<INT, _host_node>			MAP_PROTECT ;
	MAP_PROTECT									m_mapProtect ;
} ;