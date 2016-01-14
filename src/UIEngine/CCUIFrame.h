#pragma once
#include "Include/UIEngine/IUIFrame.h"
#include "Include/UIEngine/TUICustomElement.h"
#include "Include/UIEngine/IUIFrameInternal.h"
#include "Include/UIEngine/IUIMessageStream.h"
#include "Include/UIEngine/IUICalcSize.h"
#include "Include/UIEngine/IUIFrameDef.h"
#include <map>
#include <vector>

typedef std::map<LONG, CComPtr<IUIDestoryCallback>> MAP_DESTORY_LISTEN_POOL ;
typedef std::map<LONG, CComPtr<IUIEventCallback>>   MAP_EVENT_LISTEN_POOL ;
typedef std::map<INT, MAP_EVENT_LISTEN_POOL>        MAP_EVENT_LISTENER ;

[
	default(IUIFrame) ,
	threading(free) ,
	uuid("7BC72638-E9EA-41ec-89E9-F4678EA5939B") ,
	coclass
]
class ATL_NO_VTABLE CUIFrame 
	: public TUICustomElement<IUIFrame, IUIElement>
	, public IDispatchImpl<IUIFrameInternal>
	, public IDispatchImpl<IUICalcSize>
	, public IDispatchImpl<IUIMessageStream>
{
public:
	DECLARE_PROTECT_FINAL_CONSTRUCT() ;
	CUIFrame() ;
	virtual ~CUIFrame() ;
	HRESULT FinalConstruct() ;
	VOID    FinalRelease() ;

public:
	// IUIFrame
	HRESULT _call SetSize                   (SIZE szSize) ;
	HRESULT _call GetSize                   (SIZE* pszSize) ;
	HRESULT _call SetLocation               (POINT ptLocation) ;
	HRESULT _call GetLocation               (POINT* pptLocation) ;
	HRESULT _call SetRect                   (RECT rcRect) ;
	HRESULT _call GetRect                   (RECT* prcRect) ;
	HRESULT _call SetMargin                 (RECT rcMargin) ;
	HRESULT _call GetMargin                 (RECT* prcMargin) ;
	HRESULT _call SetPadding                (RECT rcPadding) ;
	HRESULT _call GetPadding                (RECT* prcPadding) ;
	HRESULT _call SetZOrder                 (INT nZOrder) ;
	HRESULT _call GetZOrder                 (INT* pnZOrder) ;
	HRESULT _call SetHidden                 (BOOL bHidden) ;
	HRESULT _call GetHidden                 (BOOL* pbHidden) ;
	HRESULT _call GetVisible                (BOOL* pbVisible) ;
	HRESULT _call SetFloat                  (BOOL bFloat) ;
	HRESULT _call GetFloat                  (BOOL* pbFloat) ;
	HRESULT _call SetEnable                 (BOOL bEnable) ;
	HRESULT _call GetEnable                 (BOOL* pbEnable) ;
	HRESULT _call SetCapture                (BOOL bCapture) ;
	HRESULT _call GetCapture                (BOOL* pbCapture) ;
	HRESULT _call SetState                  (INT nState) ;
	HRESULT _call GetState                  (INT* pnState) ;
	HRESULT _call SetEnableState            (BOOL bEnableState) ;
	HRESULT _call GetEnableState            (BOOL* pbEnableState) ;
	HRESULT _call SetHittest                (INT nHittest) ;
	HRESULT _call GetHittest                (INT* pnHittest) ;
	HRESULT _call SetHoverCursor			(INT nHoverCursor) ;
	HRESULT _call GetHoverCursor			(INT* pnHoverCursor) ;
	HRESULT _call GetAbsolutDepth           (INT* pnDepth) ;
	HRESULT _call GetAbsolutLocation        (POINT* pptLocation) ;
	HRESULT _call GetScreenLocation         (POINT* pptLocation) ;
	HRESULT _call GetAbsolutRect            (RECT* prcRect) ;
	HRESULT _call GetScreenRect             (RECT* prcRect) ;
	HRESULT _call GetAbsolutVisibleRect     (RECT* prcRect) ;

	HRESULT _call SetLayouter				(IUILayout* pLayouter) ;
	HRESULT _call GetLayouter				(IUILayout** ppLayouter) ;

	HRESULT _call Draw                      (IUICanvas* pCanvas) ;
	HRESULT _call Render                    (IUICanvas* pCanvas, RECT rcRender, INT nState) ;
	HRESULT _call SetDoubleBuffer           (BOOL bDoubleBuffer) ;
	HRESULT _call GetDoubleBuffer           (BOOL* pbDoubleBuffer) ;
	HRESULT _call SetAlpha                  (BYTE cAlpha) ;
	HRESULT _call GetAlpha                  (BYTE* pcAlpha) ;
	HRESULT _call GetShowAlpha              (BYTE* pcAlpha) ;
	HRESULT _call SetBkgDraw                (IUIDraw* pBkgDraw) ;
	HRESULT _call GetBkgDraw                (IUIDraw** ppBkgDraw) ;
	HRESULT _call SetBkgDrawAlpha           (BYTE cBkgAlpha) ;
	HRESULT _call GetBkgDrawAlpha           (BYTE* pcBkgAlpha) ;
	HRESULT _call SetBkgMaskDraw            (IUIDraw* pBkgMaskDraw) ;
	HRESULT _call GetBkgMaskDraw            (IUIDraw** ppBkgMaskDraw) ;
	HRESULT _call SetBkgMaskDrawAlpha       (BYTE cBkgMaskAlpha) ;
	HRESULT _call GetBkgMaskDrawAlpha       (BYTE* pcBkgMaskAlpha) ;

	HRESULT _call Update                    (BOOL bFoceLayout, BOOL bFoceSync) ;

	HRESULT _call SetAnchor                 (INT nAnchor) ;
	HRESULT _call SetAnchor                 (BSTR bstrAnchor) ;
	HRESULT _call GetAnchor                 (INT* pnAnchor) ;
	HRESULT _call SetDrift					(INT nDrift) ;
	HRESULT _call SetDrift					(BSTR bstrDrift) ;
	HRESULT _call GetDrift					(INT* pnDrift) ;
	HRESULT _call SetAutoWidth              (BOOL bAutoWidth) ;
	HRESULT _call GetAutoWidth              (BOOL* pbAutoWidth) ;
	HRESULT _call SetAutoHeight             (BOOL bAutoHeight) ;
	HRESULT _call GetAutoHeight             (BOOL* pbAutoHeight) ;
	HRESULT _call SetAutoSize               (BOOL bAutoSize) ;
	HRESULT _call GetAutoSize               (BOOL* pbAutoSize) ;
	HRESULT _call SetMaxAutoSize            (SIZE szMaxAutoSize) ;
	HRESULT _call GetMaxAutoSize            (SIZE* pszMaxAutoSize) ;
	HRESULT _call SetMinAutoSize            (SIZE szMinAutoSize) ;
	HRESULT _call GetMinAutoSize            (SIZE* pszMinAutoSize) ;
	HRESULT _call SetWidthAsParent          (BOOL bWidthAsParent) ;
	HRESULT _call GetWidthAsParent          (BOOL* pbWidthAsParent) ;
	HRESULT _call SetHeightAsParent         (BOOL bHeightAsParent) ;
	HRESULT _call GetHeightAsParent         (BOOL* pbHeightAsParent) ;
	HRESULT _call SetSizeAsParent           (BOOL bSizeAsParent) ;
	HRESULT _call GetSizeAsParent           (BOOL* pbSizeAsParent) ;

	HRESULT _call SetEnableDrag             (BOOL bEnable) ;
	HRESULT _call GetEnableDrag             (BOOL* pbEnable) ;
	HRESULT _call SetDragRange              (RECT rcRange) ;
	HRESULT _call GetDragRange              (RECT* prcRange) ;
	HRESULT _call SetEnableVerticalDrag     (BOOL bEnable) ;
	HRESULT _call GetEnableVerticalDrag     (BOOL* pbEnable) ;
	HRESULT _call SetEnableHorizontalDrag   (BOOL bEnable) ;
	HRESULT _call GetEnableHorizontalDrag   (BOOL* pbEnable) ;

	HRESULT _call SetEnableDBClick          (BOOL bEnable) ;
	HRESULT _call GetEnableDBClick          (BOOL* pbEnable) ;
	HRESULT _call SetIntercepMouse          (BOOL bIntercept) ;
	HRESULT _call GetIntercepMouse          (BOOL* pbIntercept) ;
	HRESULT _call SetTransparentMouse       (BOOL bTransparent) ;
	HRESULT _call GetTransparentMouse       (BOOL* pbTransparent) ;
	HRESULT _call SetIntercepKeyboard		(BOOL bIntercept) ;
	HRESULT _call GetIntercepKeyboard		(BOOL* pbIntercept) ;
	HRESULT _call SetTransparentKeyboard	(BOOL bTransparent) ;
	HRESULT _call GetTransparentKeyboard	(BOOL* pbTransparent) ;

	HRESULT _call Invalidate                () ;
	HRESULT _call InvalidateRect            (RECT rcInvalidate) ;

	HRESULT _call RaiseEvent                (INT nEventId, tEventArg* pArgs) ;
	HRESULT _call AddEventListener          (INT nEventId, IUIEventCallback* pListener) ;
	HRESULT _call DelEventListener          (INT nEventId, IUIEventCallback* pListener) ;
	HRESULT _call AddDestoryListener        (IUIDestoryCallback* pListener) ;
	HRESULT _call DelDestoryListener        (IUIDestoryCallback* pListener) ;

	// IUIFrameInternal
	HRESULT _call Layout                    () ;
	HRESULT _call SetExtPadding				(RECT rcPadding) ;
	HRESULT _call GetExtPadding				(RECT* prcPadding) ;
	HRESULT _call Synchronize               (BOOL bErase) ;
	HRESULT _call SynchronizeDeeply         (BOOL bErase) ;
	HRESULT _call SetEstimateSize           (SIZE szEstimate) ;
	HRESULT _call SetLayoutRect             (RECT rcLayout) ;
	HRESULT _call GetLayoutRect             (RECT* prcLayout) ;
	HRESULT _call DragBegin                 () ;
	HRESULT _call Dragging                  (POINT ptOld, POINT ptTarget, POINT* ptOut) ;
	HRESULT _call DragEnd                   () ;
	HRESULT _call GetMousePosInternal       (POINT* pptPoint) ;
	HRESULT _call SetCaptureInternal        (BOOL bCapture, IUIFrame* pFrame) ;
	HRESULT _call GetCaptureInternal        (IUIFrame** ppFrame) ;
	HRESULT _call SynchronizeInternal       (IUIFrame* pFrame, BOOL bErase) ;
	HRESULT _call InvalidateInternal        (IUIFrame* pFrame) ;
	HRESULT _call InvalidateLayout          (IUIFrame* pFrame) ;
	HRESULT _call MarkReCalcsize            () ;
	HRESULT _call MarkParentReCalcsize      () ;
	HRESULT _call MarkRelayout              () ;
	HRESULT _call MarkParentRelayout        () ;
	HRESULT _call NotifyAlphaChange         () ;

	// IUICalcSize
	HRESULT _call CalcSize					(SIZE szOld, SIZE* pszCalcOut) ;

	//IUIElement
	HRESULT _call AddChildFront             (IUIElement* pChild) ;
	HRESULT _call AddChildBack              (IUIElement* pChild) ;
	HRESULT _call InsertChild               (INT nIndex, IUIElement* pChild) ;
	HRESULT _call RemoveChildByIndex        (INT nIndex) ;

	// IUIMessageStream
	HRESULT _call OnMessageSink             (IUIFrame* pTarget, tMsgArg* pArg, BOOL* pbHandle, BOOL* pbIntercept) ;
	HRESULT _call OnMessage                 (IUIFrame* pTarget, tMsgArg* pArg) ;
	HRESULT _call OnMessageRiase            (IUIFrame* pTarget, tMsgArg* pArg, BOOL* pbIntercept) ;

public:
	HRESULT _call SetAttribute              (ICVarData* pAttrData) ;

private:
	CSize                                   m_szFrameSize ;
	CPoint                                  m_ptFrameLocation ;
	CRect                                   m_rcFrameMargin ;
	CRect                                   m_rcFramePadding ;
	CRect									m_rcFrameExtPadding ;
	INT                                     m_nFrameZOrder ;
	BYTE                                    m_cFrameAlpha ;
	BYTE                                    m_cFrameShowAlpha ;
	BOOL                                    m_bCacheFrameShowAlpha ;
	BOOL                                    m_bFrameHidden ;
	BOOL                                    m_bFrameFloat ;
	BOOL                                    m_bFrameEnable ;
	BOOL                                    m_bEnableFrameState ;
	INT                                     m_nFrameState ;
	INT                                     m_nFrameHittest ;
	INT										m_nFrameHoverCursor ;
	INT                                     m_bFrameDepth ;
	BOOL                                    m_bCacheFrameDepth ;
	CPoint                                  m_ptAbsolutLocation ;
	BOOL                                    m_bCacheAbsolutLocation ;
	CRect                                   m_rcVisibleRect ;
	BOOL                                    m_bCacheVisibleRect ;
	BOOL                                    m_bDoubleBuffer ;
	CComPtr<IUICanvas>                      m_pDoubleBufferCanvas ;
	CComPtr<IUIDraw>                        m_pBkgDraw ;
	BYTE                                    m_cBkgDrawAlpha ;
	CComPtr<IUIDraw>                        m_pBkgMaskDraw ;
	BYTE                                    m_cBkgMaskDrawAlpha ;
	INT                                     m_nAnchor ;
	INT										m_nDrift ;
	BOOL                                    m_bAutoWidth ;
	BOOL                                    m_bAutoHeight ;
	CSize                                   m_szAutoMinSize ;
	CSize                                   m_szAutoMaxSize ;
	BOOL                                    m_bWidthAsParent ;
	BOOL                                    m_bHeightAsParent ;
	BOOL                                    m_bEnableVerticalDrag ;
	BOOL                                    m_bEnableHorizontalDrag ;
	CRect                                   m_rcDragRange ;
	BOOL                                    m_bDragging ;
	BOOL                                    m_bLBtnDown ;
	POINT                                   m_ptLBtnDownLocation ;
	BOOL                                    m_bEnableDBClick ;
	BOOL                                    m_bInterceptMouse ;
	BOOL                                    m_bTransparentMouse ;
	BOOL                                    m_bInterceptKeyboard ;
	BOOL                                    m_bTransparentKeyboard ;
	BOOL                                    m_bUpdating ;
	BOOL                                    m_bReCalcsize ;
	BOOL                                    m_bRelayout ;
	BOOL									m_bReRender ;
	/*BOOL                                    m_bHaveRelayoutChild ;*/
	BOOL                                    m_bNeedSynch ;
	/*BOOL                                    m_bHaveNeedSychChild ;*/
	CComPtr<IUILayout>						m_pLayouter ;
	BOOL                                    m_bEstimateSizeChange ;
	MAP_DESTORY_LISTEN_POOL                 m_mapDestoryListenerPool ;
	MAP_EVENT_LISTENER                      m_mapEventListenerPool ;
} ;
