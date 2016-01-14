#include "stdafx.h"
#include "CCUIWin.h"

CCUIWin::CCUIWin():m_pTimerCallback(this)
{
	this->m_bTopMost		= FALSE ;
	this->m_bLayerWin		= FALSE ;
	this->m_bToolWin		= FALSE ;
	this->m_bFixSize		= FALSE ;
	this->m_bFixLocation	= FALSE ;
	this->m_bDoModal		= FALSE ;
	this->m_bNeedRePaint	= TRUE ;
	this->m_szWin           = CSize(800, 600) ;
	this->m_szWinMinSize    = CSize(0, 0) ;
	this->m_szWinMaxSize    = CSize(INT_MAX, INT_MAX) ;
	this->m_ptWinLocation   = CPoint(INT_MIN, INT_MIN) ;
	this->m_rcWinBorder     = CRect(8, 8, 8, 8) ;
	this->m_rcWinOutBorder  = CRect(0, 0, 0, 0) ;
	this->m_cWinAlpha       = 255 ;

	// test
	RotateX					= 0 ;
	OffsetZ					= 0 ;
	m_pTimerCallback->Hook_OnTimer(&CCUIWin::OnTimer) ;
	CWeakPtr<IUITimer> pTimer ;
	Common::Util::GetService(&pTimer) ;
	//pTimer->SetInterval(m_pTimerCallback, 20, 1) ;
}

CCUIWin::~CCUIWin()
{
	
}

HRESULT CCUIWin::FinalConstruct()
{
	Common::Util::CreateObject(&m_pQuadTree) ;
	DEBUG_ASSERT(m_pQuadTree) ;
	Common::Util::CreateObject(&m_pSplit) ;
	DEBUG_ASSERT(m_pSplit) ;
	Common::Util::CreateObject(&m_pWinCanvas) ;
	DEBUG_ASSERT(m_pWinCanvas) ;
	Common::Util::CreateObject(&m_pHittest) ;
	DEBUG_ASSERT(m_pHittest) ;
	Common::Util::CreateObject(&m_pRender) ;
	DEBUG_ASSERT(m_pRender) ;

	Common::Util::CreateObject(&m_p3DTransfrom) ;
	DEBUG_ASSERT(m_p3DTransfrom) ;
	Common::Util::GetService(&m_pWinMgr) ;
	DEBUG_ASSERT(m_pWinMgr) ;

	__self->SetHittest(HTCAPTION) ;

	return S_OK ;
}

HRESULT CCUIWin::SetTitle(BSTR bsTitle)
{
	IF_RETURN(!::IsWindow(this->m_hWnd), E_FAIL) ;
	::SetWindowText(this->m_hWnd, (LPCWSTR)bsTitle) ;
	return TRUE ;
}

HRESULT CCUIWin::GetTitle(BSTR* bsTitle)
{
	IF_RETURN(!::IsWindow(this->m_hWnd), E_FAIL) ;
	DEBUG_ASSERT(bsTitle) ;
	IF_RETURN(NULL == bsTitle, E_FAIL) ;

	TCHAR _tStr[MAX_PATH] = {0} ;
	::GetWindowText(this->m_hWnd, _tStr, MAX_PATH) ;
	CComBSTR bstrTitle(_tStr) ;
	return bstrTitle.CopyTo(bsTitle) ;
}

HRESULT CCUIWin::SetLayerWin(BOOL bLayerWin)
{
	this->m_bLayerWin = bLayerWin ;
	if (::IsWindow(this->m_hWnd))
	{
		LONG lStyle = ::GetWindowLong(this->m_hWnd, GWL_EXSTYLE) ;
		if (bLayerWin)
		{
			lStyle |= WS_EX_LAYERED ;
		}
		else
		{
			lStyle &= ~WS_EX_LAYERED ;
		}

		::SetWindowLong(this->m_hWnd, GWL_EXSTYLE, lStyle) ;
		::InvalidateRect(this->m_hWnd, NULL, TRUE) ;
	}
	return S_OK ;
}

HRESULT CCUIWin::GetLayerWin(BOOL* pbLayerWin)
{
	DEBUG_ASSERT(pbLayerWin) ;
	IF_RETURN(NULL == pbLayerWin, E_INVALIDARG) ;
	*pbLayerWin = this->m_bLayerWin ;
	return S_OK ;
}

HRESULT CCUIWin::SetWindowAlpha(BYTE cAlpha)
{
	this->m_cWinAlpha = cAlpha ;
	if (::IsWindow(this->m_hWnd))
	{
		::InvalidateRect(this->m_hWnd, NULL, TRUE) ;
	}
	return S_OK ;
}

HRESULT CCUIWin::GetWindowAlpha(BYTE* pcAlpha)
{
	DEBUG_ASSERT(pcAlpha) ;
	IF_RETURN(NULL == pcAlpha, E_INVALIDARG) ;

	if (this->m_bLayerWin)
	{
		*pcAlpha = this->m_cWinAlpha ;
	}
	else
	{
		*pcAlpha = 255 ;
	}
	return S_OK ;
}

HRESULT CCUIWin::GetHWnd(HWND* pHWnd)
{
	DEBUG_ASSERT(pHWnd) ;
	IF_RETURN(NULL == pHWnd, E_INVALIDARG) ;
	*pHWnd = this->m_hWnd ;
	return S_OK ;
}

HRESULT CCUIWin::SetWinSize(SIZE szWin)
{
	__super::SetSize(szWin) ;
	this->m_szWin = szWin ;
	if (::IsWindow(this->m_hWnd))
	{
		::SetWindowPos(this->m_hWnd, NULL, 0, 0,
			szWin.cx, szWin.cy, SWP_NOMOVE|SWP_NOZORDER|SWP_NOACTIVATE) ;
	}
	return S_OK ;
}

HRESULT CCUIWin::GetWinSize(SIZE* pszWin)
{
	DEBUG_ASSERT(pszWin) ;
	IF_RETURN(NULL == pszWin, E_INVALIDARG) ;
	if (::IsWindow(this->m_hWnd))
	{
		CRect rcWnd(0, 0, 0, 0) ;
		::GetWindowRect(this->m_hWnd, &rcWnd) ;
		CRect rc = rcWnd ;
		pszWin->cx = rcWnd.Width() ;
		pszWin->cy = rcWnd.Height() ;
	}
	else
	{
		*pszWin = CSize(0, 0) ;
	}
	return S_OK ;
}

