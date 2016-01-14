#pragma once

[
    object ,
    uuid("E9721F60-6048-4ba2-852F-5B47D9156B74") ,
    pointer_default(unique)
]
__interface IUIMsgLoopFunction : IDispatch
{
    HRESULT OnMsgLoop               () ;
} ;

COMMON_SINK_BEGIN(CComSinkUIMsgLoopFunction)
COMMON_SINK_FUNC(OnMsgLoop, (), ())
COMMON_SINK_END()
DECLARE_COMMON_SINK_PTR(CComSinkUIMsgLoopFunction, IUIMsgLoopFunction)

[
    object ,
    uuid("BE3E565A-BF1C-4f11-9975-DA1D1BA1F13E") ,
    pointer_default(unique)
]
__interface IUIMsgLoopCallback : IDispatch
{
    HRESULT OnMsgArrive             (MSG* pMsg) ;
    HRESULT OnMsgComplete           (MSG* pMsg) ;
} ;

COMMON_SINK_BEGIN(CComSinkUIMsgLoopCallback)
COMMON_SINK_FUNC(OnMsgArrive, (MSG* pMsg), (pMsg))
COMMON_SINK_FUNC(OnMsgComplete, (MSG* pMsg), (pMsg))
COMMON_SINK_END()
DECLARE_COMMON_SINK_PTR(CComSinkUIMsgLoopCallback, IUIMsgLoopCallback)

[
    object ,
    uuid("DF7BBD5E-490E-4594-8329-E17A6E09C50D") ,
    pointer_default(unique)
]
__interface IUIMsgLoop : IDispatch
{
    HRESULT StartLoop               () ;
    HRESULT QuitCurrentLoop         () ;
    HRESULT ShouldQuitLoop          () ;
	HRESULT ForceQuitAllLoop		() ;
	HRESULT SetMsgLoopFunction      (IUIMsgLoopFunction* pMsgLoop) ;
    HRESULT RegisterLoopCallback    (IUIMsgLoopCallback* pCallback) ;
    HRESULT UnRegisterLoopCallback  (IUIMsgLoopCallback* pCallback) ;
    HRESULT NotifyMsgArrive         (MSG* pMsg) ;
    HRESULT NotifyMsgComplete       (MSG* pMsg) ;
} ;
