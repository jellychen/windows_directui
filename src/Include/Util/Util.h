#pragma once
#include "Include/Def/Require.h"

namespace Common
{
	namespace Util
	{
		FUNC_API HRESULT WINAPI Init						() ;
		FUNC_API HRESULT WINAPI UnInit						() ;
		FUNC_API HRESULT WINAPI SetProjectBaseDir			(BSTR bstrDir) ;
		FUNC_API HRESULT WINAPI RegisterComponent			(REFIID iid, REFCLSID clsid, BSTR bstrFile) ;
		FUNC_API HRESULT WINAPI RegisterComponentString		(BSTR bsiid, BSTR bsclsid, BSTR bstrFile) ;
		FUNC_API HRESULT WINAPI RegisterService				(REFIID iid, REFCLSID clsid, BSTR bstrFile) ;
		FUNC_API HRESULT WINAPI RegisterServiceString		(BSTR bsiid, BSTR bsclsid, BSTR bstrFile) ;
		FUNC_API HRESULT WINAPI CreateObjectByIid			(REFIID iid, VOID** ppOut, IUnknown* pOutUnknow) ;
		FUNC_API HRESULT WINAPI CreateObjectByClsid			(REFIID iid, REFCLSID clsid, VOID** ppOut, IUnknown* pOutUnknow) ;
		FUNC_API HRESULT WINAPI GetServiceByIid				(REFIID iid, IWeakAgent** ppOutAgent, IUnknown* pOutUnknow) ;
		FUNC_API HRESULT WINAPI GetServiceByClsid			(REFIID iid, REFCLSID clsid, IWeakAgent** ppOutAgent, IUnknown* pOutUnknow) ;
		FUNC_API HRESULT WINAPI CreateObjectByIidWidthKey	(REFIID iid, VOID** ppOut, IUnknown* pOutUnknow, LONG key) ;
		FUNC_API HRESULT WINAPI CreateObjectByClsidWidthKey	(REFIID iid, REFCLSID clsid, VOID** ppOut, IUnknown* pOutUnknow, LONG key) ;
		FUNC_API HRESULT WINAPI GetServiceByIidWidthKey		(REFIID iid, IWeakAgent** ppOutAgent, IUnknown* pOutUnknow, LONG key) ;
		FUNC_API HRESULT WINAPI GetServiceByClsidWidthKey	(REFIID iid, REFCLSID clsid, IWeakAgent** ppOutAgent, IUnknown* pOutUnknow, LONG key) ;
		FUNC_API HRESULT WINAPI ClearServicePool			() ;
	}
}
