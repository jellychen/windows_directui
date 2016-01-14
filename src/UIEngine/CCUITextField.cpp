#include "stdafx.h"
#include "CCUITextField.h"

CCUITextField::CCUITextField()
{
	this->m_hTempeDC		= ::GetDC(NULL) ;
	this->m_hOldFont		= NULL ;
	this->m_nLineHeight		= 0 ;
	this->m_strEdit			= _T("") ;
	this->m_nMaxLength		= INT_MAX ;
	this->m_nLeftSelect		= 0 ;
	this->m_nRightSelect	= 0 ;
	this->m_bLeftButtonDwon	= FALSE ;
	this->m_bReadOnly		= FALSE ;
	this->m_bPasswd			= FALSE ;
	this->m_tcPasswdChar	= _T('●') ;
	this->m_bNumberOnly		= FALSE ;
	this->m_bWantTab		= TRUE ;
	this->m_bWantReturn		= TRUE ;
	this->m_bSingleLine		= FALSE ;
	this->m_ptLayoutOffset	= CPoint(0, 0) ;
	this->m_nCaretIndex		= 0 ;
	this->m_bCaretSide		= FALSE ;
	this->m_nCaretLine		= 0 ;
	this->m_nSelectLeft		= 0 ;
	this->m_bSelectLeftSide	= FALSE ;
	this->m_nSelectRight	= 0 ;
	this->m_bSelectRightSide= FALSE ;
	this->m_clrTextColor	= RGB(255, 255, 255) ;
	this->m_clrHighTextColor= RGB(255, 0, 0) ;
	this->m_clrHighTextMaskColor = RGB(0, 0, 0) ;
	this->m_nNeedFieldHeight= 0 ;
	this->m_bShowScroll		= FALSE ;
}

CCUITextField::~CCUITextField()
{
	if (this->m_hOldFont)
	{
		::SelectObject(this->m_hTempeDC, this->m_hOldFont) ;
	}
	if (this->m_hTempeDC)
	{
		::DeleteDC(this->m_hTempeDC) ;
	}
}

HRESULT CCUITextField::FinalConstruct()
{
	Common::Util::CreateObject(&m_pFont) ;
	DEBUG_ASSERT(m_pFont) ;
	Common::Util::CreateObject(&m_pCaret) ;
	DEBUG_ASSERT(this->m_pCaret) ;
	Common::Util::CreateObject(&m_pScroll) ;
	DEBUG_ASSERT(this->m_pScroll) ;

	__self->SetDoubleBuffer(TRUE) ;
	__self->SetHoverCursor(UI::CURSOR::EM_CURSOR_IBEAM) ;
	__self->SetPadding(CRect(4, 4, 4, 4)) ;

	if (this->m_pFont)
	{
		this->m_pFont->SetHeight(-16) ;
		HFONT _hFont = NULL ;
		this->m_pFont->GetHFont(&_hFont) ;
		this->m_hOldFont = (HFONT)::SelectObject(m_hTempeDC, _hFont) ;
	}

	if (this->m_pCaret)
	{
		this->m_pCaret->SetSize(CSize(2, 20)) ;
		this->m_pCaret->SetFloat(TRUE) ;
		__self->AddChildBack(this->m_pCaret) ;
	}

	if (this->m_pScroll)
	{
		this->m_pScroll->SetFloat(TRUE) ;
		this->m_pScroll->SetAutoWidth(TRUE) ;
		this->m_pScroll->SetOrientation(SCROLL::VERTICAL) ;
		this->m_pScroll->SetHidden(TRUE) ;
		__self->AddChildBack(this->m_pScroll) ;
	}
	return S_OK ;
}

HRESULT CCUITextField::SetFont(IUIFont* pFont)
{
	DEBUG_ASSERT(pFont) ;
	IF_RETURN(NULL == pFont, E_INVALIDARG) ;

	this->m_pFont = pFont ;
	this->ReChar() ;
	this->LayoutChar() ;
	__self->Invalidate() ;
	return S_OK ;
}

HRESULT CCUITextField::GetFont(IUIFont** ppFont)
{
	DEBUG_ASSERT(ppFont) ;
	IF_RETURN(NULL == ppFont, E_INVALIDARG) ;
	*ppFont = NULL ;
	
	if (this->m_pFont)
	{
		return this->m_pFont->QueryInterface(__uuidof(IUIFont), (VOID**)ppFont) ;
	}
	return E_FAIL ;
}

HRESULT CCUITextField::SetLineHeight(INT nLineHeight)
{
	if (this->m_nLineHeight != nLineHeight)
	{
		this->m_nLineHeight = nLineHeight ;
		this->LayoutChar() ;
		__self->Invalidate() ;
	}
	return S_OK ;
}

HRESULT CCUITextField::GetLineHeight(INT* pnLineHeight)
{
	DEBUG_ASSERT(pnLineHeight) ;
	IF_RETURN(NULL == pnLineHeight, E_INVALIDARG) ;

	*pnLineHeight = this->m_nLineHeight ;
	return S_OK ;
}

HRESULT CCUITextField::SetReadOnly(BOOL bReadOnly)
{
	this->m_bReadOnly = bReadOnly ;
	return S_OK ;
}

HRESULT CCUITextField::GetReadOnly(BOOL* pbReadOnly)
{
	DEBUG_ASSERT(pbReadOnly) ;
	IF_RETURN(NULL == pbReadOnly, E_INVALIDARG) ;

	*pbReadOnly = this->m_bReadOnly ;
	return S_OK ;
}

HRESULT CCUITextField::SetMaxLength(INT nMaxLength)
{
	this->m_nMaxLength = nMaxLength ;
	return S_OK ;
}

HRESULT CCUITextField::GetMaxLength(INT* pnMaxLength)
{
	DEBUG_ASSERT(pnMaxLength) ;
	IF_RETURN(NULL == pnMaxLength, E_INVALIDARG) ;
	*pnMaxLength = this->m_nMaxLength ;
	return S_OK ;
}

HRESULT CCUITextField::SetPassWord(BOOL bPassWord)
{
	this->m_bPasswd = bPassWord ;
	return S_OK ;
}

HRESULT CCUITextField::GetPassWord(BOOL* pbPassWord)
{
	DEBUG_ASSERT(pbPassWord) ;
	IF_RETURN(NULL == pbPassWord, E_INVALIDARG) ;

	*pbPassWord = this->m_bPasswd ;
	return S_OK ;
}

HRESULT CCUITextField::SetOnlyNumber(BOOL bOnlyNumber)
{
	this->m_bNumberOnly = bOnlyNumber ;
	return S_OK ;
}

HRESULT CCUITextField::GetOnlyNumber(BOOL* pbOnlyNumber)
{
	DEBUG_ASSERT(pbOnlyNumber) ;
	IF_RETURN(NULL == pbOnlyNumber, E_INVALIDARG) ;

	*pbOnlyNumber = this->m_bNumberOnly ;
	return S_OK ;
}

HRESULT CCUITextField::SetEnableIME(BOOL bEnableIME)
{
	this->m_bEnableIME = bEnableIME ;
	return S_OK ;
}

HRESULT CCUITextField::GetEnableIME(BOOL* pbEnableIME)
{
	DEBUG_ASSERT(pbEnableIME) ;
	IF_RETURN(NULL == pbEnableIME, E_INVALIDARG) ;

	*pbEnableIME = this->m_bEnableIME ;
	return S_OK ;
}

HRESULT CCUITextField::SetWantTab(BOOL bWantTab)
{
	this->m_bWantTab = bWantTab ;
	return S_OK ;
}

HRESULT CCUITextField::GetWantTab(BOOL* pbWantTab)
{
	DEBUG_ASSERT(pbWantTab) ;
	IF_RETURN(NULL == pbWantTab, E_INVALIDARG) ;

	*pbWantTab = this->m_bWantTab ;
	return S_OK ;
}

HRESULT CCUITextField::SetWantReturn(BOOL bWantReturn)
{
	this->m_bWantReturn = bWantReturn ;
	return S_OK ;
}

HRESULT CCUITextField::GetWantReturn(BOOL* pbWantReturn)
{
	DEBUG_ASSERT(pbWantReturn) ;
	IF_RETURN(NULL == pbWantReturn, E_INVALIDARG) ;
	*pbWantReturn = this->m_bWantReturn ;
	return S_OK ;
}

