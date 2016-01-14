
#include "stdafx.h"
#include "CCommonBase.h"
#include "CCommonRegister.h"

CCommonBase::CCommonBase()
{
	::InitializeCriticalSection(&m_section) ;

	TCHAR _strFullPath[MAX_PATH + 1] = {0} ;
	::GetModuleFileName(NULL, _strFullPath, MAX_PATH + 1) ;
	_strFullPath[MAX_PATH] = _T('\0') ;
	::PathRemoveFileSpec(_strFullPath) ;
	this->m_cstrProjDir = _strFullPath ;
}

CCommonBase::~CCommonBase()
{
	::DeleteCriticalSection(&m_section) ;
}

HRESULT CCommonBase::Init()
{
	INT nObjectCount = sizeof(Common::Reg::_object_table)/sizeof(BSTR)/3 ;
	for (INT i = 0; i < nObjectCount; ++i)
	{
		this->RegisterComponentString (
			CComBSTR(Common::Reg::_object_table[i][0]),
			CComBSTR(Common::Reg::_object_table[i][1]),
			CComBSTR(Common::Reg::_object_table[i][2])) ;
	}

	INT nServiceCount = sizeof(Common::Reg::_service_table)/sizeof(BSTR)/3 ;
	for (INT i = 0; i < nServiceCount; ++i)
	{
		this->RegisterServiceString (
			CComBSTR(Common::Reg::_service_table[i][0]),
			CComBSTR(Common::Reg::_service_table[i][1]),
			CComBSTR(Common::Reg::_service_table[i][2])) ;
	}
	return S_OK ;
}

HRESULT CCommonBase::UnInit()
{
	return S_OK ;
}

HRESULT CCommonBase::SetProjectBaseDir(BSTR bstrDir)
{
	this->m_cstrProjDir = bstrDir ;
	return S_OK ;
}

HRESULT CCommonBase::RegisterComponent(REFIID iid, REFCLSID clsid, BSTR bstrFile)
{
	this->m_mapComponentPool[iid] = clsid ;
	this->m_mapObjectPathPool[clsid] = bstrFile ;
	return S_OK ;
}

HRESULT CCommonBase::RegisterComponentString(BSTR bsiid, BSTR bsclsid, BSTR bstrFile)
{
	IID _iid ; CLSID _clsid ;
	::UuidFromString((RPC_WSTR)(bsiid), &_iid) ;
	::UuidFromString((RPC_WSTR)(bsclsid), &_clsid) ;
	return this->RegisterComponent(_iid, _clsid, bstrFile) ;
}

HRESULT CCommonBase::RegisterService(REFIID iid, REFCLSID clsid, BSTR bstrFile)
{
	this->m_mapServicePool[iid] = clsid ;
	this->m_mapObjectPathPool[clsid] = bstrFile ;
	return S_OK ;
}

HRESULT CCommonBase::RegisterServiceString(BSTR bsiid, BSTR bsclsid, BSTR bstrFile)
{
	IID _iid ; CLSID _clsid ;
	::UuidFromString((RPC_WSTR)(bsiid), &_iid) ;
	::UuidFromString((RPC_WSTR)(bsclsid), &_clsid) ;
	return this->RegisterService(_iid, _clsid, bstrFile) ;
}

HRESULT CCommonBase::CreateObjectByIid(REFIID iid, VOID** ppOut, IUnknown* pOutUnknow)
{
	DEBUG_ASSERT(ppOut) ;
	IF_RETURN(NULL == ppOut, E_INVALIDARG) ;
	*ppOut = NULL ;
	MAP_IID_CLSID_POOL::iterator _it = this->m_mapComponentPool.find(iid) ;
	IF_RETURN(this->m_mapComponentPool.end() == _it, E_FAIL) ;
	return this->CreateObjectByClsid(iid, _it->second, ppOut, pOutUnknow) ;
}

HRESULT CCommonBase::CreateObjectByClsid(REFIID iid, REFCLSID clsid, VOID** ppOut, IUnknown* pOutUnknow)
{
	DEBUG_ASSERT(ppOut) ;
	IF_RETURN(NULL == ppOut, E_INVALIDARG) ;
	*ppOut = NULL ;
	MAP_PATH_POOL::iterator _it = this->m_mapObjectPathPool.find(clsid) ;
	IF_RETURN(this->m_mapObjectPathPool.end() == _it, E_FAIL) ;
	return this->CreateObjectFromDll_(iid, clsid, _it->second, ppOut, pOutUnknow) ;
}

HRESULT CCommonBase::GetServiceByIid(REFIID iid, IWeakAgent** ppOutAgent, IUnknown* pOutUnknow)
{
	DEBUG_ASSERT(ppOutAgent) ;
	IF_RETURN(NULL == ppOutAgent, E_INVALIDARG) ;
	*ppOutAgent = NULL ;
	
	MAP_IID_CLSID_POOL::iterator _it = this->m_mapServicePool.find(iid) ;
	IF_RETURN(this->m_mapServicePool.end() == _it, E_FAIL) ;
	return this->GetServiceByClsid(iid, _it->second, ppOutAgent, pOutUnknow) ;
}

