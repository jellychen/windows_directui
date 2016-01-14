#include "stdafx.h"
#include "CSUIWinMgr.h"

CSUIWinMgr::CSUIWinMgr()
{
}

CSUIWinMgr::~CSUIWinMgr()
{
}

HRESULT CSUIWinMgr::OnServiceInit()
{
	return S_OK ;
}

HRESULT CSUIWinMgr::OnServiceUnInit()
{
	return S_OK ;
}

HRESULT CSUIWinMgr::AddWindow(IUIWin* pWin)
{
	DEBUG_ASSERT(pWin) ;
	IF_RETURN(NULL == pWin, E_INVALIDARG) ;

	CWeakPtr<IUIWin> pWinAgent = pWin ;
	IF_RETURN(NULL == pWinAgent, E_FAIL) ;

	this->m_mapWindowsAgentPool[(LONG)(pWin)] = pWinAgent ;
	return S_OK ;
}

HRESULT CSUIWinMgr::DelWindow(IUIWin* pWin)
{
	DEBUG_ASSERT(pWin) ;
	IF_RETURN(NULL == pWin, E_INVALIDARG) ;

	MAP_WIN_AGENT_POOL::iterator it 
		= this->m_mapWindowsAgentPool.find((LONG)(pWin)) ;

	if (this->m_mapWindowsAgentPool.end() != it)
	{
		this->m_mapWindowsAgentPool.erase(it) ;
	}
	return S_OK ;
}

HRESULT CSUIWinMgr::GetWindowByHWnd(HWND hWnd, IUIWin** pWin)
{
	DEBUG_ASSERT(pWin) ;
	IF_RETURN(NULL == pWin, E_INVALIDARG) ;

	MAP_WIN_AGENT_POOL::iterator it
		= this->m_mapWindowsAgentPool.begin() ;

	for (; it != this->m_mapWindowsAgentPool.end(); ++it)
	{
		CWeakPtr<IUIWin> pWinAgent = it->second ;
		IF_CONTINUE(NULL == pWinAgent) ;

		HWND _hWnd = NULL ;
		pWinAgent->GetHWnd(&_hWnd) ;
		if (hWnd == _hWnd)
		{
			return pWinAgent.Promote(__uuidof(IUIWin), (VOID**)pWin) ;
		}
	}
	return S_OK ;
}

HRESULT CSUIWinMgr::GetAllWindows(ICVarArray* pWinArray)
{
	DEBUG_ASSERT(pWinArray) ;
	IF_RETURN(NULL == pWinArray, E_INVALIDARG) ;

	MAP_WIN_AGENT_POOL::iterator it
		= this->m_mapWindowsAgentPool.begin() ;

	for (; it != this->m_mapWindowsAgentPool.end(); ++it)
	{
		CWeakPtr<IUIWin> pWinAgent = it->second ;
		IF_CONTINUE(NULL == pWinAgent) ;

		CComPtr<IUIWin> pWindow ;
		pWinAgent.Promote(__uuidof(IUIWin), (VOID**)&pWindow) ;
		pWinArray->AddInterface(pWindow) ;
	}
	return S_OK ;
}

HRESULT CSUIWinMgr::GetAllWindowsCount(INT* pnCount)
{
	DEBUG_ASSERT(pnCount) ;
	IF_RETURN(NULL == pnCount, E_INVALIDARG) ;

	*pnCount = (INT)this->m_mapWindowsAgentPool.size() ;
	return S_OK ;
}