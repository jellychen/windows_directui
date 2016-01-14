#include "stdafx.h"
#include "CCUIFrame.h"

CUIFrame::CUIFrame()
{
    this->m_szFrameSize             = CSize(0, 0) ;
    this->m_ptFrameLocation         = CPoint(0, 0) ;
    this->m_rcFrameMargin           = CRect(0, 0, 0, 0) ;
    this->m_rcFramePadding          = CRect(0, 0, 0, 0) ;
	this->m_rcFrameExtPadding		= CRect(0, 0, 0, 0) ;
    this->m_nFrameZOrder            = 0 ;
    this->m_cFrameAlpha             = 255 ;
    this->m_cFrameShowAlpha         = 255 ;
    this->m_bCacheFrameShowAlpha    = FALSE ;
    this->m_bFrameHidden            = FALSE ;
    this->m_bFrameFloat             = FALSE ;
    this->m_bFrameEnable            = TRUE ;
    this->m_bEnableFrameState       = FALSE ;
    this->m_nFrameState             = STATE::NORMAL ;
    this->m_nFrameHittest           = HTCLIENT ;
	this->m_nFrameHoverCursor		= UI::CURSOR::EM_CURSOR_ARROW ;
    this->m_bFrameDepth             = 0 ;
    this->m_bCacheFrameDepth        = FALSE ;
    this->m_ptAbsolutLocation       = CPoint(0, 0) ;
    this->m_bCacheAbsolutLocation   = FALSE ;
    this->m_rcVisibleRect           = CRect(0, 0, 0, 0) ;
    this->m_bCacheVisibleRect       = FALSE ;
    this->m_bDoubleBuffer           = FALSE ;
    this->m_cBkgDrawAlpha           = 255 ;
    this->m_cBkgMaskDrawAlpha       = 255 ;
    this->m_nAnchor                 = ANCHOR::NONE ;
	this->m_nDrift					= DRIFT::DRIFT_NEAR ;
    this->m_bAutoWidth              = FALSE ;
    this->m_bAutoHeight             = FALSE ;
    this->m_szAutoMinSize           = CSize(0, 0) ;
    this->m_szAutoMaxSize           = CSize(INT_MAX, INT_MAX) ;
    this->m_bWidthAsParent          = FALSE ;
    this->m_bHeightAsParent         = FALSE ;
    this->m_bEnableVerticalDrag     = FALSE ;
    this->m_bEnableHorizontalDrag   = FALSE ;
    this->m_rcDragRange             = CRect(INT_MIN, INT_MIN, INT_MAX, INT_MAX) ;
    this->m_bDragging               = FALSE ;
    this->m_bLBtnDown               = FALSE ;
    this->m_ptLBtnDownLocation      = CPoint(0, 0) ;
    this->m_bEnableDBClick          = FALSE ;
    this->m_bInterceptMouse         = FALSE ;
    this->m_bTransparentMouse       = FALSE ;
    this->m_bUpdating               = FALSE ;
    this->m_bReCalcsize             = TRUE ;
    this->m_bRelayout               = TRUE ;
	this->m_bReRender				= TRUE ;
    this->m_bEstimateSizeChange     = FALSE ;
}

CUIFrame::~CUIFrame()
{
    this->m_mapDestoryListenerPool.clear() ;
    this->m_mapEventListenerPool.clear() ;
}

HRESULT CUIFrame::FinalConstruct()
{
    Common::Util::CreateObject(&m_pDoubleBufferCanvas) ;
    DEBUG_ASSERT(m_pDoubleBufferCanvas) ;

    return S_OK ;
}

VOID CUIFrame::FinalRelease()
{
    MAP_DESTORY_LISTEN_POOL::iterator it 
        = this->m_mapDestoryListenerPool.begin() ;
    for (; it != this->m_mapDestoryListenerPool.end(); ++it)
    {
        IF_CONTINUE(NULL ==  it->second) ;
        it->second->OnDestory(GetEntity<IUIFrame>()) ;
    }
}

HRESULT CUIFrame::SetSize(SIZE szSize)
{
    IF_RETURN(this->m_szFrameSize == szSize, S_OK) ;

    BOOL bSizeChange = FALSE ;

    if (!this->m_bAutoWidth 
        && !this->m_bWidthAsParent
        && this->m_szFrameSize.cx != szSize.cx)
    {
        this->m_szFrameSize.cx = szSize.cx ;
        bSizeChange = TRUE ;
    }

    if (!this->m_bAutoHeight 
        && !this->m_bHeightAsParent
        && this->m_szFrameSize.cy != szSize.cy)
    {
        this->m_szFrameSize.cy = szSize.cy ;
        bSizeChange = TRUE ;
    }

    if (bSizeChange)
    {
        this->m_bRelayout = TRUE ;
        this->m_bNeedSynch = TRUE ;
        this->m_bCacheVisibleRect = FALSE ;

        GetEntity<IUIFrameInternal>()->MarkParentReCalcsize() ;
        __self->Invalidate() ;
    }

    return S_OK ;
}

HRESULT CUIFrame::GetSize(SIZE* pszSize)
{
    DEBUG_ASSERT(pszSize) ;
    IF_RETURN(NULL == pszSize, E_INVALIDARG) ;

    if ((this->m_bAutoHeight || this->m_bAutoWidth) && this->m_bReCalcsize)
    {
        CComPtr<IUICalcSize> pCalcSize = GetEntity<IUICalcSize>() ;
        DEBUG_ASSERT(pCalcSize) ;
        IF_RETURN(NULL == pCalcSize, E_FAIL) ;

        CSize szCalcOut(0, 0) ;
        pCalcSize->CalcSize(m_szFrameSize, &szCalcOut) ;
        this->m_szFrameSize = szCalcOut ;
        this->m_bReCalcsize = FALSE ;

        if (this->m_bAutoWidth && szCalcOut.cx > this->m_szAutoMaxSize.cx)
        {
            this->m_szFrameSize.cx = this->m_szAutoMaxSize.cx ;
        }

        if (this->m_bAutoHeight && szCalcOut.cy > this->m_szAutoMaxSize.cy)
        {
            this->m_szFrameSize.cy = this->m_szAutoMaxSize.cy ;
        }

        if (this->m_bAutoWidth && szCalcOut.cx < this->m_szAutoMinSize.cx)
        {
            this->m_szFrameSize.cx = this->m_szAutoMinSize.cx ;
        }

        if (this->m_bAutoHeight && szCalcOut.cy < this->m_szAutoMinSize.cy)
        {
            this->m_szFrameSize.cy = this->m_szAutoMinSize.cy ;
        }

    }
    *pszSize = this->m_szFrameSize ;
    return S_OK ;
}

HRESULT CUIFrame::SetLocation(POINT ptLocation)
{
    if (ANCHOR::NONE == this->m_nAnchor&& this->m_bFrameFloat)
    {
        this->m_bNeedSynch = TRUE ;
        this->m_bCacheVisibleRect = FALSE ;
        this->m_bCacheAbsolutLocation = FALSE ;
        this->m_ptFrameLocation = ptLocation ;

        __self->Invalidate() ;
    }
    return S_OK ;
}

HRESULT CUIFrame::GetLocation(POINT* pptLocation)
{
    DEBUG_ASSERT(pptLocation) ;
    IF_RETURN(NULL == pptLocation, E_INVALIDARG) ;
    
    *pptLocation = this->m_ptFrameLocation ;
    return S_OK ;
}

HRESULT CUIFrame::SetRect(RECT rcRect)
{
    CRect rc(rcRect) ;
    __self->SetSize(CSize(rc.Width(), rc.Height())) ;
    __self->SetLocation(rc.TopLeft()) ;
    return S_OK ;
}

HRESULT CUIFrame::GetRect(RECT* prcRect)
{
    DEBUG_ASSERT(prcRect) ;
    IF_RETURN(NULL == prcRect, E_INVALIDARG) ;

    CSize szSize(0, 0) ;
    CPoint ptLocation(0, 0) ;
    __self->GetSize(&szSize) ;
    __self->GetLocation(&ptLocation) ;

    prcRect->left   = ptLocation.x ;
    prcRect->top    = ptLocation.y ;
    prcRect->right  = prcRect->left + szSize.cx ;
    prcRect->bottom = prcRect->top + szSize.cy ;
    return S_OK ;
}

HRESULT CUIFrame::SetMargin(RECT rcMargin)
{
    IF_RETURN(this->m_rcFrameMargin == rcMargin, S_OK) ;
    this->m_rcFrameMargin = rcMargin ;

    /*CComPtr<IUIElement> pElement ;
    __self->GetParent(&pElement) ;
    CComQIPtr<IUIFrameInternal> pInternal = pElement ;
    if (pElement && pInternal)
    {
        pInternal->MarkReCalcsize() ;
    }*/
    GetEntity<IUIFrameInternal>()->MarkParentReCalcsize() ;
    __self->Invalidate() ;
    return S_OK ;
}

HRESULT CUIFrame::GetMargin(RECT* prcMargin)
{
    DEBUG_ASSERT(prcMargin) ;
    IF_RETURN(NULL == prcMargin, E_INVALIDARG) ;
    *prcMargin = this->m_rcFrameMargin ;
    return S_OK ;
}

HRESULT CUIFrame::SetPadding(RECT rcPadding)
{
    IF_RETURN(this->m_rcFramePadding == rcPadding, S_OK) ;

    this->m_rcFramePadding = rcPadding ;
    GetEntity<IUIFrameInternal>()->MarkReCalcsize() ;
    __self->Invalidate() ;
    return S_OK ;
}

HRESULT CUIFrame::GetPadding(RECT* prcPadding)
{
    DEBUG_ASSERT(prcPadding) ;
    IF_RETURN(NULL == prcPadding, E_INVALIDARG) ;
    *prcPadding = this->m_rcFramePadding ;
    return S_OK ;
}

HRESULT CUIFrame::SetZOrder(INT nZOrder)
{
    if (0 > nZOrder)
    {
        nZOrder = INT_MAX ;
    }

    IF_RETURN(this->m_nFrameZOrder == nZOrder, S_OK) ;

    this->m_nFrameZOrder = nZOrder ;
    __self->Invalidate() ;
    return S_OK ;
}

