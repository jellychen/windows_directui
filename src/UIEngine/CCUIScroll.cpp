#include "stdafx.h"
#include "CCUIScroll.h"

CCUIScroll::CCUIScroll()
{
	this->m_nOrientation		= SCROLL::VERTICAL ;
	this->m_szScrollBarMinSize	= CSize(15, 15) ;
	this->m_nScale				= 0 ;
	this->m_fPercentage			= 0 ;
	this->m_bEnableWheel		= FALSE ;
}

CCUIScroll::~CCUIScroll()
{

}

HRESULT CCUIScroll::FinalConstruct()
{
	Common::Util::CreateObject(&m_pScrollBar) ;
	DEBUG_ASSERT(m_pScrollBar) ;
	if (this->m_pScrollBar)
	{
		this->m_pScrollBar->SetFloat(TRUE) ;
		this->m_pScrollBar->SetSize(CSize(15, 15)) ;
		__self->AddChildBack(m_pScrollBar) ;
	}

	CComPtr<IUIBrush> _pBackDraw ;
	Common::Util::CreateObject(&_pBackDraw) ;
	if (_pBackDraw)
	{
		_pBackDraw->SetColor(RGB(200, 200, 200)) ;
		_pBackDraw->SetBrushType(BRUSH::RECT_FILL) ;
		__self->SetBkgDraw(_pBackDraw) ;
	}

	CComPtr<IUIBrush> _pBarBackDraw ;
	Common::Util::CreateObject(&_pBarBackDraw) ;
	if (_pBarBackDraw)
	{
		_pBarBackDraw->SetColor(RGB(150, 150, 150)) ;
		_pBarBackDraw->SetBrushType(BRUSH::RECT_FILL) ;
		__self->SetScrollBarNormalDraw(_pBarBackDraw) ;
	}

	CComPtr<IUIBrush> _pBarHoverBackDraw ;
	Common::Util::CreateObject(&_pBarHoverBackDraw) ;
	if (_pBarHoverBackDraw)
	{
		_pBarHoverBackDraw->SetColor(RGB(120, 120, 120)) ;
		_pBarHoverBackDraw->SetBrushType(BRUSH::RECT_FILL) ;
		__self->SetScrollBarHighlightDraw(_pBarHoverBackDraw) ;
	}

	CComPtr<IUIBrush> _pBarPushBackDraw ;
	Common::Util::CreateObject(&_pBarPushBackDraw) ;
	if (_pBarPushBackDraw)
	{
		_pBarPushBackDraw->SetColor(RGB(80, 80, 80)) ;
		_pBarPushBackDraw->SetBrushType(BRUSH::RECT_FILL) ;
		__self->SetScrollBarPushedDraw(_pBarPushBackDraw) ;
	}
	return S_OK ;
}

HRESULT CCUIScroll::SetOrientation(INT nOrientation)
{
	IF_RETURN(this->m_nOrientation == nOrientation, S_OK) ;

	this->m_nOrientation = nOrientation ;
	GetEntity<IUIFrameInternal>()->MarkRelayout() ;
	return S_OK ;
}

HRESULT CCUIScroll::SetOrientation(BSTR bstrOrientation)
{
	CString _cstrOrientation = bstrOrientation ;

	if (0 == _cstrOrientation.CompareNoCase(_T("HORIZONTAL")))
	{
		return __self->SetOrientation(SCROLL::HORIZONTAL) ;
	}
	else if (0 == _cstrOrientation.CompareNoCase(_T("VERTICAL")))
	{
		return __self->SetOrientation(SCROLL::VERTICAL) ;
	}

	return E_FAIL ;
}

HRESULT CCUIScroll::GetOrientation(INT* pnOrientation)
{
	DEBUG_ASSERT(pnOrientation) ;
	IF_RETURN(NULL == pnOrientation, E_INVALIDARG) ;

	*pnOrientation = this->m_nOrientation ;
	return S_OK ;
}

HRESULT CCUIScroll::SetEnableWheel(BOOL bEnableWheel)
{
	this->m_bEnableWheel = bEnableWheel ;
	return S_OK ;
}

HRESULT CCUIScroll::GetEnableWheel(BOOL* pbEnableWheel)
{
	DEBUG_ASSERT(pbEnableWheel) ;
	IF_RETURN(NULL == pbEnableWheel, E_INVALIDARG) ;

	*pbEnableWheel = this->m_bEnableWheel ;
	return S_OK ;
}

HRESULT CCUIScroll::SetPercentage(INT nPercetage)
{
	this->m_fPercentage = nPercetage ;
	return S_OK ;
}

HRESULT CCUIScroll::GetPercentage(INT* pnPercetage)
{
	DEBUG_ASSERT(pnPercetage) ;
	IF_RETURN(NULL == pnPercetage, E_INVALIDARG) ;

	*pnPercetage = this->m_fPercentage ;
	return S_OK ;
}

HRESULT CCUIScroll::SetScrollScale(INT nScale)
{
	this->m_nScale = nScale ;
	GetEntity<IUIFrameInternal>()->MarkRelayout() ;
	return S_OK ;
}