HRESULT CCUIWin::SetMinWinSize(SIZE szWin)
{
	return S_OK ;
}

HRESULT CCUIWin::GetMinWinSize(SIZE* pszWin)
{
	return S_OK ;
}

HRESULT CCUIWin::SetMaxWinSize(SIZE szWin)
{
	return S_OK ;
}

HRESULT CCUIWin::GetMaxWinSize(SIZE* pszWin)
{
	return S_OK ;
}

HRESULT CCUIWin::SetFixSize(BOOL bFixSize)
{
	if (::IsWindow(m_hWnd) && this->m_bFixSize != bFixSize )
	{
		DWORD dwStyle = ::GetWindowLong(this->m_hWnd, GWL_STYLE) ;
		if (bFixSize)
		{
			dwStyle = dwStyle & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX;
		}
		else
		{
			dwStyle = dwStyle | WS_SIZEBOX ;
		}
		::SetWindowLong(this->m_hWnd, GWL_STYLE, (LONG)dwStyle) ;
	}
	this->m_bFixSize = bFixSize ;
	return S_OK ;
}

HRESULT CCUIWin::GetFixSize(BOOL* pbFixSize)
{
	DEBUG_ASSERT(pbFixSize) ;
	IF_RETURN(NULL == pbFixSize, E_INVALIDARG) ;
	*pbFixSize = this->m_bFixSize ;
	return S_OK ;
}

HRESULT CCUIWin::SetWinLocation(POINT ptLocation)
{
	this->m_ptWinLocation = ptLocation ;
	if (::IsWindow(this->m_hWnd))
	{
		::SetWindowPos(this->m_hWnd, NULL, ptLocation.x, ptLocation.y , 
			this->m_szWin.cx, this->m_szWin.cy, SWP_NOZORDER|SWP_NOACTIVATE) ;
	}
	return S_OK ;
}

HRESULT CCUIWin::GetWinLocation(POINT* pptLocation)
{
	DEBUG_ASSERT(pptLocation) ;
	IF_RETURN(NULL == pptLocation, E_INVALIDARG) ;
	if (::IsWindow(this->m_hWnd))
	{
		CRect rcWnd ;
		::GetWindowRect(this->m_hWnd, &rcWnd) ;
		*pptLocation = rcWnd.TopLeft() ;
	}
	else
	{
		*pptLocation = CPoint(0, 0) ;
	}
	return S_OK ;
}

HRESULT CCUIWin::SetFixLocation(BOOL bFixLocation)
{
	return S_OK ;
}

HRESULT CCUIWin::GetFixLocation(BOOL* pbFixLocation)
{
	return S_OK ;
}

HRESULT CCUIWin::SetWindowBorder(RECT rcBorder)
{
	this->m_rcWinBorder = rcBorder ;
	return S_OK ;
}

HRESULT CCUIWin::GetWindowBorder(RECT* prcBorder)
{
	DEBUG_ASSERT(prcBorder) ;
	IF_RETURN(NULL == prcBorder, E_INVALIDARG) ;

	*prcBorder = this->m_rcWinBorder ;
	return S_OK ;
}

HRESULT CCUIWin::SetWindowOutBorder(RECT rcBorder)
{
	this->m_rcWinOutBorder = rcBorder ;
	return S_OK ;
}

HRESULT CCUIWin::GetWindowOutBorder(RECT* prcBorder)
{
	DEBUG_ASSERT(prcBorder) ;
	IF_RETURN(NULL == prcBorder, E_INVALIDARG) ;

	*prcBorder = this->m_rcWinOutBorder ;
	return S_OK ;
}

HRESULT CCUIWin::SetTopMost(BOOL bTopMost)
{
	this->m_bTopMost = bTopMost ;
	if (::IsWindow(this->m_hWnd) && bTopMost)
	{
		::SetWindowPos(this->m_hWnd, HWND_TOPMOST, 
			0,0,0,0, SWP_NOACTIVATE|SWP_NOMOVE|SWP_NOSIZE) ;
	}
	return S_OK ;
}

HRESULT CCUIWin::GetTopMoust(BOOL* pbTopMost)
{
	DEBUG_ASSERT(pbTopMost) ;
	IF_RETURN(NULL == pbTopMost, E_INVALIDARG) ;

	*pbTopMost = this->m_bTopMost ;
	return S_OK ;
}

HRESULT CCUIWin::SetToolWindow(BOOL bToolWindow)
{
	this->m_bToolWin = bToolWindow ;
	IF_RETURN(FALSE == ::IsWindow(this->m_hWnd), S_OK) ;

	if (bToolWindow)
	{
		__self->ModifyStyle(WS_MAXIMIZEBOX, 0, 0) ;
		__self->ModifyStyleEx(0, WS_EX_TOOLWINDOW, 0) ;
	}
	else
	{
		__self->ModifyStyle(0, WS_MAXIMIZEBOX, 0) ;
		__self->ModifyStyleEx(WS_EX_TOOLWINDOW, 0, 0) ;
	}

	return S_OK ;
}

HRESULT CCUIWin::GetToolWindow(BOOL* pbToolWindow)
{
	DEBUG_ASSERT(pbToolWindow) ;
	IF_RETURN(NULL == pbToolWindow, E_INVALIDARG) ;

	*pbToolWindow = this->m_bToolWin ;
	return S_OK ;
}

HRESULT CCUIWin::GetStyle(DWORD* pdwStyle)
{
	DEBUG_ASSERT(pdwStyle) ;
	IF_RETURN(NULL == pdwStyle, E_INVALIDARG) ;
	*pdwStyle = 0 ;

	DEBUG_ASSERT(::IsWindow(this->m_hWnd)) ;
	IF_RETURN(FALSE == ::IsWindow(this->m_hWnd), E_FAIL) ;
	*pdwStyle = ::GetWindowLong(this->m_hWnd, GWL_STYLE) ;
	return S_OK ;
}

HRESULT CCUIWin::GetStyleEx(DWORD* pdwStyleEx)
{
	DEBUG_ASSERT(pdwStyleEx) ;
	IF_RETURN(NULL == pdwStyleEx, E_INVALIDARG) ;
	*pdwStyleEx = 0 ;

	DEBUG_ASSERT(::IsWindow(this->m_hWnd)) ;
	IF_RETURN(FALSE == ::IsWindow(this->m_hWnd), E_FAIL) ;
	*pdwStyleEx = ::GetWindowLong(this->m_hWnd, GWL_EXSTYLE) ;
	return S_OK ;
}

