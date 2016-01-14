#pragma once

[
    object ,
    uuid("08E20FCE-06D8-415d-A77F-9251837EC447") ,
    pointer_default(unique)
]
__interface IUIExtWndCallback : IDispatch
{
    HRESULT OnNotifyMessage (INT nMessageId, WPARAM wParam, LPARAM lParam) ;
} ;

COMMON_SINK_BEGIN(CComSinkExtWndCallback)
COMMON_SINK_FUNC(OnNotifyMessage, (INT nMessageId, WPARAM wParam, LPARAM lParam), (nMessageId, wParam, lParam))
COMMON_SINK_END()
DECLARE_COMMON_SINK_PTR(CComSinkExtWndCallback, IUIExtWndCallback) ;

[
    object ,
    uuid("D24D28E2-1D21-4531-B6CC-B745E72F0BB1") ,
    pointer_default(unique)
]
__interface IUIExtWnd : IDispatch
{
    HRESULT GetExtHWnd          (HWND* pHWnd) ;
    HRESULT PostMessage         (INT nMsg, WPARAM wParam, LPARAM lParam) ;
    HRESULT SendMessage         (INT nMsg, WPARAM wParam, LPARAM lParam) ;
    HRESULT RegisterCallback    (INT nMessageId, IUIExtWndCallback* pCallback) ;
    HRESULT UnRegisterCallback  (INT nMessageId, IUIExtWndCallback* pCallback) ;
} ;