HRESULT CUIFrame::GetZOrder(INT* pnZOrder)
{
    DEBUG_ASSERT(pnZOrder) ;
    IF_RETURN(NULL == pnZOrder, E_INVALIDARG) ;
    *pnZOrder = this->m_nFrameZOrder ;
    return S_OK ;
}

HRESULT CUIFrame::SetHidden(BOOL bHidden)
{
    IF_RETURN(this->m_bFrameHidden == bHidden, S_OK) ;

    this->m_bFrameHidden = bHidden ;
    this->m_bNeedSynch = TRUE ;
    GetEntity<IUIFrameInternal>()->MarkParentReCalcsize() ;
    __self->Invalidate() ;
    return S_OK ;
}

HRESULT CUIFrame::GetHidden(BOOL* pbHidden)
{
    DEBUG_ASSERT(pbHidden) ;
    IF_RETURN(NULL == pbHidden, E_INVALIDARG) ;
    *pbHidden = this->m_bFrameHidden ;
    return S_OK ;
}

HRESULT CUIFrame::GetVisible(BOOL* pbVisible)
{
    DEBUG_ASSERT(pbVisible) ;
    IF_RETURN(NULL == pbVisible, E_INVALIDARG) ;

    CRect rcVisibleRect(0, 0, 0, 0) ;
    __self->GetAbsolutVisibleRect(&rcVisibleRect) ;
    *pbVisible = !rcVisibleRect.IsRectEmpty() ;
    return S_OK ;
}

HRESULT CUIFrame::SetFloat(BOOL bFloat)
{
    IF_RETURN(this->m_bFrameFloat == bFloat, S_OK) ;

    this->m_bFrameFloat = bFloat ;
    GetEntity<IUIFrameInternal>()->MarkParentReCalcsize() ;
    __self->Invalidate() ;
    return S_OK ;
}

HRESULT CUIFrame::GetFloat(BOOL* pbFloat)
{
    DEBUG_ASSERT(pbFloat) ;
    IF_RETURN(NULL == pbFloat, E_INVALIDARG) ;

    *pbFloat = this->m_bFrameFloat ;
    return S_OK ;
}

HRESULT CUIFrame::SetEnable(BOOL bEnable)
{
    this->m_bFrameEnable = bEnable ;
    return S_OK ;
}

HRESULT CUIFrame::GetEnable(BOOL* pbEnable)
{
    DEBUG_ASSERT(pbEnable) ;
    IF_RETURN(NULL == pbEnable, E_INVALIDARG) ;

    *pbEnable = this->m_bFrameEnable ;
    return S_OK ;
}

HRESULT CUIFrame::SetCapture(BOOL bCapture)
{
    CComQIPtr<IUIFrameInternal> pInternal = GetEntity<IUIFrameInternal>() ;
    DEBUG_ASSERT(pInternal) ;
    IF_RETURN(NULL == pInternal, E_FAIL) ;
    
    return pInternal->SetCaptureInternal(bCapture, GetEntity<IUIFrame>()) ;
}

HRESULT CUIFrame::GetCapture(BOOL* pbCapture)
{
    DEBUG_ASSERT(pbCapture) ;
    IF_RETURN(NULL == pbCapture, E_INVALIDARG) ;

    CComQIPtr<IUIFrameInternal> pInternal = GetEntity<IUIFrameInternal>() ;
    DEBUG_ASSERT(pInternal) ;
    IF_RETURN(NULL == pInternal, E_FAIL) ;

    CComPtr<IUIFrame> pFrame ;
    pInternal->GetCaptureInternal(&pFrame) ;
    *pbCapture = GetEntity<IUIFrame>() == pFrame ;

    return S_OK ;
}

HRESULT CUIFrame::SetState(INT nState)
{
    this->m_nFrameState = nState ;
    return S_OK ;
}

HRESULT CUIFrame::GetState(INT* pnState)
{
    DEBUG_ASSERT(pnState) ;
    IF_RETURN(NULL == pnState, E_INVALIDARG) ;

    *pnState = this->m_nFrameState ;
    return S_OK ;
}

HRESULT CUIFrame::SetEnableState(BOOL bEnableState)
{
    this->m_bEnableFrameState = bEnableState ;
    return S_OK ;
}

HRESULT CUIFrame::GetEnableState(BOOL* pbEnableState)
{
    DEBUG_ASSERT(pbEnableState) ;
    IF_RETURN(NULL == pbEnableState, E_INVALIDARG) ;

    *pbEnableState = this->m_bEnableFrameState ;
    return S_OK ;
}

HRESULT CUIFrame::SetHittest(INT nHittest)
{
    this->m_nFrameHittest = nHittest ;
    return S_OK ;
}

HRESULT CUIFrame::GetHittest(INT* pnHittest)
{
    DEBUG_ASSERT(pnHittest) ;
    IF_RETURN(NULL == pnHittest, E_INVALIDARG) ;

    *pnHittest = this->m_nFrameHittest ;
    return S_OK ;
}

HRESULT CUIFrame::SetHoverCursor(INT nHoverCursor)
{
	this->m_nFrameHoverCursor = nHoverCursor ;
	return S_OK ;
}

HRESULT CUIFrame::GetHoverCursor(INT* pnHoverCursor)
{
	DEBUG_ASSERT(pnHoverCursor) ;
    IF_RETURN(NULL == pnHoverCursor, E_INVALIDARG) ;

	*pnHoverCursor = this->m_nFrameHoverCursor ;
	return S_OK ;
}

HRESULT CUIFrame::GetAbsolutDepth(INT* pnDepth)
{
    DEBUG_ASSERT(pnDepth) ;
    IF_RETURN(NULL == pnDepth, E_INVALIDARG) ;
    if (this->m_bCacheFrameDepth)
    {
        *pnDepth = this->m_bFrameDepth ;
        return S_OK ;
    }
    else
    {
        CComPtr<IUIElement> pElement ;
        __self->GetParent(&pElement) ;
        CComQIPtr<IUIFrame> pParentFrame = pElement ;
        IF_RETURN(NULL == pParentFrame, E_FAIL) ;

        INT nParentDepth = 0 ;
        HRESULT hRet = pParentFrame->GetAbsolutDepth(&nParentDepth) ;
        IF_RETURN(FAILED(hRet), E_FAIL) ;

        this->m_bFrameDepth = nParentDepth + 1 ;
        this->m_bCacheFrameDepth = TRUE ;
        *pnDepth = this->m_bFrameDepth ;
        return S_OK ;
    }
    return E_FAIL ;
}

HRESULT CUIFrame::GetAbsolutLocation(POINT* pptLocation)
{
    DEBUG_ASSERT(pptLocation) ;
    IF_RETURN(NULL == pptLocation, E_INVALIDARG) ;
    if (this->m_bCacheAbsolutLocation)
    {
        *pptLocation = this->m_ptAbsolutLocation ;
        return S_OK ;
    }
    else
    {
        CComPtr<IUIElement> pElement ;
        __self->GetParent(&pElement) ;
        CComQIPtr<IUIFrame> pParentFrame = pElement ;
        IF_RETURN(NULL == pParentFrame, E_FAIL) ;

        CPoint ptParentLocation(0, 0) ;
        HRESULT hRet = pParentFrame->GetAbsolutLocation(&ptParentLocation) ;
        IF_RETURN(FAILED(hRet), E_FAIL) ;

        CPoint ptLocation(0, 0) ;
        hRet = __self->GetLocation(&ptLocation) ;
        IF_RETURN(FAILED(hRet), E_FAIL) ;

        this->m_ptAbsolutLocation.x = ptLocation.x + ptParentLocation.x ;
        this->m_ptAbsolutLocation.y = ptLocation.y + ptParentLocation.y ;
        this->m_bCacheAbsolutLocation = TRUE ;

        *pptLocation = this->m_ptAbsolutLocation ;
        return S_OK ;
    }
    return E_FAIL ;
}

HRESULT CUIFrame::GetScreenLocation(POINT* pptLocation)
{
    DEBUG_ASSERT(pptLocation) ;
    IF_RETURN(NULL == pptLocation, E_INVALIDARG) ;

    CComPtr<IUIElement> pElement ;
    __self->GetParent(&pElement) ;
    CComQIPtr<IUIFrame> pParentFrame = pElement ;
    IF_RETURN(NULL == pParentFrame, E_FAIL) ;

    CPoint ptParentScreen(0, 0) ;
    HRESULT hRet = pParentFrame->GetScreenLocation(&ptParentScreen) ;
    IF_RETURN(FAILED(hRet), E_FAIL) ;

    CPoint ptLocation(0, 0) ;
    hRet = __self->GetLocation(&ptLocation) ;
    IF_RETURN(FAILED(hRet), E_FAIL) ;

    pptLocation->x  = ptLocation.x + ptParentScreen.x ;
    pptLocation->y  = ptLocation.y + ptParentScreen.y ;

    return S_OK ; ;
}

HRESULT CUIFrame::GetAbsolutRect(RECT* prcRect)
{
    DEBUG_ASSERT(prcRect) ;
    IF_RETURN(NULL == prcRect, E_INVALIDARG) ;

    CPoint ptLocation(0, 0) ;
    if (SUCCEEDED(__self->GetAbsolutLocation(&ptLocation)))
    {
        prcRect->left   = ptLocation.x ;
        prcRect->top    = ptLocation.y ;
        prcRect->right  = ptLocation.x + this->m_szFrameSize.cx ;
        prcRect->bottom = ptLocation.y + this->m_szFrameSize.cy ;
        return S_OK ;
    }
    return E_FAIL ;
}

HRESULT CUIFrame::GetScreenRect(RECT* prcRect)
{
    DEBUG_ASSERT(prcRect) ;
    IF_RETURN(NULL == prcRect, E_INVALIDARG) ;
    
    CPoint ptScreenLocation(0, 0) ;
    __self->GetScreenLocation(&ptScreenLocation) ;
    prcRect->left   = ptScreenLocation.x ;
    prcRect->top    = ptScreenLocation.y ;
    prcRect->right  = prcRect->left + this->m_szFrameSize.cx ;
    prcRect->bottom = prcRect->top + this->m_szFrameSize.cy ;

    return S_OK ;
}

