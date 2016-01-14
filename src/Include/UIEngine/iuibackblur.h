#pragma once
#include "Include/UIEngine/IUIControl.h"

[
	object ,
	uuid("83A50E93-82C1-43c6-8E3F-2E24F2DA7D60") ,
	pointer_default(unique)
]
__interface IUIBackBlur : IUIControl
{
	HRESULT SetRadius	(INT nRadius) ;
	HRESULT GetRadius	(INT* pnRadius) ;
} ;