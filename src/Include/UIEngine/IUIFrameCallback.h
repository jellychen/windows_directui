#pragma once

__interface IUIFrame ;
[idl_quote("interface IUIFrame")] ;


// Destory Callback
[
	object ,
	uuid("A0740CD7-6B28-405b-92CB-F72C06E3BBC5") ,
	pointer_default(unique)
]
__interface IUIDestoryCallback : IDispatch
{
	HRESULT OnDestory   (IUIFrame* pFrame) ;
} ;

COMMON_SINK_BEGIN(CComSinkUIDestoryCallback)
COMMON_SINK_FUNC(OnDestory, (IUIFrame* pFrame), (pFrame))
COMMON_SINK_END()
DECLARE_COMMON_SINK_PTR(CComSinkUIDestoryCallback, IUIDestoryCallback)

// Event Callback
[
	object ,
	uuid("44E5BA8C-98F6-4536-A655-D7C4A04BC58F") ,
	pointer_default(unique)
]
__interface IUIEventCallback : IDispatch
{
	HRESULT OnEvent     (IUIFrame* pFrame, INT nEventId, tEventArg* pArgs) ;
} ;

COMMON_SINK_BEGIN(CComSinkUIEventCallback)
COMMON_SINK_FUNC(OnEvent, (IUIFrame* pFrame, INT nEventId, tEventArg* pArgs), (pFrame, nEventId, pArgs))
COMMON_SINK_END()
DECLARE_COMMON_SINK_PTR(CComSinkUIEventCallback, IUIEventCallback)