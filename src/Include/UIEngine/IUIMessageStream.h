#pragma once

#include "Include/UIEngine/IUIFrame.h"
#include "Include/UIEngine/IUIMessageDef.h"

[
	object ,
	uuid("F606774A-09C1-4f46-B02C-B28AD1DEED48") ,
	pointer_default(unique)
]
__interface IUIMessageStream : IDispatch
{
	HRESULT OnMessageSink   (IUIFrame* pTarget, tMsgArg* pArg, BOOL* pbHandle, BOOL* pbIntercept) ;
	HRESULT OnMessage       (IUIFrame* pTarget, tMsgArg* pArg) ;
	HRESULT OnMessageRiase  (IUIFrame* pTarget, tMsgArg* pArg, BOOL* pbIntercept) ;
} ;