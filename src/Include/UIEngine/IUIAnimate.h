#pragma once
#include "Include/UIEngine/IUIControl.h"
#include "Include/UIEngine/IUIDraw.h"

[
	object ,
	uuid("22244093-8C80-45c3-B2C0-FF0EA3DD5803") ,
	pointer_default(unique)
]
__interface IUIAnimate : IUIControl
{
	HRESULT AddFrame		(IUIDraw* pDraw) ;
	HRESULT SetInterval		(INT nInterval) ;
	HRESULT GetInterval		(INT* pnInterval) ;
	HRESULT DoForward		(BOOL bForward) ; 
} ;
