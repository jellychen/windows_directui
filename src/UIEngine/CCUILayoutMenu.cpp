#include "stdafx.h"
#include "CCUILayoutMenu.h"

HRESULT CCUILayoutMenu::Layout(IUIFrame* pHostFrame)
{
	DEBUG_ASSERT(pHostFrame) ;
	IF_RETURN(NULL == pHostFrame, E_INVALIDARG) ;

	CComQIPtr<IUIFrameInternal> pInternal = pHostFrame ;
	DEBUG_ASSERT(pInternal) ;
	IF_RETURN(NULL == pInternal, E_FAIL) ;

	CSize szContainer(0, 0) ;
	pHostFrame->GetSize(&szContainer) ;
	CRect rcPadding(0, 0, 0, 0) ;
	pHostFrame->GetPadding(&rcPadding) ;
	CRect rcExtPadding(0, 0, 0, 0) ;
	CComQIPtr<IUIFrameInternal> pFrameInternal = pHostFrame ;
	if (pFrameInternal)
	{
		pFrameInternal->GetExtPadding(&rcExtPadding) ;
	}

	CRect rcContainer(0, 0, 0, 0) ;
	rcContainer.left    = rcPadding.left + rcExtPadding.left ;
	rcContainer.top     = rcPadding.top + rcExtPadding.top ;
	rcContainer.right   = szContainer.cx - rcPadding.right - rcExtPadding.right ;
	rcContainer.bottom  = szContainer.cy - rcPadding.bottom - rcExtPadding.bottom ;

	INT nCurrentLayout  = 0 ;
	LONG lChildrenCount = 0 ;
	pHostFrame->GetChildrenCount(&lChildrenCount) ;
	for (INT i = 0; i < lChildrenCount; ++i)
	{
		CComPtr<IUIElement> pElement ;
		pHostFrame->GetChildByIndex(i, &pElement) ;
		CComQIPtr<IUIFrame> pFrameChild = pElement ;
		CComQIPtr<IUIFrameInternal> pFrameInternal = pElement ;
		IF_CONTINUE(NULL == pFrameChild || NULL == pFrameInternal) ;

		BOOL bHidden = FALSE ;
		pFrameChild->GetHidden(&bHidden) ;
		IF_CONTINUE(bHidden) ;

		BOOL bFloat = FALSE ;
		pFrameChild->GetFloat(&bFloat) ;
		IF_CONTINUE(bFloat) ;

		CRect rcChildMargin(0, 0, 0, 0) ;
		pFrameChild->GetMargin(&rcChildMargin) ;

		BOOL bChildWidthAsParent = FALSE ;
		pFrameChild->GetWidthAsParent(&bChildWidthAsParent) ;
		if (bChildWidthAsParent)
		{
			CSize szEstimateSize(0, 0) ;
			szEstimateSize.cx   = rcContainer.Width() - rcChildMargin.left - rcChildMargin.right ;
			szEstimateSize.cy   = -1 ;
			pFrameInternal->SetEstimateSize(szEstimateSize) ;
		}

		BOOL bChildHeightAsParent = FALSE ;
		pFrameChild->GetHeightAsParent(&bChildHeightAsParent) ;
		if (bChildHeightAsParent)
		{
			CSize szEstimateSize(-1, 0) ;
			pFrameInternal->SetEstimateSize(szEstimateSize) ;
		}

		CSize szChildChild(0, 0) ;
		pFrameChild->GetSize(&szChildChild) ;

		CRect rcTarget(0, 0, 0, 0) ;
		rcTarget.left   = rcContainer.left + rcChildMargin.left ;
		rcTarget.top    = nCurrentLayout + rcChildMargin.top ;
		rcTarget.right  = rcTarget.left + rcContainer.Width() ;
		rcTarget.bottom = rcTarget.top + szChildChild.cy ;
		nCurrentLayout += szChildChild.cy + rcChildMargin.top + rcChildMargin.bottom ;

		pFrameInternal->SetLayoutRect(rcTarget) ;
	}
	return S_OK ;
}

