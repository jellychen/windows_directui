#include "stdafx.h"
#include "CCUILayoutDock.h"

HRESULT CCUILayoutDock::Layout(IUIFrame* pFrame)
{
	DEBUG_ASSERT(pFrame) ;
	IF_RETURN(NULL == pFrame, E_INVALIDARG) ;

	CComQIPtr<IUIFrameInternal> pInternal = pFrame ;
	DEBUG_ASSERT(pInternal) ;
	IF_RETURN(NULL == pInternal, E_FAIL) ;

	CRect rcRect(0, 0, 0, 0) ;
	pInternal->GetLayoutRect(&rcRect) ;
	CSize szSize(rcRect.Width(), rcRect.Height()) ;
	
	CRect rcPadding(0, 0, 0, 0) ;
	pFrame->GetPadding(&rcPadding) ;
	CRect rcExtPadding(0, 0, 0, 0) ;
	pInternal->GetExtPadding(&rcExtPadding) ;

	CRect rcLeft(0, 0, 0, 0) ;
	rcLeft.left     = rcPadding.left + rcExtPadding.left ;
	rcLeft.top      = rcPadding.top + rcExtPadding.top ;
	rcLeft.right    = szSize.cx - rcExtPadding.right - rcPadding.right ;
	rcLeft.bottom   = szSize.cy - rcExtPadding.bottom - rcPadding.bottom ;

	LONG lChildrenCount = 0 ;
	pFrame->GetChildrenCount(&lChildrenCount) ;
	for (INT i = 0; i < lChildrenCount; ++i)
	{
		CComPtr<IUIElement> pElement ;
		pFrame->GetChildByIndex(i, &pElement) ;
		CComQIPtr<IUIFrame> pFrameChild = pElement ;
		CComQIPtr<IUIFrameInternal> pFrameChildInternal = pElement ;
		IF_CONTINUE(NULL == pFrameChild || NULL == pFrameChildInternal) ;

		BOOL bHidden = FALSE ;
		pFrameChild->GetHidden(&bHidden) ;
		IF_CONTINUE(TRUE == bHidden) ;

		BOOL bFloat = TRUE ;
		pFrameChild->GetFloat(&bFloat) ;
		IF_CONTINUE(TRUE == bFloat) ;

		INT nDrift = DRIFT::DRIFT_NEAR ;
		pFrameChild->GetDrift(&nDrift) ;
		
		CRect rcChildMargin(0, 0, 0, 0) ;
		pFrameChild->GetMargin(&rcChildMargin) ;

		BOOL bWithAsParent = FALSE ;
		BOOL bHeightAsParent = FALSE ;
		pFrameChild->GetWidthAsParent(&bWithAsParent) ;
		pFrameChild->GetHeightAsParent(&bHeightAsParent) ;
		CSize szEstimateSize(-1, -1) ;
		if (bWithAsParent)
		{
			szEstimateSize.cx = rcLeft.Width() - rcChildMargin.left - rcChildMargin.right ;
			szEstimateSize.cx = szEstimateSize.cx > 0 ? szEstimateSize.cx : 0 ;
		}
		if (bHeightAsParent)
		{
			szEstimateSize.cy = rcLeft.Height() - rcChildMargin.top - rcChildMargin.bottom ;
			szEstimateSize.cy = szEstimateSize.cy > 0 ? szEstimateSize.cy : 0 ;
		}
		pFrameChildInternal->SetEstimateSize(szEstimateSize) ;

		CSize szChildSize(0, 0) ;
		pFrameChild->GetSize(&szChildSize) ;

		CPoint  ptTarget(0, 0) ;
		CSize   szTarget = szChildSize ;
		BOOL    bLayoutComplete = FALSE ;

		INT nAnchor = ANCHOR::NONE ;
		pFrameChild->GetAnchor(&nAnchor) ;
		if (ANCHOR::TOP == nAnchor)
		{
			//szTarget.cx     = rcLeft.Width() - rcChildMargin.left - rcChildMargin.right ;
			if (DRIFT::DRIFT_NEAR == nDrift)
			{
				ptTarget.x	= rcLeft.left + rcChildMargin.left ;
			}
			else if (DRIFT::DRIFT_FAR == nDrift)
			{
				ptTarget.x = rcLeft.right - rcChildMargin.right - szTarget.cx ;
			}
			else if (DRIFT::DRIFT_MIDDLE == nDrift)
			{
				ptTarget.x = (rcLeft.Width() - szTarget.cx)/2  + rcLeft.left ;
			}
			ptTarget.y      = rcLeft.top + rcChildMargin.top ;
			rcLeft.top      += (szTarget.cy + rcChildMargin.top + rcChildMargin.bottom) ;
		}
		else if (ANCHOR::BOTTOM == nAnchor)
		{
			//szTarget.cx     = rcLeft.Width() - rcChildMargin.left - rcChildMargin.right ;
			if (DRIFT::DRIFT_NEAR == nDrift)
			{
				ptTarget.x	= rcLeft.left + rcChildMargin.left ;
			}
			else if (DRIFT::DRIFT_FAR == nDrift)
			{
				ptTarget.x = rcLeft.right - rcChildMargin.right - szTarget.cx ;
			}
			else if (DRIFT::DRIFT_MIDDLE == nDrift)
			{
				ptTarget.x = (rcLeft.Width() - szTarget.cx)/2 + rcLeft.left ;
			}
			ptTarget.y      = rcLeft.bottom - szTarget.cy - rcChildMargin.bottom ;
			rcLeft.bottom   -= (szTarget.cy + rcChildMargin.top + rcChildMargin.bottom) ;
		}
		else if (ANCHOR::LEFT == nAnchor)
		{
			//szTarget.cy     = rcLeft.Height() - rcChildMargin.top - rcChildMargin.bottom ;
			if (DRIFT::DRIFT_NEAR == nDrift)
			{
				ptTarget.y	= rcLeft.top + rcChildMargin.top ;
			}
			else if (DRIFT::DRIFT_FAR == nDrift)
			{
				ptTarget.y  = rcLeft.bottom - rcChildMargin.right - szTarget.cy ;
			}
			else if (DRIFT::DRIFT_MIDDLE == nDrift)
			{
				ptTarget.y = (rcLeft.Height() - szTarget.cy)/2 + rcLeft.top ;
			}
			ptTarget.x      = rcLeft.left + rcChildMargin.left ;
			rcLeft.left     += (szTarget.cx + rcChildMargin.left + rcChildMargin.right) ;
		}
		else if (ANCHOR::RIGHT == nAnchor)
		{
			//szTarget.cy     = rcLeft.Height() - rcChildMargin.top - rcChildMargin.bottom ;
			if (DRIFT::DRIFT_NEAR == nDrift)
			{
				ptTarget.y	= rcLeft.top + rcChildMargin.top ;
			}
			else if (DRIFT::DRIFT_FAR == nDrift)
			{
				ptTarget.y  = rcLeft.bottom - rcChildMargin.right - szTarget.cy ;
			}
			else if (DRIFT::DRIFT_MIDDLE == nDrift)
			{
				ptTarget.y = (rcLeft.Height() - szTarget.cy)/2  + rcLeft.top ;
			}
			ptTarget.x      = rcLeft.right - szTarget.cx - rcChildMargin.right ;
			rcLeft.right    -= (szTarget.cx + rcChildMargin.left + rcChildMargin.right) ;
		}
		else if (ANCHOR::FILL == nAnchor)
		{
			szTarget.cx     = rcLeft.Width() - rcChildMargin.left - rcChildMargin.right ;
			szTarget.cy     = rcLeft.Height() - rcChildMargin.top - rcChildMargin.bottom ;
			ptTarget.x      = rcLeft.left + rcChildMargin.left ;
			ptTarget.y      = rcLeft.top + rcChildMargin.top ;
			rcLeft          = CRect(0, 0, 0, 0) ;
			bLayoutComplete = TRUE ;
		}

		CRect rcTarget(0, 0, 0, 0) ;
		rcTarget.left   = ptTarget.x ;
		rcTarget.top    = ptTarget.y ;
		rcTarget.right  = rcTarget.left + szTarget.cx ;
		rcTarget.bottom = rcTarget.top + szTarget.cy ;
		pFrameChildInternal->SetLayoutRect(rcTarget) ;

		IF_BREAK(bLayoutComplete) ;
	}
	return S_OK ;
}

HRESULT CCUILayoutDock::CalcSize(IUIFrame* pFrame, SIZE szOld, SIZE* pOutSize)
{
	IF_RETURN(NULL == pFrame, E_INVALIDARG) ;
	IF_RETURN(NULL == pOutSize, E_INVALIDARG) ;

	pOutSize->cx = 0 ;
	pOutSize->cy = 0 ;
	return S_OK ;
}