HRESULT CUIFrame::GetAbsolutVisibleRect(RECT* prcRect)
{
    DEBUG_ASSERT(prcRect) ;
    IF_RETURN(NULL == prcRect, E_INVALIDARG) ;

    HRESULT hRet = E_FAIL ;
    if (this->m_bCacheVisibleRect)
    {
        *prcRect = this->m_rcVisibleRect ;
        hRet = S_OK ;
    }
    else
    {
        if (this->m_bFrameHidden)
        {
            this->m_rcVisibleRect = CRect(0, 0, 0, 0) ;
        }
        else
        {
            CComPtr<IUIElement> pElement ;
            __self->GetParent(&pElement) ;
            CComQIPtr<IUIFrame> pFrameParent = pElement ;
            IF_RETURN(NULL == pFrameParent, E_FAIL) ;

			CRect rcVisibleRect ;
			HRESULT hRet = pFrameParent->GetAbsolutVisibleRect(&rcVisibleRect) ;
			IF_RETURN(FAILED(hRet), E_FAIL) ;
	            
			CRect rcAbsoluteRect(0, 0, 0, 0) ;
			hRet = __self->GetAbsolutRect(rcAbsoluteRect) ;
			IF_RETURN(FAILED(hRet), E_FAIL) ;

			::IntersectRect(&rcAbsoluteRect, &rcAbsoluteRect, &rcVisibleRect) ;
			this->m_rcVisibleRect = rcAbsoluteRect ;
        }

        this->m_bCacheVisibleRect = TRUE ;
        *prcRect = this->m_rcVisibleRect ;
        hRet = S_OK ;
    }

    return hRet ;
}

HRESULT CUIFrame::SetLayouter(IUILayout* pLayouter)
{
	this->m_pLayouter = pLayouter ;
	GetEntity<IUIFrameInternal>()->MarkReCalcsize() ;
	__self->Invalidate() ;
	return S_OK ;
}

HRESULT CUIFrame::GetLayouter(IUILayout** ppLayouter)
{
	DEBUG_ASSERT(ppLayouter) ;
	IF_RETURN(NULL == ppLayouter, E_INVALIDARG) ;
	*ppLayouter = NULL ;
	if (this->m_pLayouter)
	{
		return this->m_pLayouter->QueryInterface(__uuidof(IUILayout), (VOID**)ppLayouter) ;
	}
	return S_OK ;
}

HRESULT CUIFrame::Draw(IUICanvas* pCanvas)
{
    DEBUG_ASSERT(pCanvas) ;
    IF_RETURN(NULL == pCanvas, E_FAIL) ;
    
    HRESULT hRet = E_FAIL ;

    CRect rcAbsoluteVisibleRect(0, 0, 0, 0) ;
    hRet = __self->GetAbsolutVisibleRect(&rcAbsoluteVisibleRect) ;
    DEBUG_ASSERT_MSG(SUCCEEDED(hRet), _T("GetAbsolutVisibleRect Failed...")) ;
    IF_RETURN(FAILED(hRet), E_FAIL) ;

    CRect rcAbsoluteRect(0, 0, 0, 0) ;
    hRet = __self->GetAbsolutRect(&rcAbsoluteRect) ;
    DEBUG_ASSERT_MSG(SUCCEEDED(hRet), _T("GetAbsolutRect Failed...")) ;
    IF_RETURN(FAILED(hRet), E_FAIL) ;

    CRect rcRgn(0, 0, 0, 0) ;
    HRGN hRgn = ::CreateRectRgnIndirect(&rcRgn) ;
    pCanvas->GetClipRgn(&hRgn) ;
    pCanvas->SetCombineRect(rcAbsoluteVisibleRect, RGN_AND) ;
    CRect rcRender(0, 0, m_szFrameSize.cx, m_szFrameSize.cy) ;
    CPoint ptOldViewPort(0, 0) ;
    pCanvas->SetViewport(rcAbsoluteRect.TopLeft(), &ptOldViewPort) ;

    __self->RaiseEvent(EVENT::DRAWBEGIN, NULL) ;
    if (this->m_pDoubleBufferCanvas && this->m_bDoubleBuffer)
    {
        CSize szCanvas(0, 0) ;
        this->m_pDoubleBufferCanvas->GetSize(&szCanvas) ;
        if (this->m_szFrameSize != szCanvas)
        {
            this->m_pDoubleBufferCanvas->DestoryCanvas() ;
            this->m_pDoubleBufferCanvas->InitFromCanvas(pCanvas, m_szFrameSize) ;
            __self->Render(m_pDoubleBufferCanvas, rcRender, this->m_nFrameState) ;
        }
		else if (this->m_bReRender)
		{
			this->m_pDoubleBufferCanvas->ClearCanvas() ;
			__self->Render(m_pDoubleBufferCanvas, rcRender, this->m_nFrameState) ;
		}
        this->m_pDoubleBufferCanvas->DrawOnCanvas(pCanvas, rcRender, 255) ;
    }
    else 
    {
        if (this->m_pDoubleBufferCanvas)
        {
            this->m_pDoubleBufferCanvas->DestoryCanvas() ;
        }
        __self->Render(pCanvas, rcRender, this->m_nFrameState) ;
    }
	this->m_bReRender = FALSE ;

    __self->RaiseEvent(EVENT::DRAWEND, NULL) ;
    pCanvas->SetViewport(ptOldViewPort, NULL) ;
    pCanvas->SetClipRgn(hRgn) ;
    ::DeleteObject(hRgn) ;
    return S_OK ;
}

HRESULT CUIFrame::Render(IUICanvas* pCanvas, RECT rcRender, INT nState)
{
    DEBUG_ASSERT(pCanvas) ;
    IF_RETURN(NULL == pCanvas, E_INVALIDARG) ;

    if (this->m_pBkgDraw)
    {
        this->m_pBkgDraw->DrawOnCanvas(pCanvas, rcRender, this->m_cBkgDrawAlpha) ;
    }

    if (this->m_pBkgMaskDraw)
    {
        this->m_pBkgMaskDraw->DrawOnCanvas(pCanvas, rcRender, this->m_cBkgMaskDrawAlpha) ;
    }
    return S_OK ;
}

HRESULT CUIFrame::SetDoubleBuffer(BOOL bDoubleBuffer)
{
    this->m_bDoubleBuffer = bDoubleBuffer ;
    return S_OK ;
}

HRESULT CUIFrame::GetDoubleBuffer(BOOL* pbDoubleBuffer)
{
    DEBUG_ASSERT(pbDoubleBuffer) ;
    IF_RETURN(NULL == pbDoubleBuffer, E_INVALIDARG) ;

    *pbDoubleBuffer = this->m_bDoubleBuffer ;
    return S_OK ;
}

HRESULT CUIFrame::SetAlpha(BYTE cAlpha)
{
    IF_RETURN(this->m_cFrameAlpha == cAlpha, S_OK) ;

    this->m_cFrameAlpha = cAlpha ;
    this->m_bCacheFrameShowAlpha = FALSE ;
    GetEntity<IUIFrameInternal>()->NotifyAlphaChange() ;
    __self->Invalidate() ;
    return S_OK ;
}

HRESULT CUIFrame::GetAlpha(BYTE* pcAlpha)
{
    DEBUG_ASSERT(pcAlpha) ;
    IF_RETURN(NULL == pcAlpha, E_INVALIDARG) ;

    *pcAlpha = this->m_cFrameAlpha ;
    return S_OK ;
}

HRESULT CUIFrame::GetShowAlpha(BYTE* pcAlpha)
{
    DEBUG_ASSERT(pcAlpha) ;
    IF_RETURN(NULL == pcAlpha, E_INVALIDARG) ;

    if (FALSE == this->m_bCacheFrameShowAlpha)
    {
        BYTE cParentShowAlpha = 255 ;

        HRESULT hRet = E_FAIL ;
        CComPtr<IUIElement> pElement ;
        __self->GetParent(&pElement) ;
        CComQIPtr<IUIFrame> pParemtFrame = pElement ;
        if (pParemtFrame)
        {
            hRet = pParemtFrame->GetShowAlpha(&cParentShowAlpha) ;
        }

        if (SUCCEEDED(hRet))
        {
            this->m_cFrameShowAlpha = this->m_cFrameAlpha * cParentShowAlpha/255 ;
            this->m_bCacheFrameShowAlpha = TRUE ;
        }
    }
    *pcAlpha = this->m_cFrameShowAlpha ;
    return S_OK ;
}

HRESULT CUIFrame::SetBkgDraw(IUIDraw* pBkgDraw)
{
    IF_RETURN(this->m_pBkgDraw == pBkgDraw, S_OK) ;
    this->m_pBkgDraw = pBkgDraw ;
    __self->Invalidate() ;
    return S_OK ;
}

HRESULT CUIFrame::GetBkgDraw(IUIDraw** ppBkgDraw)
{
    DEBUG_ASSERT(ppBkgDraw) ;
    IF_RETURN(NULL == ppBkgDraw, E_INVALIDARG) ;
    *ppBkgDraw = NULL ;
    
    if (this->m_pBkgDraw)
    {
        return this->m_pBkgDraw->QueryInterface(__uuidof(IUIDraw), (VOID**)ppBkgDraw) ;
    }
    return E_FAIL ;
}

HRESULT CUIFrame::SetBkgDrawAlpha(BYTE cBkgAlpha)
{
    this->m_cBkgDrawAlpha = cBkgAlpha ;
    return S_OK ;
}

HRESULT CUIFrame::GetBkgDrawAlpha(BYTE* pcBkgAlpha)
{
    DEBUG_ASSERT(pcBkgAlpha) ;
    IF_RETURN(NULL == pcBkgAlpha, E_INVALIDARG) ;
    *pcBkgAlpha = this->m_cBkgDrawAlpha ;
    return S_OK ;
}

HRESULT CUIFrame::SetBkgMaskDraw(IUIDraw* pBkgMaskDraw)
{
    this->m_pBkgMaskDraw = pBkgMaskDraw ;
    return S_OK ;
}

HRESULT CUIFrame::GetBkgMaskDraw(IUIDraw** ppBkgMaskDraw)
{
    DEBUG_ASSERT(ppBkgMaskDraw) ;
    IF_RETURN(NULL == ppBkgMaskDraw, E_INVALIDARG) ;
    *ppBkgMaskDraw = NULL ;

    if (this->m_pBkgMaskDraw)
    {
        return this->m_pBkgMaskDraw->QueryInterface(__uuidof(IUIDraw), (VOID**)ppBkgMaskDraw) ;
    }
    return E_FAIL ;
}

