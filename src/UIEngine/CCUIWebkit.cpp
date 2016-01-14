#include "stdafx.h"
#include "CCUIWebkit.h"

CCUIWebkit::CCUIWebkit():m_pTimeCallbackPtr(this)
{
	
	this->m_pTimeCallbackPtr->Hook_OnTimer(&CCUIWebkit::OnTimer) ;
}

CCUIWebkit::~CCUIWebkit()
{
	this->m_pTimer->Erase(this->m_pTimeCallbackPtr, 1) ;
	wkeDestroyWebView(m_pWebkit) ;
}

HRESULT CCUIWebkit::FinalConstruct()
{
	wkeInit() ;
	this->m_pWebkit = wkeCreateWebView() ;
	this->m_pWebkit->setCookieEnabled(TRUE) ;
	this->m_pWebkit->setEditable(FALSE) ;
	this->m_pWebkit->setTransparent(true) ;
	this->m_pWebkit->setBufHandler(this) ;
	//this->m_pWebkit->tick() ;

	Common::Util::GetService(&m_pTimer) ;
	this->m_pTimer->SetInterval(this->m_pTimeCallbackPtr, 50, 1) ;
	return S_OK ;
}

HRESULT CCUIWebkit::SetUrl(BSTR bstrUrl)
{
	this->m_pWebkit->loadURL(bstrUrl) ;
	return S_OK ;
}

HRESULT CCUIWebkit::GetSize(SIZE* pszSize)
{
	DEBUG_ASSERT(pszSize) ;
	IF_RETURN(NULL == pszSize, E_INVALIDARG) ;

	CSize _sz(0, 0) ;
	__super::GetSize(&_sz) ;

	BOOL _bAutoWidth = FALSE, _bAutoHeight = FALSE ;
	__self->GetAutoWidth(&_bAutoWidth) ;
	__self->GetAutoHeight(&_bAutoHeight) ;
	if (_bAutoWidth && this->m_pWebkit)
	{
		_sz.cx = this->m_pWebkit->contentsWidth() ;
	}

	if (_bAutoHeight && this->m_pWebkit)
	{
		_sz.cy = this->m_pWebkit->contentsHeight() ;
	}
	*pszSize = _sz ;
	return S_OK ;
}

HRESULT CCUIWebkit::SetLayoutRect(RECT rcLayout)
{
	__super::SetLayoutRect(rcLayout) ;
	if (this->m_pWebkit)
	{
		CRect _rc = rcLayout ;
		this->m_pWebkit->resize(_rc.Width(), _rc.Height()) ;
		this->m_pWebkit->tick() ;
	}
	return S_OK ;
}

HRESULT CCUIWebkit::Render(IUICanvas* pCanvas, RECT rcRender, INT nState)
{
	__super::Render(pCanvas, rcRender, nState) ;
	HDC hCanvasDC = NULL ;
	pCanvas->GetCanvasDC(&hCanvasDC) ;

	CSize _sz(0, 0) ;
	__self->GetSize(&_sz) ;
	this->m_pWebkit->paint(hCanvasDC, 0, 0, _sz.cx, _sz.cy, 0, 0, TRUE) ;
	return S_OK ;
}

