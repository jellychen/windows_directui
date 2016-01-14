#include "stdafx.h"
#include "CSUIExtWnd.h"

static CSUIExtWnd* _static_extwnd_service = NULL ;

LRESULT CALLBACK _extwnd_wnd_porc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (_static_extwnd_service)
	{
		_static_extwnd_service->OnMessage(hWnd, uMsg, wParam, lParam) ;
	}
	return ::DefWindowProc(hWnd, uMsg, wParam, lParam) ;
}

CSUIExtWnd::CSUIExtWnd()
{
	this->m_hExtWnd         = NULL ;
	_static_extwnd_service  = this ;
}

CSUIExtWnd::~CSUIExtWnd()
{
	_static_extwnd_service  = NULL ;
}

HRESULT CSUIExtWnd::OnInit()
{
	WNDCLASSEX wc       = {sizeof(WNDCLASSEX)} ;
	wc.hInstance        = ::GetModuleHandle(NULL) ;
	wc.lpszClassName    = _T("{UB_UI_TIMER}") ;
	wc.lpfnWndProc      = &_extwnd_wnd_porc ;
	wc.hbrBackground    = (HBRUSH)::GetStockObject(WHITE_BRUSH) ;

	::RegisterClassEx(&wc) ;
	this->m_hExtWnd = ::CreateWindowEx(0, wc.lpszClassName, 
		_T("{E44DC2CD-8E70-4a09-800E-902D3FABD3F9}"),
		WS_OVERLAPPED, 0, 0, 1, 1, HWND_MESSAGE, NULL, wc.hInstance, NULL) ;
	::ShowWindow(this->m_hExtWnd, SW_HIDE) ;

	return S_OK ;
}

HRESULT CSUIExtWnd::OnUnInit()
{
	if (::IsWindow(this->m_hExtWnd))
	{
		::DestroyWindow(this->m_hExtWnd) ;
		this->m_hExtWnd = NULL ;
		_static_extwnd_service  = NULL ;
	}
	return S_OK ;
}

HRESULT CSUIExtWnd::GetExtHWnd(HWND* pHWnd)
{
	DEBUG_ASSERT(pHWnd) ;
	IF_RETURN(NULL == pHWnd, E_INVALIDARG) ;

	*pHWnd = this->m_hExtWnd ;
	return S_OK ;
}

HRESULT CSUIExtWnd::PostMessage(INT nMsg, WPARAM wParam, LPARAM lParam)
{
	IF_RETURN(FALSE == ::IsWindow(this->m_hExtWnd), E_FAIL) ;

	::PostMessage(this->m_hExtWnd, (UINT)nMsg, wParam, lParam) ;
	return S_OK ;
}

HRESULT CSUIExtWnd::SendMessage(INT nMsg, WPARAM wParam, LPARAM lParam)
{
	IF_RETURN(FALSE == ::IsWindow(this->m_hExtWnd), E_FAIL) ;

	::SendMessage(this->m_hExtWnd, (UINT)nMsg, wParam, lParam) ;
	return S_OK ;
}

HRESULT CSUIExtWnd::RegisterCallback(INT nMessageId, IUIExtWndCallback* pCallback)
{
	DEBUG_ASSERT(pCallback) ;
	IF_RETURN(NULL == pCallback, E_INVALIDARG) ;

	this->m_mapCallback[nMessageId][LONG(pCallback)] = pCallback ;
	return S_OK ;
}

HRESULT CSUIExtWnd::UnRegisterCallback(INT nMessageId, IUIExtWndCallback* pCallback)
{
	DEBUG_ASSERT(pCallback) ;
	IF_RETURN(NULL == pCallback, E_INVALIDARG) ;

	MAP_CALLBACK_POOL::iterator it_outside = this->m_mapCallback.find(nMessageId) ;
	IF_RETURN(this->m_mapCallback.end() == it_outside, E_FAIL) ;

	MAP_CALLBACK::iterator it_inside = it_outside->second.find((LONG)(pCallback)) ;
	if (it_outside->second.end() != it_inside)
	{
		it_outside->second.erase(it_inside) ;
	}
	return S_OK ;
}

LRESULT CSUIExtWnd::OnMessage(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	MAP_CALLBACK_POOL::iterator it = this->m_mapCallback.find(uMsg) ;
	if (this->m_mapCallback.end() != it)
	{
		MAP_CALLBACK::iterator it_inside = it->second.begin() ;
		for (; it_inside != it->second.end(); ++it_inside)
		{
			IF_CONTINUE(NULL == it_inside->second) ;
			it_inside->second->OnNotifyMessage(uMsg, wParam, lParam) ;
		}
	}
	return 0 ;
}