#include "stdafx.h"
#include "CSTaskHostAgent.h"

CSTaskHostAgent::CSTaskHostAgent()
{
	::InitializeCriticalSection(this) ;
}

CSTaskHostAgent::~CSTaskHostAgent()
{
	::DeleteCriticalSection(this) ;
}

HRESULT CSTaskHostAgent::AddHostAgent(INT nHostId, IUnknown* pHost)
{
	DEBUG_ASSERT(pHost) ;
	IF_RETURN(NULL == pHost, E_INVALIDARG) ;

	CComQIPtr<IWeakAgentSupport> _pWeakSupport = pHost ;
	DEBUG_ASSERT(_pWeakSupport) ;
	IF_RETURN(NULL == _pWeakSupport, E_INVALIDARG) ;

	this->_lock() ;
	CComPtr<IWeakAgent> _pWeakPtr ;
	_pWeakSupport->QueryAgent(&_pWeakPtr) ;
	DEBUG_ASSERT(_pWeakPtr) ;
	this->m_mapProtectWeak[nHostId] = _pWeakPtr ;
	this->_unlock() ;

	return S_OK ;
}

HRESULT CSTaskHostAgent::DelHostAgent(INT nHostId)
{
	this->_lock() ;
	MAP_PROTECT_WEAK::iterator _it = this->m_mapProtectWeak.find(nHostId) ;
	if (this->m_mapProtectWeak.end() != _it)
	{
		this->m_mapProtectWeak.erase(_it) ;
	}
	this->_unlock() ;
	return S_OK ;
}

HRESULT CSTaskHostAgent::AddHostProtect(INT nHostId)
{
	this->_lock() ;
	HRESULT _hRet = E_FAIL ;
	MAP_PROTECT::iterator _it = this->m_mapProtect.find(nHostId) ;
	DWORD dwCurrentThreadId = ::GetThreadId(NULL) ;
	if (this->m_mapProtect.end() == _it)
	{
		
		CComPtr<IWeakAgent> _pWeakAgent ;
		MAP_PROTECT_WEAK::iterator _it_weak = this->m_mapProtectWeak.find(nHostId) ;
		if (this->m_mapProtectWeak.end() != _it_weak && _it_weak->second)
		{
			CComPtr<IUnknown> _ptr ;
			 _it_weak->second->QueryOrigin(__uuidof(IUnknown), (VOID**)&_ptr) ;

			host_node _node ;
			_node.dwProtectCount = 1 ;
			_node.dwProtectThreadId = dwCurrentThreadId ;
			_node.pHostPtr = _ptr ;
			this->m_mapProtect[nHostId] = _node ;
			_hRet = S_OK ;
		}
	}
	else
	{
		DEBUG_ASSERT(_it->second.dwProtectThreadId != dwCurrentThreadId) ;
		_it->second.dwProtectCount++ ;
		_hRet = S_OK ;
	}
	this->_unlock() ;
	return _hRet ;
}

HRESULT CSTaskHostAgent::DelHostProtect(INT nHostId)
{
	this->_lock() ;
	MAP_PROTECT::iterator _it = this->m_mapProtect.find(nHostId) ;
	DWORD dwCurrentThreadId = ::GetThreadId(NULL) ;
	DEBUG_ASSERT(this->m_mapProtect.end() != _it) ;
	if (this->m_mapProtect.end() != _it)
	{
		DEBUG_ASSERT(dwCurrentThreadId != _it->second.dwProtectThreadId) ;
		_it->second.dwProtectCount-- ;
		if (0 == _it->second.dwProtectCount)
		{
			this->m_mapProtect.erase(_it) ;
		}
	}
	this->_unlock() ;
	return S_OK ;
}

VOID CSTaskHostAgent::_lock()
{
	::EnterCriticalSection(this) ;
}

VOID CSTaskHostAgent::_unlock()
{
	::LeaveCriticalSection(this) ;
}