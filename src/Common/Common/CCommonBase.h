#pragma once

#include <map>
#include <set>
#include "CCommomHelper.h"
#include "Include/Def/Require.h"
#include "Include/Common/ISService.h"

class CCommonBase
{
public:
	CCommonBase() ;
	virtual ~CCommonBase() ;

public:
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

private:
	BOOL	CreateObjectFromDll_    (REFIID iid, REFCLSID clsid, LPCTSTR lpstrFile, VOID** ppOut, IUnknown* pOutUnknown) ;
	BOOL	ObjectFactoryFromDll_   (REFCLSID clsid, LPCTSTR lpstrFile, IClassFactory** ppObjectFactory) ;
	BOOL	Lock_					() ;
	BOOL	UnLock_					() ;

private:
	CRITICAL_SECTION				m_section ;
	CString                         m_cstrProjDir ;
	typedef std::map<IID, CLSID>    MAP_IID_CLSID_POOL ;
	MAP_IID_CLSID_POOL				m_mapComponentPool ;
	MAP_IID_CLSID_POOL				m_mapServicePool ;

	typedef std::set<CString>						SET_LOAD_DLL ;
	SET_LOAD_DLL									m_setLoadDll ;
	typedef std::map<CLSID, CString>				MAP_PATH_POOL ;
	MAP_PATH_POOL									m_mapObjectPathPool ;
	typedef std::map<CGID, CComPtr<ISServiceBase>>	MAP_SERVICE_POOL ;
	MAP_SERVICE_POOL								m_mapServiceBasePool ;
	typedef std::map<CLSID, CComPtr<IClassFactory>>	MAP_FACTORY_POOL ;
	MAP_FACTORY_POOL								m_mapFactoryPool ;
} ;