HRESULT CCUIWin::ModifyStyle(DWORD dwRmove, DWORD dwAdd, UINT uFlags)
{
	DEBUG_ASSERT(::IsWindow(this->m_hWnd)) ;
	IF_RETURN(FALSE == ::IsWindow(this->m_hWnd), E_FAIL) ;
	DWORD dwStyle = ::GetWindowLong(this->m_hWnd, GWL_STYLE) ;
	DWORD dwNewStyle = (dwStyle & ~dwRmove) | dwAdd ;
	IF_RETURN(dwStyle == dwNewStyle, S_OK) ;

	::SetWindowLong(this->m_hWnd, GWL_STYLE, dwNewStyle) ;
	if (0 != uFlags)
	{
		::SetWindowPos(this->m_hWnd, NULL, 0, 0, 0, 0,
			SWP_NOSIZE | SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE | uFlags) ;
	}
	return S_OK ;
}

HRESULT CCUIWin::ModifyStyleEx(DWORD dwRmove, DWORD dwAdd, UINT uFlags)
{
	DEBUG_ASSERT(::IsWindow(this->m_hWnd)) ;
	IF_RETURN(FALSE == ::IsWindow(this->m_hWnd), E_FAIL) ;
	DWORD dwStyle = ::GetWindowLong(this->m_hWnd, GWL_EXSTYLE) ;
	DWORD dwNewStyle = (dwStyle & ~dwRmove) | dwAdd ;
	IF_RETURN(dwStyle == dwNewStyle, S_OK) ;

	::SetWindowLong(this->m_hWnd, GWL_EXSTYLE, dwNewStyle) ;
	if (0 != uFlags)
	{
		::SetWindowPos(this->m_hWnd, NULL, 0, 0, 0, 0,
			SWP_NOSIZE | SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE | uFlags) ;
	}
	return S_OK ;
}

HRESULT CCUIWin::SendMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	DEBUG_ASSERT(::IsWindow(this->m_hWnd)) ;
	IF_RETURN(FALSE == ::IsWindow(this->m_hWnd), E_FAIL) ;
	::SendMessage(this->m_hWnd, uMsg, wParam, lParam) ;
	return S_OK ;
}

HRESULT CCUIWin::PostMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	DEBUG_ASSERT(::IsWindow(this->m_hWnd)) ;
	IF_RETURN(FALSE == ::IsWindow(this->m_hWnd), E_FAIL) ;
	::PostMessage(this->m_hWnd, uMsg, wParam, lParam) ;
	return S_OK ;
}

HRESULT CCUIWin::SetWinCenter()
{
	IF_RETURN(!::IsWindow(m_hWnd), E_FAIL) ;
	INT nScreenWidth = ::GetSystemMetrics(SM_CXSCREEN) ;
	INT nScreenHeight= ::GetSystemMetrics(SM_CYSCREEN) ;

	CPoint ptTarget(0, 0) ;
	ptTarget.x  = (nScreenWidth - this->m_szWin.cx)/2 ;
	ptTarget.y  = (nScreenHeight - this->m_szWin.cy)/2 ;

	::SetWindowPos(this->m_hWnd, NULL, ptTarget.x, 
		ptTarget.y, 0, 0,SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE) ;

	this->m_ptWinLocation = ptTarget ;
	return S_OK ;
}

HRESULT CCUIWin::BringToTop()
{
	DEBUG_ASSERT(::IsWindow(this->m_hWnd)) ;
	IF_RETURN(FALSE == ::IsWindow(this->m_hWnd), E_FAIL) ;

	::BringWindowToTop(this->m_hWnd) ;
	return S_OK ;
}

HRESULT CCUIWin::SetActiveWindow()
{
	DEBUG_ASSERT(::IsWindow(this->m_hWnd)) ;
	IF_RETURN(FALSE == ::IsWindow(this->m_hWnd), E_FAIL) ;

	::SetActiveWindow(this->m_hWnd) ;
	return S_OK ;
}

HRESULT CCUIWin::RefreshWindow()
{
	if (FALSE == this->m_bNeedRePaint)
	{
		::InvalidateRect(this->m_hWnd, NULL, TRUE) ;
		this->m_bNeedRePaint = TRUE ;
	}
	return S_OK ;
}

HRESULT CCUIWin::GetCaptureFrame(IUIFrame** ppFrame)
{
	DEBUG_ASSERT(ppFrame) ;
	IF_RETURN(NULL == ppFrame, E_INVALIDARG) ;
	*ppFrame = NULL ;

	if (this->m_pCatureFrameAgent)
	{
		return  this->m_pCatureFrameAgent.Promote(__uuidof(IUIFrame), (VOID**)ppFrame) ;
	}
	return E_FAIL ;
}

HRESULT CCUIWin::FrameFromPoint(POINT ptTarget, IUIFrame** ppFrame)
{
	DEBUG_ASSERT(ppFrame && m_pQuadTree) ;
	IF_RETURN(NULL == ppFrame ||  NULL == m_pQuadTree, E_INVALIDARG) ;
	*ppFrame = NULL ;

	CComQIPtr<IUIAddFrame> pAddFrame = this->m_pHittest ;
	DEBUG_ASSERT(pAddFrame) ;
	IF_RETURN(NULL == pAddFrame , E_FAIL) ;

	this->m_pQuadTree->FrameFromPoint2(ptTarget, pAddFrame) ;
	return this->m_pHittest->GetHitFrame(ppFrame, FALSE) ;
}

HRESULT CCUIWin::SetFoucsControl(IUIControl* pControl)
{
	if (this->m_pFoucsControl)
	{
		this->m_pFoucsControl->SetFocus(FALSE) ;
	}
	
	IF_RETURN(NULL == pControl, E_FAIL) ;
	this->m_pFoucsControl = pControl ;

	if (this->m_pFoucsControl)
	{
		this->m_pFoucsControl->SetFocus(TRUE) ;
	}
	return S_OK ;
}

