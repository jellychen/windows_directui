#pragma once
#include "Include/UIEngine/IUIControl.h"

[
	object ,
	uuid("8124371B-D0A0-43b8-86D4-09CE4F6C2ED1") ,
	pointer_default(unique)
]
__interface IUIWebkit : IUIControl
{
	HRESULT SetUrl		(BSTR bstrUrl) ;
} ;