HRESULT CCUITextField::SetSingleLine(BOOL bSingleLine)
{
	this->m_bSingleLine = bSingleLine ;
	this->LayoutChar() ;
	__self->Invalidate() ;
	return S_OK ;
}

HRESULT CCUITextField::GetSingleLine(BOOL* pbSingleLine)
{
	DEBUG_ASSERT(pbSingleLine) ;
	IF_RETURN(NULL == pbSingleLine, E_INVALIDARG) ;

	*pbSingleLine = this->m_bSingleLine ;
	return S_OK ;
}

HRESULT CCUITextField::SetTextColor(COLORREF clrText)
{
	this->m_clrTextColor = clrText ;
	__self->Invalidate() ;
	return S_OK ;
}

HRESULT CCUITextField::GetTextColor(COLORREF* pclrText)
{
	DEBUG_ASSERT(pclrText) ;
	IF_RETURN(NULL == pclrText, E_INVALIDARG) ;

	*pclrText = this->m_clrTextColor ;
	return S_OK ;
}

HRESULT CCUITextField::SetHighTextColor(COLORREF clrText)
{
	this->m_clrHighTextColor = clrText ;
	__self->Invalidate() ;
	return S_OK ;
}

HRESULT CCUITextField::GetHighTextColor(COLORREF* pclrText)
{
	DEBUG_ASSERT(pclrText) ;
	IF_RETURN(NULL == pclrText, E_INVALIDARG) ;

	*pclrText = this->m_clrHighTextColor ;
	return S_OK ;
}

HRESULT CCUITextField::SetHightMaskColor(COLORREF clrMask)
{
	this->m_clrHighTextMaskColor = clrMask ;
	__self->Invalidate() ;
	return S_OK ;
}

HRESULT CCUITextField::GetHightMaskColor(COLORREF* pclrMask)
{
	DEBUG_ASSERT(pclrMask) ;
	IF_RETURN(NULL == pclrMask, E_INVALIDARG) ;

	*pclrMask = this->m_clrHighTextMaskColor ;
	return S_OK ;
}

HRESULT CCUITextField::SetPassWordChar(TCHAR tcReplace)
{
	this->m_tcPasswdChar = tcReplace ;
	this->ReChar() ;
	this->LayoutChar() ;
	__self->Invalidate() ;
	return S_OK ;
}

HRESULT CCUITextField::GetPassWordChar(TCHAR* ptcReplace)
{
	DEBUG_ASSERT(ptcReplace) ;
	IF_RETURN(NULL == ptcReplace, E_INVALIDARG) ;

	*ptcReplace = this->m_tcPasswdChar ;
	return S_OK ;
}

HRESULT CCUITextField::SetText(BSTR bstrText)
{
	this->m_strEdit = bstrText ;
	this->m_strEdit.Remove(_T('\r')) ;
	this->ReChar() ;
	this->LayoutChar() ;
	__self->Invalidate() ;
	return S_OK ;
}

HRESULT CCUITextField::GetText(BSTR* pbstrText)
{
	DEBUG_ASSERT(pbstrText) ;
	IF_RETURN(NULL == pbstrText, E_INVALIDARG) ;
	CComBSTR bstrText(this->m_strEdit) ;
	return bstrText.CopyTo(pbstrText) ;
}


//HRESULT CCUITextField::GetSelectText(BSTR* pbstrText)
//{
//	DEBUG_ASSERT(pbstrText) ;
//	IF_RETURN(NULL == pbstrText, E_INVALIDARG) ;
//
//	INT _nLeft = 0, _nRight = 0 ;
//	this->CalcSelectRange(&_nLeft, &_nRight) ;
//	CString _str = m_strEdit.Left(_nLeft) 
//		+ m_strEdit.Right(m_strEdit.GetLength() - _nRight) ;
//	CComBSTR _comStr(_str) ;
//	_comStr.CopyTo(pbStrText) ;
//	return S_OK ;
//}

HRESULT CCUITextField::SetSelectRange(INT nLeft, INT nRight)
{
	if (nLeft <= 0) 
	{
		nLeft = 0 ;
	}
	else if (nLeft > this->m_strEdit.GetLength() - 1)
	{
		nLeft = this->m_strEdit.GetLength() - 1 ;
	}

	if (nRight <= 0) 
	{
		nRight = 0 ;
	}
	else if (nRight > this->m_strEdit.GetLength() - 1)
	{
		nRight = this->m_strEdit.GetLength() - 1 ;
	}

	this->m_nSelectLeft		= nLeft ;
	this->m_bSelectLeftSide = FALSE ;
	this->m_nSelectRight	= nRight ;
	this->m_bSelectRightSide= TRUE ;
	return S_OK ;
}

HRESULT CCUITextField::GetSelectRange(INT* pnLeft, INT* pnRight)
{
	this->CalcSelectRange(pnLeft, pnRight) ;
	return S_OK ;
}

HRESULT CCUITextField::SetScroll(IUIScroll* pScroll)
{
	this->m_pScroll = pScroll ;
	this->LayoutChar() ;
	__self->Invalidate() ;
	return S_OK ;
}

HRESULT CCUITextField::GetScroll(IUIScroll** ppScroll)
{
	DEBUG_ASSERT(ppScroll) ;
	IF_RETURN(NULL == ppScroll, E_INVALIDARG) ;
	*ppScroll = NULL ;

	if (this->m_pScroll)
	{
		return this->m_pScroll->QueryInterface(__uuidof(IUIScroll), (VOID**)ppScroll) ;
	}
	return S_OK ;
}

HRESULT CCUITextField::Layout()
{
	CSize _szTextField(0, 0) ;
	__self->GetSize(&_szTextField) ;
	if (_szTextField != this->m_szTextFieldSize)
	{
		this->m_szTextFieldSize = _szTextField ;
		this->LayoutChar() ;
		this->MoveCaretIndex(m_nCaretIndex, m_bCaretSide) ;
		this->MakeSureCaretInScrope() ;
	}
	return S_OK ;
}

