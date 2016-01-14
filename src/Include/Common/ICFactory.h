#pragma once
#include "Include/Def/Require.h"

[
	object ,
	uuid("BB32F3E5-687A-45fb-A50E-F60317C40D23") ,
	pointer_default(unique)
]
__interface ICFactory : IDispatch
{
	HRESULT Init					() ;
	HRESULT UnInit					() ;
	HRESULT SetProjectBaseDir		(BSTR bstrDir) ;
	HRESULT RegisterComponent		(REFIID iid, REFCLSID clsid, BSTR bstrFile) ;
	HRESULT RegisterComponentString	(BSTR bsiid, BSTR bsclsid, BSTR bstrFile) ;
	HRESULT RegisterService			(REFIID iid, REFCLSID clsid, BSTR bstrFile) ;
	HRESULT RegisterServiceString	(BSTR bsiid, BSTR bsclsid, BSTR bstrFile) ;
	HRESULT CreateObjectByIid		(REFIID iid, VOID** ppOut, IUnknown* pOutUnknow) ;
	HRESULT CreateObjectByClsid		(REFIID iid, REFCLSID clsid, VOID** ppOut, IUnknown* pOutUnknow) ;
	HRESULT GetServiceByIid			(REFIID iid, IWeakAgent** ppOutAgent, IUnknown* pOutUnknow) ;
	HRESULT GetServiceByClsid		(REFIID iid, REFCLSID clsid, IWeakAgent** ppOutAgent, IUnknown* pOutUnknow) ;
	HRESULT ClearServicePool		() ;
} ;