HRESULT CUIFrame::SetBkgMaskDrawAlpha(BYTE cBkgMaskAlpha)
{
    this->m_cBkgMaskDrawAlpha = cBkgMaskAlpha ;
    return S_OK ;
}

HRESULT CUIFrame::GetBkgMaskDrawAlpha(BYTE* pcBkgMaskAlpha)
{
    DEBUG_ASSERT(pcBkgMaskAlpha) ;
    IF_RETURN(NULL == pcBkgMaskAlpha, E_INVALIDARG) ;
    *pcBkgMaskAlpha = this->m_cBkgMaskDrawAlpha ;
    return S_OK ;
}

HRESULT CUIFrame::Update(BOOL bFoceLayout, BOOL bFoceSync)
{
    CComQIPtr<IUIFrameInternal> pFrameInternal = GetEntity<IUIFrameInternal>() ;
    IF_RETURN(NULL == pFrameInternal, E_FAIL) ;
    this->m_bUpdating = TRUE ;

    if (this->m_bRelayout || bFoceLayout)
    {
        __self->RaiseEvent(EVENT::LAYOUTBEGIN, NULL) ;
        pFrameInternal->Layout() ;
        this->m_bRelayout = FALSE ;
        __self->RaiseEvent(EVENT::LAYOUTEND, NULL) ;
    }

    if (this->m_bNeedSynch || bFoceSync)
    {
        this->m_bCacheVisibleRect = FALSE ;
        this->m_bCacheAbsolutLocation = FALSE ;
        pFrameInternal->Synchronize(FALSE) ;
        bFoceSync = bFoceSync || m_bNeedSynch ;

        this->m_bNeedSynch = FALSE ;
    }

    LONG lChildrenCount = 0 ;
    __self->GetChildrenCount(&lChildrenCount) ;
    for (INT i = 0; i < lChildrenCount; ++i)
    {
        CComPtr<IUIElement> pElement ;
        __self->GetChildByIndex(i, &pElement) ;
        CComQIPtr<IUIFrame> pFrame = pElement ;
        IF_CONTINUE(NULL == pFrame) ;

        pFrame->Update(bFoceLayout, bFoceSync) ;
    }

    /*this->m_bHaveNeedSychChild = FALSE ;
    this->m_bHaveRelayoutChild = FALSE ;*/

    this->m_bUpdating = FALSE ;
    return S_OK ;
}

HRESULT CUIFrame::SetAnchor(INT nAnchor)
{
    IF_RETURN(this->m_nAnchor == nAnchor, S_OK) ;
    this->m_nAnchor = nAnchor ;

    GetEntity<IUIFrameInternal>()->MarkParentRelayout() ;
    __self->Invalidate() ;
    return S_OK ;
}

HRESULT CUIFrame::SetAnchor(BSTR bstrAnchor)
{
    CString cstrAnchor = bstrAnchor ;
    if (0 == cstrAnchor.CompareNoCase(_T("NONE")))
    {
        return __self->SetAnchor(ANCHOR::NONE) ;
    }
    else if (0 == cstrAnchor.CompareNoCase(_T("TOP_LEFT")))
    {
        return __self->SetAnchor(ANCHOR::TOP_LEFT) ;
    }
    else if (0 == cstrAnchor.CompareNoCase(_T("TOP_RIGHT")))
    {
        return __self->SetAnchor(ANCHOR::TOP_RIGHT) ;
    }
    else if (0 == cstrAnchor.CompareNoCase(_T("TOP_CENTER")))
    {
        return __self->SetAnchor(ANCHOR::TOP_CENTER) ;
    }
    else if (0 == cstrAnchor.CompareNoCase(_T("BOTTOM_LEFT")))
    {
        return __self->SetAnchor(ANCHOR::BOTTOM_LEFT) ;
    }
    else if (0 == cstrAnchor.CompareNoCase(_T("BOTTOM_RIGHT")))
    {
        return __self->SetAnchor(ANCHOR::BOTTOM_RIGHT) ;
    }
    else if (0 == cstrAnchor.CompareNoCase(_T("BOTTOM_CENTER")))
    {
        return __self->SetAnchor(ANCHOR::BOTTOM_CENTER) ;
    }
    else if (0 == cstrAnchor.CompareNoCase(_T("CENTER")))
    {
        return __self->SetAnchor(ANCHOR::CENTER) ;
    }
    else if (0 == cstrAnchor.CompareNoCase(_T("LEFT_CENTER")))
    {
        return __self->SetAnchor(ANCHOR::LEFT_CENTER) ;
    }
    else if (0 == cstrAnchor.CompareNoCase(_T("RIGHT_CENTER")))
    {
        return __self->SetAnchor(ANCHOR::RIGHT_CENTER) ;
    }
    else if (0 == cstrAnchor.CompareNoCase(_T("LEFT")))
    {
        return __self->SetAnchor(ANCHOR::LEFT) ;
    }
    else if (0 == cstrAnchor.CompareNoCase(_T("RIGHT")))
    {
        return __self->SetAnchor(ANCHOR::RIGHT) ;
    }
    else if (0 == cstrAnchor.CompareNoCase(_T("TOP")))
    {
        return __self->SetAnchor(ANCHOR::TOP) ;
    }
    else if (0 == cstrAnchor.CompareNoCase(_T("BOTTOM")))
    {
        return __self->SetAnchor(ANCHOR::BOTTOM) ;
    }
    else if (0 == cstrAnchor.CompareNoCase(_T("FILL")))
    {
        return __self->SetAnchor(ANCHOR::FILL) ;
    }
    return E_FAIL ;
}

HRESULT CUIFrame::GetAnchor(INT* pnAnchor)
{
    DEBUG_ASSERT(pnAnchor) ;
    IF_RETURN(NULL == pnAnchor, E_INVALIDARG) ;

    *pnAnchor = this->m_nAnchor ;
    return S_OK ;
}

HRESULT CUIFrame::SetDrift(INT nDrift)
{
	this->m_nDrift = nDrift ;
	GetEntity<IUIFrameInternal>()->MarkParentRelayout() ;
	return S_OK ;
}

HRESULT CUIFrame::SetDrift(BSTR bstrDrift)
{
	CString cstrDrift = bstrDrift ;
	if (0 == cstrDrift.CompareNoCase(_T("NEAR")))
	{
		return __self->SetDrift(DRIFT::DRIFT_NEAR) ;
	}
	else if (0 == cstrDrift.CompareNoCase(_T("FAR")))
	{
		return __self->SetDrift(DRIFT::DRIFT_FAR) ;
	}
	else if (0 == cstrDrift.CompareNoCase(_T("MIDDLE")))
	{
		return __self->SetDrift(DRIFT::DRIFT_MIDDLE) ;
	}
	return S_OK ;
}

HRESULT CUIFrame::GetDrift(INT* pnDrift)
{
	DEBUG_ASSERT(pnDrift) ;
	IF_RETURN(NULL == pnDrift, E_FAIL) ;

	*pnDrift = this->m_nDrift ;
	return S_OK ;
}

HRESULT CUIFrame::SetAutoWidth(BOOL bAutoWidth)
{
    IF_RETURN(this->m_bAutoWidth == bAutoWidth, S_OK) ;
    this->m_bAutoWidth = bAutoWidth ;

    GetEntity<IUIFrameInternal>()->MarkReCalcsize() ;
    __self->Invalidate() ;
    return S_OK ;
}

HRESULT CUIFrame::GetAutoWidth(BOOL* pbAutoWidth)
{
    DEBUG_ASSERT(pbAutoWidth) ;
    IF_RETURN(NULL == pbAutoWidth, E_INVALIDARG) ;

    *pbAutoWidth = this->m_bAutoWidth ;
    return S_OK ;
}

HRESULT CUIFrame::SetAutoHeight(BOOL bAutoHeight)
{
    IF_RETURN(this->m_bAutoHeight == bAutoHeight, S_OK) ;
    this->m_bAutoHeight = bAutoHeight ;

    GetEntity<IUIFrameInternal>()->MarkReCalcsize() ;
    __self->Invalidate() ;
    return S_OK ;
}

HRESULT CUIFrame::GetAutoHeight(BOOL* pbAutoHeight)
{
    DEBUG_ASSERT(pbAutoHeight) ;
    IF_RETURN(NULL == pbAutoHeight, E_INVALIDARG) ;
    *pbAutoHeight = this->m_bAutoHeight ;
    return S_OK ;
}

HRESULT CUIFrame::SetAutoSize(BOOL bAutoSize)
{
    __self->SetAutoWidth(bAutoSize) ;
    __self->SetAutoHeight(bAutoSize) ;
    return S_OK ;
}

HRESULT CUIFrame::GetAutoSize(BOOL* pbAutoSize)
{
    DEBUG_ASSERT(pbAutoSize) ;
    IF_RETURN(NULL == pbAutoSize, E_INVALIDARG) ;
    *pbAutoSize = this->m_bAutoWidth && this->m_bAutoHeight ;
    return S_OK ;
}

HRESULT CUIFrame::SetMaxAutoSize(SIZE szMaxAutoSize)
{
    this->m_szAutoMaxSize = szMaxAutoSize ;
    
    if (0 > this->m_szAutoMaxSize.cx)
    {
        this->m_szAutoMaxSize.cx = INT_MAX ;
    }
    
    if (0 > this->m_szAutoMaxSize.cy)
    {
        this->m_szAutoMaxSize.cy = INT_MAX ;
    }

    return S_OK ;
}

HRESULT CUIFrame::GetMaxAutoSize(SIZE* pszMaxAutoSize)
{
    DEBUG_ASSERT(pszMaxAutoSize) ;
    IF_RETURN(NULL == pszMaxAutoSize, E_INVALIDARG) ;
    *pszMaxAutoSize = this->m_szAutoMaxSize ;
    return S_OK ;
}

HRESULT CUIFrame::SetMinAutoSize(SIZE szMinAutoSize)
{
    this->m_szAutoMinSize = szMinAutoSize ;
    return S_OK ;
}

HRESULT CUIFrame::GetMinAutoSize(SIZE* pszMinAutoSize)
{
    DEBUG_ASSERT(pszMinAutoSize) ;
    IF_RETURN(NULL == pszMinAutoSize, E_INVALIDARG) ;
    *pszMinAutoSize = this->m_szAutoMinSize ;
    return S_OK ;
}

HRESULT CUIFrame::SetWidthAsParent(BOOL bWidthAsParent)
{
    this->m_bWidthAsParent = bWidthAsParent ;
    return S_OK ;
}