HRESULT CCUIScroll::GetScrollScale(INT* pnScale)
{
	DEBUG_ASSERT(pnScale) ;
	IF_RETURN(NULL == pnScale, E_INVALIDARG) ;

	*pnScale = this->m_nScale ;
	return S_OK ;
}

HRESULT CCUIScroll::SetScrollBarSize(SIZE szScrollBar)
{
	if (this->m_pScrollBar)
	{
		return this->m_pScrollBar->SetSize(szScrollBar) ;
	}
	return E_FAIL ;
}

HRESULT CCUIScroll::GetScrollBarSize(SIZE* pszScrollBar)
{
	if (this->m_pScrollBar)
	{
		return this->m_pScrollBar->GetSize(pszScrollBar) ;
	}
	return E_FAIL ;
}

HRESULT CCUIScroll::SetScrollBarMinSize(SIZE szScrollBar)
{
	this->m_szScrollBarMinSize = szScrollBar ;
	return S_OK ;
}

HRESULT CCUIScroll::GetScrollBarMinSize(SIZE* pszScrollBar)
{
	DEBUG_ASSERT(pszScrollBar) ;
	IF_RETURN(NULL == pszScrollBar, E_INVALIDARG) ;

	*pszScrollBar = this->m_szScrollBarMinSize ;
	return S_OK ;
}

HRESULT CCUIScroll::SetScrollBarNormalDraw(IUIDraw* pNormalDraw)
{
	if (this->m_pScrollBar)
	{
		return this->m_pScrollBar->SetNormalBkgDraw(pNormalDraw) ;
	}
	return E_FAIL ;
}

HRESULT CCUIScroll::GetScrollBarNormalDraw(IUIDraw** ppNormalDraw)
{
	DEBUG_ASSERT(ppNormalDraw) ;
	IF_RETURN(NULL == ppNormalDraw, E_INVALIDARG) ;
	*ppNormalDraw = NULL ;

	if (this->m_pScrollBar)
	{
		return this->m_pScrollBar->GetNormalBkgDraw(ppNormalDraw) ;
	}
	return E_FAIL ;
}

HRESULT CCUIScroll::SetScrollBarHighlightDraw(IUIDraw* pHighlightDraw)
{
	if (this->m_pScrollBar)
	{
		return this->m_pScrollBar->SetHighlightBkgDraw(pHighlightDraw) ;
	}
	return E_FAIL ;
}

HRESULT CCUIScroll::GetScrollBarHighlightDraw(IUIDraw** ppHighlightDraw)
{
	DEBUG_ASSERT(ppHighlightDraw) ;
	IF_RETURN(NULL == ppHighlightDraw, E_INVALIDARG) ;
	*ppHighlightDraw = NULL ;

	if (this->m_pScrollBar)
	{
		return this->m_pScrollBar->GetHighlightBkgDraw(ppHighlightDraw) ;
	}
	return E_FAIL ;
}

HRESULT CCUIScroll::SetScrollBarPushedDraw(IUIDraw* pPushedDraw)
{
	if (this->m_pScrollBar)
	{
		return this->m_pScrollBar->SetPushedBkgDraw(pPushedDraw) ;
	}
	return E_FAIL ;
}

HRESULT CCUIScroll::GetScrollBarPushedDraw(IUIDraw** ppPushedraw)
{
	DEBUG_ASSERT(ppPushedraw) ;
	IF_RETURN(NULL == ppPushedraw, E_INVALIDARG) ;
	*ppPushedraw = NULL ;

	if (this->m_pScrollBar)
	{
		return this->m_pScrollBar->GetPushedBkgDraw(ppPushedraw) ;
	}
	return E_FAIL ;
}

HRESULT CCUIScroll::CalcSize(SIZE szOld, SIZE* pszCalcOut)
{
	DEBUG_ASSERT(pszCalcOut) ;
	IF_RETURN(NULL == pszCalcOut, E_INVALIDARG) ;

	BOOL bAutoWidth = FALSE ;
	__self->GetAutoWidth(&bAutoWidth) ;
	BOOL bAutoHeight = FALSE ;
	__self->GetAutoHeight(&bAutoHeight) ;

	CSize szScrollBar(0, 0) ;
	if (this->m_pScrollBar)
	{
		this->m_pScrollBar->GetSize(&szScrollBar) ;
	}

	if (SCROLL::VERTICAL == this->m_nOrientation)
	{
		if (bAutoHeight)
		{
			*pszCalcOut = CSize(0, 0) ;
			DEBUG_ASSERT_MSG(FALSE, _T("vertical scroll not support auto_height...")) ;
			return E_FAIL ;
		}
		else
		{
			*pszCalcOut = szOld ;
			pszCalcOut->cx = szScrollBar.cx ;
			return S_OK ;
		}
	}
	else if (SCROLL::HORIZONTAL == this->m_nOrientation)
	{
		if (bAutoWidth)
		{
			*pszCalcOut = CSize(0, 0) ;
			DEBUG_ASSERT_MSG(FALSE, _T("horizontal scroll not support auto_width...")) ;
			return E_FAIL ;
		}
		else
		{
			*pszCalcOut = szOld ;
			pszCalcOut->cy = szScrollBar.cy ;
			return S_OK ;
		}
	}
	return S_OK ;
}