HRESULT CCUIWin::GetFoucsControl(IUIControl** ppControl)
{
	DEBUG_ASSERT(ppControl) ;
	IF_RETURN(NULL == ppControl, E_INVALIDARG) ;
	*ppControl = NULL ;
	
	if (this->m_pFoucsControl)
	{
		return this->m_pFoucsControl.Promote(__uuidof(IUIControl), (VOID**)ppControl) ;
	}
	return E_FAIL ;
}

HRESULT CCUIWin::AddMessageCallback(IUIWindowMessageCallback* pCallback)
{
	DEBUG_ASSERT(pCallback) ;
	IF_RETURN(NULL == pCallback, E_INVALIDARG) ;

	this->m_mapWindowMessageCallbackPool[(LONG)(pCallback)] = pCallback ;
	return S_OK ;
}

HRESULT CCUIWin::DelMessageCallback(IUIWindowMessageCallback* pCallback)
{
	DEBUG_ASSERT(pCallback) ;
	IF_RETURN(NULL == pCallback, E_INVALIDARG) ;

	MAP_MESSAGE_CALLBACK::iterator it 
		= this->m_mapWindowMessageCallbackPool.find((LONG)(pCallback)) ;
	if (this->m_mapWindowMessageCallbackPool.end() != it)
	{
		this->m_mapWindowMessageCallbackPool.erase(it) ;
	}
	return S_OK ;
}

HRESULT CCUIWin::HandleWinMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL* pbHandle, LRESULT* pResult)
{
	IF_RETURN(NULL == pbHandle || NULL == pResult, E_INVALIDARG) ;
	BOOL bHandle = FALSE ;

	MAP_MESSAGE_CALLBACK::iterator it 
		= this->m_mapWindowMessageCallbackPool.begin() ;
	for (;this->m_mapWindowMessageCallbackPool.end() != it; ++it)
	{
		IF_CONTINUE(NULL == it->second) ;
		it->second->OnWindowMessage(this->m_hWnd, uMsg, wParam, lParam) ;
	}

	WINDOW_MESSAGE_BEGIN    (uMsg, pResult)
	WINDOW_ACTIVATE         (OnActivate,        wParam, lParam, bHandle)
	WINDOW_ERASEBKGND       (OnEraseBkgnd,      wParam, lParam, bHandle)
	WINDOW_NCCALCSIZE       (OnNcCalcSize,      wParam, lParam, bHandle)
	WINDOW_GETMINMAXINFO    (OnGetMinMaxInfo,   wParam, lParam, bHandle)
	WINDOW_NCHITTEST        (OnNcHitTest,       wParam, lParam, bHandle)
	WINDOW_NCPAINT          (OnNcPaint,         wParam, lParam, bHandle)
	WINDOW_NCLBUTTONDOWN    (OnNcLBtnDown,      wParam, lParam, bHandle)
	WINDOW_SIZE             (OnSize,            wParam, lParam, bHandle)
	WINDOW_MOVING           (OnMoving,          wParam, lParam, bHandle)
	WINDOW_PAINT            (OnPaint,           wParam, lParam, bHandle)
	WINDOW_MOUSEMOVE        (OnMouseMove,       wParam, lParam, bHandle)
	WINDOW_MOUSELEAVE       (OnMouseLeave,      wParam, lParam, bHandle)
	WINDOW_KEYDOWN          (OnKeyDown,         wParam, lParam, bHandle)
	WINDOW_DESTROY          (OnDestory,         wParam, lParam, bHandle)
	WINDOW_MESSAGE_END      ()
	//if (uMsg == WM_NCACTIVATE)
	//{
	//	bHandle = TRUE ;
	//}

	BOOL bHandleMsgRoute = this->m_pMessageRoute.DispatchMessage(uMsg, wParam, lParam) ;

	if (FALSE == bHandle /*&& FALSE == bHandleMsgRoute*/)
	{
		*pResult = ::DefWindowProc(m_hWnd, uMsg, wParam, lParam) ;
	}

	if (WM_NCHITTEST == uMsg)
	{
		//DEBUG_TRACE(_T("%d \n"), *pResult) ;
		
	}
	return S_OK ;
}

HRESULT CCUIWin::SetWinIcon(BOOL bBig, HICON hIcon)
{
	return S_OK ;
}

HRESULT CCUIWin::CreateWin(IUIWin* pParent, ICVarData* pArg)
{
	IF_RETURN(::IsWindow(this->m_hWnd), E_FAIL) ;

	HWND        hParent = NULL ;
	DWORD       dwStyle = WS_THICKFRAME|WS_MINIMIZEBOX|WS_MAXIMIZEBOX ;
	DWORD       dwExStyle = WS_EX_LEFT|WS_EX_LTRREADING ;
	CComBSTR    bstrWinTitle = _T("UB_WINDOWS") ;
	CRect       rcWindow(0, 0, 800, 600) ;

	if (pParent)
	{
		pParent->GetHWnd(&hParent) ;
	}

	if (pArg)
	{
		pArg->GetString(CComBSTR(WINDOW::tcWinTitle), &bstrWinTitle) ;
		pArg->GetRect(CComBSTR(WINDOW::tcWinRect), &rcWindow) ;
		pArg->GetDWord(CComBSTR(WINDOW::tcWinStyle),&dwStyle) ;
		pArg->GetDWord(CComBSTR(WINDOW::tcWinStyleEx), &dwExStyle) ;
	}

	__super::Create(hParent, rcWindow, NULL, dwStyle, dwExStyle) ;

	IF_RETURN(!::IsWindow(this->m_hWnd), E_FAIL) ;

	
	if (this->m_pWinMgr)
	{
		this->m_pWinMgr->AddWindow(GetEntity<IUIWin>()) ;
	}
	this->m_pMessageRoute.InitMsgRoute(this->m_hWnd, GetEntity<IUIWin>()) ;


	__self->SetLayerWin(this->m_bLayerWin) ;
	__self->SetToolWindow(this->m_bToolWin) ;
	__self->SetWinLocation(this->m_ptWinLocation) ;
	__self->SetSize(this->m_szWin) ;
	__self->SetTopMost(this->m_bTopMost) ;

	if (INT_MIN == this->m_ptWinLocation.x || INT_MIN == this->m_ptWinLocation.y)
	{
		__self->SetWinCenter() ;
	}
	return S_OK ;
}

