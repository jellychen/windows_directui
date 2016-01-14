#include "stdafx.h"
#include "CUIWindowMsgRoute.h"

CUIMsgRoute::CUIMsgRoute()
{
    this->m_hWnd        = NULL ;
    this->m_bTrackLeave = FALSE ;
}

BOOL CUIMsgRoute::InitMsgRoute(HWND hWnd, IUIWin* pTargeWin)
{
    DEBUG_ASSERT(hWnd && pTargeWin) ;
    IF_RETURN(!(hWnd && pTargeWin), FALSE) ;
    
    this->m_hWnd = hWnd ;
	this->m_pHostWinAgent = pTargeWin ;

    return TRUE ;
}

BOOL CUIMsgRoute::DispatchMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch(uMsg)
    {
    case WM_ACTIVATE:
        return this->DispatchInActive(wParam, lParam, uMsg) ;
    case WM_LBUTTONDOWN:
        return this->DispatchBtnMessage(wParam, lParam, TRUE, TRUE, FALSE, uMsg) ;
    case WM_LBUTTONUP:
        return this->DispatchBtnMessage(wParam, lParam, TRUE, FALSE, FALSE, uMsg) ;
    case WM_RBUTTONDOWN:
        return this->DispatchBtnMessage(wParam, lParam, FALSE, TRUE, FALSE, uMsg) ;
    case WM_RBUTTONUP:
        return this->DispatchBtnMessage(wParam, lParam, FALSE, FALSE, FALSE, uMsg) ;
    case WM_MOUSEMOVE:
        return this->DispatchMouseMove (wParam, lParam, FALSE, uMsg) ;
    case WM_MOUSEWHEEL:
        return this->DispatchMouseWheel (wParam, lParam, uMsg) ;
    case WM_KEYDOWN:
        return this->DispatchKeyMessage (wParam, lParam, uMsg) ;
    case WM_KEYUP:
        return this->DispatchKeyMessage (wParam, lParam, uMsg) ;
    case WM_CHAR:
        return this->DispatchKeyMessage (wParam, lParam, uMsg) ;
    case WM_MOUSELEAVE:
        return this->DispatchMouseLeave (wParam, lParam, FALSE, uMsg) ;
    case WM_NCLBUTTONDOWN:
        return this->DispatchBtnMessage (wParam, lParam, TRUE, TRUE, TRUE, uMsg) ;
    case WM_NCLBUTTONUP:
        return this->DispatchBtnMessage (wParam, lParam, TRUE, FALSE, TRUE, uMsg) ;
    case WM_NCRBUTTONDOWN:
        return this->DispatchBtnMessage (wParam, lParam, FALSE, TRUE, TRUE, uMsg) ;
    case WM_NCRBUTTONUP:
        return this->DispatchBtnMessage (wParam, lParam, FALSE, FALSE, TRUE, uMsg) ;
    case WM_NCMOUSEMOVE:
        return this->DispatchMousgeMove  (wParam, lParam, TRUE, uMsg) ;
    case WM_LBUTTONDBLCLK:
        return this->DispatchDBClick    (wParam, lParam, FALSE, uMsg) ;
    case WM_NCLBUTTONDBLCLK:
        return this->DispatchDBClick    (wParam, lParam, TRUE, uMsg) ;
    case WM_SETCURSOR:
        return this->DispatchCursor     (wParam, lParam, uMsg) ;
    case WM_SETFOCUS:
        return this->DispatchFoucs      (wParam, lParam, uMsg) ;

    #if(WINVER >= 0x0400)
    case WM_IME_SETCONTEXT :
    case WM_IME_NOTIFY :
    case WM_IME_CONTROL:
    case WM_IME_COMPOSITIONFULL:
    case WM_IME_SELECT:
    case WM_IME_CHAR:
	case WM_IME_STARTCOMPOSITION:
    #endif

    #if(WINVER >= 0x0500)
    case WM_IME_REQUEST:
    #endif

    #if(WINVER >= 0x0400)
    case WM_IME_KEYDOWN :
    case WM_IME_KEYUP:
    //case WM_SETCURSOR:
    #endif
        return this->DispatchImeMessage (wParam, lParam, uMsg) ;
    }

    return FALSE ; 
}

