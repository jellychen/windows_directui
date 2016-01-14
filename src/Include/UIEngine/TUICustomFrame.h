#pragma once
#include "Include/UIEngine/IUIFrame.h"
#include "Include/UIEngine/IUIFrameInternal.h"
#include "Include/UIEngine/IUIMessageStream.h"
#include "Include/UIEngine/IUICalcSize.h"
#include "Include/UIEngine/TUICustomElement.h"

template<typename IActual, typename IBase>
class TUICustomFrame
	: public TUICustomElement<IActual, IBase>
	, public IDispatchImpl<IUIFrameInternal>
	, public IDispatchImpl<IUICalcSize>
	, public IDispatchImpl<IUIMessageStream>
{
public:
	//IUIFrame
	HRESULT _call SetSize(SIZE szSize)
	{
		return this->m_pRawObject->SetSize(szSize) ;
	}

	HRESULT _call GetSize(SIZE* pszSize)
	{
		return this->m_pRawObject->GetSize(pszSize) ;
	}

	HRESULT _call SetLocation(POINT ptLocation)
	{
		return this->m_pRawObject->SetLocation(ptLocation) ;
	}

	HRESULT _call GetLocation(POINT* pptLocation)
	{
		return this->m_pRawObject->GetLocation(pptLocation) ;
	}

	HRESULT _call SetRect(RECT rcRect)
	{
		return this->m_pRawObject->SetRect(rcRect) ;
	}

	HRESULT _call GetRect(RECT* prcRect)
	{
		return this->m_pRawObject->GetRect(prcRect) ;
	}

	HRESULT _call SetMargin(RECT rcMargin)
	{
		return this->m_pRawObject->SetMargin(rcMargin) ;
	}

	HRESULT _call GetMargin(RECT* prcMargin)
	{
		return this->m_pRawObject->GetMargin(prcMargin) ;
	}

	HRESULT _call SetPadding(RECT rcPadding)
	{
		return this->m_pRawObject->SetPadding(rcPadding) ;
	}

	HRESULT _call GetPadding(RECT* prcPadding)
	{
		return this->m_pRawObject->GetPadding(prcPadding) ;
	}

	HRESULT _call SetZOrder(INT nZOrder)
	{
		return this->m_pRawObject->SetZOrder(nZOrder) ;
	}

	HRESULT _call GetZOrder(INT* pnZOrder)
	{
		return this->m_pRawObject->GetZOrder(pnZOrder) ;
	}

	HRESULT _call SetHidden(BOOL bHidden)
	{
		return this->m_pRawObject->SetHidden(bHidden) ;
	}

	HRESULT _call GetHidden(BOOL* pbHidden)
	{
		return this->m_pRawObject->GetHidden(pbHidden) ;
	}

	HRESULT _call GetVisible(BOOL* pbVisible)
	{
		return this->m_pRawObject->GetVisible(pbVisible) ;
	}

	HRESULT _call SetFloat(BOOL bFloat)
	{
		return this->m_pRawObject->SetFloat(bFloat) ;
	}

	HRESULT _call GetFloat(BOOL* pbFloat)
	{
		return this->m_pRawObject->GetFloat(pbFloat) ;
	}

	HRESULT _call SetEnable(BOOL bEnable)
	{
		return this->m_pRawObject->SetEnable(bEnable) ;
	}

	HRESULT _call GetEnable(BOOL* pbEnable)
	{
		return this->m_pRawObject->GetEnable(pbEnable) ;
	}

	HRESULT _call SetCapture(BOOL bCapture)
	{
		return this->m_pRawObject->SetCapture(bCapture) ;
	}

	HRESULT _call GetCapture(BOOL* pbCapture)
	{
		return this->m_pRawObject->GetCapture(pbCapture) ;
	}

	HRESULT _call SetState(INT nState)
	{
		return this->m_pRawObject->SetState(nState) ;
	}

	HRESULT _call GetState(INT* pnState)
	{
		return this->m_pRawObject->GetState(pnState) ;
	}

	HRESULT _call SetEnableState(BOOL bEnableState)
	{
		return this->m_pRawObject->SetEnableState(bEnableState) ;
	}

	HRESULT _call GetEnableState(BOOL* pbEnableState)
	{
		return this->m_pRawObject->GetEnableState(pbEnableState) ;
	}

	HRESULT	_call SetCaptureRender(BOOL bCaptureRender)
	{
		return this->m_pRawObject->SetCaptureRender(bCaptureRender) ;
	}
	
	HRESULT	_call GetCaptureRender(BOOL* pbCaptureRender)
	{
		return this->m_pRawObject->GetCaptureRender(pbCaptureRender) ;
	}

	HRESULT _call SetHittest(INT nHittest)
	{
		return this->m_pRawObject->SetHittest(nHittest) ;
	}

	HRESULT _call GetHittest(INT* pnHittest)
	{
		return this->m_pRawObject->GetHittest(pnHittest) ;
	}

	HRESULT _call SetHoverCursor(INT nHoverCursor)
	{
		return this->m_pRawObject->SetHoverCursor(nHoverCursor) ;
	}

	HRESULT _call GetHoverCursor(INT* pnHoverCursor)
	{
		return this->m_pRawObject->GetHoverCursor(pnHoverCursor) ;
	}

	HRESULT _call GetAbsolutDepth(INT* pnDepth)
	{
		return this->m_pRawObject->GetAbsolutDepth(pnDepth) ;
	}

	HRESULT _call GetAbsolutLocation(POINT* pptLocation)
	{
		return this->m_pRawObject->GetAbsolutLocation(pptLocation) ;
	}

	HRESULT _call GetScreenLocation(POINT* pptLocation)
	{
		return this->m_pRawObject->GetScreenLocation(pptLocation) ;
	}

	HRESULT _call GetAbsolutRect(RECT* prcRect)
	{
		return this->m_pRawObject->GetAbsolutRect(prcRect) ;
	}

	HRESULT _call GetScreenRect(RECT* prcRect)
	{
		return this->m_pRawObject->GetScreenRect(prcRect) ;
	}

	HRESULT _call GetAbsolutVisibleRect(RECT* prcRect)
	{
		return this->m_pRawObject->GetAbsolutVisibleRect(prcRect) ;
	}

	HRESULT _call SetLayouter(IUILayout* pLayouter)
	{
		return this->m_pRawObject->SetLayouter(pLayouter) ;
	}

	HRESULT _call GetLayouter(IUILayout** ppLayouter)
	{
		return this->m_pRawObject->GetLayouter(ppLayouter) ;
	}

	HRESULT _call Draw(IUICanvas* pCanvas)
	{
		return this->m_pRawObject->Draw(pCanvas) ;
	}

	HRESULT _call Render(IUICanvas* pCanvas, RECT rcRender, INT nState)
	{
		return this->m_pRawObject->Render(pCanvas, rcRender, nState) ;
	}

	HRESULT _call SetDoubleBuffer(BOOL bDoubleBuffer)
	{
		return this->m_pRawObject->SetDoubleBuffer(bDoubleBuffer) ;
	}

	HRESULT _call GetDoubleBuffer(BOOL* pbDoubleBuffer)
	{
		return this->m_pRawObject->GetDoubleBuffer(pbDoubleBuffer) ;
	}

	HRESULT _call SetAlpha(BYTE cAlpha)
	{
		return this->m_pRawObject->SetAlpha(cAlpha) ;
	}

	HRESULT _call GetAlpha(BYTE* pcAlpha)
	{
		return this->m_pRawObject->GetAlpha(pcAlpha) ;
	}

	HRESULT _call GetShowAlpha(BYTE* pcAlpha)
	{
		return this->m_pRawObject->GetShowAlpha(pcAlpha) ;
	}

	HRESULT _call SetBkgDraw(IUIDraw* pBkgDraw)
	{
		return this->m_pRawObject->SetBkgDraw(pBkgDraw) ;
	}

	HRESULT _call GetBkgDraw(IUIDraw** ppBkgDraw)
	{
		return this->m_pRawObject->GetBkgDraw(ppBkgDraw) ;
	}

	HRESULT _call SetBkgDrawAlpha(BYTE cBkgAlpha)
	{
		return this->m_pRawObject->SetBkgDrawAlpha(cBkgAlpha) ;
	}

	HRESULT _call GetBkgDrawAlpha(BYTE* pcBkgAlpha)
	{
		return this->m_pRawObject->GetBkgDrawAlpha(pcBkgAlpha) ;
	}

	HRESULT _call SetBkgMaskDraw(IUIDraw* pBkgMaskDraw)
	{
		return this->m_pRawObject->SetBkgMaskDraw(pBkgMaskDraw) ;
	}

	HRESULT _call GetBkgMaskDraw(IUIDraw** ppBkgMaskDraw)
	{
		return this->m_pRawObject->GetBkgMaskDraw(ppBkgMaskDraw) ;
	}

	HRESULT _call SetBkgMaskDrawAlpha(BYTE cBkgMaskAlpha)
	{
		return this->m_pRawObject->SetBkgMaskDrawAlpha(cBkgMaskAlpha) ;
	}

	HRESULT _call GetBkgMaskDrawAlpha(BYTE* pcBkgMaskAlpha)
	{
		return this->m_pRawObject->GetBkgMaskDrawAlpha(pcBkgMaskAlpha) ;
	}

	HRESULT _call Update(BOOL bFoceLayout, BOOL bFoceSync)
	{
		return this->m_pRawObject->Update(bFoceLayout, bFoceSync) ;
	}

	HRESULT _call SetAnchor(INT nAnchor)
	{
		return this->m_pRawObject->SetAnchor(nAnchor) ;
	}

	HRESULT _call GetAnchor(INT* pAnchor)
	{
		return this->m_pRawObject->GetAnchor(pAnchor) ;
	}

	HRESULT _call SetDrift(INT nDrift)
	{
		return this->m_pRawObject->SetDrift(nDrift) ;
	}

	HRESULT _call GetDrift(INT* pnDrift)
	{
		return this->m_pRawObject->GetDrift(pnDrift) ;
	}

	HRESULT _call SetAutoWidth(BOOL bAutoWidth)
	{
		return this->m_pRawObject->SetAutoWidth(bAutoWidth) ;
	}

	HRESULT _call GetAutoWidth(BOOL* pbAutoWidth)
	{
		return this->m_pRawObject->GetAutoWidth(pbAutoWidth) ;
	}

	HRESULT _call SetAutoHeight(BOOL bAutoHeight)
	{
		return this->m_pRawObject->SetAutoHeight(bAutoHeight) ;
	}

	HRESULT _call GetAutoHeight(BOOL* pbAutoHeight)
	{
		return this->m_pRawObject->GetAutoHeight(pbAutoHeight) ;
	}

	HRESULT _call SetAutoSize(BOOL bAutoSize)
	{
		return this->m_pRawObject->SetAutoSize(bAutoSize) ;
	}

	HRESULT _call GetAutoSize(BOOL* pbAutoSize)
	{
		return this->m_pRawObject->GetAutoSize(pbAutoSize) ;
	}

	HRESULT _call SetMaxAutoSize(SIZE szMaxAutoSize)
	{
		return this->m_pRawObject->SetMaxAutoSize(szMaxAutoSize) ;
	}

	HRESULT _call GetMaxAutoSize(SIZE* pszMaxAutoSize)
	{
		return this->m_pRawObject->GetMaxAutoSize(pszMaxAutoSize) ;
	}

	HRESULT _call SetMinAutoSize(SIZE szMinAutoSize)
	{
		return this->m_pRawObject->SetMinAutoSize(szMinAutoSize) ;
	}

	HRESULT _call GetMinAutoSize(SIZE* pszMinAutoSize)
	{
		return this->m_pRawObject->GetMinAutoSize(pszMinAutoSize) ;
	}

	HRESULT _call SetWidthAsParent(BOOL bWidthAsParent)
	{
		return this->m_pRawObject->SetWidthAsParent(bWidthAsParent) ;
	}

	HRESULT _call GetWidthAsParent(BOOL* pbWidthAsParent)
	{
		return this->m_pRawObject->GetWidthAsParent(pbWidthAsParent) ;
	}

	HRESULT _call SetHeightAsParent(BOOL bHeightAsParent)
	{
		return this->m_pRawObject->SetHeightAsParent(bHeightAsParent) ;
	}

	HRESULT _call GetHeightAsParent(BOOL* pbHeightAsParent)
	{
		return this->m_pRawObject->GetHeightAsParent(pbHeightAsParent) ;
	}

	HRESULT _call SetSizeAsParent(BOOL bSizeAsParent)
	{
		return this->m_pRawObject->SetSizeAsParent(bSizeAsParent) ;
	}

	HRESULT _call GetSizeAsParent(BOOL* pbSizeAsParent)
	{
		return this->m_pRawObject->GetSizeAsParent(pbSizeAsParent) ;
	}

	HRESULT _call SetEnableDrag(BOOL bEnable)
	{
		return this->m_pRawObject->SetEnableDrag(bEnable) ;
	}

	HRESULT _call GetEnableDrag(BOOL* pbEnable)
	{
		return this->m_pRawObject->GetEnableDrag(pbEnable) ;
	}

	HRESULT _call SetDragRange(RECT rcRange)
	{
		return this->m_pRawObject->SetDragRange(rcRange) ;
	}

	HRESULT _call GetDragRange(RECT* prcRange)
	{
		return this->m_pRawObject->GetDragRange(prcRange) ;
	}

	HRESULT _call SetEnableVerticalDrag(BOOL bEnable)
	{
		return this->m_pRawObject->SetEnableVerticalDrag(bEnable) ;
	}

	HRESULT _call GetEnableVerticalDrag(BOOL* pbEnable)
	{
		return this->m_pRawObject->GetEnableVerticalDrag(pbEnable) ;
	}

	HRESULT _call SetEnableHorizontalDrag(BOOL bEnable)
	{
		return this->m_pRawObject->SetEnableHorizontalDrag(bEnable) ;
	}

	HRESULT _call GetEnableHorizontalDrag(BOOL* pbEnable)
	{
		return this->m_pRawObject->GetEnableHorizontalDrag(pbEnable) ;
	}

	HRESULT _call SetEnableDBClick(BOOL bEnable)
	{
		return this->m_pRawObject->SetEnableDBClick(bEnable) ;
	}

	HRESULT _call GetEnableDBClick(BOOL* pbEnable)
	{
		return this->m_pRawObject->GetEnableDBClick(pbEnable) ;
	}

	HRESULT _call SetIntercepMouse(BOOL bIntercept)
	{
		return this->m_pRawObject->SetIntercepMouse(bIntercept) ;
	}

	HRESULT _call GetIntercepMouse(BOOL* pbIntercept)
	{
		return this->m_pRawObject->GetIntercepMouse(pbIntercept) ;
	}

	HRESULT _call SetTransparentMouse(BOOL bTransparent)
	{
		return this->m_pRawObject->SetTransparentMouse(bTransparent) ;
	}

	HRESULT _call GetTransparentMouse(BOOL* pbTransparent)
	{
		return this->m_pRawObject->GetTransparentMouse(pbTransparent) ;
	}

	HRESULT _call SetIntercepKeyboard(BOOL bIntercept)
	{
		return this->m_pRawObject->SetIntercepKeyboard(bIntercept) ;
	}

	HRESULT _call GetIntercepKeyboard(BOOL* pbIntercept)
	{
		return this->m_pRawObject->GetIntercepKeyboard(pbIntercept) ;
	}

	HRESULT _call SetTransparentKeyboard(BOOL bTransparent)
	{
		return this->m_pRawObject->SetTransparentKeyboard(bTransparent) ;
	}

	HRESULT _call GetTransparentKeyboard(BOOL* pbTransparent)
	{
		return this->m_pRawObject->GetTransparentKeyboard(pbTransparent) ;
	}

	HRESULT _call Invalidate()
	{
		return this->m_pRawObject->Invalidate() ;
	}

	HRESULT _call InvalidateRect(RECT rcInvalidate)
	{
		return this->m_pRawObject->InvalidateRect(rcInvalidate) ;
	}

	HRESULT _call RaiseEvent(INT nEventId, tEventArg* pArgs)
	{
		return this->m_pRawObject->RaiseEvent(nEventId, pArgs) ;
	}

	HRESULT _call AddEventListener(INT nEventId, IUIEventCallback* pListener)
	{
		return this->m_pRawObject->AddEventListener(nEventId, pListener) ;
	}

	HRESULT _call DelEventListener(INT nEventId, IUIEventCallback* pListener)
	{
		return this->m_pRawObject->DelEventListener(nEventId, pListener) ;
	}

	HRESULT _call AddDestoryListener(IUIDestoryCallback* pListener)
	{
		return this->m_pRawObject->AddDestoryListener(pListener) ;
	}

	HRESULT _call DelDestoryListener(IUIDestoryCallback* pListener)
	{
		return this->m_pRawObject->DelDestoryListener(pListener) ;
	}

	//IUIFrameInternal
	HRESULT _call Layout()
	{
		return GetInterfaceEntity<IUIFrameInternal>(m_pRawObject)->Layout() ;
	}

	HRESULT _call SetExtPadding(RECT rcPadding)
	{
		return GetInterfaceEntity<IUIFrameInternal>(m_pRawObject)->SetExtPadding(rcPadding) ;
	}

	HRESULT _call GetExtPadding(RECT* prcPadding)
	{
		return GetInterfaceEntity<IUIFrameInternal>(m_pRawObject)->GetExtPadding(prcPadding) ;
	}

	HRESULT _call Synchronize(BOOL bErase)
	{
		return GetInterfaceEntity<IUIFrameInternal>(m_pRawObject)->Synchronize(bErase) ;
	}

	HRESULT _call SynchronizeDeeply(BOOL bErase)
	{
		return GetInterfaceEntity<IUIFrameInternal>(m_pRawObject)->SynchronizeDeeply(bErase) ;
	}

	HRESULT _call SetEstimateSize(SIZE szEstimate)
	{
		return GetInterfaceEntity<IUIFrameInternal>(m_pRawObject)->SetEstimateSize(szEstimate) ;
	}

	HRESULT _call SetLayoutRect(RECT rcLayout)
	{
		return GetInterfaceEntity<IUIFrameInternal>(m_pRawObject)->SetLayoutRect(rcLayout) ;
	}

	HRESULT _call GetLayoutRect(RECT* prcLayout)
	{
		return GetInterfaceEntity<IUIFrameInternal>(m_pRawObject)->GetLayoutRect(prcLayout) ;
	}

	HRESULT _call DragBegin()
	{
		return GetInterfaceEntity<IUIFrameInternal>(m_pRawObject)->DragBegin() ;
	}

	HRESULT _call Dragging(POINT ptOld, POINT ptTarget, POINT* ptOut)
	{
		return GetInterfaceEntity<IUIFrameInternal>(m_pRawObject)->Dragging(ptOld, ptTarget, ptOut) ;
	}

	HRESULT _call DragEnd()
	{
		return GetInterfaceEntity<IUIFrameInternal>(m_pRawObject)->DragEnd() ;
	}

	HRESULT _call GetMousePosInternal(POINT* pptPoint)
	{
		return GetInterfaceEntity<IUIFrameInternal>(m_pRawObject)->GetMousePosInternal(pptPoint) ;
	}

	HRESULT _call SetCaptureInternal(BOOL bCapture, IUIFrame* pFrame)
	{
		return GetInterfaceEntity<IUIFrameInternal>(m_pRawObject)->SetCaptureInternal(bCapture, pFrame) ;
	}

	HRESULT _call GetCaptureInternal(IUIFrame** ppFrame)
	{
		return GetInterfaceEntity<IUIFrameInternal>(m_pRawObject)->GetCaptureInternal(ppFrame) ;
	}

	HRESULT _call SynchronizeInternal(IUIFrame* pFrame, BOOL bErase)
	{
		return GetInterfaceEntity<IUIFrameInternal>(m_pRawObject)->SynchronizeInternal(pFrame, bErase) ;
	}

	HRESULT _call InvalidateInternal(IUIFrame* pFrame)
	{
		return GetInterfaceEntity<IUIFrameInternal>(m_pRawObject)->InvalidateInternal(pFrame) ;
	}

	HRESULT _call InvalidateLayout(IUIFrame* pFrame)
	{
		return GetInterfaceEntity<IUIFrameInternal>(m_pRawObject)->InvalidateLayout(pFrame) ;
	}

	HRESULT _call MarkReCalcsize()
	{
		return GetInterfaceEntity<IUIFrameInternal>(m_pRawObject)->MarkReCalcsize() ;
	}

	HRESULT _call MarkParentReCalcsize()
	{
		return GetInterfaceEntity<IUIFrameInternal>(m_pRawObject)->MarkParentReCalcsize() ;
	}

	HRESULT _call MarkRelayout()
	{
		return GetInterfaceEntity<IUIFrameInternal>(m_pRawObject)->MarkRelayout() ;
	}

	HRESULT _call MarkParentRelayout()
	{
		return GetInterfaceEntity<IUIFrameInternal>(m_pRawObject)->MarkParentRelayout() ;
	}

	HRESULT _call NotifyAlphaChange()
	{
		return GetInterfaceEntity<IUIFrameInternal>(m_pRawObject)->NotifyAlphaChange() ;
	}


	//IUICalcSize
	HRESULT _call CalcSize(SIZE szOld, SIZE* pszCalcOut)
	{
		return GetInterfaceEntity<IUICalcSize>(m_pRawObject)->CalcSize(szOld, pszCalcOut) ;
	}

	//IUIMessageStream
	HRESULT _call OnMessageSink(IUIFrame* pTarget, tMsgArg* pArg, BOOL* pbHandle, BOOL* pbIntercept)
	{
		return GetInterfaceEntity<IUIMessageStream>(m_pRawObject)->OnMessageSink(pTarget, pArg, pbHandle, pbIntercept) ;
	}

	HRESULT _call OnMessage(IUIFrame* pTarget, tMsgArg* pArg)
	{
		return GetInterfaceEntity<IUIMessageStream>(m_pRawObject)->OnMessage(pTarget, pArg) ;
	}

	HRESULT _call OnMessageRiase(IUIFrame* pTarget, tMsgArg* pArg, BOOL* pbIntercept)
	{
		return GetInterfaceEntity<IUIMessageStream>(m_pRawObject)->OnMessageRiase(pTarget, pArg, pbIntercept) ;
	}
} ;