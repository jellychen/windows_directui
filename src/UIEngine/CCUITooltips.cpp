#include "stdafx.h"
#include "CCUITooltips.h"

CSUIIUITooltips::CSUIIUITooltips()
	: m_pExtensionCallback(this)
	, m_pToolTipsDismissExtensionCallback(this)
{
	this->m_bCreate = FALSE ;
	this->m_pExtensionCallback->Hook_OnExtension(&CSUIIUITooltips::OnToolTipsExtension) ;
	this->m_pToolTipsDismissExtensionCallback->Hook_OnExtension(&CSUIIUITooltips::OnToolTipsDismissExtension) ;
}

CSUIIUITooltips::~CSUIIUITooltips()
{

}

HRESULT CSUIIUITooltips::FinalConstruct()
{
	Common::Util::CreateObject(&m_pWindow) ;
	DEBUG_ASSERT(m_pWindow) ;
	Common::Util::CreateObject(&m_pStatic) ;
	DEBUG_ASSERT(m_pStatic) ;
	
	CComPtr<IUILayoutVertical> _pLayoutVertical ;
	Common::Util::CreateObject(&_pLayoutVertical) ;
	DEBUG_ASSERT(_pLayoutVertical) ;

	if (this->m_pWindow && this->m_pStatic && _pLayoutVertical)
	{
		this->m_pStatic->SetAutoSize(TRUE) ;
		this->m_pWindow->SetAutoSize(TRUE) ;
		this->m_pWindow->SetLayouter(_pLayoutVertical) ;
		this->m_pWindow->AddChildBack(this->m_pStatic) ;
		this->m_pWindow->SetToolWindow(TRUE) ;
		this->m_pWindow->SetLayerWin(TRUE) ;
		this->m_pWindow->SetFixSize(TRUE) ;
	}
	return S_OK ;
}

HRESULT CSUIIUITooltips::OnInit()
{
	Common::Util::GetService(&m_pExtensionCenter) ;
	DEBUG_ASSERT(m_pExtensionCenter) ;
	
	if (this->m_pExtensionCenter)
	{
		this->m_pExtensionCenter
			->AddExtensionListener(__uuidof(IUIExtensionToolTips), m_pExtensionCallback) ;
		this->m_pExtensionCenter
			->AddExtensionListener(__uuidof(IUIExtensionToolTipsDismiss), m_pToolTipsDismissExtensionCallback) ;
	}
	return S_OK ;
}

HRESULT CSUIIUITooltips::SetTooltipsDraw(IUIDraw* pDraw)
{
	if (this->m_pWindow)
	{
		return this->m_pWindow->SetBkgDraw(pDraw) ;
	}
	return E_FAIL ;
}

HRESULT CSUIIUITooltips::GetTooltipsDraw(IUIDraw** ppDraw)
{
	DEBUG_ASSERT(ppDraw) ;
    IF_RETURN(NULL == ppDraw, E_INVALIDARG) ;

	if (this->m_pWindow)
	{
		return this->m_pWindow->GetBkgDraw(ppDraw) ;
	}
	return E_FAIL ;
}

HRESULT CSUIIUITooltips::SetTooltipsPadding(RECT rcPadding)
{
	if (this->m_pWindow)
	{
		return this->m_pWindow->SetPadding(rcPadding) ;
	}
	return E_FAIL ;
}

HRESULT CSUIIUITooltips::GetTooltipsPadding(RECT* prcPadding)
{
	DEBUG_ASSERT(prcPadding) ;
    IF_RETURN(NULL == prcPadding, E_INVALIDARG) ;
	if (this->m_pWindow)
	{
		return this->m_pWindow->GetPadding(prcPadding) ;
	}
	return E_FAIL ;
}

HRESULT CSUIIUITooltips::SetTooltipsOffset(POINT ptOffset)
{
	this->m_ptOffset = ptOffset ;
	return S_OK ;
}

HRESULT CSUIIUITooltips::GetTooltipsOffset(POINT* pptOffset)
{
	DEBUG_ASSERT(pptOffset) ;
    IF_RETURN(NULL == pptOffset, E_INVALIDARG) ;

	*pptOffset = this->m_ptOffset ;
	return S_OK ;
}

HRESULT CSUIIUITooltips::OnToolTipsExtension(REFIID iid, IUIFrame* pFrame, ICVarData* pData)
{
	CComQIPtr<IUIControl> _pControl = pFrame ;
	IF_RETURN(NULL == _pControl, E_FAIL) ;

	CComBSTR _bstrToolTips ;
	_pControl->GetToolTips(&_bstrToolTips) ;
	if (this->m_pStatic)
	{
		this->m_pStatic->SetText(_bstrToolTips) ;
	}

	if (this->m_bCreate)
	{
		this->m_pWindow->DestoryWin() ;
	}
	this->m_bCreate = TRUE ;
	
	CComPtr<IUIElement> _pParentElement ;
	pFrame->GetRoot(&_pParentElement) ;
	CComQIPtr<IUIWin> _pHostWin = _pParentElement ;
	
	CRect _rcScreenRect(0, 0, 0, 0) ;
	pFrame->GetScreenRect(&_rcScreenRect) ;
	CPoint _ptToolTips(0, 0) ;
	_ptToolTips.x = _rcScreenRect.left ;
	_ptToolTips.y = _rcScreenRect.top + _rcScreenRect.Height() ;

	if (this->m_pWindow)
	{
		this->m_pWindow->CreateWin(_pHostWin, NULL) ;
		this->m_pWindow->ShowWin(SW_SHOW) ;
		this->m_pWindow->SetWinLocation(_ptToolTips) ;
	}
	return S_OK ;
}

HRESULT CSUIIUITooltips::OnToolTipsDismissExtension(REFIID iid, IUIFrame* pFrame, ICVarData* pData)
{
	if (this->m_bCreate)
	{
		this->m_pWindow->DestoryWin() ;
	}
	this->m_bCreate = FALSE ;
	return S_OK ;
}