HRESULT CUIFrame::GetWidthAsParent(BOOL* pbWidthAsParent)
{
    DEBUG_ASSERT(pbWidthAsParent) ;
    IF_RETURN(NULL == pbWidthAsParent, E_INVALIDARG) ;
    *pbWidthAsParent = this->m_bWidthAsParent ;
    return S_OK ;
}

HRESULT CUIFrame::SetHeightAsParent(BOOL bHeightAsParent)
{
    this->m_bHeightAsParent = bHeightAsParent ;
    return S_OK ;
}

HRESULT CUIFrame::GetHeightAsParent(BOOL* pbHeightAsParent)
{
    DEBUG_ASSERT(pbHeightAsParent) ;
    IF_RETURN(NULL == pbHeightAsParent, E_INVALIDARG) ;
    *pbHeightAsParent = this->m_bHeightAsParent ;
    return S_OK ;
}

HRESULT CUIFrame::SetSizeAsParent(BOOL bSizeAsParent)
{
    this->m_bWidthAsParent  = bSizeAsParent ;
    this->m_bHeightAsParent = bSizeAsParent ;
    return S_OK ;
}

HRESULT CUIFrame::RaiseEvent(INT nEventId, tEventArg* pArgs)
{
    MAP_EVENT_LISTENER::iterator it = this->m_mapEventListenerPool.find(nEventId) ;
    IF_RETURN(this->m_mapEventListenerPool.end() == it, S_OK) ;

    MAP_EVENT_LISTEN_POOL::iterator it_ptr = it->second.begin() ;
    for (; it_ptr != it->second.end(); ++it_ptr)
    {
        IF_CONTINUE(!it_ptr->second) ;
        it_ptr->second->OnEvent(GetEntity<IUIFrame>(), nEventId, pArgs) ;
    }
    return S_OK ;
}

HRESULT CUIFrame::AddEventListener(INT nEventId, IUIEventCallback* pListener)
{
    DEBUG_ASSERT(pListener) ;
    IF_RETURN(NULL == pListener, E_INVALIDARG) ;

    this->m_mapEventListenerPool[nEventId][(LONG)(pListener)] = pListener ;
    return S_OK ;
}

HRESULT CUIFrame::DelEventListener(INT nEventId, IUIEventCallback* pListener)
{   
    DEBUG_ASSERT(pListener) ;
    IF_RETURN(NULL == pListener, E_INVALIDARG) ;

    MAP_EVENT_LISTENER::iterator it 
        = this->m_mapEventListenerPool.find(nEventId) ;
    IF_RETURN(this->m_mapEventListenerPool.end() == it, S_OK) ;
    
    MAP_EVENT_LISTEN_POOL::iterator it_ptr = it->second.find((LONG)(pListener)) ;
    IF_RETURN(it->second.end() == it_ptr, S_OK) ;

    it->second.erase(it_ptr) ;
    return S_OK ;
}

HRESULT CUIFrame::GetSizeAsParent(BOOL* pbSizeAsParent)
{
    DEBUG_ASSERT(pbSizeAsParent) ;
    IF_RETURN(NULL == pbSizeAsParent, E_INVALIDARG) ;
    *pbSizeAsParent = this->m_bWidthAsParent && this->m_bHeightAsParent ;
    return S_OK ;
}

HRESULT CUIFrame::SetEnableDrag(BOOL bEnable)
{
    this->m_bEnableVerticalDrag = bEnable ;
    this->m_bEnableHorizontalDrag = bEnable ;
    return S_OK ;
}

HRESULT CUIFrame::GetEnableDrag(BOOL* pbEnable)
{
    DEBUG_ASSERT(pbEnable) ;
    IF_RETURN(NULL == pbEnable, E_INVALIDARG) ;

    *pbEnable = m_bEnableVerticalDrag || m_bEnableHorizontalDrag ;
    return S_OK ;
}

HRESULT CUIFrame::SetDragRange(RECT rcRange)
{
    this->m_rcDragRange = rcRange ;
    return S_OK ;
}

HRESULT CUIFrame::GetDragRange(RECT* prcRange)
{
    DEBUG_ASSERT(prcRange) ;
    IF_RETURN(NULL == prcRange, E_INVALIDARG) ;

    *prcRange = this->m_rcDragRange ;
    return S_OK ;
}

HRESULT CUIFrame::SetEnableVerticalDrag(BOOL bEnable)
{
    this->m_bEnableVerticalDrag = bEnable ;
    return S_OK ;
}

HRESULT CUIFrame::GetEnableVerticalDrag(BOOL* pbEnable)
{
    DEBUG_ASSERT(pbEnable) ;
    IF_RETURN(NULL == pbEnable, E_INVALIDARG) ;

    *pbEnable = this->m_bEnableVerticalDrag ;
    return S_OK ;
}

HRESULT CUIFrame::SetEnableHorizontalDrag(BOOL bEnable)
{
    this->m_bEnableHorizontalDrag = bEnable ;
    return S_OK ;
}

HRESULT CUIFrame::GetEnableHorizontalDrag(BOOL* pbEnable)
{
    DEBUG_ASSERT(pbEnable) ;
    IF_RETURN(NULL == pbEnable, E_INVALIDARG) ;

    *pbEnable = this->m_bEnableHorizontalDrag ;
    return S_OK ;
}

HRESULT CUIFrame::SetEnableDBClick(BOOL bEnable)
{
    this->m_bEnableDBClick = bEnable ;
    return S_OK ;
}

HRESULT CUIFrame::GetEnableDBClick(BOOL* pbEnable)
{
    DEBUG_ASSERT(pbEnable) ;
    IF_RETURN(NULL == pbEnable, E_INVALIDARG) ;
    
    *pbEnable = this->m_bEnableDBClick ;
    return S_OK ;
}

HRESULT CUIFrame::SetIntercepMouse(BOOL bIntercept)
{
    this->m_bInterceptMouse = bIntercept ;
    return S_OK ;
}

HRESULT CUIFrame::GetIntercepMouse(BOOL* pbIntercept)
{
    DEBUG_ASSERT(pbIntercept) ;
    IF_RETURN(NULL == pbIntercept, E_INVALIDARG) ;

    *pbIntercept = this->m_bInterceptMouse ;
    return S_OK ;
}

HRESULT CUIFrame::SetTransparentMouse(BOOL bTransparent)
{
    this->m_bTransparentMouse = bTransparent ;
    return S_OK ;
}

HRESULT CUIFrame::Invalidate()
{
    CComPtr<IUIFrame> pFrame = GetEntity<IUIFrame>() ;
    CComQIPtr<IUIFrameInternal> pInternal = pFrame ;
    DEBUG_ASSERT(pInternal && pFrame) ;
    IF_RETURN(NULL == pInternal || NULL == pFrame, E_INVALIDARG) ;

	this->m_bReRender = TRUE ;
    return pInternal->InvalidateInternal(pFrame) ;
}

HRESULT CUIFrame::InvalidateRect(RECT rcInvalidate)
{
    CComPtr<IUIElement> pElement ;
    __self->GetParent(&pElement) ;
    CComQIPtr<IUIFrame> pFrameParent = pElement ;
    IF_RETURN(NULL == pFrameParent, E_FAIL) ;

	this->m_bReRender = TRUE ;
    return pFrameParent->InvalidateRect(rcInvalidate) ;
}

HRESULT CUIFrame::GetTransparentMouse(BOOL* pbTransparent)
{
    DEBUG_ASSERT(pbTransparent) ;
    IF_RETURN(NULL == pbTransparent, E_INVALIDARG) ;

    *pbTransparent = this->m_bTransparentMouse ;
    return S_OK ;
}

HRESULT CUIFrame::SetIntercepKeyboard(BOOL bIntercept)
{
	this->m_bInterceptKeyboard = bIntercept ;
	return S_OK ;
}

HRESULT CUIFrame::GetIntercepKeyboard(BOOL* pbIntercept)
{
	DEBUG_ASSERT(pbIntercept) ;
	IF_RETURN(NULL == pbIntercept, E_INVALIDARG) ;
	*pbIntercept = this->m_bInterceptKeyboard ;
	return S_OK ;
}

HRESULT CUIFrame::SetTransparentKeyboard(BOOL bTransparent)
{
	this->m_bTransparentKeyboard = bTransparent ;
	return S_OK ;
}

HRESULT CUIFrame::GetTransparentKeyboard(BOOL* pbTransparent)
{
	DEBUG_ASSERT(pbTransparent) ;
	IF_RETURN(NULL == pbTransparent, E_INVALIDARG) ;
	*pbTransparent = this->m_bTransparentKeyboard ;
	return S_OK ;
}

HRESULT CUIFrame::AddDestoryListener(IUIDestoryCallback* pListener)
{
    DEBUG_ASSERT(pListener) ;
    IF_RETURN(NULL == pListener, E_INVALIDARG) ;
    this->m_mapDestoryListenerPool[(LONG)(pListener)] = pListener ;
    return S_OK ;
}

HRESULT CUIFrame::DelDestoryListener(IUIDestoryCallback* pListener)
{
    DEBUG_ASSERT(pListener) ;
    IF_RETURN(NULL == pListener, E_INVALIDARG) ;
    MAP_DESTORY_LISTEN_POOL::iterator it 
        = this->m_mapDestoryListenerPool.find((LONG)(pListener)) ;
    if (this->m_mapDestoryListenerPool.end() != it)
    {
        this->m_mapDestoryListenerPool.erase(it) ;
    }
    return S_OK ;
}

