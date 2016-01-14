#pragma once
#include "Include/UIEngine/IUIFrameInternal.h"
#include "Include/Common/ICStruct.h"
#include "Include/UIEngine/IUIFrame.h"

[
	object ,
	uuid("A0864053-25FD-4c38-AFDA-22F402CE988A") ,
	pointer_default(unique)
]
__interface IUIQuad : IDispatch
{
	HRESULT SynchFrame      (RECT rcFrame, IUIFrame* pFrame) ;
	HRESULT GetFrameRect    (IUIFrame* pFrame, RECT* prcRect) ;
	HRESULT FrameFromPoint  (POINT ptTarget, ICVarArray* pFrameArray) ;
	HRESULT FrameFromPoint2 (POINT ptTarget, IUIAddFrame* pAddFrame) ;
	HRESULT FrameFromRect   (RECT rcTarget, ICVarArray* pFrameArray) ;
	HRESULT FrameFromRect2  (RECT rcTarget, IUIAddFrame* pAddFrame) ;
	HRESULT EraseFrame      (IUIFrame* pFrame) ;
	HRESULT Clear           () ;
} ;