HRESULT CCUIWebkit::OnMessage(IUIFrame* pTarget, tMsgArg* pArg)
{
	IF_RETURN(NULL == pArg, E_FAIL) ;
	
	CPoint _pt(0, 0), _screen_pt(0, 0) ;
	__self->GetAbsolutLocation(&_pt) ;
	__self->GetScreenLocation(&_screen_pt) ;

	if (MESSAGE::UI_MOUSEWHEEL == pArg->dwMsgId)
	{
		int x = GET_X_LPARAM(pArg->lParam) - _screen_pt.x ;
		int y = GET_Y_LPARAM(pArg->lParam) - _screen_pt.y ;

		unsigned int flags = 0;
		if (pArg->wParam & MK_CONTROL)	flags |= WKE_CONTROL ;
		if (pArg->wParam & MK_SHIFT)	flags |= WKE_SHIFT ;
		if (pArg->wParam & MK_LBUTTON)	flags |= WKE_LBUTTON ;
		if (pArg->wParam & MK_MBUTTON)	flags |= WKE_MBUTTON ;
		if (pArg->wParam & MK_RBUTTON)	flags |= WKE_RBUTTON ;

		int delta = GET_WHEEL_DELTA_WPARAM(pArg->wParam) ;
		this->m_pWebkit->mouseWheel(x, y, delta, flags) ;
	}
	else if (MESSAGE::UI_MOUSEENTER == pArg->dwMsgId || MESSAGE::UI_MOUSELEAVE == pArg->dwMsgId)
	{
		int x = GET_X_LPARAM(pArg->lParam) - _pt.x ;
		int y = GET_Y_LPARAM(pArg->lParam) - _pt.y ;

		unsigned int flags = 0 ;
		if (pArg->wParam & MK_CONTROL)	flags |= WKE_CONTROL ;
		if (pArg->wParam & MK_SHIFT)	flags |= WKE_SHIFT ;
		if (pArg->wParam & MK_LBUTTON)	flags |= WKE_LBUTTON ;
		if (pArg->wParam & MK_MBUTTON)	flags |= WKE_MBUTTON ;
		if (pArg->wParam & MK_RBUTTON)	flags |= WKE_RBUTTON ;
		
		if (MESSAGE::UI_MOUSEENTER == pArg->dwMsgId)
		{
			this->m_pWebkit->mouseEvent(WM_MOUSEMOVE, x, y, flags) ;
		}
		else
		{
			this->m_pWebkit->mouseEvent(WM_MOUSELEAVE, x, y, flags) ;
		}
	}
	else if (MESSAGE::UI_LBTNDOWN == pArg->dwMsgId)
	{
		this->m_pWebkit->focus() ;
		__self->SetFocus(TRUE) ;

		int x = GET_X_LPARAM(pArg->lParam) - _pt.x ;
		int y = GET_Y_LPARAM(pArg->lParam) - _pt.y ;

		unsigned int flags = 0 ;
		if (pArg->wParam & MK_CONTROL)	flags |= WKE_CONTROL ;
		if (pArg->wParam & MK_SHIFT)	flags |= WKE_SHIFT ;
		if (pArg->wParam & MK_LBUTTON)	flags |= WKE_LBUTTON ;
		if (pArg->wParam & MK_MBUTTON)	flags |= WKE_MBUTTON ;
		if (pArg->wParam & MK_RBUTTON)	flags |= WKE_RBUTTON ;

		this->m_pWebkit->mouseEvent(WM_LBUTTONDOWN, x, y, flags) ;
	}
	else if (MESSAGE::UI_LBTNUP == pArg->dwMsgId)
	{
		int x = GET_X_LPARAM(pArg->lParam) - _pt.x ;
		int y = GET_Y_LPARAM(pArg->lParam) - _pt.y ;

		unsigned int flags = 0 ;
		if (pArg->wParam & MK_CONTROL)	flags |= WKE_CONTROL ;
		if (pArg->wParam & MK_SHIFT)	flags |= WKE_SHIFT ;
		if (pArg->wParam & MK_LBUTTON)	flags |= WKE_LBUTTON ;
		if (pArg->wParam & MK_MBUTTON)	flags |= WKE_MBUTTON ;
		if (pArg->wParam & MK_RBUTTON)	flags |= WKE_RBUTTON ;

		this->m_pWebkit->mouseEvent(WM_LBUTTONUP, x, y, flags);
	}
	else if (MESSAGE::UI_MOUSEMOVE == pArg->dwMsgId)
	{
		int x = GET_X_LPARAM(pArg->lParam) - _pt.x ;
		int y = GET_Y_LPARAM(pArg->lParam) - _pt.y ;

		unsigned int flags = 0 ;
		if (pArg->wParam & MK_CONTROL)	flags |= WKE_CONTROL ;
		if (pArg->wParam & MK_SHIFT)	flags |= WKE_SHIFT ;
		if (pArg->wParam & MK_LBUTTON)	flags |= WKE_LBUTTON ;
		if (pArg->wParam & MK_MBUTTON)	flags |= WKE_MBUTTON ;
		if (pArg->wParam & MK_RBUTTON)	flags |= WKE_RBUTTON ;

		this->m_pWebkit->mouseEvent(WM_MOUSEMOVE, x, y, flags);
	}
	else if (MESSAGE::UI_KEYDOWN == pArg->dwMsgId)
	{
		unsigned int virtualKeyCode = pArg->wParam ;
		unsigned int flags = 0;
		if (HIWORD(pArg->lParam) & KF_REPEAT)	flags |= WKE_REPEAT ;
		if (HIWORD(pArg->lParam) & KF_EXTENDED)	flags |= WKE_EXTENDED ;
		this->m_pWebkit->keyDown(virtualKeyCode, flags, false) ;
	}
	else if (MESSAGE::UI_KEYUP == pArg->dwMsgId)
	{
		unsigned int virtualKeyCode = pArg->wParam ;
		unsigned int flags = 0 ;
		if (HIWORD(pArg->lParam) & KF_REPEAT)	flags |= WKE_REPEAT ;
		if (HIWORD(pArg->lParam) & KF_EXTENDED)	flags |= WKE_EXTENDED ;
		this->m_pWebkit->keyUp(virtualKeyCode, flags, false);
	}
	else if (MESSAGE::UI_CHAR == pArg->dwMsgId)
	{
		tMsgArgKey* _pKeyArg = (tMsgArgKey*)pArg ;
		unsigned int charCode = _pKeyArg->unChar;
		unsigned int flags = 0;
		if (HIWORD(pArg->lParam) & KF_REPEAT)	flags |= WKE_REPEAT ;
		if (HIWORD(pArg->lParam) & KF_EXTENDED)	flags |= WKE_EXTENDED ;
		this->m_pWebkit->keyPress(charCode, flags, false) ;
	}
	else if (MESSAGE::UI_IME_STARTCOMPOSITION == pArg->dwMsgId)
	{
		wkeRect caret = this->m_pWebkit->getCaret() ;
		HWND _hWnd = UI::GetHostWnd<void>(GetEntity<IUIElement>()) ;
		IF_RETURN(!IsWindow(_hWnd), S_OK) ;

		CANDIDATEFORM form;
		form.dwIndex = 0;
		form.dwStyle = CFS_EXCLUDE;
		form.ptCurrentPos.x = caret.x + _pt.x;
		form.ptCurrentPos.y = caret.y + caret.h + _pt.y;
		form.rcArea.top = caret.y + _pt.y;
		form.rcArea.bottom = caret.y + caret.h + _pt.y;
		form.rcArea.left = caret.x + _pt.x;
		form.rcArea.right = caret.x + caret.w + _pt.x +1 ;
		COMPOSITIONFORM compForm ;
		compForm.ptCurrentPos=form.ptCurrentPos ;
		compForm.rcArea=form.rcArea ;
		compForm.dwStyle=CFS_POINT ;
	
		HIMC hIMC = ImmGetContext(_hWnd) ;
		ImmSetCandidateWindow(hIMC, &form) ;
		ImmSetCompositionWindow(hIMC,&compForm) ;
		ImmReleaseContext(_hWnd, hIMC) ;
	}
	
	
	if (MESSAGE::UI_CURSOR == pArg->dwMsgId)
	{
		return S_OK ;
	}

	return __super::OnMessage(pTarget, pArg) ;
}