HRESULT CCUIWin::ShowWin(INT nShowCmd)
{
	DEBUG_ASSERT(::IsWindow(this->m_hWnd)) ;
	IF_RETURN(!::IsWindow(this->m_hWnd), E_FAIL) ;

	::ShowWindow(this->m_hWnd, nShowCmd) ;
	return S_OK ;
}

HRESULT CCUIWin::DoModal(IUIWin* pParent, INT nShowCmd)
{
	if (pParent)
	{
		pParent->SetEnable(FALSE) ;
	}

	this->m_pDoModalWinAgent = pParent ;

	this->m_bDoModal = TRUE ;
	::ShowWindow(this->m_hWnd, nShowCmd) ;

	CWeakPtr<IUIMsgLoop> pMessageLoop ;
	Common::Util::GetService(&pMessageLoop) ;
	if (pMessageLoop)
	{
		pMessageLoop->StartLoop() ;
	}

	this->m_bDoModal = FALSE ;
	return S_OK ;
}

HRESULT CCUIWin::DestoryWin()
{
	DEBUG_ASSERT(::IsWindow(this->m_hWnd)) ;
	IF_RETURN(FALSE == ::IsWindow(this->m_hWnd), E_FAIL) ;

	if (this->m_bDoModal && this->m_pDoModalWinAgent)
	{
		this->m_pDoModalWinAgent->SetEnable(TRUE) ;
		this->m_pDoModalWinAgent = NULL ;
	}
	::DestroyWindow(this->m_hWnd) ;
	return S_OK ;
}

HRESULT CCUIWin::IdleDestoryWin()
{
	return S_OK ;
}

HRESULT CCUIWin::SetCapture(BOOL bCapture)
{
	return E_FAIL ;
}

HRESULT CCUIWin::SetEnable(BOOL bEnable)
{
	HRESULT hRet = __super::SetEnable(bEnable) ;

	DEBUG_ASSERT(::IsWindow(this->m_hWnd)) ;
	IF_RETURN(FALSE == ::IsWindow(this->m_hWnd), E_FAIL) ;
	::EnableWindow(this->m_hWnd, bEnable) ;

	return hRet ;
}

HRESULT CCUIWin::GetAbsolutLocation(POINT* pptLocation)
{
	DEBUG_ASSERT(pptLocation) ;
	IF_RETURN(NULL == pptLocation, E_INVALIDARG) ;

	pptLocation->x = 0 ;
	pptLocation->y = 0 ;
	return S_OK ;
}

HRESULT CCUIWin::GetScreenLocation(POINT* pptLocation)
{
	DEBUG_ASSERT(pptLocation) ;
	IF_RETURN(NULL == pptLocation, E_INVALIDARG) ;

	*pptLocation = CPoint(0, 0) ;
	if (::IsWindow(this->m_hWnd))
	{
		CRect rcWnd(0, 0, 0, 0) ;
		::GetWindowRect(this->m_hWnd, &rcWnd) ;
		*pptLocation = rcWnd.TopLeft() ;
	}
	return S_OK ;
}

HRESULT CCUIWin::GetAbsolutVisibleRect(RECT* prcRect)
{
	DEBUG_ASSERT(prcRect) ;
	IF_RETURN(NULL == prcRect, E_INVALIDARG) ;

	prcRect->left   = 0 ;
	prcRect->top    = 0 ;
	prcRect->right  = this->m_szWin.cx ;
	prcRect->bottom = this->m_szWin.cy ;
	return S_OK ;
}

HRESULT CCUIWin::GetShowAlpha(BYTE* pcAlpha)
{
	DEBUG_ASSERT(pcAlpha) ;
	IF_RETURN(NULL == pcAlpha, E_INVALIDARG) ;

	*pcAlpha = 255 ;
	return S_OK ;
}

HRESULT CCUIWin::GetMousePosInternal(POINT* pptPoint)
{
	DEBUG_ASSERT(pptPoint) ;
	IF_RETURN(NULL == pptPoint, E_INVALIDARG) ;

	::GetCursorPos(pptPoint) ;
	if (::IsWindow(this->m_hWnd))
	{
		::ScreenToClient(this->m_hWnd, pptPoint) ;
	}

	return E_FAIL ;
}

HRESULT CCUIWin::SetCaptureInternal(BOOL bCapture, IUIFrame* pFrame)
{
	DEBUG_ASSERT(pFrame) ;
	IF_RETURN(NULL == pFrame, E_INVALIDARG) ;

	CComPtr<IUIFrame> pCurrentCapture ;
	if (this->m_pCatureFrameAgent)
	{
		this->m_pCatureFrameAgent.GetAgent()
			->QueryOrigin(__uuidof(IUIFrame), (VOID**)&pCurrentCapture) ;
	}

	if (bCapture && pCurrentCapture != pFrame)
	{
		::SetCapture(this->m_hWnd) ;
		this->m_pCatureFrameAgent = pFrame ;
	}
	else if (!bCapture && pCurrentCapture == pFrame)
	{
		::ReleaseCapture() ;
		this->m_pCatureFrameAgent = NULL ;
	}

	return S_OK ;
}

HRESULT CCUIWin::GetCaptureInternal(IUIFrame** ppFrame)
{
	DEBUG_ASSERT(ppFrame) ;
	IF_RETURN(NULL == ppFrame, E_INVALIDARG) ;
	*ppFrame = NULL ;

	if (this->m_pCatureFrameAgent)
	{
		return this->m_pCatureFrameAgent.Promote(__uuidof(IUIFrame), (VOID**)ppFrame) ;
	}
	return E_FAIL ;
}

HRESULT CCUIWin::SynchronizeInternal(IUIFrame* pFrame, BOOL bErase)
{
	DEBUG_ASSERT(pFrame) ;
	IF_RETURN(NULL == pFrame , E_INVALIDARG) ;
	IF_RETURN(NULL == this->m_pQuadTree, E_INVALIDARG) ;

	if (FALSE == bErase)
	{
		CRect rcVisibleRect(0, 0, 0, 0) ;
		CRect rcOldVisibleRect(0, 0, 0, 0) ;
		pFrame->GetAbsolutVisibleRect(&rcVisibleRect) ;
		this->m_pQuadTree->GetFrameRect(pFrame, &rcOldVisibleRect) ;

		if (rcVisibleRect != rcOldVisibleRect)
		{
			this->m_pQuadTree->SynchFrame(rcVisibleRect, pFrame) ;

			if (this->m_pSplit)
			{
				this->m_pSplit->AddRect(rcVisibleRect) ;
				this->m_pSplit->AddRect(rcOldVisibleRect) ;
			}

			if (FALSE == this->m_bNeedRePaint)
			{
				::InvalidateRect(this->m_hWnd, NULL, TRUE) ;
				this->m_bNeedRePaint = TRUE ;
			}
		}
	}
	else
	{
		this->m_pQuadTree->EraseFrame(pFrame) ;
	}
	return S_OK ;
}

