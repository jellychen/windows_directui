#include "stdafx.h"
#include "CCUIBackBlur.h"
#include "CCUIStackBlurAlgorithm.h"
#include <cmath>

CCUIBackBlur::CCUIBackBlur()
{
	this->m_nRadius = 1 ;
	this->m_bLBtnDown = FALSE ;
}

CCUIBackBlur::~CCUIBackBlur()
{

}

HRESULT CCUIBackBlur::FinalConstruct()
{
	Common::Util::CreateObject(&m_pCanvas) ;
	return S_OK ;
}

HRESULT CCUIBackBlur::SetRadius(INT nRadius)
{
	this->m_nRadius = nRadius ;
	__self->Invalidate() ;
	return S_OK ;
}

HRESULT CCUIBackBlur::GetRadius(INT* pnRadius)
{
	DEBUG_ASSERT(pnRadius) ;
	IF_RETURN(NULL == pnRadius, E_INVALIDARG) ;

	*pnRadius = this->m_nRadius ;
	return S_OK ;
}

HRESULT CCUIBackBlur::Draw(IUICanvas* pCanvas)
{
	if (this->m_pCanvas && pCanvas && this->m_nRadius > 0)
	{
		CRect _rc(0, 0, 0, 0) ;
		__self->GetAbsolutRect(&_rc) ;
		CSize _sz(_rc.Width(), _rc.Height()) ;

		CSize szCanvas(0, 0) ;
		this->m_pCanvas->GetSize(&szCanvas) ;
		if (_sz != szCanvas)
		{
			this->m_pCanvas->DestoryCanvas() ;
			this->m_pCanvas->InitFromCanvas(pCanvas, _sz) ;
		}
		else
		{
			this->m_pCanvas->ClearCanvas() ;	
		}

		HDC hTargetDC = NULL ;
		pCanvas->GetCanvasDC(&hTargetDC) ;
		HDC hTempTargetDC = NULL ;
		this->m_pCanvas->GetCanvasDC(&hTempTargetDC) ;

		::BitBlt(hTempTargetDC, 0, 0, _sz.cx, _sz.cy, hTargetDC, _rc.left, _rc.top, SRCCOPY) ;
		this->_blur(this->m_pCanvas) ;
		::BitBlt(hTargetDC, _rc.left, _rc.top, _sz.cx, _sz.cy, hTempTargetDC, 0, 0, SRCCOPY) ;
	}
	return __super::Draw(pCanvas) ;
}

HRESULT CCUIBackBlur::Render(IUICanvas* pCanvas, RECT rcRender, INT nState)
{
	__super::Render(pCanvas, rcRender, nState) ;
	return S_OK ;
}

HRESULT CCUIBackBlur::SetAttribute(ICVarData* pAttrData)
{
	__super::SetAttribute(pAttrData) ;

	SET_ATTR_CLASS_BEGIN    (pAttrData, IUIBackBlur)
	SET_ATTR_INT			(Radius)
	SET_ATTR_END            ()
	
	return S_OK ;
}


HRESULT CCUIBackBlur::OnMessage(IUIFrame* pTarget, tMsgArg* pArg)
{
	__super::OnMessage(pTarget, pArg) ;
	IF_RETURN(NULL == pArg, E_FAIL) ;
	switch(pArg->dwMsgId)
	{
	case MESSAGE::UI_LBTNDOWN:
		this->m_bLBtnDown = TRUE ;
		this->m_ptLBtnDownPoint = ((tMsgArgPoint*)pArg)->pt ;
		break ;
	case MESSAGE::UI_LBTNUP:
		this->m_bLBtnDown = FALSE ;
		break ;
	case MESSAGE::UI_MOUSEMOVE:
		if (this->m_bLBtnDown)
		{
			CPoint _pt = ((tMsgArgPoint*)pArg)->pt ;
			DEBUG_TRACE(_T("--- %d"), abs(_pt.y - this->m_ptLBtnDownPoint.y)/10) ;
			//this->SetRadius(abs(_pt.y - this->m_ptLBtnDownPoint.y)/10) ;
		}
		break ;
	}
	return S_OK ;
}

// box blur
BOOL CCUIBackBlur::_blur(IUICanvas* pCanvas)
{
	IF_RETURN(NULL == pCanvas, FALSE) ;
	int _nRadius = 5 ;

	CSize _szCanvas(0, 0) ;
	pCanvas->GetSize(&_szCanvas) ;
	BYTE* _pInBuffer = NULL ;
	pCanvas->GetMemBuffer(&_pInBuffer) ;
	DWORD* _pdwInBuffer = (DWORD*) _pInBuffer ;
	IF_RETURN(NULL == _pInBuffer, FALSE) ;

	StackBlur((INT*)_pInBuffer, _szCanvas.cx, _szCanvas.cy, this->m_nRadius) ;
	return TRUE ;
}