BOOL CUIMsgRoute::MessageTarget(IUIFrame* pTarget, tMsgArg* pArgs, UINT uMsg)
{
    IF_RETURN(NULL == pTarget, FALSE) ;
	HRESULT _hMessageRet = E_FAIL ;

    VEC_FRAME vecFrame ;
    this->AncestorFrames(pTarget, &vecFrame) ;

    do 
    {
        BOOL bIntercept = FALSE ;
        BOOL bHandle    = FALSE ;
        INT nFrameIndex = 0 ;

        for (INT i = (INT)vecFrame.size()-1; i >= 0; --i)
        {
            CComQIPtr<IUIMessageStream> pMessageStream = vecFrame[i] ;
            DEBUG_ASSERT(pMessageStream) ;
            IF_CONTINUE(NULL == pMessageStream) ;
            nFrameIndex = (INT)i ;
            pMessageStream->OnMessageSink(pTarget, pArgs, &bHandle, &bIntercept) ;
            IF_BREAK(bIntercept || bHandle) ;
        }

        IF_BREAK(bIntercept) ;

        CComQIPtr<IUIMessageStream> pMessageStream = vecFrame[nFrameIndex] ;
        if (pMessageStream)
        {
            _hMessageRet = pMessageStream->OnMessage(pTarget, pArgs) ;
        }

        for (size_t i = (size_t)nFrameIndex; i < vecFrame.size(); ++i)
        {
            CComQIPtr<IUIMessageStream> pMessageStream = vecFrame[i] ;
            IF_CONTINUE(NULL == pMessageStream) ;
            pMessageStream->OnMessageRiase(pTarget, pArgs, &bIntercept) ;
            IF_BREAK(bIntercept) ;
        }
    } while (FALSE) ;

    return SUCCEEDED(_hMessageRet) ;
}

BOOL CUIMsgRoute::AncestorFrames(IUIFrame* pTarget, VEC_FRAME* pvecFrame)
{
    IF_RETURN(!(pTarget && pvecFrame), FALSE) ;

    CComPtr<IUIFrame> pFrame = pTarget ;
    while (pFrame)
    {
        pvecFrame->push_back(pFrame) ;

        CComPtr<IUIElement> pElement ;
        pFrame->GetParent(&pElement) ;
        CComQIPtr<IUIFrame> pFrameTemp = pElement ;
        pFrame = pFrameTemp ;
    }
    return TRUE ;
}

BOOL CUIMsgRoute::DispatchBtnMessage(WPARAM wParam, 
    LPARAM lParam, BOOL bLeftBtn, BOOL bBtnDown, BOOL bNcMsg, UINT uMsg)
{

    IF_RETURN(!(m_pHostWinAgent) , FALSE) ;
    
    CPoint ptMouse = CPoint(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)) ;
    if (bNcMsg)
    {
        ::ScreenToClient(m_hWnd, &ptMouse) ;
    }

    CComPtr<IUIFrame> pHitFrame ;
    this->m_pHostWinAgent->GetCaptureFrame(&pHitFrame) ;

    if (NULL == pHitFrame)
    {
        /*this->m_pHostWinAgent->*/FrameFromPoint(ptMouse, &pHitFrame) ;
    }
    //DEBUG_ASSERT(pHitFrame) ;
    IF_RETURN(NULL == pHitFrame, FALSE) ;

    tMsgArgPoint        _arg ;
    _arg.wParam         = wParam ;
    _arg.lParam         = lParam ;
    _arg.pt             = ptMouse ;
    _arg.hWnd           = this->m_hWnd ;
    _arg.dwSysmteMsgId  = uMsg ;

    if (TRUE == bLeftBtn && TRUE == bBtnDown)
    {
        _arg.dwMsgId = MESSAGE::UI_LBTNDOWN ;
        this->MessageTarget(pHitFrame, &_arg, uMsg) ;
        this->m_pBtnDownFrameAgent = NULL ;
		this->m_pBtnDownFrameAgent = pHitFrame ;
    }
    else if (FALSE == bLeftBtn && TRUE == bBtnDown)
    {
        _arg.dwMsgId = MESSAGE::UI_RBTNDOWN ;
        this->MessageTarget(pHitFrame, &_arg, uMsg) ;
        this->m_pBtnDownFrameAgent  = NULL ;
        this->m_pBtnDownFrameAgent = pHitFrame ;
    }
    else if (TRUE == bLeftBtn && FALSE == bBtnDown)
    {
        CComPtr<IUIFrame> pLastBtnDownFrame ;
        if (this->m_pBtnDownFrameAgent)
        {
            this->m_pBtnDownFrameAgent.Promote(__uuidof(IUIFrame), (VOID**)&pLastBtnDownFrame) ;
        }

        _arg.dwMsgId = MESSAGE::UI_LBTNUP ;
        this->MessageTarget(pHitFrame, &_arg, uMsg) ;

        if (pHitFrame == pLastBtnDownFrame)
        {
            _arg.dwMsgId = MESSAGE::UI_LBTNCLICK ;
            this->MessageTarget(pHitFrame, &_arg, uMsg) ;
        }

        
    }
    else if (FALSE == bLeftBtn && FALSE == bBtnDown)
    {
        CComPtr<IUIFrame> pLastBtnDownFrame ;
        if (this->m_pBtnDownFrameAgent)
        {
            this->m_pBtnDownFrameAgent.Promote(__uuidof(IUIFrame), (VOID**)&pLastBtnDownFrame) ;
        }
        
        _arg.dwMsgId = MESSAGE::UI_RBTNUP ;
        this->MessageTarget(pHitFrame, &_arg, uMsg) ;

        if (pHitFrame == pLastBtnDownFrame)
        {
            _arg.dwMsgId = MESSAGE::UI_RBTNCLICK ;
            this->MessageTarget(pHitFrame, &_arg, uMsg) ;
        }
    }

    return FALSE ;
}