HRESULT CCUIWin::InvalidateInternal(IUIFrame* pFrame)
{
	DEBUG_ASSERT(pFrame) ;
	IF_RETURN(NULL == pFrame, E_INVALIDARG) ;

	CWeakPtr<IUIFrame> pFrameAgent  = pFrame ;
	if (pFrameAgent)
	{
		this->m_vecFrameAgent.push_back(pFrameAgent) ;
	}

	if (FALSE == this->m_bNeedRePaint && this->m_hWnd)
	{
		::InvalidateRect(this->m_hWnd, NULL, TRUE) ;
		this->m_bNeedRePaint = TRUE ;
	}
	return E_FAIL ;
}

HRESULT CCUIWin::InvalidateRect(RECT rcInvalidate)
{
	if (this->m_pSplit)
	{
		return this->m_pSplit->AddRect(rcInvalidate) ;
	}

	if (FALSE == this->m_bNeedRePaint)
	{
		::InvalidateRect(this->m_hWnd, NULL, TRUE) ;
		this->m_bNeedRePaint = TRUE ;
	}
	return S_OK ;
}

HRESULT CCUIWin::InvalidateLayout(IUIFrame* pFrame)
{
	DEBUG_ASSERT(pFrame) ;
	IF_RETURN(NULL == pFrame, E_INVALIDARG) ;


	return E_FAIL ;
}

HRESULT CCUIWin::SetAttribute(ICVarData* pAttrData)
{
	HRESULT hRet = __super::SetAttribute(pAttrData) ;
	SET_ATTR_INTERFACE_BEGIN(pAttrData, IUIWin)
	SET_ATTR_BOOL           (LayerWin)
	SET_ATTR_SIZE           (WinSize)
	SET_ATTR_BOOL           (FixSize)
	SET_ATTR_SIZE           (MinWinSize)
	SET_ATTR_SIZE           (MaxWinSize)
	SET_ATTR_BOOL           (FixLocation)
	SET_ATTR_POINT          (WinLocation)
	SET_ATTR_RECT           (WindowBorder)
	SET_ATTR_RECT           (WindowOutBorder)
	SET_ATTR_BOOL           (TopMost)
	SET_ATTR_BOOL           (ToolWindow)
	SET_ATTR_BSTR           (Title)
	SET_ATTR_END            ()

	return hRet ;
}

HRESULT CCUIWin::SetControlFoucs(IUIControl* pControl)
{
	CComPtr<IUIControl> pControlOld = NULL ;
	if (this->m_pFoucsControl)
	{
		this->m_pFoucsControl.Promote(__uuidof(IUIControl), (VOID**)&pControlOld) ;
	}

	IF_RETURN(pControlOld == pControl, S_OK) ;
	if (this->m_pFoucsControl)
	{
		this->m_pFoucsControl->ControlFocusChange(FALSE) ;
	}

	this->m_pFoucsControl = pControl ;
	if (this->m_pFoucsControl)
	{
		this->m_pFoucsControl->ControlFocusChange(TRUE) ;
	}
	return S_OK ;
}

HRESULT CCUIWin::GetControlFoucs(IUIControl** ppControl)
{
	IF_RETURN(NULL == ppControl, E_FAIL) ;
	*ppControl = NULL ;
	if (this->m_pFoucsControl)
	{
		return this->m_pFoucsControl.Promote(__uuidof(IUIControl), (VOID**)ppControl) ;
	}
	return S_OK ;
}

BOOL CCUIWin::ProcessWindowMessage(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT& lResult, DWORD dwMsgMapID)
{
	BOOL bHandle = FALSE ;
	__self->HandleWinMessage(uMsg, wParam, lParam, &bHandle, &lResult) ;

	if (uMsg == WM_NCDESTROY || uMsg == WM_DESTROY)
	{
		return FALSE ;
	}
	return TRUE ;
}

LRESULT CCUIWin::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	return 0 ;
}

LRESULT CCUIWin::OnActivate(UINT unState, BOOL bMinimized, BOOL& bHandled)
{
	//bHandled = TRUE ;
	return 1 ;
}

LRESULT CCUIWin::OnNcCalcSize(BOOL bCalc, LPARAM lParam, BOOL& bHandled)
{
	bHandled = TRUE ;
	return 0 ;
}

LRESULT CCUIWin::OnGetMinMaxInfo(LPMINMAXINFO lpmmInfo, BOOL& bHandled)
{
	bHandled = TRUE ;
	IF_RETURN(NULL == lpmmInfo, 0) ;

	lpmmInfo->ptMinTrackSize.x = this->m_szWinMinSize.cx ;
	lpmmInfo->ptMinTrackSize.y = this->m_szWinMinSize.cy ;
	lpmmInfo->ptMaxTrackSize.x = this->m_szWinMaxSize.cx ;
	lpmmInfo->ptMaxTrackSize.y = this->m_szWinMaxSize.cy ;

	return 0 ;
}