HRESULT CUIFrame::Layout()
{
    LONG lChildrenCount = 0 ;
    __self->GetChildrenCount(&lChildrenCount) ;

    for (INT i = 0; i < lChildrenCount; ++i)
    {
        CComPtr<IUIElement> pElement ;
        __self->GetChildByIndex(i, &pElement) ;
        CComQIPtr<IUIFrame> pFrameChild = pElement ;
        CComQIPtr<IUIFrameInternal> pFrameChildInternal = pElement ;
        IF_CONTINUE(NULL == pFrameChild || NULL == pFrameChildInternal) ;

        BOOL bFloat = FALSE ;
        pFrameChild->GetFloat(&bFloat) ;
        IF_CONTINUE(FALSE == bFloat) ;

        CPoint ptLocation(0, 0) ;
        pFrameChild->GetLocation(&ptLocation) ;
        CRect rcChildMargin(0, 0, 0, 0) ;
        pFrameChild->GetMargin(&rcChildMargin) ;

        BOOL bWithAsParent = FALSE ;
        BOOL bHeightAsParent = FALSE ;
        pFrameChild->GetWidthAsParent(&bWithAsParent) ;
        pFrameChild->GetHeightAsParent(&bHeightAsParent) ;

        INT nAnchor = 0 ;
        pFrameChild->GetAnchor(&nAnchor) ;

        CSize szEstimateSize(-1, -1) ;
        if (ANCHOR::NONE == nAnchor)
        {
            if (bWithAsParent)
            {
                szEstimateSize.cx = m_szFrameSize.cx  ;
            }
            if (bHeightAsParent)
            {
                szEstimateSize.cy = m_szFrameSize.cy ;
            }
        }
        else
        {
            if (bWithAsParent)
            {
                szEstimateSize.cx = m_szFrameSize.cx - m_rcFramePadding.left 
                    - m_rcFramePadding.right -rcChildMargin.left - rcChildMargin.right ;
				szEstimateSize.cx = szEstimateSize.cx > 0 ? szEstimateSize.cx : 0 ;
            }
            if (bHeightAsParent)
            {
                szEstimateSize.cy = m_szFrameSize.cy - m_rcFramePadding.top
                    - m_rcFramePadding.bottom - rcChildMargin.top - rcChildMargin.bottom ;
				szEstimateSize.cy = szEstimateSize.cy > 0 ? szEstimateSize.cy : 0 ;
            }
        }
        pFrameChildInternal->SetEstimateSize(szEstimateSize) ;

        CSize szChild(0, 0) ;
        pFrameChild->GetSize(&szChild) ;

        CRect rcChildTarget(0, 0, 0, 0) ;
        if (ANCHOR::NONE == nAnchor)
        {
            rcChildTarget.right = rcChildTarget.left + szChild.cx ;
            rcChildTarget.bottom = rcChildTarget.top + szChild.cy ;
            rcChildTarget.MoveToXY(ptLocation) ;
        }
        else if (ANCHOR::TOP_LEFT == nAnchor)
        {
            rcChildTarget.left      = m_rcFramePadding.left + rcChildMargin.left ;
            rcChildTarget.top       = m_rcFramePadding.top + rcChildMargin.top ;
            rcChildTarget.right     = rcChildTarget.left + szChild.cx ;
            rcChildTarget.bottom    = rcChildTarget.top + szChild.cy ;
        }
        else if (ANCHOR::TOP_RIGHT == nAnchor)
        {
            rcChildTarget.right     = m_szFrameSize.cx - rcChildMargin.right - m_rcFramePadding.right ;
            rcChildTarget.top       = m_rcFramePadding.top + rcChildMargin.top ;
            rcChildTarget.left      = rcChildTarget.right - szChild.cx ;
            rcChildTarget.bottom    = rcChildTarget.top + szChild.cy ;
        }
        else if (ANCHOR::TOP_CENTER == nAnchor)
        {
            rcChildTarget.top       = m_rcFramePadding.top + rcChildMargin.top ;
            rcChildTarget.bottom    = rcChildTarget.top + szChild.cy ;
            rcChildTarget.left      = (m_szFrameSize.cx - m_rcFramePadding.left - m_rcFramePadding.right
                - szChild.cx - rcChildMargin.left - rcChildMargin.right)/2 +m_rcFramePadding.left + rcChildMargin.left ;
            rcChildTarget.right     = rcChildTarget.left + szChild.cx ;
        }
        else if (ANCHOR::BOTTOM_LEFT == nAnchor)
        {
            rcChildTarget.left      = m_rcFramePadding.left + rcChildMargin.left ;
            rcChildTarget.right     = rcChildTarget.left + szChild.cx ;
            rcChildTarget.bottom    = m_szFrameSize.cy - rcChildMargin.bottom - m_rcFramePadding.bottom ;
            rcChildTarget.top       = rcChildTarget.bottom - szChild.cy ;
        }
        else if (ANCHOR::BOTTOM_RIGHT == nAnchor)
        {
            rcChildTarget.right     = m_szFrameSize.cx - rcChildMargin.right - m_rcFramePadding.right ;
            rcChildTarget.left      = rcChildTarget.right - szChild.cx ;
            rcChildTarget.bottom    = m_szFrameSize.cy - rcChildMargin.bottom - m_rcFramePadding.bottom ;
            rcChildTarget.top       = rcChildTarget.bottom - szChild.cy ;
        }
        else if (ANCHOR::BOTTOM_CENTER == nAnchor)
        {
            rcChildTarget.bottom    = m_szFrameSize.cy - rcChildMargin.bottom - m_rcFramePadding.bottom ;
            rcChildTarget.top       = rcChildTarget.bottom - szChild.cy ;
            rcChildTarget.left      = (m_szFrameSize.cx - m_rcFramePadding.left - m_rcFramePadding.right
                - szChild.cx - rcChildMargin.left - rcChildMargin.right)/2 +m_rcFramePadding.left + rcChildMargin.left ;
            rcChildTarget.right     = rcChildTarget.left + szChild.cx ;
        }
        else if (ANCHOR::CENTER == nAnchor)
        {
            rcChildTarget.left      = (m_szFrameSize.cx - m_rcFramePadding.left - m_rcFramePadding.right
                - szChild.cx - rcChildMargin.left - rcChildMargin.right)/2 +m_rcFramePadding.left + rcChildMargin.left ;
            rcChildTarget.right     = rcChildTarget.left + szChild.cx ;
            rcChildTarget.top       = (m_szFrameSize.cy - m_rcFramePadding.top - m_rcFramePadding.bottom
                - rcChildMargin.top - rcChildMargin.bottom - szChild.cy)/2 + m_rcFramePadding.top + rcChildMargin.top ;
            rcChildTarget.bottom    = rcChildTarget.top + szChild.cy ;
        }
        else if (ANCHOR::LEFT_CENTER == nAnchor)
        {
            rcChildTarget.left      = m_rcFramePadding.left + rcChildMargin.left ;
            rcChildTarget.right     = rcChildTarget.left + szChild.cx ;
            rcChildTarget.top       = (m_szFrameSize.cy - m_rcFramePadding.top - m_rcFramePadding.bottom
                - rcChildMargin.top - rcChildMargin.bottom - szChild.cy)/2 + m_rcFramePadding.top + rcChildMargin.top ;
            rcChildTarget.bottom    = rcChildTarget.top + szChild.cy ;
            
        }
        else if (ANCHOR::RIGHT_CENTER == nAnchor)
        {
            rcChildTarget.right     = m_szFrameSize.cx - rcChildMargin.right - m_rcFramePadding.right ;
            rcChildTarget.left      = rcChildTarget.right - szChild.cx ;
            rcChildTarget.top       = (m_szFrameSize.cy - m_rcFramePadding.top - m_rcFramePadding.bottom
                - rcChildMargin.top - rcChildMargin.bottom - szChild.cy)/2 + m_rcFramePadding.top + rcChildMargin.top ;
            rcChildTarget.bottom    = rcChildTarget.top + szChild.cy ;
        }

        pFrameChildInternal->SetLayoutRect(rcChildTarget) ;
    }

	if (this->m_pLayouter)
	{
		this->m_pLayouter->Layout(GetEntity<IUIFrame>()) ;
	}

    return S_OK ;
}

HRESULT CUIFrame::SetExtPadding(RECT rcPadding)
{
	this->m_rcFrameExtPadding = rcPadding ;
	GetEntity<IUIFrameInternal>()->MarkReCalcsize() ;
	__self->Invalidate() ;
	return S_OK ;
}

HRESULT CUIFrame::GetExtPadding(RECT* prcPadding)
{
	DEBUG_ASSERT(prcPadding) ;
	IF_RETURN(NULL == prcPadding, E_INVALIDARG) ;

	*prcPadding = this->m_rcFrameExtPadding ;
	return S_OK ;
}

HRESULT CUIFrame::Synchronize(BOOL bErase)
{
    CComPtr<IUIFrame> pFrame = GetEntity<IUIFrame>() ;
    CComQIPtr<IUIFrameInternal> pInternal = pFrame ;
    DEBUG_ASSERT(pInternal && pFrame) ;
    IF_RETURN(NULL == pInternal || NULL == pFrame, E_INVALIDARG) ;

    return pInternal->SynchronizeInternal(pFrame, bErase) ;
}

HRESULT CUIFrame::SynchronizeDeeply(BOOL bErase)
{
    CComPtr<IUIFrame> pFrame = GetEntity<IUIFrame>() ;
    CComQIPtr<IUIFrameInternal> pInternal = pFrame ;
    DEBUG_ASSERT(pInternal && pFrame) ;
    IF_RETURN(NULL == pInternal || NULL == pFrame, E_INVALIDARG) ;

    pInternal->SynchronizeInternal(pFrame, bErase) ;

    LONG lChildrenCount = 0 ;
    __self->GetChildrenCount(&lChildrenCount) ;
    for (INT i = 0; i < lChildrenCount; ++i)
    {
        CComPtr<IUIElement> pElement ;
        __self->GetChildByIndex(i, &pElement) ;
        CComQIPtr<IUIFrameInternal> pFrameInternal = pElement ;
        IF_CONTINUE(NULL == pFrameInternal) ;

        pFrameInternal->SynchronizeDeeply(bErase) ;
    }

    return S_OK ;
}

HRESULT CUIFrame::SetEstimateSize(SIZE szEstimate)
{
    if (szEstimate.cx >= 0 && m_szFrameSize.cx != szEstimate.cx)
    {
        this->m_szFrameSize.cx = szEstimate.cx ;
        this->m_bEstimateSizeChange = TRUE ;

        if (this->m_bAutoWidth || this->m_bAutoHeight)
        {
            this->m_bReCalcsize = TRUE ;
        }
    }

    if (szEstimate.cy >= 0 && m_szFrameSize.cy != szEstimate.cy)
    {
        this->m_szFrameSize.cy = szEstimate.cy ;
        this->m_bEstimateSizeChange = TRUE ;

        if (this->m_bAutoWidth || this->m_bAutoHeight)
        {
            this->m_bReCalcsize = TRUE ;
        }
    }
    return S_OK ;
}

