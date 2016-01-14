#pragma once

[
    object ,
    uuid("AE1951A6-DDEE-4CAB-864E-AA259EF7802C") ,
    pointer_default(unique)
]
__interface IUITimerCallback : IDispatch
{
    HRESULT OnTimer (INT nTimerId) ;
} ;

COMMON_SINK_BEGIN(CComSinkTimerCallback)
COMMON_SINK_FUNC(OnTimer, (INT nTimerId), (nTimerId))
COMMON_SINK_END()
DECLARE_COMMON_SINK_PTR(CComSinkTimerCallback, IUITimerCallback) ;

[
    object ,
    uuid("C55D0347-1253-41B3-9F4E-D496C11BF5C3") ,
    pointer_default(unique)
]
__interface IUITimer : IDispatch
{
    HRESULT SetTimerOut (IUITimerCallback* pCallback, DWORD dwTime, INT nTimerId) ;
    HRESULT SetInterval (IUITimerCallback* pCallback, DWORD dwTime, INT nTimerId) ;
    HRESULT Erase       (IUITimerCallback* pCallback, INT nTimerId) ;
} ;