LRESULT CCUIWin::OnNcHitTest(WPARAM wParam, LPARAM lParam, POINT pt, BOOL& bHandled)
{
	bHandled = TRUE ;
	CRect rcWnd(0, 0, m_szWin.cx, m_szWin.cy) ;
	::ScreenToClient(this->m_hWnd, &pt) ;

	BOOL bAutoWidth = FALSE, bAutoHeight = FALSE ;
	__self->GetAutoWidth(&bAutoWidth) ;
	__self->GetAutoHeight(&bAutoHeight) ;

	if (FALSE == this->m_bFixSize)
	{
		if (pt.x > m_rcWinOutBorder.left && pt.x < m_rcWinBorder.left)
		{
			if (!bAutoWidth && !bAutoHeight
					&& pt.y > m_rcWinOutBorder.top && pt.y < m_rcWinBorder.top)
			{
				return HTTOPLEFT ;
			}
			
			if (!bAutoWidth && !bAutoHeight
					&&pt.y > rcWnd.Height() - m_rcWinBorder.bottom 
						&& pt.y < rcWnd.Height() - m_rcWinOutBorder.bottom)
			{
				return HTBOTTOMLEFT ;
			}

			if (!bAutoWidth)
			{
				return HTLEFT ;
			}
		}
		else if (pt.x > (rcWnd.Width() - m_rcWinBorder.right) 
			&& pt.x < (rcWnd.Width() - m_rcWinOutBorder.right))
		{
			if (!bAutoWidth && !bAutoHeight
					&& pt.y > m_rcWinOutBorder.top && pt.y < m_rcWinBorder.top)
			{
				return HTTOPRIGHT ;
			}
			
			if (!bAutoWidth && !bAutoHeight
					&&pt.y > rcWnd.Height() - m_rcWinBorder.bottom 
						&& pt.y < rcWnd.Height() - m_rcWinOutBorder.bottom)
			{
				return HTBOTTOMRIGHT ;
			}

			if (!bAutoWidth)
			{
				return HTRIGHT ;
			}
		}
		else if (pt.y > m_rcWinOutBorder.top && pt.y < m_rcWinBorder.top)
		{
			if (!bAutoHeight)	return HTTOP ;
		}
		else if (pt.y > (rcWnd.Height() - m_rcWinBorder.bottom)
			&& pt.y < (rcWnd.Height() - m_rcWinOutBorder.bottom))
		{
			if (!bAutoHeight)	return HTBOTTOM ;
		}
	}

	CComPtr<IUIFrame> pTargetFrame ;
	__self->FrameFromPoint(pt, &pTargetFrame) ;
	if (pTargetFrame)
	{
		INT nHittest = HTNOWHERE ;
		pTargetFrame->GetHittest(&nHittest) ;
		IF_RETURN(HTNOWHERE != nHittest, nHittest) ;
	}

	return HTCLIENT ;
}

LRESULT CCUIWin::OnNcPaint(LONG hRGN, BOOL& bHandled)
{
	//bHandled = TRUE ;
	return 0 ;
}

LRESULT CCUIWin::OnNcLBtnDown(UINT uArg, POINT pt, BOOL& bHandled)
{
	return 0 ;
}

LRESULT CCUIWin::OnNCDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	return 0 ;
}

LRESULT CCUIWin::OnEraseBkgnd(HDC hDC, BOOL& bHandled)
{
	bHandled = TRUE ;
	return 1 ;
}

LRESULT CCUIWin::OnPaint(HDC hDC, BOOL& bHandled)
{
	this->RenderWnd() ;
	return 0 ;
}

LRESULT CCUIWin::OnSize(UINT uType, SIZE szWnd, BOOL& bHandled)
{
	CRect rcWnd(0, 0, 0, 0) ;
	::GetWindowRect(this->m_hWnd, &rcWnd) ;
	//IF_RETURN(this->m_szWin.cx == rcWnd.Width() && this->m_szWin.cy == rcWnd.Height(), 0) ;

	this->m_szWin.cx = rcWnd.Width() ;
	this->m_szWin.cy = rcWnd.Height() ;

	GetEntity<IUIFrameInternal>()->SetLayoutRect(CRect(0, 0, m_szWin.cx, m_szWin.cy)) ;
	GetEntity<IUIFrameInternal>()->MarkRelayout() ;

	if (this->m_pWinCanvas)
	{
		this->m_pWinCanvas->InitFromWnd(m_hWnd, m_szWin) ;
	}

	if (this->m_pSplit)
	{
		this->m_pSplit->AddRect(CRect(0, 0, m_szWin.cx, m_szWin.cy)) ;
	}

	if (this->m_pQuadTree)
	{
		CRect _rc(0, 0, m_szWin.cx, m_szWin.cy) ;
		this->m_pQuadTree->SynchFrame(_rc, GetEntity<IUIFrame>()) ;
	}

	if (this->m_bLayerWin)
	{
		::InvalidateRect(this->m_hWnd, NULL, TRUE) ;
	}

	return 0 ;
}

LRESULT CCUIWin::OnMoving(RECT* prcWnd, BOOL& bHandled)
{
	DEBUG_ASSERT(prcWnd) ;
	IF_RETURN(NULL == prcWnd, E_INVALIDARG) ;

	this->m_ptWinLocation.x = prcWnd->left ;
	this->m_ptWinLocation.y = prcWnd->top ;
	return 0 ;
}

LRESULT CCUIWin::OnKeyDown(UINT unChar, UINT unRepCnt, UINT unFlags, BOOL& bHandled)
{
	return 0 ;
}

LRESULT CCUIWin::OnMouseMove(UINT unFlags, POINT pt, BOOL& bHandled)
{
	return 0 ;
}

LRESULT CCUIWin::OnMouseLeave(BOOL& bHandled)
{
	return 0 ;
}

LRESULT CCUIWin::OnDestory(BOOL& bHandled)
{
	CWeakPtr<IUIMsgLoop> pMsgLoopService ;
	Common::Util::GetService(&pMsgLoopService) ;
	DEBUG_ASSERT(pMsgLoopService) ;

	if (this->m_bDoModal && pMsgLoopService)
	{
		pMsgLoopService->QuitCurrentLoop() ;
	}

	if (this->m_pWinMgr)
	{
		this->m_pWinMgr->DelWindow(GetEntity<IUIWin>()) ;

		/*INT nWindowCount = 0 ;
		this->m_pWinMgr->GetAllWindowsCount(&nWindowCount) ;
		if (0 == nWindowCount && pMsgLoopService)
		{
			pMsgLoopService->QuitCurrentLoop() ;
			::PostQuitMessage(0) ;
		}*/
	}
	
	return 0 ;
}