HRESULT CCUITextField::Render(IUICanvas* pCanvas, RECT rcRender, INT nState)
{
	__super::Render(pCanvas, rcRender, nState) ;
	IF_RETURN(NULL == this->m_pFont, E_FAIL) ;
	CComQIPtr<IUIFrameInternal> _pInternal = GetEntity<IUIFrameInternal>() ;
	DEBUG_ASSERT(_pInternal) ;
	IF_RETURN(NULL == _pInternal, E_FAIL) ;

	CRect _rcPadding(0, 0, 0, 0) ;
	__self->GetPadding(&_rcPadding) ;
	CRect _rcExtPadding(0, 0, 0, 0) ;
	_pInternal->GetExtPadding(&_rcExtPadding) ;
	CSize _szRender(0, 0) ;
	__self->GetSize(&_szRender) ;
	CRect _rcRender(0, 0, _szRender.cx, _szRender.cy) ;
	_rcRender.left	+= _rcPadding.left + _rcExtPadding.left ;
	_rcRender.right	-= _rcPadding.right + _rcExtPadding.right ;
	_rcRender.top	+= _rcPadding.top + _rcExtPadding.top ;
	_rcRender.bottom-= _rcPadding.bottom + _rcExtPadding.bottom ;

	CRect _rcRgn(0, 0, 0, 0) ;
	HRGN _hRgn = ::CreateRectRgnIndirect(&_rcRgn) ;
	pCanvas->GetClipRgn(&_hRgn) ;
	pCanvas->SetCombineRect(_rcRender, RGN_AND) ;

	HDC _hCanvasDC = NULL ;
	pCanvas->GetCanvasDC(&_hCanvasDC) ;
	LOGFONT _log_font ;
	DWORD _dwFontDrawType = Gdiplus::TextRenderingHintAntiAlias  ;
	this->m_pFont->GetDrawType(&_dwFontDrawType) ;
	this->m_pFont->GetLogFont(&_log_font) ;
	Gdiplus::FontFamily _font_family(_log_font.lfFaceName);
	Gdiplus::Font _font(_hCanvasDC, &_log_font) ;
	Gdiplus::StringFormat _string_format ;
	_string_format.SetFormatFlags(Gdiplus::StringFormatFlagsMeasureTrailingSpaces) ;
	_string_format.SetAlignment(Gdiplus::StringAlignmentCenter) ;
	_string_format.SetLineAlignment(Gdiplus::StringAlignmentNear) ;
	Gdiplus::Graphics _graphic(_hCanvasDC) ;
	_graphic.SetSmoothingMode(Gdiplus::SmoothingModeHighQuality) ;
	_graphic.SetTextRenderingHint((Gdiplus::TextRenderingHint)_dwFontDrawType) ;

	Gdiplus::SolidBrush _burshText(Gdiplus::Color
		(255, GetRValue(m_clrTextColor), GetGValue(m_clrTextColor), GetBValue(m_clrTextColor))) ;
	Gdiplus::SolidBrush _burshHighText(Gdiplus::Color
		(255, GetRValue(m_clrHighTextColor), GetGValue(m_clrHighTextColor), GetBValue(m_clrHighTextColor))) ;
	Gdiplus::SolidBrush _burshHighTextMask(Gdiplus::Color
		(100, GetRValue(m_clrHighTextMaskColor), GetGValue(m_clrHighTextMaskColor), GetBValue(m_clrHighTextMaskColor))) ;

	CPoint _ptLeftTop = this->CalcRenderRect().TopLeft() ;
	_ptLeftTop.x -= this->m_ptLayoutOffset.x ;
	_ptLeftTop.y -= this->m_ptLayoutOffset.y ;

	// 纠正下选择区域
	INT _nSelectLeft = 0, _nSelectRight = 0 ;
	this->CalcSelectRange(&_nSelectLeft, &_nSelectRight) ;

	CPoint _ptRenderTemp = _ptLeftTop ;
	for (INT i = 0; i < (INT)this->m_vecVertical.size(); ++i)
	{
		INT _left = this->m_vecVertical[i].m_nLeftIndex ;
		INT _right = this->m_vecVertical[i].m_nRightIndex ;
		INT _maxHeight = this->m_vecVertical[i].m_nMaxHeight ;
		
		Gdiplus::RectF _mask_rc ; BOOL _bmask_start = FALSE ;
		for (INT j = _left; j <= _right; ++j)
		{
			if (j >= _nSelectLeft && j < _nSelectRight)
			{
				if (FALSE == _bmask_start)
				{
					_mask_rc.X		= _ptRenderTemp.x ;
					_mask_rc.Y		= _ptRenderTemp.y ;
					_mask_rc.Height	= _maxHeight ;
					_mask_rc.Width	= this->m_vecChar[j].m_szChar.cx ;
					_bmask_start = TRUE ;
				}
				else
				{
					_mask_rc.Width	= _ptRenderTemp.x - _mask_rc.X + this->m_vecChar[j].m_szChar.cx ;
				}
			}
			_ptRenderTemp.x += this->m_vecChar[j].m_szChar.cx ;
		}
		_graphic.FillRectangle(&_burshHighTextMask, _mask_rc) ;
		_ptRenderTemp.x = _ptLeftTop.x ;
		_ptRenderTemp.y += _maxHeight ;
	}
	
	_ptRenderTemp = _ptLeftTop ;
	for (INT i = 0; i < (INT)this->m_vecVertical.size(); ++i)
	{
		INT _left = this->m_vecVertical[i].m_nLeftIndex ;
		INT _right = this->m_vecVertical[i].m_nRightIndex ;
		INT _maxHeight = this->m_vecVertical[i].m_nMaxHeight ;
		INT _lineHeight = this->m_vecVertical[i].m_nLineHeight ;
		for (INT j = _left; j <= _right; ++j)
		{
			if (_T('\r') != this->m_vecChar[j].m_tcChar 
					&& _T('\n') != this->m_vecChar[j].m_tcChar
						&& _T('\t') != this->m_vecChar[j].m_tcChar)
			{
				Gdiplus::RectF _rect ;
				_rect.X		= _ptRenderTemp.x ;
				_rect.Y		= _ptRenderTemp.y + (_maxHeight - _lineHeight)/2 + _lineHeight - this->m_vecChar[j].m_szChar.cy ;
				_rect.Width	= this->m_vecChar[j].m_szChar.cx ;
				_rect.Height= this->m_vecChar[j].m_szChar.cy ;
				
				if (j >= _nSelectLeft && j < _nSelectRight)
				{
					_graphic.DrawString(CString(this->m_vecChar[j].m_tcChar), 1, &_font, _rect, &_string_format, &_burshHighText) ;
				}
				else
				{
					_graphic.DrawString(CString(this->m_vecChar[j].m_tcChar), 1, &_font, _rect, &_string_format, &_burshText) ;
				}
			}
			_ptRenderTemp.x += this->m_vecChar[j].m_szChar.cx ;
		}

		_ptRenderTemp.x = _ptLeftTop.x ;
		_ptRenderTemp.y += _maxHeight ;
	}

	pCanvas->SetClipRgn(_hRgn) ;
	::DeleteObject(_hRgn) ;
	return S_OK ;
}

HRESULT CCUITextField::OnMessage(IUIFrame* pTarget, tMsgArg* pArg)
{
	__super::OnMessage(pTarget, pArg) ;
	IF_RETURN(NULL == pArg, E_FAIL) ;
	switch(pArg->dwMsgId)
	{
	case MESSAGE::UI_KEYDOWN:
		this->OnKeyDown(pTarget, pArg) ;
		break ;
	case MESSAGE::UI_KEYUP:
		this->OnKeyUp(pTarget, pArg) ;
		break ;
	case MESSAGE::UI_CHAR:
		this->OnChar(pTarget, pArg) ;
		break ;
	case MESSAGE::UI_LBTNDOWN:
		this->OnLButtonDown(pTarget, pArg) ;
		break ;
	case MESSAGE::UI_LBTNUP:
		this->OnLButtonUp(pTarget, pArg) ;
		break ;
	case MESSAGE::UI_MOUSEMOVE:
		this->OnMouseMove(pTarget, pArg) ;
		break ;
	case MESSAGE::UI_IME_STARTCOMPOSITION:
		this->OnImeStartComposition(pTarget, pArg) ;
		break ;
	}
	return S_OK ;
}

HRESULT CCUITextField::SetPadding(RECT rcPadding)
{
	return __super::SetPadding(CRect(2, 2, 2, 2)) ;
}

HRESULT CCUITextField::ControlFocusChange(BOOL bFoucs)
{
	__super::ControlFocusChange(bFoucs) ;
	if (bFoucs)
	{
		this->m_pCaret->ShowCaret() ;
	}
	else
	{
		this->ClearSelectRange() ;
		this->m_pCaret->HideCaret() ;
	}
	return S_OK ;
}

BOOL CCUITextField::ReChar()
{
	for (int i = 0; i < this->m_strEdit.GetLength(); ++i)
	{
		_TextNode _node ;
		this->CalcCharInfo(this->m_strEdit[i], _node) ;
		this->m_vecChar.push_back(_node) ;
	}
	return S_OK ;
}