HRESULT CCUIWebkit::SetAttribute(ICVarData* pAttrData)
{
	__super::SetAttribute(pAttrData) ;

	SET_ATTR_INTERFACE_BEGIN(pAttrData, IUIWebkit)
	SET_ATTR_BSTR			(Url)
	SET_ATTR_END            ()
	return S_OK ;
}

void CCUIWebkit::onBufUpdated(const HDC hdc,int x, int y, int cx, int cy)
{
	if (this->m_pWebkit)
	{
		BOOL _bAutoWidth = FALSE, _bAutoHeight = FALSE ;
		__self->GetAutoWidth(&_bAutoWidth) ;
		__self->GetAutoHeight(&_bAutoHeight) ;

		if (_bAutoWidth || _bAutoHeight)
		{
			BOOL _bNeedRelayout = FALSE ;

			CSize _sz(0, 0) ;
			__super::GetSize(&_sz) ;
			CSize _szWeb(0, 0) ;
			_szWeb.cx = this->m_pWebkit->contentsWidth() ;
			_szWeb.cy = this->m_pWebkit->contentsHeight() ;

			if (_bAutoHeight && _sz.cy != _szWeb.cy)
			{
				_bNeedRelayout = TRUE ;
			}

			if (_bAutoWidth && _sz.cx != _szWeb.cx)
			{
				_bNeedRelayout = TRUE ;
			}

			if (_bNeedRelayout)
			{
				GetEntity<IUIFrameInternal>()->MarkParentReCalcsize() ;
			}
		}
	}
	__self->Invalidate() ;
}

HRESULT CCUIWebkit::OnTimer(INT nTimerId)
{
	this->m_pWebkit->tick() ;
	return S_OK ;
}