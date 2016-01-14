#include "stdafx.h"
#include "CSUIMsgLoop.h"

CSUIMsgLoop::CSUIMsgLoop()
{
	this->m_dwQuitRef = 0 ;
	this->m_nCurrentLoopIndex = 0 ;
	this->m_bForceQuitAllLoop = FALSE ;
}

CSUIMsgLoop::~CSUIMsgLoop()
{
}

HRESULT CSUIMsgLoop::OnInit()
{
	return S_OK ;
}

HRESULT CSUIMsgLoop::OnUnInit()
{
	return S_OK ;
}

HRESULT CSUIMsgLoop::StartLoop()
{
	this->m_nCurrentLoopIndex++ ;
	this->_message_loop() ;
	this->m_nCurrentLoopIndex-- ;

	if (0 == this->m_nCurrentLoopIndex)
	{
		this->m_bForceQuitAllLoop = FALSE ;
	}
	return S_OK ;
}

HRESULT CSUIMsgLoop::QuitCurrentLoop()
{
	this->m_dwQuitRef++ ;
	return S_OK ;
}

HRESULT CSUIMsgLoop::ShouldQuitLoop()
{
	HRESULT hRet = E_FAIL ;
	if (this->m_dwQuitRef > 0)
	{
		hRet = S_OK ;
		this->m_dwQuitRef-- ;
	}
	return hRet ;
}

HRESULT CSUIMsgLoop::ForceQuitAllLoop()
{
	this->m_bForceQuitAllLoop = TRUE ;
	return S_OK ;
}

HRESULT CSUIMsgLoop::SetMsgLoopFunction(IUIMsgLoopFunction* pMsgLoop)
{
	this->m_pMsgLoopFunction = pMsgLoop ;
	return S_OK ;
}

HRESULT CSUIMsgLoop::RegisterLoopCallback(IUIMsgLoopCallback* pCallback)
{
	DEBUG_ASSERT(pCallback) ;
	IF_RETURN(NULL == pCallback, E_INVALIDARG) ;

	this->m_mapLoopCallback[(LONG)(pCallback)] = pCallback ;
	return S_OK ;
}

HRESULT CSUIMsgLoop::UnRegisterLoopCallback(IUIMsgLoopCallback* pCallback)
{
	DEBUG_ASSERT(pCallback) ;
	IF_RETURN(NULL == pCallback, E_INVALIDARG) ;

	MAP_CALLBACK::iterator it = this->m_mapLoopCallback.find((LONG)(pCallback)) ;
	if (this->m_mapLoopCallback.end() != it)
	{
		this->m_mapLoopCallback.erase(it) ;
	}
	return S_OK ;
}

HRESULT CSUIMsgLoop::NotifyMsgArrive(MSG* pMsg)
{
	MAP_CALLBACK::iterator it = this->m_mapLoopCallback.begin() ;
	for (;this->m_mapLoopCallback.end() != it; ++it)
	{
		IF_CONTINUE(NULL == it->second) ;
		it->second->OnMsgArrive(pMsg) ;
	}
	return S_OK ;
}

HRESULT CSUIMsgLoop::NotifyMsgComplete(MSG* pMsg)
{
	MAP_CALLBACK::iterator it = this->m_mapLoopCallback.begin() ;
	for (;this->m_mapLoopCallback.end() != it; ++it)
	{
		IF_CONTINUE(NULL == it->second) ;
		it->second->OnMsgComplete(pMsg) ;
	}
	return S_OK ;
}

VOID CSUIMsgLoop::_message_loop()
{
	if (this->m_pMsgLoopFunction)
	{
		this->m_pMsgLoopFunction->OnMsgLoop() ;
	}
	else
	{
		MSG _msg ;
		while(::GetMessage(&_msg, NULL, 0, 0) > 0) 
		{ 
			::TranslateMessage(&_msg) ; 
			::DispatchMessage(&_msg) ;

			if (SUCCEEDED(this->ShouldQuitLoop()))
			{
				break ;
			}
		} 
	}
}