HRESULT CUIFrame::SetLayoutRect(RECT rcLayout)
{
    CComQIPtr<IUIFrameInternal> pInternal = GetEntity<IUIFrameInternal>() ;
    DEBUG_ASSERT(pInternal) ;
    IF_RETURN(NULL == pInternal, E_FAIL) ;

    CRect   rcTarget(rcLayout) ;
    CSize   szTarget(rcTarget.Width(), rcTarget.Height()) ;
    CPoint  ptTarget = rcTarget.TopLeft() ;

    if (this->m_bEstimateSizeChange)
    {
        this->m_bRelayout               = TRUE ;
        this->m_bNeedSynch              = TRUE ;
    }

    if (this->m_szFrameSize != szTarget)
    {
        this->m_szFrameSize             = szTarget ;
        this->m_bRelayout               = TRUE ;
        this->m_bNeedSynch              = TRUE ;
    }

    if (this->m_ptFrameLocation != ptTarget)
    {
        this->m_ptFrameLocation         = ptTarget ;
        this->m_bNeedSynch              = TRUE ;
    }

    return S_OK ;
}

HRESULT CUIFrame::GetLayoutRect(RECT* prcLayout)
{
    DEBUG_ASSERT(prcLayout) ;
    IF_RETURN(NULL == prcLayout, E_INVALIDARG) ;

    prcLayout->left     = this->m_ptFrameLocation.x ;
    prcLayout->top      = this->m_ptFrameLocation.y ;
    prcLayout->right    = this->m_ptFrameLocation.x + this->m_szFrameSize.cx ;
    prcLayout->bottom   = this->m_ptFrameLocation.y + this->m_szFrameSize.cy ;
    return S_OK ;
}

HRESULT CUIFrame::DragBegin()
{
    return S_OK ;
}

HRESULT CUIFrame::Dragging(POINT ptOld, POINT ptTarget, POINT* ptOut)
{
    DEBUG_ASSERT(ptOut) ;
    IF_RETURN(NULL == ptOut, E_INVALIDARG) ;

    *ptOut = ptTarget ;
    return S_OK ;
}

HRESULT CUIFrame::DragEnd()
{
    return S_OK ;
}

HRESULT CUIFrame::GetMousePosInternal(POINT* pptPoint)
{
    CComPtr<IUIElement> pElement ;
    __self->GetParent(&pElement) ;
    CComQIPtr<IUIFrameInternal> pFrameParentInternal = pElement ;
    IF_RETURN(NULL == pFrameParentInternal, E_FAIL) ;

    return pFrameParentInternal->GetMousePosInternal(pptPoint) ;
}

HRESULT CUIFrame::SetCaptureInternal(BOOL bCapture, IUIFrame* pFrame)
{
    DEBUG_ASSERT(pFrame) ;
    IF_RETURN(NULL == pFrame, E_INVALIDARG) ;

    CComPtr<IUIElement> pElement ;
    __self->GetParent(&pElement) ;
    CComQIPtr<IUIFrameInternal> pFrameParentInternal = pElement ;
    //DEBUG_ASSERT(pFrameParentInternal) ;
    IF_RETURN(NULL == pFrameParentInternal, E_FAIL) ;

    return pFrameParentInternal->SetCaptureInternal(bCapture, pFrame) ;
}

HRESULT CUIFrame::GetCaptureInternal(IUIFrame** ppFrame)
{
    DEBUG_ASSERT(ppFrame) ;
    IF_RETURN(NULL == ppFrame, E_INVALIDARG) ;
    *ppFrame = NULL ;

    CComPtr<IUIElement> pElement ;
    __self->GetParent(&pElement) ;
    CComQIPtr<IUIFrameInternal> pFrameParentInternal = pElement ;
    //DEBUG_ASSERT(pFrameParentInternal) ;
    IF_RETURN(NULL == pFrameParentInternal, E_FAIL) ;

    return pFrameParentInternal->GetCaptureInternal(ppFrame) ;
}

HRESULT CUIFrame::SynchronizeInternal(IUIFrame* pFrame, BOOL bErase)
{
    DEBUG_ASSERT(pFrame) ;
    IF_RETURN(NULL == pFrame, E_INVALIDARG) ;

    CComPtr<IUIElement> pElement ;
    __self->GetParent(&pElement) ;
    CComQIPtr<IUIFrameInternal> pFrameParentInternal = pElement ;
    //DEBUG_ASSERT(pFrameParentInternal) ;
    IF_RETURN(NULL == pFrameParentInternal, E_FAIL) ;

    return pFrameParentInternal->SynchronizeInternal(pFrame, bErase) ;
}

HRESULT CUIFrame::InvalidateInternal(IUIFrame* pFrame)
{
    DEBUG_ASSERT(pFrame) ;
    IF_RETURN(NULL == pFrame, E_INVALIDARG) ;
    
    //IF_RETURN(this->m_bFrameHidden, S_OK) ;

    CComPtr<IUIElement> pElement ;
    __self->GetParent(&pElement) ;
    CComQIPtr<IUIFrameInternal> pFrameParentInternal = pElement ;
    IF_RETURN(NULL == pFrameParentInternal, E_FAIL) ;

    return pFrameParentInternal->InvalidateInternal(pFrame) ;
}

HRESULT CUIFrame::InvalidateLayout(IUIFrame* pFrame)
{
    DEBUG_ASSERT(pFrame) ;
    IF_RETURN(NULL == pFrame, E_INVALIDARG) ;
    
    CComPtr<IUIElement> pElement ;
    __self->GetParent(&pElement) ;
    CComQIPtr<IUIFrameInternal> pFrameParentInternal = pElement ;
    IF_RETURN(NULL == pFrameParentInternal, E_FAIL) ;
    return pFrameParentInternal->InvalidateLayout(pFrame) ;
}

HRESULT CUIFrame::MarkReCalcsize()
{
    this->m_bRelayout = TRUE ;
    this->m_bNeedSynch = TRUE ;

    if (this->m_bAutoHeight || this->m_bAutoWidth)
    {
        this->m_bReCalcsize = TRUE ;
    }

    if (FALSE == this->m_bFrameFloat)
    {
        return GetEntity<IUIFrameInternal>()->MarkParentReCalcsize() ;
    }

    GetEntity<IUIFrameInternal>()->MarkRelayout() ;
    GetEntity<IUIFrameInternal>()->MarkParentRelayout() ;
    return S_OK ;
}

HRESULT CUIFrame::MarkParentReCalcsize()
{
    CComPtr<IUIElement> pElement ;
    __self->GetParent(&pElement) ;
    CComQIPtr<IUIFrameInternal> pInternal = pElement ;
    if (pElement && pInternal)
    {
        pInternal->MarkReCalcsize() ;
    }
    return S_OK ;
}

HRESULT CUIFrame::MarkRelayout()
{
    this->m_bRelayout = TRUE ;
    return S_OK ;
}

HRESULT CUIFrame::MarkParentRelayout()
{
    CComPtr<IUIElement> pElement ;
    __self->GetParent(&pElement) ;
    CComQIPtr<IUIFrameInternal> pInternal = pElement ;
    if (pElement && pInternal)
    {
        pInternal->MarkRelayout() ;
    }
    return S_OK ;
}

HRESULT CUIFrame::NotifyAlphaChange()
{
    this->m_bCacheFrameShowAlpha = FALSE ;

    LONG lChildrenCount = 0 ;
    __self->GetChildrenCount(&lChildrenCount) ;
    for (INT i = 0; i < lChildrenCount; ++i)
    {
        CComPtr<IUIElement> pElement ;
        __self->GetChildByIndex(i, &pElement) ;
        CComQIPtr<IUIFrameInternal> pFrameInternal = pElement ;
        IF_CONTINUE(NULL == pFrameInternal) ;

        pFrameInternal->NotifyAlphaChange() ;
    }
    return S_OK ;
}

HRESULT CUIFrame::CalcSize(SIZE szOld, SIZE* pszCalcOut)
{
	DEBUG_ASSERT(pszCalcOut) ;
	IF_RETURN(NULL == pszCalcOut, E_FAIL) ;

	if (this->m_pLayouter)
	{
		return this->m_pLayouter->CalcSize(GetEntity<IUIFrame>(), szOld, pszCalcOut) ;
	}
	else
	{
		*pszCalcOut = szOld ;
	}
	return S_OK ;
}

HRESULT CUIFrame::AddChildFront(IUIElement* pChild)
{
    HRESULT hRet = __super::AddChildFront(pChild) ;
    IF_RETURN(!SUCCEEDED(hRet), hRet) ;

    GetEntity<IUIFrameInternal>()->MarkParentReCalcsize() ;
    __self->Invalidate() ;
    return S_OK ;
}

HRESULT CUIFrame::AddChildBack(IUIElement* pChild)
{
    HRESULT hRet = __super::AddChildBack(pChild) ;
    IF_RETURN(!SUCCEEDED(hRet), hRet) ;

    GetEntity<IUIFrameInternal>()->MarkParentReCalcsize() ;
    __self->Invalidate() ;
    return S_OK ;
}

HRESULT CUIFrame::InsertChild(INT nIndex, IUIElement* pChild)
{
    HRESULT hRet = __super::InsertChild(nIndex, pChild) ;
    IF_RETURN(!SUCCEEDED(hRet), hRet) ;

    GetEntity<IUIFrameInternal>()->MarkParentReCalcsize() ;
    __self->Invalidate() ;
    return S_OK ;
}

HRESULT CUIFrame::RemoveChildByIndex(INT nIndex)
{
    CComPtr<IUIElement> pElement ;
    __self->GetChildByIndex(nIndex, &pElement) ;
    CComQIPtr<IUIFrameInternal> pFrameInternal = pElement ;
    IF_RETURN(NULL == pFrameInternal, E_FAIL) ;
    pFrameInternal->SynchronizeDeeply(TRUE) ;

    return __super::RemoveChildByIndex(nIndex) ;
}

HRESULT CUIFrame::OnMessageSink(IUIFrame* pTarget, tMsgArg* pArg, BOOL* pbHandle, BOOL* pbIntercept)
{
    if (pbHandle)
    {
        *pbHandle = FALSE ;
    }

	
    if (pbIntercept)
    {
        *pbIntercept = this->m_bInterceptMouse ;
    }
    return S_OK ;
}

