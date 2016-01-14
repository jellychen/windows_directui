
#include "stdafx.h"
#include "Include/Def/Require.h"
#include "CCommonBase.h"

static CCommonBase _static_common_base ;

FUNC_API HRESULT WINAPI Init()
{
	return _static_common_base.Init() ;
}

FUNC_API HRESULT WINAPI UnInit()
{
	return _static_common_base.UnInit() ;
}

FUNC_API HRESULT WINAPI SetProjectBaseDir(BSTR bstrDir)
{
	return _static_common_base.SetProjectBaseDir(bstrDir) ;
}

FUNC_API HRESULT WINAPI RegisterComponent(REFIID iid, REFCLSID clsid, BSTR bstrFile)
{
	return _static_common_base.RegisterComponent(iid, clsid, bstrFile) ;
}

FUNC_API HRESULT WINAPI RegisterComponentString(BSTR bsiid, BSTR bsclsid, BSTR bstrFile)
{
	return _static_common_base.RegisterComponentString(bsiid, bsclsid, bstrFile) ;
}

FUNC_API HRESULT WINAPI RegisterService(REFIID iid, REFCLSID clsid, BSTR bstrFile)
{
	return _static_common_base.RegisterService(iid, clsid, bstrFile) ;
}

FUNC_API HRESULT WINAPI RegisterServiceString(BSTR bsiid, BSTR bsclsid, BSTR bstrFile)
{
	return _static_common_base.RegisterServiceString(bsiid, bsclsid, bstrFile) ;
}

FUNC_API HRESULT WINAPI CreateObjectByIid(REFIID iid, VOID** ppOut, IUnknown* pOutUnknow)
{
	return _static_common_base.CreateObjectByIid(iid, ppOut, pOutUnknow) ;
}

FUNC_API HRESULT WINAPI CreateObjectByClsid(REFIID iid, REFCLSID clsid, VOID** ppOut, IUnknown* pOutUnknow)
{
	return _static_common_base.CreateObjectByClsid(iid, clsid, ppOut, pOutUnknow) ;
}

FUNC_API HRESULT WINAPI GetServiceByIid(REFIID iid, IWeakAgent** ppOutAgent, IUnknown* pOutUnknow)
{
	return _static_common_base.GetServiceByIid(iid, ppOutAgent, pOutUnknow) ;
}

FUNC_API HRESULT WINAPI GetServiceByClsid(REFIID iid, REFCLSID clsid, IWeakAgent** ppOutAgent, IUnknown* pOutUnknow)
{
	return _static_common_base.GetServiceByClsid(iid, clsid, ppOutAgent, pOutUnknow) ;
}

FUNC_API HRESULT WINAPI CreateObjectByIidWidthKey(REFIID iid, VOID** ppOut, IUnknown* pOutUnknow, LONG key)
{
	return E_FAIL ;
}

FUNC_API HRESULT WINAPI CreateObjectByClsidWidthKey(REFIID iid, REFCLSID clsid, VOID** ppOut, IUnknown* pOutUnknow, LONG key)
{
	return E_FAIL ;
}

FUNC_API HRESULT WINAPI GetServiceByIidWidthKey(REFIID iid, IWeakAgent** ppOutAgent, IUnknown* pOutUnknow, LONG key)
{
	return E_FAIL ;
}

FUNC_API HRESULT WINAPI GetServiceByClsidWidthKey(REFIID iid, REFCLSID clsid, IWeakAgent** ppOutAgent, IUnknown* pOutUnknow, LONG key)
{
	return E_FAIL ;
}

FUNC_API HRESULT WINAPI ClearServicePool()
{
	return E_FAIL ;
}