HRESULT CCUILayoutMenu::CalcSize(IUIFrame* pHostFrame, SIZE szOld, SIZE* pOutSize)
{
	DEBUG_ASSERT(pHostFrame) ;
	IF_RETURN(NULL == pHostFrame, E_INVALIDARG) ;
	DEBUG_ASSERT(pOutSize) ;
	IF_RETURN(NULL == pOutSize, E_INVALIDARG) ;

	BOOL bAutoWidth = FALSE, bAutoHeight = FALSE ;
	pHostFrame->GetAutoWidth(&bAutoWidth) ;
	pHostFrame->GetAutoHeight(&bAutoHeight) ;

	if (!bAutoWidth && !bAutoHeight)
	{
		*pOutSize = szOld ;
		return S_OK ;
	}

	CSize _calcSize = szOld ;
	CRect _rcPadding(0, 0, 0, 0) ;
	pHostFrame->GetPadding(_rcPadding) ;
	CRect _rcExtPadding(0, 0, 0, 0) ;
	CComQIPtr<IUIFrameInternal> pFrameInternal = pHostFrame ;
	if (pFrameInternal)
	{
		pFrameInternal->GetExtPadding(&_rcExtPadding) ;
	}

	if (bAutoWidth)
	{
		_calcSize.cx = 0 ;

		LONG lChildrenCount = 0 ;
		pHostFrame->GetChildrenCount(&lChildrenCount) ;
		for (INT i = 0; i < lChildrenCount; ++i)
		{
			CComPtr<IUIElement> pElement ;
			pHostFrame->GetChildByIndex(i, &pElement) ;
			CComQIPtr<IUIFrame> pFrame = pElement ;
			IF_CONTINUE(NULL == pFrame) ;

			CComQIPtr<IUIFrameInternal> pFrameInternal = pFrame ;
			IF_CONTINUE(NULL == pFrameInternal) ;

			BOOL bHidden = FALSE ;
			pFrame->GetHidden(&bHidden) ;
			IF_CONTINUE(TRUE == bHidden) ;

			BOOL bFloat = TRUE ;
			pFrame->GetFloat(&bFloat) ;
			IF_CONTINUE(TRUE == bFloat) ;

			BOOL bChildWidthAsParent = FALSE ;
			pFrame->GetWidthAsParent(&bChildWidthAsParent) ;
			IF_CONTINUE(bChildWidthAsParent) ;

			CSize szFrame(0, 0) ;
			pFrame->GetSize(&szFrame) ;

			CRect rcFrameMargin(0, 0, 0, 0) ;
			pFrame->GetMargin(&rcFrameMargin) ;

			if (szFrame.cx + rcFrameMargin.left + rcFrameMargin.right > _calcSize.cx)
			{
				_calcSize.cx = szFrame.cx + rcFrameMargin.left + rcFrameMargin.right ;
			}
		}
	}

	if (bAutoHeight)
	{
		_calcSize.cy = 0 ;

		LONG lChildrenCount = 0 ;
		pHostFrame->GetChildrenCount(&lChildrenCount) ;
		for (INT i = 0; i < lChildrenCount; ++i)
		{
			CComPtr<IUIElement> pElement ;
			pHostFrame->GetChildByIndex(i, &pElement) ;
			CComQIPtr<IUIFrame> pFrame = pElement ;
			IF_CONTINUE(NULL == pFrame) ;

			CComQIPtr<IUIFrameInternal> pFrameInternal = pFrame ;
			IF_CONTINUE(NULL == pFrameInternal) ;

			BOOL bHidden = FALSE ;
			pFrame->GetHidden(&bHidden) ;
			IF_CONTINUE(TRUE == bHidden) ;

			BOOL bFloat = TRUE ;
			pFrame->GetFloat(&bFloat) ;
			IF_CONTINUE(TRUE == bFloat) ;

			BOOL bChildHeightAsParent = FALSE ;
			pFrame->GetHeightAsParent(&bChildHeightAsParent) ;
			IF_CONTINUE(bChildHeightAsParent) ;

			CRect rcFrameMargin(0, 0, 0, 0) ;
			pFrame->GetMargin(&rcFrameMargin) ;

			BOOL bChildAutoHeight = FALSE ;
			pFrame->GetAutoHeight(&bChildAutoHeight) ;

			if (bChildAutoHeight)
			{
				INT nWidth = _calcSize.cx - rcFrameMargin.left - rcFrameMargin.right ;
				pFrameInternal->SetEstimateSize(CSize(nWidth, -1)) ;
			}

			CSize szFrame(0, 0) ;
			pFrame->GetSize(&szFrame) ;
			_calcSize.cy += szFrame.cy + rcFrameMargin.top + rcFrameMargin.bottom ;
		}
	}

	_calcSize.cx += _rcPadding.left + _rcPadding.right + _rcExtPadding.left + _rcExtPadding.right ;
	_calcSize.cy += _rcPadding.top + _rcPadding.bottom + _rcExtPadding.top + _rcExtPadding.bottom ;
	*pOutSize = _calcSize ;
	return S_OK ;
}