BOOL CCUITextField::LayoutChar()
{
	this->m_vecVertical.clear() ;
	CRect _rectRender = this->CalcRenderRect() ;

	_TextVerticalInfo _info ;
	INT _strDefaultHeight = this->CalcDefautCharSize().cy ;
	INT _strLen = 0, _strStart = 0 ;
	INT	_strMaxHeight = _strDefaultHeight ;

	if (this->m_bSingleLine)
	{
		for (INT i = 0; i < (INT)this->m_vecChar.size(); ++i)
		{
			if (this->m_vecChar[i].m_szChar.cy > _strMaxHeight)
			{
				_strMaxHeight = this->m_vecChar[i].m_szChar.cy ;
			}
		}
		
		_info.m_nLeftIndex	= _strStart ;
		_info.m_nRightIndex	= (INT)this->m_vecChar.size() -1 ;
		_info.m_nLineHeight = _strMaxHeight ;
		_info.m_nMaxHeight	= _strMaxHeight ;
		if (this->m_nLineHeight > _strMaxHeight)
		{
			_info.m_nMaxHeight = this->m_nLineHeight ;
		}

		this->m_vecVertical.push_back(_info) ;
		this->m_bShowScroll = FALSE ;
		this->m_nNeedFieldHeight = _info.m_nMaxHeight ;

		if (this->m_pScroll)
		{
			this->m_pScroll->SetHidden(TRUE) ;
		}
	}
	else
	{
		BOOL _bNeedScroll = FALSE ;
		INT _iCurrentLayoutHeight = 0 ;
		for (INT i = 0; i < (INT)this->m_vecChar.size(); ++i)
		{
			_strLen += this->m_vecChar[i].m_szChar.cx ;
			if (this->m_vecChar[i].m_szChar.cy > _strMaxHeight)
			{
				_strMaxHeight = this->m_vecChar[i].m_szChar.cy ;
			}

			if (_T('\r') == this->m_vecChar[i].m_tcChar)
			{
				continue ;
			}

			BOOL bHaveNext = FALSE ;
			if (i < (INT)this->m_vecChar.size()-1)
			{
				bHaveNext = TRUE ;
			}

			if ((_strLen <= _rectRender.Width() 
				&& ((bHaveNext && _strLen + m_vecChar[i+1].m_szChar.cx > _rectRender.Width()) || !bHaveNext))
				|| ((_strLen > _rectRender.Width()) && i == _strStart)
				|| (this->m_bWantReturn && _T('\n') == this->m_vecChar[i].m_tcChar))
			{
				_info.m_nLeftIndex	= _strStart ;
				_info.m_nRightIndex = i ;
				_info.m_nLineHeight = _strMaxHeight ;
				_info.m_nMaxHeight	= _strMaxHeight ;
				if (this->m_nLineHeight > _strMaxHeight)
				{
					_info.m_nMaxHeight = this->m_nLineHeight ;
				}
				this->m_vecVertical.push_back(_info) ;
				_iCurrentLayoutHeight += _info.m_nMaxHeight ;

				_strStart			= i + 1 ;
				_strLen				= 0 ;
				_strMaxHeight		= _strDefaultHeight ;
			}

			if (_iCurrentLayoutHeight > _rectRender.Height())
			{
				_bNeedScroll = TRUE ;
				break ;
			}
		}
		this->m_nNeedFieldHeight = _iCurrentLayoutHeight ;

		_iCurrentLayoutHeight = 0 ;
		if (_bNeedScroll)
		{
			this->m_vecVertical.clear() ;
			_strLen = 0; _strStart = 0 ;
			_strMaxHeight = _strDefaultHeight ;

			CSize _szScroll(0, 0) ;
			if (this->m_pScroll)
			{
				this->m_pScroll->GetSize(&_szScroll) ;
			}
			_rectRender.right -= _szScroll.cx ;

			for (INT i = 0; i < (INT)this->m_vecChar.size(); ++i)
			{
				_strLen += this->m_vecChar[i].m_szChar.cx ;
				if (this->m_vecChar[i].m_szChar.cy > _strMaxHeight)
				{
					_strMaxHeight = this->m_vecChar[i].m_szChar.cy ;
				}

				if (_T('\r') == this->m_vecChar[i].m_tcChar)
				{
					continue ;
				}

				BOOL bHaveNext = FALSE ;
				if (i < (INT)this->m_vecChar.size()-1)
				{
					bHaveNext = TRUE ;
				}

				if ((_strLen <= _rectRender.Width() 
					&& ((bHaveNext && _strLen + m_vecChar[i+1].m_szChar.cx > _rectRender.Width()) || !bHaveNext))
					|| ((_strLen > _rectRender.Width()) && i == _strStart)
					|| (this->m_bWantReturn && _T('\n') == this->m_vecChar[i].m_tcChar))
				{
					_info.m_nLeftIndex	= _strStart ;
					_info.m_nRightIndex = i ;
					_info.m_nLineHeight = _strMaxHeight ;
					_info.m_nMaxHeight	= _strMaxHeight ;
					if (this->m_nLineHeight > _strMaxHeight)
					{
						_info.m_nMaxHeight = this->m_nLineHeight ;
					}
					this->m_vecVertical.push_back(_info) ;
					_iCurrentLayoutHeight += _info.m_nMaxHeight ;

					_strStart			= i + 1 ;
					_strLen				= 0 ;
					_strMaxHeight		= _strDefaultHeight ;
				}
			}

			if (this->m_pScroll)
			{
				CSize _szScroll(0, 0) ;
				this->m_pScroll->SetHidden(FALSE) ;
				this->m_pScroll->GetSize(&_szScroll) ;
				
				_szScroll.cy = _rectRender.Height() ;
				this->m_pScroll->SetSize(_szScroll) ;
				
				CPoint _ptScroll(0, 0) ;
				_ptScroll.x = _rectRender.right ;
				_ptScroll.y = _rectRender.top ;
				this->m_pScroll->SetLocation(_ptScroll) ;
				this->m_pScroll->SetScrollScale(_iCurrentLayoutHeight) ;
			}
		}
		else if (this->m_pScroll)
		{
			this->m_pScroll->SetHidden(TRUE) ;
		}

		this->m_bShowScroll = _bNeedScroll ;
		this->m_nNeedFieldHeight = _iCurrentLayoutHeight ;
	}
	return TRUE ;
}

CRect CCUITextField::CalcRenderRect()
{
	CComQIPtr<IUIFrameInternal> _pInternal = GetEntity<IUIFrameInternal>() ;
	DEBUG_ASSERT(_pInternal) ;
	IF_RETURN(NULL == _pInternal, CRect(0, 0, 0, 0)) ;
	CRect _rcRect(0, 0, 0, 0) ;
	_pInternal->GetLayoutRect(&_rcRect) ;
	CSize _szSize(_rcRect.Width(), _rcRect.Height()) ;
	CRect _rcPadding(0, 0, 0, 0) ;
	__self->GetPadding(&_rcPadding) ;
	CRect _rcExtPadding(0, 0, 0, 0) ;
	_pInternal->GetExtPadding(&_rcExtPadding) ;

	CRect _rcLeft(0, 0, 0, 0) ;
	_rcLeft.left	= _rcPadding.left + _rcExtPadding.left ;
	_rcLeft.top		= _rcPadding.top + _rcExtPadding.top ;
	_rcLeft.right	= _szSize.cx - _rcExtPadding.right - _rcPadding.right ;
	_rcLeft.bottom	= _szSize.cy - _rcExtPadding.bottom - _rcPadding.bottom ;

	return _rcLeft ;
}

CSize CCUITextField::CalcDefautCharSize()
{
	return this->CalcCharSize(_T('A')) ;
}

BOOL CCUITextField::CanVisibleChar(TCHAR tcChar)
{
	if (_T('\r') != tcChar && _T('\n') != tcChar)
	{
		return TRUE ;
	}
	return FALSE ;
}

CSize CCUITextField::CalcCharSize(TCHAR tcChar)
{
	if (_T('\r') != tcChar && _T('\t') != tcChar)
	{
		CSize _szCalcOut(0, 0) ;
		TCHAR _str[2] ; _str[0] = tcChar, _str[1] = _T('\0') ;
		::GetTextExtentPoint32(this->m_hTempeDC, _str, 1, &_szCalcOut) ;
		_szCalcOut.cx += 1 ;
		_szCalcOut.cy += 1 ;
		return _szCalcOut ;
	}
	else if (_T('\t') == tcChar)
	{
		CSize _szDefault = this->CalcDefautCharSize() ;
		_szDefault.cx *= 4 ;
		return _szDefault ;
	}
	else if (_T('\n') != tcChar )
	{
		return CSize(1, 0) ;
	}
	else
	{
		return CSize(0, 0) ;
	}
}

BOOL CCUITextField::CalcCharInfo(TCHAR tcChar, _TextNode& _node)
{
	_node.m_tcChar = tcChar ;
	_node.m_szChar = this->CalcCharSize(tcChar) ;
	return TRUE ;
}

