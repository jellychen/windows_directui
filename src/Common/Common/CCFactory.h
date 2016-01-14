#pragma once

#include "Include/Common/ICFactory.h"
#include "CCommonBase.h"

[
	default(ICFactory) ,
	threading(free) ,
	uuid("03EDA4C3-EE5E-4427-8D29-139C6538F0D0") ,
	coclass
]
class ATL_NO_VTABLE CCFactory : public IDispatchImpl<ICFactory>
{
public:
	DECLARE_PROTECT_FINAL_CONSTRUCT() ;
	CCFactory() ;
	virtual ~CCFactory() ;

public:
	HRESULT _call Init						() ;
	HRESULT _call UnInit					() ;
	HRESULT _call SetProjectBaseDir			(BSTR bstrDir) ;
	HRESULT _call RegisterComponent			(REFIID iid, REFCLSID clsid, BSTR bstrFile) ;
	HRESULT _call RegisterComponentString	(BSTR bsiid, BSTR bsclsid, BSTR bstrFile) ;
	HRESULT _call RegisterService			(REFIID iid, REFCLSID clsid, BSTR bstrFile) ;
	HRESULT _call RegisterServiceString		(BSTR bsiid, BSTR bsclsid, BSTR bstrFile) ;
	HRESULT _call CreateObjectByIid			(REFIID iid, VOID** ppOut, IUnknown* pOutUnknow) ;
	HRESULT _call CreateObjectByClsid		(REFIID iid, REFCLSID clsid, VOID** ppOut, IUnknown* pOutUnknow) ;
	HRESULT _call GetServiceByIid			(REFIID iid, IWeakAgent** ppOutAgent, IUnknown* pOutUnknow) ;
	HRESULT _call GetServiceByClsid			(REFIID iid, REFCLSID clsid, IWeakAgent** ppOutAgent, IUnknown* pOutUnknow) ;
	HRESULT _call ClearServicePool			() ;

private:
	CCommonBase								m_common ;
} ;