BOOL CUIMsgRoute::DispatchMouseMove(WPARAM wParam, LPARAM lParam, BOOL bNcMsg, UINT uMsg)
{
    IF_RETURN(!(m_pHostWinAgent), FALSE) ;
    CPoint ptMouse = CPoint(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)) ;
    
    if (!this->m_bTrackLeave)
    {
        TRACKMOUSEEVENT     tme ;
        tme.cbSize          = sizeof(tme) ;
        tme.hwndTrack       = this->m_hWnd ;
        tme.dwFlags         = TME_LEAVE ;
        this->m_bTrackLeave = TRUE ;
        ::TrackMouseEvent(&tme) ;
    }

    if (bNcMsg)
    {
        ::ScreenToClient(this->m_hWnd, &ptMouse) ;
    }

    CComPtr<IUIFrame> pHitFrame ;
    this->m_pHostWinAgent->GetCaptureFrame(&pHitFrame) ;

    if (NULL == pHitFrame)
    {
        /*this->m_pHostWinAgent->*/FrameFromPoint(ptMouse, &pHitFrame) ;
    }
    //DEBUG_ASSERT(pHitFrame) ;
    IF_RETURN(NULL == pHitFrame, FALSE) ;
    
    tMsgArgPoint        _arg ;
    _arg.wParam         = wParam ;
    _arg.lParam         = lParam ;
    _arg.hWnd           = this->m_hWnd ;
    _arg.dwMsgId        = MESSAGE::UI_MOUSEMOVE ;
    _arg.pt             = ptMouse ;
    _arg.dwSysmteMsgId  = uMsg ;
    this->MessageTarget(pHitFrame, &_arg, uMsg) ;

    CComPtr<IUIFrame> pLastMouseOnFrame ;
    if (this->m_pMouseOnFrameAgent)
    {
        this->m_pMouseOnFrameAgent.GetAgent()
                ->QueryOrigin(__uuidof(IUIFrame), (VOID**)&pLastMouseOnFrame) ;
    }

    if (pHitFrame != pLastMouseOnFrame)
    {
        this->m_pMouseOnFrameAgent = NULL ;
		this->m_pMouseOnFrameAgent = pHitFrame ;

        VEC_FRAME vecFramePoolCurrent ;
        this->AncestorFrames(pHitFrame, &vecFramePoolCurrent) ;
        VEC_FRAME vecFramePoolLast ;
        this->AncestorFrames(pLastMouseOnFrame, &vecFramePoolLast) ;

        INT nCurrentNewFrameIndex   = (INT)vecFramePoolCurrent.size() -1 ;
        INT nLastNewFrameIndex      = (INT)vecFramePoolLast.size() -1;

        for (; nCurrentNewFrameIndex >= 0 && nLastNewFrameIndex >= 0;)
        {
            if (vecFramePoolCurrent[nCurrentNewFrameIndex] 
                    == vecFramePoolLast[nLastNewFrameIndex])
            {
                nCurrentNewFrameIndex-- ;
                nLastNewFrameIndex-- ;
            }
            else
            {
                break ;
            }
        }

        tMsgArg             _arg ;
        _arg.wParam         = wParam ;
        _arg.lParam         = lParam ;
        _arg.hWnd           = this->m_hWnd ;

        _arg.dwMsgId      = MESSAGE::UI_MOUSEENTER ;
        for (INT i = 0; i <= nCurrentNewFrameIndex; ++i)
        {
            this->MessageTarget(vecFramePoolCurrent[i], &_arg, uMsg) ;
        }

        _arg.dwMsgId      = MESSAGE::UI_MOUSELEAVE ;
        for (INT i = 0; i <= nLastNewFrameIndex; ++i)
        {
            this->MessageTarget(vecFramePoolLast[i], &_arg, uMsg) ;
        }
    }
    return FALSE ;
}