INT	CCUITextField::CalcCharIndex(INT x, INT y, BOOL* pbSide, INT* pLine, INT* pCaretTop, INT* pCaretLeft)
{
	CRect _renderRect = this->CalcRenderRect() ;
	x -= _renderRect.left - this->m_ptLayoutOffset.x ;
	y -= _renderRect.top - this->m_ptLayoutOffset.y ;
	x = x > 0 ? x : 0 ;
	y = y > 0 ? y : 0 ;

	BOOL _bSide = FALSE ;
	INT _nH = 0, _nHTemp = 0 ; BOOL _bFindH = FALSE ;
	for (INT i = 0; i < (INT)this->m_vecVertical.size(); ++i)
	{
		_nH = i ;
		if (y >= _nHTemp && y < _nHTemp + this->m_vecVertical[i].m_nMaxHeight)
		{
			_bFindH = TRUE ;
			break ;	
		}

		if (i != this->m_vecVertical.size() - 1)
		{
			_nHTemp += this->m_vecVertical[i].m_nMaxHeight ;
		}
	}

	BOOL _bShouldCheckV = TRUE ;
	if (FALSE == _bFindH
			&& this->m_vecChar.size() > 0
				&& _T('\n') == this->m_vecChar[this->m_vecChar.size() -1].m_tcChar)
	{
		_nH++ ;
		_bSide = TRUE ;
		_bShouldCheckV = FALSE ;
		_nHTemp += this->m_vecVertical[this->m_vecVertical.size() -1].m_nMaxHeight ;
	}

	INT _nV = 0, _nVTemp = 0 ;
	if (_bShouldCheckV)
	{
		if (_nH < (INT)this->m_vecVertical.size())
		{
			_nV = this->m_vecVertical[_nH].m_nLeftIndex ;
			for (INT i = m_vecVertical[_nH].m_nLeftIndex; i <= m_vecVertical[_nH].m_nRightIndex; ++i)
			{
				if (i ==  m_vecVertical[_nH].m_nRightIndex && _T('\n') == this->m_vecChar[i].m_tcChar)
				{
					break ;
				}

				if (_nVTemp + m_vecChar[i].m_szChar.cx/2 < x && _nVTemp + m_vecChar[i].m_szChar.cx >= x)
				{
					_nV = i ;
					_bSide = TRUE ;
					_nVTemp += this->m_vecChar[i].m_szChar.cx ;
					break ;
				}
				else if (x < _nVTemp + m_vecChar[i].m_szChar.cx/2)
				{
					if (i > this->m_vecVertical[_nH].m_nLeftIndex)
					{
						_nV = i ;
					}
					else
					{
						_nV = this->m_vecVertical[_nH].m_nLeftIndex ;
					}
					_bSide = FALSE ;
					break ;
				}
				_nV = i ;
				_bSide = TRUE ;
				_nVTemp += this->m_vecChar[i].m_szChar.cx ;
			}
		}
	}

	if (pbSide)
	{
		*pbSide = _bSide ;
	}

	if (pLine)
	{
		*pLine = _nH ;
	}

	if (pCaretTop)
	{
		*pCaretTop = _nHTemp + _renderRect.top - this->m_ptLayoutOffset.y ;
	}

	if (pCaretLeft)
	{
		*pCaretLeft = _nVTemp + _renderRect.left - this->m_ptLayoutOffset.x ;
	}

	if (_bShouldCheckV)
	{
		return _nV ;
	}

	return (INT)this->m_vecChar.size() -1 ;
}

BOOL CCUITextField::MoveCaretIndex(INT nIndex, BOOL bSide, BOOL bRight)
{
	INT		_nLine = 0 ;
	CSize	_szCaret(0, 0) ;
	CPoint	_ptCaret(0, 0) ;
	CRect	_renderRect = this->CalcRenderRect() ;
	if (0 == this->m_vecChar.size())
	{
		_szCaret.cx = 2 ;
		_szCaret.cy = this->CalcDefautCharSize().cy ;
		
		if (this->m_nLineHeight > _szCaret.cy)
		{
			_szCaret.cy = this->m_nLineHeight ;
		}

		_ptCaret.x = _renderRect.left - this->m_ptLayoutOffset.x ;
		_ptCaret.y = _renderRect.top - this->m_ptLayoutOffset.y ;
	}
	else if ((INT)this->m_vecChar.size() > nIndex)
	{
		BOOL _bCalcCaret = TRUE ;
		if (_T('\n') == this->m_vecChar[nIndex].m_tcChar && bSide)
		{
			if (bRight)
			{
				if (nIndex < (INT)this->m_vecChar.size() -1)
				{
					bSide = FALSE ;
					nIndex = nIndex +1 ;
				}
				else
				{
					_bCalcCaret = FALSE ;
				}
			}
			else
			{
				if (nIndex > 0)
				{
					bSide = TRUE ;
					nIndex = nIndex - 1 ;
				}
				else
				{
					_bCalcCaret = FALSE ;
				}
			}
		}

		if (_bCalcCaret)
		{
			for (INT i = 0; i < (INT)this->m_vecVertical.size(); ++i)
			{
				if (nIndex >= this->m_vecVertical[i].m_nLeftIndex
					&& nIndex <= this->m_vecVertical[i].m_nRightIndex)
				{
					_nLine = i ;
					break ;
				}
				_ptCaret.y += this->m_vecVertical[i].m_nMaxHeight ;
			}

			_szCaret.cx = 2 ;
			_szCaret.cy = this->m_vecVertical[_nLine].m_nMaxHeight ;
			
			for (INT i = m_vecVertical[_nLine].m_nLeftIndex; 
					i <= m_vecVertical[_nLine].m_nRightIndex && i <= nIndex; ++i)
			{
				if (i == nIndex && FALSE == bSide)
				{
					break ;
				}
				_ptCaret.x += this->m_vecChar[i].m_szChar.cx ;
			}
		}
		else
		{
			_ptCaret.x = 0 ;
			_szCaret.cx = 2 ;
			_szCaret.cy = this->CalcDefautCharSize().cy ;

			if (this->m_nLineHeight > _szCaret.cy)
			{
				_szCaret.cy = this->m_nLineHeight ;
			}

			_nLine = (INT)this->m_vecVertical.size() - 1 ;
			for (INT i = 0; i < (INT)this->m_vecVertical.size(); ++i)
			{
				_ptCaret.y += this->m_vecVertical[i].m_nMaxHeight ;
			}
		}

		_ptCaret.x += _renderRect.left - this->m_ptLayoutOffset.x ;
		_ptCaret.y += _renderRect.top - this->m_ptLayoutOffset.y ;
	}

	if (this->m_pCaret)
	{
		this->m_pCaret->SetSize(_szCaret) ;
		this->m_pCaret->SetLocation(_ptCaret) ;
	}

	this->m_nCaretLine		= _nLine ;
	this->m_nCaretIndex		= nIndex ;
	this->m_bCaretSide		= bSide ;
	return TRUE ;
}

BOOL CCUITextField::CalcIndexInLine(INT nIndexLeft, INT nIndexRight)
{
	INT _nLine = 0 ;
	for (INT i = 0; i < (INT)this->m_vecVertical.size(); ++i)
	{
		if (this->m_vecVertical[i].m_nLeftIndex >= nIndexLeft
			&& this->m_vecVertical[i].m_nRightIndex <= nIndexLeft
				&& this->m_vecVertical[i].m_nLeftIndex >= nIndexRight
					&& this->m_vecVertical[i].m_nRightIndex <= nIndexRight)
		{
			return TRUE ;
		}
	}
	return FALSE ;
}

BOOL CCUITextField::IsIndexIsLineStart(INT nIndex)
{
	for (INT i = 0; i < (INT)this->m_vecVertical.size(); ++i)
	{
		if (this->m_vecVertical[i].m_nLeftIndex == nIndex)
		{
			return TRUE ;
		}
	}
	return FALSE ;
}

BOOL CCUITextField::IsIndexIsLineEnd(INT nIndex)
{
	for (INT i = 0; i < (INT)this->m_vecVertical.size(); ++i)
	{
		if (this->m_vecVertical[i].m_nRightIndex == nIndex)
		{
			return TRUE ;
		}
	}
	return FALSE ;
}

BOOL CCUITextField::MoveCaretLeft()
{
	if (this->m_bCaretSide)
	{
		this->MoveCaretIndex(m_nCaretIndex, FALSE) ;
	}
	else if (this->m_nCaretIndex > 0)
	{
		this->MoveCaretIndex(m_nCaretIndex -1, FALSE, FALSE) ;
	}

	this->MakeSureCaretInScrope() ;
	return TRUE ;
}
BOOL CCUITextField::MoveCaretRight()
{
	if (!this->m_bCaretSide)
	{
		this->MoveCaretIndex(m_nCaretIndex, TRUE) ;
	}
	else if (this->m_nCaretIndex < (INT)this->m_vecChar.size() - 1)
	{
		this->MoveCaretIndex(m_nCaretIndex +1, TRUE, TRUE) ;
	}

	this->MakeSureCaretInScrope() ;
	return TRUE ;
}

