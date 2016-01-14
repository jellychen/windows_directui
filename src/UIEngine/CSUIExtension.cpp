#include "stdafx.h"
#include "CSUIExtensionDef.h"
#include "CSUIExtension.h"

CSUIExtensionCenter::CSUIExtensionCenter()
{

}

CSUIExtensionCenter::~CSUIExtensionCenter()
{

}

HRESULT CSUIExtensionCenter::CallExtension(REFIID iid, IUIFrame* pFrame, ICVarData* pArg)
{
	DEBUG_ASSERT(pFrame) ;
	IF_RETURN(NULL == pFrame, E_INVALIDARG) ;

	MAP_CALLBACK::iterator _it_callback = this->m_mapGlobalExtension.begin() ;
	for (; _it_callback != this->m_mapGlobalExtension.end(); ++_it_callback)
	{
		IF_CONTINUE(NULL == _it_callback->second) ;
		_it_callback->second->OnExtension(iid, pFrame, pArg) ;
	}

	MAP_EXTENSION::iterator _it = this->m_mapExtension.find(iid) ;
	IF_RETURN(this->m_mapExtension.end() == _it, S_OK) ;
	
	_it_callback = _it->second.begin() ;
	for (; _it_callback != _it->second.end(); ++_it_callback)
	{
		IF_CONTINUE(NULL == _it_callback->second) ;
		_it_callback->second->OnExtension(iid, pFrame, pArg) ;
	}

	return S_OK ;
}

HRESULT CSUIExtensionCenter::AddExtensionListener(REFIID iid, IUIExtensionCallback* pCallback)
{
	DEBUG_ASSERT(pCallback) ;
	IF_RETURN(NULL == pCallback, E_INVALIDARG) ;

	this->m_mapExtension[iid][(LONG)(pCallback)] = pCallback ;
	return S_OK ;
}

HRESULT CSUIExtensionCenter::DelExtensionListener(REFIID iid, IUIExtensionCallback* pCallback)
{
	DEBUG_ASSERT(pCallback) ;
	IF_RETURN(NULL == pCallback, E_INVALIDARG) ;

	MAP_EXTENSION::iterator _it = this->m_mapExtension.find(iid) ;
	IF_RETURN(this->m_mapExtension.end() == _it, S_OK) ;

	MAP_CALLBACK::iterator _it_callback = _it->second.find((LONG)(pCallback)) ;
	IF_RETURN(_it->second.end() == _it_callback, S_OK) ;

	_it->second.erase(_it_callback) ;
	return S_OK ;
}

HRESULT CSUIExtensionCenter::AddGlobalExtensionListener(IUIExtensionCallback* pCallback)
{
	DEBUG_ASSERT(pCallback) ;
	IF_RETURN(NULL == pCallback, E_INVALIDARG) ;

	this->m_mapGlobalExtension[(LONG)pCallback] = pCallback ;
	return S_OK ;
}

HRESULT CSUIExtensionCenter::DelGlobalExtensionListener(IUIExtensionCallback* pCallback)
{
	DEBUG_ASSERT(pCallback) ;
	IF_RETURN(NULL == pCallback, E_INVALIDARG) ;

	MAP_CALLBACK::iterator _it = this->m_mapGlobalExtension.find((LONG)pCallback) ;
	if (this->m_mapGlobalExtension.end() != _it)
	{
		this->m_mapGlobalExtension.erase(_it) ;
	}
	return S_OK ;
}