HRESULT CCommonBase::GetServiceByClsid(REFIID iid, REFCLSID clsid, IWeakAgent** ppOutAgent, IUnknown* pOutUnknow)
{
	DEBUG_ASSERT(ppOutAgent) ;
	IF_RETURN(NULL == ppOutAgent, E_INVALIDARG) ;
	*ppOutAgent = NULL ;

	CGID _key = {iid, clsid} ;
	CComPtr<IUnknown> _pServicePtr = NULL ;
	MAP_SERVICE_POOL::iterator _it = this->m_mapServiceBasePool.find(_key) ;
	if (this->m_mapServiceBasePool.end() == _it)
	{
		MAP_PATH_POOL::iterator _it_path = this->m_mapObjectPathPool.find(clsid) ;
		if (this->m_mapObjectPathPool.end() != _it_path)
		{
			HRESULT _hCreateRet = this->CreateObjectFromDll_(iid, clsid, _it_path->second, (VOID**)&_pServicePtr, pOutUnknow) ;
			CComQIPtr<ISServiceBase> _pServiceBasePtr = _pServicePtr ;
			if (SUCCEEDED(_hCreateRet) && _pServicePtr && _pServiceBasePtr)
			{
				this->m_mapServiceBasePool[_key] = _pServiceBasePtr ;
				_pServiceBasePtr->OnInit() ;
			}
		}
	}
	else if (_it->second)
	{
		_it->second->QueryInterface(iid, (void**)&_pServicePtr) ;
	}
	
	CComQIPtr<IWeakAgentSupport> _pWeakSupport = _pServicePtr ;
	if (_pServicePtr && _pWeakSupport)
	{
		return _pWeakSupport->QueryAgent(ppOutAgent) ;
	}
	return E_FAIL ;
}

HRESULT CCommonBase::ClearServicePool()
{
	return S_OK ;
}

BOOL CCommonBase::CreateObjectFromDll_(REFIID iid, REFCLSID clsid, LPCTSTR lpstrFile, VOID** ppOut, IUnknown* pOutUnknown)
{
	IF_RETURN(NULL == ppOut, E_INVALIDARG) ;
	*ppOut = NULL ;

	CComPtr<IClassFactory> _pClassFactory ;
	MAP_FACTORY_POOL::iterator _it = this->m_mapFactoryPool.find(clsid) ;
	if (this->m_mapFactoryPool.end() != _it)
	{
		_pClassFactory = _it->second ;
	}

	if (NULL == _pClassFactory)
	{
		this->ObjectFactoryFromDll_(clsid, lpstrFile, &_pClassFactory) ;
	}

	DEBUG_ASSERT_MSG(_pClassFactory, _T("CreateObjectFromDll_ %s Failed.."), lpstrFile) ;
	IF_RETURN(NULL == _pClassFactory, E_FAIL) ;
	this->m_mapFactoryPool[clsid] = _pClassFactory ;

	return _pClassFactory->CreateInstance(pOutUnknown, (NULL == pOutUnknown)? iid: IID_IUnknown, ppOut) ;
}

BOOL CCommonBase::ObjectFactoryFromDll_(REFCLSID clsid, LPCTSTR lpstrFile, IClassFactory** ppObjectFactory)
{
	IF_RETURN(NULL == ppObjectFactory, E_INVALIDARG) ;
	*ppObjectFactory = NULL ;

	CString _strDllPath ;
	{
		TCHAR _path[MAX_PATH + 1] ;
		_snwprintf_s(_path, _countof(_path), _TRUNCATE, _T("%s\\%s"), (LPCTSTR)(m_cstrProjDir), lpstrFile) ;
		_strDllPath = _path ;
	}

	HINSTANCE _hInst = ::GetModuleHandle(_strDllPath) ;
	if (NULL == _hInst)
	{
		SET_LOAD_DLL::iterator _it = this->m_setLoadDll.find(_strDllPath) ;
		if (this->m_setLoadDll.end() == _it)
		{
			_hInst = ::LoadLibrary(_strDllPath) ;
			this->m_setLoadDll.insert(_strDllPath) ;
		}
	}
	DEBUG_ASSERT_MSG(_hInst, _T("Load Dll %s Failed..."), _strDllPath) ;
	IF_RETURN(NULL == _hInst, E_FAIL) ;

	typedef HRESULT (__stdcall* _get_class_proc)(REFCLSID, REFIID, LPVOID*) ;
	_get_class_proc _proc = (_get_class_proc)::GetProcAddress(_hInst, "DllGetClassObject") ;
	DEBUG_ASSERT_MSG(_proc, _T("Get dll %s class function failed ..."), _strDllPath) ;
	IF_RETURN(NULL == _proc, E_FAIL) ;

	return _proc(clsid, IID_IClassFactory, (void**)ppObjectFactory) ;
}

BOOL CCommonBase::Lock_()
{
	::EnterCriticalSection(&m_section) ;
	return TRUE ;
}

BOOL CCommonBase::UnLock_()
{
	::LeaveCriticalSection(&m_section) ;
	return TRUE ;
}