BOOL CCUITextField::MoveCaretUp()
{
	if (0 < this->m_nCaretLine && this->m_pCaret)
	{
		INT _nMaxHeight = this->m_vecVertical[this->m_nCaretLine - 1].m_nMaxHeight ;
		CPoint _ptCaret(0, 0) ;
		this->m_pCaret->GetLocation(&_ptCaret) ;
		_ptCaret.y -= _nMaxHeight/2 ;

		INT _nLine = 0, _nCaretLeft = 0, _nCaretTop = 0 ; INT _nCaretHeight = 0 ;
		this->m_nCaretIndex = this->CalcCharIndex(_ptCaret.x, _ptCaret.y, &m_bCaretSide, &_nLine, &_nCaretTop, &_nCaretLeft) ;
		
		if ((INT)this->m_vecVertical.size() > _nLine)
		{
			_nCaretHeight = this->m_vecVertical[_nLine].m_nMaxHeight ;
		}
		else
		{
			_nCaretHeight = this->CalcDefautCharSize().cy ;
			if (this->m_nLineHeight > _nCaretHeight)
			{
				_nCaretHeight = this->m_nLineHeight ;
			}
		}

		if (this->m_pCaret)
		{
			this->m_pCaret->SetSize(CSize(2, _nCaretHeight)) ;
			this->m_pCaret->SetLocation(CPoint(_nCaretLeft, _nCaretTop)) ;
		}
		this->m_nCaretLine = _nLine ;
	}

	this->MakeSureCaretInScrope() ;
	return TRUE ;
}

BOOL CCUITextField::MoveCaretDown()
{
	if (this->m_nCaretLine < (INT)this->m_vecVertical.size() -1 && this->m_pCaret)
	{
		INT _nMaxOldHeight = this->m_vecVertical[this->m_nCaretLine].m_nMaxHeight ;
		INT _nMaxHeight = this->m_vecVertical[this->m_nCaretLine + 1].m_nMaxHeight ;
		CPoint _ptCaret(0, 0) ;
		this->m_pCaret->GetLocation(&_ptCaret) ;
		_ptCaret.y += _nMaxOldHeight + _nMaxHeight/2 ;

		INT _nLine = 0, _nCaretLeft = 0, _nCaretTop = 0 ; INT _nCaretHeight = 0 ;
		this->m_nCaretIndex = this->CalcCharIndex(_ptCaret.x, _ptCaret.y, &m_bCaretSide, &_nLine, &_nCaretTop, &_nCaretLeft) ;
		
		if ((INT)this->m_vecVertical.size() > _nLine)
		{
			_nCaretHeight = this->m_vecVertical[_nLine].m_nMaxHeight ;
		}
		else
		{
			_nCaretHeight = this->CalcDefautCharSize().cy ;
			if (this->m_nLineHeight > _nCaretHeight)
			{
				_nCaretHeight = this->m_nLineHeight ;
			}
		}

		if (this->m_pCaret)
		{
			this->m_pCaret->SetSize(CSize(2, _nCaretHeight)) ;
			this->m_pCaret->SetLocation(CPoint(_nCaretLeft, _nCaretTop)) ;
		}
		this->m_nCaretLine = _nLine ;
	}

	this->MakeSureCaretInScrope() ;
	return TRUE ;
}

BOOL CCUITextField::CalcSelectRange(INT* pnLeft, INT* pnRight)
{
	INT _nSelectLeft = 0, _nSelectRight = 0 ;
	if (this->m_nSelectLeft < this->m_nSelectRight)
	{
		if (this->m_bSelectLeftSide)
		{
			_nSelectLeft = this->m_nSelectLeft + 1 ;
		}
		else
		{
			_nSelectLeft = this->m_nSelectLeft ;
		}

		if (this->m_bSelectRightSide)
		{
			_nSelectRight = this->m_nSelectRight + 1 ;
		}
		else
		{
			_nSelectRight = this->m_nSelectRight ;
		}
	}
	else if (this->m_nSelectLeft > this->m_nSelectRight)
	{
		if (this->m_bSelectLeftSide)
		{
			_nSelectRight = this->m_nSelectLeft + 1 ;
		}
		else
		{
			_nSelectRight = this->m_nSelectLeft ;
		}

		if (this->m_bSelectRightSide)
		{
			_nSelectLeft = this->m_nSelectRight + 1 ;
		}
		else
		{
			_nSelectLeft = this->m_nSelectRight ;
		}
	}
	else
	{
		if (this->m_bSelectLeftSide)
		{
			_nSelectLeft = this->m_nSelectLeft ;
		}
		else
		{
			_nSelectLeft = this->m_nSelectLeft + 1 ;
		}

		if (this->m_bSelectRightSide)
		{
			_nSelectRight = this->m_nSelectLeft ;
		}
		else
		{
			_nSelectRight = this->m_nSelectRight + 1 ;
		}
	}

	if (pnLeft)
	{
		*pnLeft = _nSelectLeft ;
	}

	if (pnRight)
	{
		*pnRight = _nSelectRight ;
	}
	return TRUE ;
}

BOOL CCUITextField::ClearSelectRange()
{
	this->m_nSelectLeft		= 0 ;
	this->m_bSelectLeftSide = FALSE ;
	this->m_nSelectRight	= 0 ;
	this->m_bSelectRightSide= FALSE ;
	__self->Invalidate() ;
	return TRUE ;
}

CString CCUITextField::GetSelectString()
{
	INT _nLeft = 0, _nRight = 0 ;
	this->CalcSelectRange(&_nLeft, &_nRight) ;
	CString _strTemp = _T("") ;
	for (INT i = _nLeft; i <= _nRight && i < this->m_strEdit.GetLength(); ++i)
	{
		_strTemp += this->m_strEdit[i] ;
	}

	return _strTemp ;
}

BOOL CCUITextField::DeleteSelect(BOOL bInvalidate)
{
	INT _nLeft = 0, _nRight = 0 ;
	this->CalcSelectRange(&_nLeft, &_nRight) ;
	IF_RETURN(_nLeft == _nRight, FALSE) ;

	CString _strEditStringTemp = this->m_strEdit ;
	INT _nStringLength = this->m_strEdit.GetLength() ;
	this->m_strEdit = _strEditStringTemp.Left(_nLeft) 
		+ _strEditStringTemp.Right(_nStringLength - _nRight) ;
	VEC_CHAR::iterator _iter = this->m_vecChar.begin() ;
	this->m_vecChar.erase(_iter + _nLeft, _iter + _nRight) ;

	if (0 == _nLeft)
	{
		this->MoveCaretIndex(0, FALSE) ;
	}
	else if (this->m_strEdit.GetLength() == _nLeft)
	{
		this->MoveCaretIndex(_nLeft - 1, TRUE) ;
	}
	else
	{
		this->MoveCaretIndex(_nLeft, TRUE) ;
	}

	this->m_nSelectLeft		= _nLeft ;
	this->m_nSelectRight	= _nLeft ;
	this->m_bSelectLeftSide	= FALSE ;
	this->m_bSelectRightSide= FALSE ;

	if (bInvalidate)
	{
		this->LayoutChar() ;
		__self->Invalidate() ;
	}
	return TRUE ;
}

BOOL CCUITextField::DeleteCurrentCaretPos(BOOL bInvalidate)
{
	if (0 == this->m_nCaretIndex && FALSE == this->m_bCaretSide)
	{
		return FALSE ;
	}

	if (this->m_strEdit.GetLength() == 0)
	{
		return FALSE ;
	}

	INT _nIndex = 0 ;
	if (this->m_bCaretSide)
	{
		_nIndex = this->m_nCaretIndex ;
		if (0 == _nIndex)
		{
			this->MoveCaretIndex(this->m_nCaretIndex, FALSE) ;
		}
		else
		{
			this->MoveCaretIndex(this->m_nCaretIndex -1, TRUE) ;
		}
	}
	else
	{
		_nIndex = this->m_nCaretIndex - 1 ;
		this->MoveCaretIndex(this->m_nCaretIndex -1, FALSE) ;
	}

	CString _strEditStringTemp = this->m_strEdit ;
	INT _nStringLength = this->m_strEdit.GetLength() ;
	this->m_strEdit = _strEditStringTemp.Left(_nIndex) 
		+ _strEditStringTemp.Right(_nStringLength - _nIndex - 1) ;
	VEC_CHAR::iterator _iter = this->m_vecChar.begin() + _nIndex ;
	this->m_vecChar.erase(_iter) ;

	if (bInvalidate)
	{
		this->LayoutChar() ;
		__self->Invalidate() ;
	}
	return TRUE ;
}