BOOL CUIMsgRoute::DispatchMouseLeave(WPARAM wParam, LPARAM lParam, BOOL bNcMsg, UINT uMsg)
{
    IF_RETURN(!(m_pHostWinAgent), FALSE) ;
    this->m_bTrackLeave = FALSE ;

    CComPtr<IUIFrame> pFrameLastMouseOn ;
    if (this->m_pMouseOnFrameAgent)
    {
        this->m_pMouseOnFrameAgent.GetAgent()
            ->QueryOrigin(__uuidof(IUIFrame), (VOID**)&pFrameLastMouseOn) ;
    }
    IF_RETURN(NULL == pFrameLastMouseOn, FALSE) ;

    /*CPoint ptMouse(0, 0) ;
    ::GetCursorPos(&ptMouse) ;
    ::ScreenToClient(this->m_hWnd, &ptMouse) ;

    CRect rcAbsolutVisibleRect(0, 0, 0, 0) ;
    pFrameLastMouseOn->GetAbsolutVisibleRect(rcAbsolutVisibleRect) ;
    IF_RETURN(rcAbsolutVisibleRect.PtInRect(ptMouse), TRUE) ;*/

    tMsgArg         _tMsg ;
    _tMsg.dwMsgId   = MESSAGE::UI_MOUSELEAVE ;
    _tMsg.hWnd      = this->m_hWnd ;
    _tMsg.wParam    = wParam ;
    _tMsg.lParam    = lParam ;

    this->m_pMouseOnFrameAgent = NULL ;

    this->MessageTarget(pFrameLastMouseOn, &_tMsg, uMsg) ;
    return FALSE ;
}

BOOL CUIMsgRoute::DispatchMouseWheel(WPARAM wParam, LPARAM lParam, UINT uMsg)
{
    IF_RETURN(!(m_pHostWinAgent) , FALSE) ;
    
    CPoint ptMouse = CPoint(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)) ;
    ::ScreenToClient(this->m_hWnd, &ptMouse) ;

    CComPtr<IUIFrame> pHitFrame ;
    this->m_pHostWinAgent->GetCaptureFrame(&pHitFrame) ;
    if (NULL == pHitFrame)
    {
        /*this->m_pHostWinAgent->*/FrameFromPoint(ptMouse, &pHitFrame) ;
    }
    IF_RETURN(NULL == pHitFrame, FALSE) ;

    tMsgArgMouseWheel       _arg ;
    _arg.dwMsgId            = MESSAGE::UI_MOUSEWHEEL ;
    _arg.wParam             = wParam ;
    _arg.lParam             = lParam ;
    _arg.pt                 = ptMouse ;
    _arg.hWnd               = this->m_hWnd ;
    _arg.uKeyFlags          = LOWORD(wParam) ;
    _arg.nZDelta            = (SHORT)HIWORD(wParam) ;

    this->MessageTarget(pHitFrame, &_arg, uMsg) ;
    return FALSE ;
}

