#pragma once
#include "Include/UIEngine/IUIFrameDef.h"
#include "Include/UIEngine/IUIFrame.h"
#include "Include/UIEngine/IUILayoutMenu.h"
#include "Include/UIEngine/IUIFrameInternal.h"

[
	default(IUILayoutMenu) ,
	threading(free) ,
	uuid("BB21164C-9877-4eb2-89B8-1ACE7F7A8868") ,
	coclass
]
class ATL_NO_VTABLE CCUILayoutMenu
	: public IDispatchImpl<IUILayoutMenu>
{
public:
	HRESULT _call Layout	(IUIFrame* pFrame) ;
	HRESULT _call CalcSize	(IUIFrame* pFrame, SIZE szOld, SIZE* pOutSize) ;
} ;