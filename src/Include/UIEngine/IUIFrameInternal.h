#pragma once

__interface IUIFrame ;
[idl_quote("interface IUIFrame;")] ;

[
	object ,
	uuid("27F08CB1-FE7C-4b73-90BD-BB5CA760DB6D") ,
	pointer_default(unique)
]
__interface IUIFrameInternal : IDispatch
{
	HRESULT Layout                  () ;
	HRESULT SetExtPadding			(RECT rcPadding) ;
	HRESULT GetExtPadding			(RECT* prcPadding) ;
	HRESULT Synchronize             (BOOL bErase) ;
	HRESULT SynchronizeDeeply       (BOOL bErase) ;
	HRESULT SetEstimateSize         (SIZE szEstimate) ;
	HRESULT SetLayoutRect           (RECT rcLayout) ;
	HRESULT GetLayoutRect           (RECT* prcLayout) ;
	HRESULT DragBegin               () ;
	HRESULT Dragging                (POINT ptOld, POINT ptTarget, POINT* ptOut) ;
	HRESULT DragEnd                 () ;
	HRESULT GetMousePosInternal     (POINT* pptPoint) ;
	HRESULT SetCaptureInternal      (BOOL bCapture, IUIFrame* pFrame) ;
	HRESULT GetCaptureInternal      (IUIFrame** ppFrame) ;
	HRESULT SynchronizeInternal     (IUIFrame* pFrame, BOOL bErase) ;
	HRESULT InvalidateInternal      (IUIFrame* pFrame) ;
	HRESULT InvalidateLayout        (IUIFrame* pFrame) ;
	HRESULT MarkReCalcsize          () ;
	HRESULT MarkParentReCalcsize    () ;
	HRESULT MarkRelayout            () ;
	HRESULT MarkParentRelayout      () ;
	HRESULT NotifyAlphaChange       () ;
} ;

[
	object ,
	uuid("3B832133-696E-4F2A-87B6-988887B1F21F") ,
	pointer_default(unique)
]
__interface IUIAddFrame : IDispatch
{
	HRESULT AddFrameBegin           () ;
	HRESULT AddFrame                (IUIFrame* pFrame) ;
	HRESULT AddFrameEnd             () ;
} ;

[
	object ,
	uuid("5A508A9E-8A0E-439f-867B-B7EFABFFD8AE") ,
	pointer_default(unique)
]
__interface IUISetFrame : IDispatch
{
	HRESULT SetFrame                (IUIFrame* pFrame) ;
} ;