BOOL CUIMsgRoute::DispatchDBClick(WPARAM wParam, LPARAM lParam, BOOL bNcMsg, UINT uMsg)
{
    IF_RETURN(!(m_pHostWinAgent) , FALSE) ;

    CPoint ptMouse = CPoint(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)) ;
    if (bNcMsg)
    {
        ::ScreenToClient(this->m_hWnd, &ptMouse) ;
    }

    CComPtr<IUIFrame> pHitFrame ;
    /*this->m_pHostWinAgent->*/FrameFromPoint(ptMouse, &pHitFrame) ;
    DEBUG_ASSERT(pHitFrame) ;
    IF_RETURN(NULL == pHitFrame, FALSE) ;

    BOOL bEnableDBClick = FALSE ;
    pHitFrame->GetEnableDBClick(&bEnableDBClick) ;

    tMsgArgPoint        _arg ;
    _arg.wParam         = wParam ;
    _arg.lParam         = lParam ;
    _arg.pt             = ptMouse ;
    _arg.hWnd           = this->m_hWnd ;

    if (bEnableDBClick)
    {
        _arg.dwMsgId    = MESSAGE::UI_LBTNDBCLICK ;
    }
    else
    {
        _arg.dwMsgId    = MESSAGE::UI_LBTNDOWN ;
    }

    this->MessageTarget(pHitFrame, &_arg, uMsg) ;
    return FALSE ;
}

BOOL CUIMsgRoute::DispatchKeyMessage(WPARAM wParam, LPARAM lParam, UINT uMsg)
{
    IF_RETURN(!(m_pHostWinAgent) , FALSE) ;

    CComPtr<IUIControl> pFoucsControl ;
    this->m_pHostWinAgent->GetFoucsControl(&pFoucsControl) ;
    CComQIPtr<IUIFrame> pFouceFrame = pFoucsControl ;
    IF_RETURN(NULL == pFouceFrame, FALSE) ;

    tMsgArgKey          _arg ;
    _arg.hWnd           = this->m_hWnd ;
    _arg.wParam         = wParam ;
    _arg.lParam         = lParam ;
    _arg.unChar         = (TCHAR)wParam ;
    _arg.unFlags        = (UINT)lParam & 0xFFFF ;
    _arg.unRepCnt       = (UINT)(lParam & 0xFFFF0000) >> 16 ;
    _arg.dwSysmteMsgId  = uMsg ;

    if (WM_KEYDOWN == uMsg)
    {
        _arg.dwMsgId        = MESSAGE::UI_KEYDOWN ;
    }
    else if (WM_KEYUP == uMsg)
    {
        _arg.dwMsgId    = MESSAGE::UI_KEYUP ;
    }
    else if (WM_CHAR == uMsg)
    {
        _arg.dwMsgId    = MESSAGE::UI_CHAR ;
    }

    return this->MessageTarget(pFouceFrame, &_arg, uMsg) ;
}

BOOL CUIMsgRoute::DispatchInActive(WPARAM wParam, LPARAM lParam, UINT uMsg)
{
    CComPtr<IUIFrame> pFrameLastMouseOn ;
    if (this->m_pMouseOnFrameAgent)
    {
        this->m_pMouseOnFrameAgent.GetAgent()
            ->QueryOrigin(__uuidof(IUIFrame), (VOID**)&pFrameLastMouseOn) ;
    }
    IF_RETURN(NULL == pFrameLastMouseOn, FALSE) ;

    tMsgArgBool         _arg ;
    _arg.dwMsgId        = MESSAGE::UI_ACTIVE ;
    _arg.hWnd           = this->m_hWnd ;
    _arg.wParam         = wParam ;
    _arg.lParam         = lParam ;
    _arg.dwSysmteMsgId  = uMsg ;

    if (LOWORD(wParam) != WA_INACTIVE)
    {
        _arg.bValue = TRUE ;
    }
    else
    {
        _arg.bValue = FALSE ;
    }

    return this->MessageTarget(pFrameLastMouseOn, &_arg, uMsg) ;
}