HRESULT CUIFrame::OnMessage(IUIFrame* pTarget, tMsgArg* pArg)
{
    DEBUG_ASSERT(pArg) ;
    IF_RETURN(NULL == pArg, E_INVALIDARG) ;

    BOOL bEnableDrag = m_bEnableVerticalDrag || m_bEnableHorizontalDrag ;
    if (MESSAGE::UI_MOUSEENTER == pArg->dwMsgId)
    {
        __self->SetState(STATE::HIGHLIGHT) ;
        __self->RaiseEvent(EVENT::MOUSEENTER, NULL) ;
        if (this->m_bEnableFrameState)
        {
            __self->Invalidate() ;
        }
    }
    else if (MESSAGE::UI_MOUSELEAVE == pArg->dwMsgId)
    {
        __self->SetState(STATE::NORMAL) ;
        __self->RaiseEvent(EVENT::MOUSELEAVE, NULL) ;
        if (this->m_bEnableFrameState)
        {
            __self->Invalidate() ;
        }
    }
    else if (MESSAGE::UI_LBTNDOWN == pArg->dwMsgId)
    {
        __self->SetState(STATE::PUSHED) ;
        __self->RaiseEvent(EVENT::MOUSELBTNDOWN, NULL) ;

        if (this->m_bEnableFrameState)
        {
            __self->Invalidate() ;
        }
        
        this->m_bLBtnDown = TRUE ;

        // about drag
        if (bEnableDrag && pArg)
        {
            tMsgArgPoint* pPointMouseArg = (tMsgArgPoint*)(pArg) ;
            this->m_ptLBtnDownLocation = pPointMouseArg->pt ;
        }
    }
    else if (MESSAGE::UI_LBTNUP == pArg->dwMsgId)
    {
        __self->RaiseEvent(EVENT::MOUSELBTNUP, NULL) ;

        tMsgArgPoint* _argPoint = (tMsgArgPoint*)(pArg) ;
        CRect rcVisbleRect(0, 0, 0, 0) ;
        __self->GetAbsolutVisibleRect(&rcVisbleRect) ;

        if (rcVisbleRect.PtInRect(_argPoint->pt))
        {
            __self->SetState(STATE::HIGHLIGHT) ;
        }
        else
        {
            __self->SetState(STATE::NORMAL) ;
        }

        if (this->m_bEnableFrameState)
        {
            __self->Invalidate() ;
        }

        if (this->m_bDragging)
        {
            GetEntity<IUIFrameInternal>()->DragEnd() ;
            __self->RaiseEvent(EVENT::DRAGEND, NULL) ;
        }

        this->m_bDragging = FALSE ;
        this->m_bLBtnDown = FALSE ;
    }
    else if (MESSAGE::UI_MOUSEMOVE == pArg->dwMsgId)
    {
        __self->RaiseEvent(EVENT::MOUSEMOVE, NULL) ;

        if (bEnableDrag && this->m_bLBtnDown)
        {
            if (FALSE == this->m_bDragging)
            {
                GetEntity<IUIFrameInternal>()->DragBegin() ;
                __self->RaiseEvent(EVENT::DRAGBEGIN, NULL) ;
                this->m_bDragging = TRUE ;
            }

            tMsgArgPoint* pPointMouseArg = (tMsgArgPoint*)(pArg) ;
            CPoint ptFrameLocation(0, 0) ;
            __self->GetLocation(&ptFrameLocation) ;
            CPoint ptFrameTargt(ptFrameLocation) ;
            
            if (this->m_bEnableHorizontalDrag)
            {
                ptFrameTargt.x += pPointMouseArg->pt.x - this->m_ptLBtnDownLocation.x ;
            }

            if (this->m_bEnableVerticalDrag)
            {
                ptFrameTargt.y += pPointMouseArg->pt.y - this->m_ptLBtnDownLocation.y ;
            }

            if (ptFrameTargt.x < this->m_rcDragRange.left)
            {
                ptFrameTargt.x = this->m_rcDragRange.left ;
            }

            if (ptFrameTargt.x > this->m_rcDragRange.right)
            {
                ptFrameTargt.x = this->m_rcDragRange.right ;
            }

            if (ptFrameTargt.y < this->m_rcDragRange.top)
            {
                ptFrameTargt.y = this->m_rcDragRange.top ;
            }

            if (ptFrameTargt.y > this->m_rcDragRange.bottom)
            {
                ptFrameTargt.y = this->m_rcDragRange.bottom ;
            }

            this->m_ptLBtnDownLocation = pPointMouseArg->pt ;
            
            CPoint ptTargetOut = ptFrameTargt ;
            GetEntity<IUIFrameInternal>()->Dragging(ptFrameLocation, ptFrameTargt, &ptTargetOut) ;
            __self->SetLocation(ptTargetOut) ;
            __self->RaiseEvent(EVENT::DRAGGING, NULL) ;
        }
    }
    else if (MESSAGE::UI_LBTNCLICK == pArg->dwMsgId)
    {
        __self->RaiseEvent(EVENT::MOUSELBTNCLICK, NULL) ;
    }
    else if (MESSAGE::UI_LBTNDBCLICK == pArg->dwMsgId)
    {
        __self->RaiseEvent(EVENT::MOUSELBTNDBCLICK, NULL) ;
    }
    else if (MESSAGE::UI_RBTNDOWN == pArg->dwMsgId)
    {
        __self->RaiseEvent(EVENT::MOUSERBTNDOWN, NULL) ;
    }
    else if (MESSAGE::UI_RBTNUP == pArg->dwMsgId)
    {
        __self->RaiseEvent(EVENT::MOUSERBTNUP, NULL) ;
    }
    else if (MESSAGE::UI_RBTNCLICK == pArg->dwMsgId)
    {
        __self->RaiseEvent(EVENT::MOUSERBCLICK, NULL) ;
    }
	else if (MESSAGE::UI_CURSOR == pArg->dwMsgId)
	{
		switch(this->m_nFrameHoverCursor)
		{
		case UI::CURSOR::EM_CURSOR_ARROW:
			::SetCursor(LoadCursor(NULL, IDC_ARROW)) ;
			break ;
		case UI::CURSOR::EM_CURSOR_IBEAM:
			::SetCursor(LoadCursor(NULL, IDC_IBEAM)) ;
			break ;
		case UI::CURSOR::EM_CURSOR_WAIT:
			::SetCursor(LoadCursor(NULL, IDC_WAIT)) ;
			break ;
		case UI::CURSOR::EM_CURSOR_CROSS:
			::SetCursor(LoadCursor(NULL, IDC_CROSS)) ;
			break ;
		case UI::CURSOR::EM_CURSOR_UPARROW:
			::SetCursor(LoadCursor(NULL, IDC_UPARROW)) ;
			break ;
		case UI::CURSOR::EM_CURSOR_SIZE:
			::SetCursor(LoadCursor(NULL, IDC_SIZE)) ;
			break ;
		case UI::CURSOR::EM_CURSOR_ICON:
			::SetCursor(LoadCursor(NULL, IDC_ICON)) ;
			break ;
		case UI::CURSOR::EM_CURSOR_SIZENWSE:
			::SetCursor(LoadCursor(NULL, IDC_SIZENWSE)) ;
			break ;
		case UI::CURSOR::EM_CURSOR_SIZENESW:
			::SetCursor(LoadCursor(NULL, IDC_SIZENESW)) ;
			break ;
		case UI::CURSOR::EM_CURSOR_SIZEWE:
			::SetCursor(LoadCursor(NULL, IDC_SIZEWE)) ;
			break ;
		case UI::CURSOR::EM_CURSOR_SIZENS:
			::SetCursor(LoadCursor(NULL, IDC_SIZENS)) ;
			break ;
		case UI::CURSOR::EM_CURSOR_SIZEALL:
			::SetCursor(LoadCursor(NULL, IDC_SIZEALL)) ;
			break ;
		}
	}

    return E_FAIL ;
}

HRESULT CUIFrame::OnMessageRiase(IUIFrame* pTarget, tMsgArg* pArg, BOOL* pbIntercept)
{
    if (pbIntercept)
    {
        *pbIntercept = FALSE ;
    }
    return S_OK ;
}

HRESULT CUIFrame::SetAttribute(ICVarData* pAttrData)
{
    HRESULT hRet = __super::SetAttribute(pAttrData) ;
    SET_ATTR_CLASS_BEGIN    (pAttrData, CUIFrame)
    SET_ATTR_BSTR           (Anchor)
	SET_ATTR_BSTR			(Drift)
    SET_ATTR_END            ()

    SET_ATTR_INTERFACE_BEGIN(pAttrData, IUIFrame)
    SET_ATTR_BOOL           (Float)
    SET_ATTR_BOOL           (AutoWidth)
    SET_ATTR_BOOL           (AutoHeight)
    SET_ATTR_BOOL           (AutoSize)
    SET_ATTR_SIZE           (MaxAutoSize)
    SET_ATTR_SIZE           (MinAutoSize)
    SET_ATTR_BOOL           (WidthAsParent)
    SET_ATTR_BOOL           (HeightAsParent)
    SET_ATTR_BOOL           (SizeAsParent)
    SET_ATTR_SIZE           (Size)
    SET_ATTR_BYTE           (Alpha)
    SET_ATTR_POINT          (Location)
    SET_ATTR_RECT           (Rect)
    SET_ATTR_RECT           (Margin)
    SET_ATTR_RECT           (Padding)
    SET_ATTR_INT            (ZOrder)
    SET_ATTR_BOOL           (Hidden)
    SET_ATTR_BOOL           (Enable)
    SET_ATTR_BOOL           (EnableState)
    SET_ATTR_BOOL           (EnableDrag)
    SET_ATTR_INT            (Hittest)
	SET_ATTR_INTERFACE		(IUILayout, Layouter)
    SET_ATTR_BOOL           (DoubleBuffer)
    SET_ATTR_BYTE           (Alpha)
    SET_ATTR_INTERFACE      (IUIDraw, BkgDraw)
    SET_ATTR_BYTE           (BkgDrawAlpha)
    SET_ATTR_INTERFACE      (IUIDraw, BkgMaskDraw)
    SET_ATTR_BYTE           (BkgMaskDrawAlpha)
    SET_ATTR_BOOL           (EnableDBClick)
    SET_ATTR_BOOL           (IntercepMouse)
    SET_ATTR_BOOL           (TransparentMouse)
    SET_ATTR_END            ()

    return hRet ;
}
