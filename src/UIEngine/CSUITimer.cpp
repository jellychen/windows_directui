#include "stdafx.h"
#include "CSUITimer.h"

CSUITimer::CSUITimer():m_pExtWndCallbackPtr(this)
{
	this->m_hTimerWnd       = NULL ;
	this->m_bTimerRunning   = FALSE ;
	m_pExtWndCallbackPtr->Hook_OnNotifyMessage(&CSUITimer::OnMessageCallback) ;
}

CSUITimer::~CSUITimer()
{

}

HRESULT CSUITimer::OnInit()
{
	Common::Util::GetService(&m_pExtWndService) ;
	DEBUG_ASSERT((m_pExtWndService)) ;
	if (this->m_pExtWndService)
	{
		this->m_pExtWndService->GetExtHWnd(&m_hTimerWnd) ;
		this->m_pExtWndService->RegisterCallback(WM_TIMER, m_pExtWndCallbackPtr) ;
	}
	return S_OK ;
}

HRESULT CSUITimer::OnUnInit()
{
	return S_OK ;
}

HRESULT CSUITimer::SetTimerOut(IUITimerCallback* pCallback, DWORD dwTime, INT nTimerId)
{
	return this->AddNewItem(pCallback, dwTime, nTimerId, TRUE) ;
}

HRESULT CSUITimer::SetInterval(IUITimerCallback* pCallback, DWORD dwTime, INT nTimerId)
{
	return this->AddNewItem(pCallback, dwTime, nTimerId, FALSE) ;
}

HRESULT CSUITimer::Erase(IUITimerCallback* pCallback, INT nTimerId)
{
	DEBUG_ASSERT(pCallback) ;
	IF_RETURN(NULL == pCallback, E_INVALIDARG) ;
	MAP_TIMER_ID_POOL::iterator it = this->m_mapTimerIdPool.find((LONG)(pCallback)) ;
	if (this->m_mapTimerIdPool.end() != it)
	{
		if (0 != nTimerId)
		{
			it->second.clear() ;
		}
		else
		{
			std::set<INT>::iterator it_inside = it->second.find(nTimerId) ;
			if (it->second.end() != it_inside)
			{
				it->second.erase(it_inside) ;
			}
		}
	}
	return S_OK ;
}

HRESULT CSUITimer::OnMessageCallback(INT nMessageId, WPARAM wParam, LPARAM lParam)
{
	if (this->m_mapTimerPool.size() > 0)
	{
		MAP_TIMER_POOL::iterator it = this->m_mapTimerPool.begin() ;
		for (; it != this->m_mapTimerPool.end();)
		{
			if (it->first <= (LONG)::GetTickCount())
			{
				VEC_TIMER_ITME _item_array = it->second ;
				this->m_mapTimerPool.erase(it++) ;

				for (size_t i = 0; i < _item_array.size(); ++i)
				{
					IF_CONTINUE(NULL == _item_array[i].m_pTimerCallback) ;

					INT nTimerId = _item_array[i].m_nTimerId ;
					CComPtr<IUITimerCallback> pCallback = _item_array[i].m_pTimerCallback ;
					MAP_TIMER_ID_POOL::iterator it_outside = this->m_mapTimerIdPool.find((LONG)(IUITimerCallback*)(pCallback)) ;
					IF_CONTINUE(this->m_mapTimerIdPool.end() == it_outside) ;
					std::set<INT>::iterator it_inside = it_outside->second.find(nTimerId) ;
					IF_CONTINUE(it_outside->second.end() == it_inside) ;

					if (FALSE == _item_array[i].m_bOnce)
					{
						this->AddNewItem(pCallback, _item_array[i].m_dwIntervalTime, nTimerId, FALSE) ;
					}
					else
					{
						this->Erase(pCallback, nTimerId) ;
					}
					_item_array[i].m_pTimerCallback->OnTimer(_item_array[i].m_nTimerId) ;
				}
			}
			else
			{
				break ;
			}
		}
	}

	if (this->m_mapTimerPool.size() <= 0)
	{
		this->m_bTimerRunning = FALSE ;
		::KillTimer(this->m_hTimerWnd, 0) ;
	}
	else
	{
		MAP_TIMER_POOL::iterator it = this->m_mapTimerPool.begin() ;
		INT nTime = it->first - ::GetTickCount() ;
		if (nTime < 0)
		{
			nTime = 0 ;
		}

		::KillTimer(this->m_hTimerWnd, 0) ;
		::SetTimer(this->m_hTimerWnd, 0, nTime, NULL) ;
	}
	return S_OK ;
}

HRESULT CSUITimer::AddNewItem(IUITimerCallback* pTimerCallback, DWORD dwTime, INT nTimerId, BOOL bOnce)
{
	DEBUG_ASSERT(pTimerCallback) ;
	DEBUG_ASSERT(0 != nTimerId) ;
	IF_RETURN(NULL == pTimerCallback || 0 == nTimerId, E_FAIL) ;

	this->m_mapTimerIdPool[(LONG)(pTimerCallback)].insert(nTimerId)  ;

	CUITimerItem _timer_item ;
	_timer_item.m_bOnce                 = bOnce ;
	_timer_item.m_nTimerId              = nTimerId ;
	_timer_item.m_dwIntervalTime        = dwTime ;
	_timer_item.m_dwEndTime             = GetTickCount() + dwTime ;
	_timer_item.m_pTimerCallback        = pTimerCallback ;
	this->m_mapTimerPool[_timer_item.m_dwEndTime].push_back(_timer_item) ;

	if (FALSE == this->m_bTimerRunning && this->m_mapTimerPool.size() > 0)
	{
		MAP_TIMER_POOL::iterator it = this->m_mapTimerPool.begin() ;
		INT nTime = it->first - ::GetTickCount() ;
		if (nTime < 0)
		{
			nTime = 0 ;
		}

		::SetTimer(this->m_hTimerWnd, 0, nTime, NULL) ;
		this->m_bTimerRunning = TRUE ;
	}
	return S_OK ;
}