#pragma once
#include "Include/UIEngine/IUIFrameDef.h"
#include "Include/UIEngine/IUIFrame.h"
#include "Include/UIEngine/IUIFrameInternal.h"
#include "Include/UIEngine/IUILayoutDefault.h"

[
	default(IUILayoutDock) ,
	threading(free) ,
	uuid("032FF0EF-0A58-4ff3-916A-49CF9EC9AB67") ,
	coclass
]
class ATL_NO_VTABLE CCUILayoutDock 
	: public IDispatchImpl<IUILayoutDock>
{
public:
	HRESULT _call Layout	(IUIFrame* pFrame) ;
	HRESULT _call CalcSize	(IUIFrame* pFrame, SIZE szOld, SIZE* pOutSize) ;
} ;