BOOL CCUITextField::InsertChar(TCHAR tcChar)
{
	if (FALSE == this->m_bWantTab && _T('\t') == tcChar)
	{
		return FALSE ;
	}

	if (_T('\n') == tcChar &&
		 (FALSE == this->m_bWantReturn || this->m_bSingleLine))
	{
		return FALSE ;
	}

	if (_T('\r') == tcChar)
	{
		return FALSE ;
	}

	this->DeleteSelect(FALSE) ;

	INT _nInsertPos = 0 ;
	if (this->m_bCaretSide)
	{
		_nInsertPos = this->m_nCaretIndex + 1 ;
	}
	else
	{
		_nInsertPos = this->m_nCaretIndex ;
	}
	
	_TextNode _node ;
	if (this->m_bPasswd)
	{
		this->CalcCharInfo(this->m_tcPasswdChar, _node) ;
	}
	else
	{
		this->CalcCharInfo(tcChar, _node) ;
	}
	VEC_CHAR::iterator _iter = this->m_vecChar.begin() + _nInsertPos ;
	this->m_vecChar.insert(_iter, _node) ;
	this->m_strEdit.Insert(_nInsertPos, tcChar) ;

	this->LayoutChar() ;
	this->MoveCaretIndex(_nInsertPos, TRUE) ;
	__self->Invalidate() ;

	return TRUE ;
}

BOOL CCUITextField::InsertString(CString strInsert)
{
	strInsert.Remove(_T('\r')) ;
	if (FALSE == this->m_bWantTab)
	{
		strInsert.Remove(_T('\t')) ;
	}

	if (FALSE == this->m_bWantReturn || this->m_bSingleLine)
	{
		strInsert.Remove(_T('\n')) ;
	}

	if (0 == strInsert.GetLength())
	{
		return TRUE ;
	}

	this->DeleteSelect(FALSE) ;

	INT _nInsertPos = 0 ;
	if (this->m_bCaretSide)
	{
		_nInsertPos = this->m_nCaretIndex + 1 ;
	}
	else
	{
		_nInsertPos = this->m_nCaretIndex ;
	}

	for (INT i = 0; i < strInsert.GetLength(); ++i)
	{
		_TextNode _node ;
		if (this->m_bPasswd)
		{
			this->CalcCharInfo(this->m_tcPasswdChar, _node) ;
		}
		else
		{
			this->CalcCharInfo(strInsert[i], _node) ;
		}
		VEC_CHAR::iterator _iter = this->m_vecChar.begin() + _nInsertPos + i ;
		this->m_vecChar.insert(_iter, _node) ;
		this->m_strEdit.Insert(_nInsertPos + i, strInsert[i]) ;
	}
	this->LayoutChar() ;
	this->MoveCaretIndex(_nInsertPos + strInsert.GetLength() -  1, TRUE) ;
	__self->Invalidate() ;

	return TRUE ;
}

BOOL CCUITextField::SelectAllText()
{
	this->m_nSelectLeft = 0 ;
	this->m_bSelectLeftSide = FALSE ;
	this->m_nSelectRight = this->m_strEdit.GetLength() - 1 ;
	this->m_bSelectRightSide = TRUE ;
	__self->Invalidate() ;
	return TRUE ;
}

BOOL CCUITextField::MakeSureCaretInScrope()
{
	IF_RETURN(NULL == this->m_pCaret, FALSE) ;
	CRect _renderRect(0, 0, 0, 0) ;
	_renderRect = this->CalcRenderRect() ;

	CPoint _ptOffset(0, 0) ;
	CPoint _ptCaret(0, 0) ;
	CSize _szCaret(0, 0) ;
	this->m_pCaret->GetLocation(&_ptCaret) ;
	this->m_pCaret->GetSize(&_szCaret) ;

	INT _nCaretIndex = this->m_nCaretIndex ;
	if (FALSE == this->m_bCaretSide)
	{
		_nCaretIndex-- ;
	}

	if (this->m_bSingleLine)
	{
		if (_ptCaret.x < _renderRect.left + 10)
		{
			if (this->IsIndexIsLineStart(_nCaretIndex + 1))
			{
				_ptOffset.x -= (_renderRect.left - _ptCaret.x) ;
				_ptCaret.x	= _renderRect.left ;
			}
			else if (_nCaretIndex >= 0)
			{
				_ptOffset.x -= (_renderRect.left - _ptCaret.x) + this->m_vecChar[_nCaretIndex].m_szChar.cx ;
				_ptCaret.x	= _renderRect.left  + this->m_vecChar[_nCaretIndex].m_szChar.cx ;
			}
		}
		else if (_ptCaret.x > _renderRect.right - 10)
		{
			_ptOffset.x += _ptCaret.x - _renderRect.right ;
			_ptCaret.x = _renderRect.right ;
		}
	}
	else
	{
		if (_ptCaret.y  < _renderRect.top + 10)
		{
			_ptOffset.y -= (_renderRect.top - _ptCaret.y) ;
			_ptCaret.y = _renderRect.top ;
		}
		else if (_ptCaret.y + _szCaret.cy > _renderRect.bottom - 10)
		{
			_ptOffset.y += (_ptCaret.y + _szCaret.cy - _renderRect.bottom) ;
			_ptCaret.y = _renderRect.bottom  - _szCaret.cy ;
		}
	}

	this->m_ptLayoutOffset.x += _ptOffset.x ;
	this->m_ptLayoutOffset.y += _ptOffset.y ;
	this->m_pCaret->SetLocation(_ptCaret) ;

	return TRUE ;
}

CString CCUITextField::GetStringFromClipboard()
{
	HWND _hWnd = UI::GetHostWnd<void>(GetEntity<IUIElement>()) ;
	if(::OpenClipboard(_hWnd))
	{
		UINT _unFormat = (sizeof(TCHAR) == sizeof(WCHAR)) ? CF_UNICODETEXT : CF_TEXT ;
		HGLOBAL _hMem = ::GetClipboardData(_unFormat) ;
		CString _strData = _T("") ;
		if (_hMem != NULL)
		{
			_strData = (LPCTSTR)::GlobalLock(_hMem) ;
			_strData.Remove(_T('\r')) ;
			::GlobalUnlock(_hMem) ;
		}
		::CloseClipboard() ;

		return _strData ;
	}
	return _T("") ;
}

BOOL CCUITextField::PutStringToClipboard(CString strClipboard)
{
	HWND _hWnd = UI::GetHostWnd<void>(GetEntity<IUIElement>()) ;
	if (::OpenClipboard(_hWnd) &&::EmptyClipboard())
	{
		size_t _cbStr = (strClipboard.GetLength() + 1) * sizeof(TCHAR) ;
		HGLOBAL _hMem = GlobalAlloc(GMEM_MOVEABLE, _cbStr); 
		if (_hMem == NULL) 
		{	
			::CloseClipboard() ;
			return FALSE ; 
		}
		LPTSTR _lpDest = (LPTSTR)::GlobalLock(_hMem) ;
		memcpy_s(_lpDest, _cbStr, strClipboard.LockBuffer(), _cbStr) ;
		strClipboard.UnlockBuffer() ;
		::GlobalUnlock(_hMem) ;
		UINT _unFormat = (sizeof(TCHAR) == sizeof(WCHAR)) ? CF_UNICODETEXT : CF_TEXT ;
		if(NULL == ::SetClipboardData(_unFormat, _hMem))
		{
			::CloseClipboard() ;
			return FALSE ;
		}
		::CloseClipboard() ;
		return TRUE ;
	}
	return FALSE ;
}