HRESULT CCUIScroll::Layout()
{
	__super::Layout() ;

	CSize _szScroll(0 ,0) ;
	__self->GetSize(&_szScroll) ;
	CSize _szScrollBar(0, 0) ;
	if (this->m_pScrollBar)
	{
		this->m_pScrollBar->GetSize(&_szScrollBar) ;
	}

	CRect _rcScrollBar(0, 0, 0, 0) ;
	CRect _rcScrollBarDragRange(0, 0, 0, 0) ;

	if (SCROLL::VERTICAL == this->m_nOrientation)
	{
		 INT _nScrollBarHeight= 0 ;
		 if (this->m_nScale <= _szScroll.cy)
		 {
			 _nScrollBarHeight = _szScroll.cy ;
		 }
		 else if (this->m_nScale > 0)
		 {
			_nScrollBarHeight = _szScroll.cy * _szScroll.cy / this->m_nScale ;
		 }

		 if (_nScrollBarHeight < this->m_szScrollBarMinSize.cy)
		 {
			_nScrollBarHeight = this->m_szScrollBarMinSize.cy ;
		 }

		_rcScrollBar.left	= (_szScroll.cx - _szScrollBar.cx) / 2 ;
		_rcScrollBar.right	= _rcScrollBar.left + _szScrollBar.cx ;
		_rcScrollBar.top	= (_szScroll.cy - _nScrollBarHeight) * this->m_fPercentage ;
		_rcScrollBar.bottom = _rcScrollBar.top + _nScrollBarHeight ;

		if (this->m_pScrollBar)
		{
			this->m_pScrollBar->SetEnableVerticalDrag(TRUE) ;
			this->m_pScrollBar->SetEnableHorizontalDrag(FALSE) ;

			CRect _rcDragRange(0, 0, 0, 0) ;
			_rcDragRange.top     = 0 ;
			_rcDragRange.bottom  = _szScroll.cy - _nScrollBarHeight ;
			this->m_pScrollBar->SetDragRange(_rcDragRange) ;
		}
	}
	else if (SCROLL::HORIZONTAL == this->m_nOrientation)
	{
		INT _nScrollBarWidth= 0 ;
		if (this->m_nScale <= _szScroll.cx)
		{
			_nScrollBarWidth = _szScroll.cx ;
		}
		else if (this->m_nScale > 0)
		{
			_nScrollBarWidth = _szScroll.cx * _szScroll.cx / this->m_nScale ;
		}

		if (_nScrollBarWidth < this->m_szScrollBarMinSize.cx)
		{
			_nScrollBarWidth = this->m_szScrollBarMinSize.cx ;
		}

		_rcScrollBar.top	= (_szScroll.cy - _szScrollBar.cy) / 2 ;
		_rcScrollBar.bottom = _rcScrollBar.top + _szScrollBar.cy ;
		_rcScrollBar.left	= (_szScroll.cx - _nScrollBarWidth) * this->m_fPercentage ;
		_rcScrollBar.right	= _rcScrollBar.left + _nScrollBarWidth ;

		if (this->m_pScrollBar)
		{
			this->m_pScrollBar->SetEnableVerticalDrag(FALSE) ;
			this->m_pScrollBar->SetEnableHorizontalDrag(TRUE) ;

			CRect _rcDragRange(0, 0, 0, 0) ;
			_rcDragRange.left	= 0 ;
			_rcDragRange.right  = _szScroll.cx - _nScrollBarWidth ;
			this->m_pScrollBar->SetDragRange(_rcDragRange) ;
		}
	}

	CComQIPtr<IUIFrameInternal> _pScrollBarInternal = this->m_pScrollBar ;
	if (this->m_pScrollBar && _pScrollBarInternal)
	{
		_pScrollBarInternal->SetLayoutRect(_rcScrollBar) ;
	}

	return S_OK ;
}

HRESULT CCUIScroll::SetAttribute(ICVarData* pAttrData)
{
	HRESULT hRet = __super::SetAttribute(pAttrData) ;
	SET_ATTR_CLASS_BEGIN    (pAttrData, CCUIScroll)
	SET_ATTR_BSTR           (Orientation)
	SET_ATTR_END            ()

	SET_ATTR_CLASS_BEGIN    (pAttrData, IUIScroll)
	SET_ATTR_BOOL           (EnableWheel)
	SET_ATTR_INT            (Percentage)
	SET_ATTR_INT            (ScrollScale)
	SET_ATTR_SIZE           (ScrollBarSize)
	SET_ATTR_SIZE           (ScrollBarMinSize)
	SET_ATTR_INTERFACE      (IUIDraw, ScrollBarNormalDraw)
	SET_ATTR_INTERFACE      (IUIDraw, ScrollBarHighlightDraw)
	SET_ATTR_INTERFACE      (IUIDraw, ScrollBarPushedDraw)
	SET_ATTR_END            ()

	return S_OK ;
}