BOOL CUIMsgRoute::DispatchFoucs(WPARAM wParam, LPARAM lParam, UINT uMsg)
{
    IF_RETURN(!(m_pHostWinAgent) , FALSE) ;

    CComPtr<IUIControl> pFoucsControl ;
    this->m_pHostWinAgent->GetFoucsControl(&pFoucsControl) ;
    CComQIPtr<IUIFrame> pFouceFrame = pFoucsControl ;
    IF_RETURN(NULL == pFouceFrame, FALSE) ;

    tMsgArg             _arg ;
    _arg.dwMsgId        = MESSAGE::UI_FOCUS ;
    _arg.hWnd           = this->m_hWnd ;
    _arg.wParam         = wParam ;
    _arg.lParam         = lParam ;
    _arg.dwSysmteMsgId  = uMsg ;

    return this->MessageTarget(pFouceFrame, &_arg, uMsg) ;
}

BOOL CUIMsgRoute::DispatchImeMessage(WPARAM wParam, LPARAM lParam, UINT uMsg)
{
    IF_RETURN(!(m_pHostWinAgent) , FALSE) ;

    CComPtr<IUIControl> pFoucsControl ;
    this->m_pHostWinAgent->GetFoucsControl(&pFoucsControl) ;
    CComQIPtr<IUIFrame> pFouceFrame = pFoucsControl ;
    IF_RETURN(NULL == pFouceFrame, FALSE) ;

    tMsgArg             _arg ;
    _arg.dwMsgId        = MESSAGE::UI_IME ;
    _arg.hWnd           = this->m_hWnd ;
    _arg.wParam         = wParam ;
    _arg.lParam         = lParam ;
    _arg.dwSysmteMsgId  = uMsg ;

	if (WM_IME_STARTCOMPOSITION == uMsg)
	{
		_arg.dwMsgId	= MESSAGE::UI_IME_STARTCOMPOSITION ;
	}
	else if (WM_IME_CHAR == uMsg)
	{
		_arg.dwMsgId	= MESSAGE::UI_IME_CHAR ;
	}

    this->MessageTarget(pFouceFrame, &_arg, uMsg) ;
	return FALSE ;
}

BOOL CUIMsgRoute::DispatchCursor(WPARAM wParam, LPARAM lParam, UINT uMsg)
{
    IF_RETURN(!(m_pMouseOnFrameAgent), FALSE) ;

    CComPtr<IUIFrame> pFrame ;
    this->m_pMouseOnFrameAgent.GetAgent()
        ->QueryOrigin(__uuidof(IUIFrame), (VOID**)&pFrame) ;
    IF_RETURN(NULL == pFrame, FALSE) ;

    tMsgArg             _arg ;
    _arg.dwMsgId        = MESSAGE::UI_CURSOR ;
    _arg.hWnd           = this->m_hWnd ;
    _arg.wParam         = wParam ;
    _arg.lParam         = lParam ;
    _arg.dwSysmteMsgId  = uMsg ;

    return this->MessageTarget(pFrame, &_arg, uMsg) ;
}

BOOL CUIMsgRoute::FrameFromPoint(POINT ptTarget, IUIFrame** ppFrame)
{
    DEBUG_ASSERT(ppFrame) ;
    IF_RETURN(NULL == ppFrame, FALSE) ;
    *ppFrame = NULL ;

    CComPtr<IUIFrame> pHitFrame ;
    this->m_pHostWinAgent->FrameFromPoint(ptTarget, &pHitFrame) ;
    IF_RETURN(NULL == pHitFrame, FALSE) ;

    CComPtr<IUIFrame> pFrameTemp = pHitFrame ;
    while (pFrameTemp)
    {
        BOOL bTransparentMouse = FALSE ;
        pFrameTemp->GetTransparentMouse(&bTransparentMouse) ;
        if (FALSE == bTransparentMouse)
        {
            pFrameTemp->QueryInterface(__uuidof(IUIFrame), (VOID**)ppFrame) ;
            break ;
        }


        CComPtr<IUIElement> pParent ;
        pFrameTemp->GetParent(&pParent) ;
        CComQIPtr<IUIFrame> pTemp = pParent ;
        pFrameTemp = pTemp ;
    }
    return TRUE ;
}