VOID CCUITextField::OnKeyDown(IUIFrame* pTarget, tMsgArg* pArg)
{
	IF_RETURN_VOID(NULL == pTarget) ;
	tMsgArgKey* _pKeyArg = (tMsgArgKey*)pArg ;
	unsigned int _charCode = _pKeyArg->unChar;
	
	if (GetKeyState(VK_CONTROL) < 0)
	{
		if (_charCode == _T('a') || _charCode == _T('A'))
		{
			this->SelectAllText() ;	
		}
		else if (_charCode == _T('x') || _charCode == _T('X'))
		{
			this->PutStringToClipboard(this->GetSelectString()) ;
			this->DeleteSelect() ;
		}
		else if (_charCode == _T('c') || _charCode == _T('C'))
		{
			this->PutStringToClipboard(this->GetSelectString()) ;
		}
		else if (_charCode == _T('v') || _charCode == _T('V'))
		{
			this->InsertString(this->GetStringFromClipboard()) ;
		}
	}
	else
	{
		if (VK_LEFT == _charCode)
		{
			this->MoveCaretLeft() ;
			this->ClearSelectRange() ;
			this->MakeSureCaretInScrope() ;
			this->m_pCaret->SetHidden(FALSE) ;
		}

		if (VK_RIGHT == _charCode)
		{
			this->MoveCaretRight() ;
			this->ClearSelectRange() ;
			this->MakeSureCaretInScrope() ;
			this->m_pCaret->SetHidden(FALSE) ;
		}

		if (VK_UP == _charCode)
		{
			this->MoveCaretUp() ;
			this->ClearSelectRange() ;
			this->m_pCaret->SetHidden(FALSE) ;
		}

		if (VK_DOWN == _charCode)
		{
			this->MoveCaretDown() ;
			this->ClearSelectRange() ;
			this->m_pCaret->SetHidden(FALSE) ;
		}
	}
}

VOID CCUITextField::OnKeyUp(IUIFrame* pTarget, tMsgArg* pArg)
{

}

VOID CCUITextField::OnLButtonDown(IUIFrame* pTarget, tMsgArg* pArg)
{
	__self->SetFocus(TRUE) ;
	this->m_bLeftButtonDwon = TRUE ;
	IF_RETURN_VOID(NULL == pTarget) ;

	CRect _controlRect(0, 0, 0, 0) ;
	__self->GetAbsolutRect(&_controlRect) ;
	int x = GET_X_LPARAM(pArg->lParam) - _controlRect.left ;
	int y = GET_Y_LPARAM(pArg->lParam) - _controlRect.top ;

	INT _nLine = 0, _nCaretLeft = 0, _nCaretTop = 0 ; INT _nCaretHeight = 0 ;
	this->m_nCaretIndex = this->CalcCharIndex(x, y, &m_bCaretSide, &_nLine, &_nCaretTop, &_nCaretLeft) ;

	this->m_nSelectLeft		= this->m_nCaretIndex ;
	this->m_bSelectLeftSide = this->m_bCaretSide ;
	this->m_nSelectRight	= this->m_nCaretIndex ;
	this->m_bSelectRightSide= this->m_bCaretSide ;

	if ((INT)this->m_vecVertical.size() > _nLine)
	{
		_nCaretHeight = this->m_vecVertical[_nLine].m_nMaxHeight ;
	}
	else
	{
		_nCaretHeight = this->CalcDefautCharSize().cy ;
		if (this->m_nLineHeight > _nCaretHeight)
		{
			_nCaretHeight = this->m_nLineHeight ;
		}
	}

	if (this->m_pCaret)
	{
		this->m_pCaret->SetSize(CSize(2, _nCaretHeight)) ;
		this->m_pCaret->SetLocation(CPoint(_nCaretLeft, _nCaretTop)) ;
	}
	this->m_nCaretLine = _nLine ;
	__self->Invalidate() ;
}

VOID CCUITextField::OnLButtonUp(IUIFrame* pTarget, tMsgArg* pArg)
{
	this->m_bLeftButtonDwon = FALSE ;
}

VOID CCUITextField::OnMouseMove(IUIFrame* pTarget, tMsgArg* pArg)
{
	IF_RETURN_VOID(NULL == pTarget) ;
	if (this->m_bLeftButtonDwon)
	{
		CPoint _location(0, 0) ;
		__self->GetAbsolutLocation(&_location) ;
		int x = GET_X_LPARAM(pArg->lParam) - _location.x ;
		int y = GET_Y_LPARAM(pArg->lParam) - _location.y ;
		x = x > 0 ? x : 0 ;
		y = y > 0 ? y : 0 ;

		INT _nLine = 0, _nCaretLeft = 0, _nCaretTop = 0 ; INT _nCaretHeight = 0 ;
		this->m_nCaretIndex = this->CalcCharIndex(x, y, &m_bCaretSide, &_nLine, &_nCaretTop, &_nCaretLeft) ;
		if ((INT)this->m_vecVertical.size() > _nLine)
		{
			_nCaretHeight = this->m_vecVertical[_nLine].m_nMaxHeight ;
		}
		else
		{
			_nCaretHeight = this->CalcDefautCharSize().cy ;
			if (this->m_nLineHeight > _nCaretHeight)
			{
				_nCaretHeight = this->m_nLineHeight ;
			}
		}
		
		if (this->m_pCaret)
		{
			this->m_pCaret->SetSize(CSize(2, _nCaretHeight)) ;
			this->m_pCaret->SetLocation(CPoint(_nCaretLeft, _nCaretTop)) ;
		}

		this->MakeSureCaretInScrope() ;

		if (this->m_nSelectRight != this->m_nCaretIndex || this->m_bSelectRightSide != this->m_bCaretSide)
		{
			this->m_nSelectRight	= this->m_nCaretIndex ;
			this->m_bSelectRightSide= this->m_bCaretSide ;
			__self->Invalidate() ;
		}
	}
}

VOID CCUITextField::OnChar(IUIFrame* pTarget, tMsgArg* pArg)
{
	IF_RETURN_VOID(NULL == pArg) ;
	tMsgArgKey* _pKeyArg = (tMsgArgKey*)pArg ;
	unsigned int _charCode = _pKeyArg->unChar ;
	
	if (GetKeyState(VK_CONTROL) >= 0)
	{
		INT _nLeft, _nRight ;
		this->CalcSelectRange(&_nLeft, &_nRight) ;

		if (_charCode == VK_BACK)
		{
			if (FALSE == this->DeleteSelect())
			{
				this->DeleteCurrentCaretPos() ;
			}
		}
		else if (_charCode == VK_TAB)
		{
			this->InsertChar(TCHAR(VK_TAB)) ;
		}
		else if (_charCode == VK_RETURN)
		{
			this->InsertChar(_T('\n')) ;
		}
		else
		{
			this->InsertChar(TCHAR(_charCode)) ;
		}
		this->MakeSureCaretInScrope() ;
	}
}

VOID CCUITextField::OnImeStartComposition(IUIFrame* pTarget, tMsgArg* pArg)
{
	HWND _hWnd = UI::GetHostWnd<void>(GetEntity<IUIElement>()) ;
	IF_RETURN_VOID(!IsWindow(_hWnd)) ;

	CPoint _pt(0, 0) ;
	__self->GetAbsolutLocation(&_pt) ;

	CSize _szCaret(0, 0) ;
	CPoint _ptCaret(0, 0) ;
	if (this->m_pCaret)
	{
		this->m_pCaret->GetSize(&_szCaret) ;
		this->m_pCaret->GetLocation(&_ptCaret) ;
	}

	CANDIDATEFORM form;
	form.dwIndex		= 0;
	form.dwStyle		= CFS_EXCLUDE;
	form.ptCurrentPos.x =  _pt.x + _ptCaret.x ;
	form.ptCurrentPos.y =  _pt.y + _ptCaret.y + _szCaret.cy ;
	form.rcArea.top		=  _pt.y + _ptCaret.y ;
	form.rcArea.bottom	=  _pt.y + _szCaret.cy + _ptCaret.y ;
	form.rcArea.left	=  _pt.x + _ptCaret.x ;
	form.rcArea.right	=  _pt.x + 1 + _szCaret.cx + _ptCaret.x ;

	COMPOSITIONFORM compForm ;
	compForm.ptCurrentPos	=form.ptCurrentPos ;
	compForm.rcArea			=form.rcArea ;
	compForm.dwStyle		=CFS_POINT ;

	HIMC hIMC = ::ImmGetContext(_hWnd) ;
	::ImmSetCandidateWindow(hIMC, &form) ;
	::ImmSetCompositionWindow(hIMC,&compForm) ;
	::ImmReleaseContext(_hWnd, hIMC) ;
}