BOOL CCUIWin::CheckWndAutoSize()
{
	BOOL bAutoWidth = FALSE, bAutoHeight = FALSE ;
	__self->GetAutoWidth(&bAutoWidth) ;
	__self->GetAutoHeight(&bAutoHeight) ;
	IF_RETURN(!bAutoHeight && !bAutoWidth, FALSE) ;

	CSize szEstimateSize(-1, -1) ;
	if (bAutoWidth)
	{
		szEstimateSize.cx = 0 ;
	}

	if (bAutoHeight)
	{
		szEstimateSize.cy = 0 ;
	}
	GetEntity<IUIFrameInternal>()->SetEstimateSize(szEstimateSize) ;

	CSize _szWnd(0, 0) ;
	CSize _szMinAutoSize(0, 0) ;
	CSize _szMaxAutoSize(0, 0) ;
	__self->GetSize(&_szWnd) ;
	__self->GetMinAutoSize(&_szMinAutoSize) ;
	__self->GetMaxAutoSize(&_szMaxAutoSize) ;

	if (bAutoWidth)
	{
		if (_szWnd.cx > _szMaxAutoSize.cx)
		{
			_szWnd.cx = _szMaxAutoSize.cx ;
		}

		if (_szWnd.cx < _szMinAutoSize.cx)
		{
			_szWnd.cx = _szMinAutoSize.cx ;
		}
	}

	if (bAutoHeight)
	{
		if (_szWnd.cy > _szMaxAutoSize.cy)
		{
			_szWnd.cy = _szMaxAutoSize.cy ;
		}

		if (_szWnd.cy < _szMinAutoSize.cy)
		{
			_szWnd.cy = _szMinAutoSize.cy ;
		}
	}

	if (this->m_szWin != _szWnd)
	{
		this->m_szWin = _szWnd ;
		GetEntity<IUIFrameInternal>()->SetLayoutRect(CRect(0, 0, m_szWin.cx, m_szWin.cy)) ;
		GetEntity<IUIFrameInternal>()->MarkRelayout() ;

		::SetWindowPos(this->m_hWnd, NULL, 0, 0, _szWnd.cx, _szWnd.cy, SWP_NOZORDER|SWP_NOMOVE) ;
	}
	return S_OK ;
}

BOOL CCUIWin::RenderWnd()
{
	this->CheckWndAutoSize() ;

	PAINTSTRUCT ps ;
	::BeginPaint(this->m_hWnd, &ps) ;
	HDC hDCTarget = ::GetWindowDC(this->m_hWnd) ;
	do 
	{
		IF_BREAK(NULL == this->m_pWinCanvas) ;
		IF_BREAK(NULL == this->m_pSplit) ;
		IF_BREAK(NULL == this->m_pRender) ;

		__self->Update(FALSE, FALSE) ;

		// invalidate frame pool
		for (INT i = 0; i < (INT)this->m_vecFrameAgent.size(); ++i)
		{
			IF_CONTINUE(!(this->m_vecFrameAgent[i])) ;

			CRect rcVisibleRect(0, 0, 0, 0) ;
			this->m_vecFrameAgent[i]->GetAbsolutVisibleRect(&rcVisibleRect) ;
			this->m_pSplit->AddRect(rcVisibleRect) ;
		}

		CComQIPtr<IUIAddFrame> pRenderAddFrame = this->m_pRender ;
		DEBUG_ASSERT(pRenderAddFrame) ;
		IF_BREAK(NULL == pRenderAddFrame) ;

		INT nSplitCount = 0 ;
		this->m_pSplit->GetCount(&nSplitCount) ;
		for (INT i = 0; i < nSplitCount; ++i)
		{
			CRect rcSplit(0, 0, 0, 0) ;
			this->m_pSplit->GetByIndex(i, &rcSplit) ;
			this->m_pWinCanvas->SetCombineRect(rcSplit, RGN_OR) ;
			this->m_pQuadTree->FrameFromRect2(rcSplit, pRenderAddFrame) ;
		}

		this->m_pWinCanvas->ClearCanvas() ;
		this->m_pRender->Render(this->m_pWinCanvas) ;

		CComPtr<IUICanvas> pTargetCanvas ;
		CComPtr<IUIWindowPrePaint> pPrePaint = GetEntity<IUIWindowPrePaint>() ;
		if (pPrePaint)
		{
			pPrePaint->PreWindowPaint(this->m_pWinCanvas, &pTargetCanvas) ;
		}

		if (NULL == pTargetCanvas)
		{
			pTargetCanvas = this->m_pWinCanvas ;
		}

		if (this->m_p3DTransfrom)
		{
			BOOL bNeedTransfrom = FALSE ;
			this->m_p3DTransfrom->GetNeedTransfrom(&bNeedTransfrom) ;
			if (bNeedTransfrom)
			{
				CComPtr<IUICanvas> pTransfromTargetCanvas ;
				Common::Util::CreateObject(&pTransfromTargetCanvas) ;
				pTransfromTargetCanvas->InitFromCanvas(pTargetCanvas, this->m_szWin) ;
				this->m_p3DTransfrom->CanvasTransfrom(pTargetCanvas, pTransfromTargetCanvas) ;
				if (pTransfromTargetCanvas)
				{
					pTargetCanvas = pTransfromTargetCanvas ;
				}
			}
		}

		CRect rcWnd(0, 0, 0, 0) ;
		::GetWindowRect(this->m_hWnd, &rcWnd) ;
		HDC hCanvasDC = NULL ;
		pTargetCanvas->GetCanvasDC(&hCanvasDC) ;

		if (this->m_bLayerWin)
		{
			CPoint ptSrc    = CPoint(0, 0) ;
			CPoint ptRender = rcWnd.TopLeft() ;
			CSize  szRender = CSize(rcWnd.Width(), rcWnd.Height()) ;
			BLENDFUNCTION bpf = {AC_SRC_OVER, 0, this->m_cWinAlpha, AC_SRC_ALPHA} ;
			::UpdateLayeredWindow(this->m_hWnd, hDCTarget, 
				&ptRender, &szRender, hCanvasDC, &ptSrc, 0, &bpf, ULW_ALPHA) ;
		}
		else
		{
			::BitBlt(hDCTarget, 0, 0, rcWnd.Width(), rcWnd.Height(), hCanvasDC, 0, 0, SRCCOPY) ;
		}

		this->m_bNeedRePaint = FALSE ;
		this->m_pSplit->Clear() ;
		this->m_pRender->Clear() ;
		this->m_pWinCanvas->ClearClipRgn() ;
		this->m_vecFrameAgent.clear() ;

	} while(FALSE) ;
	::EndPaint(this->m_hWnd, &ps) ;
	::ReleaseDC(this->m_hWnd, hDCTarget) ;
	return TRUE ;
}