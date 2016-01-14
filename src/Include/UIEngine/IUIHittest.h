#pragma once
#include "Include/UIEngine/IUIFrame.h"

[
	object ,
	uuid("3AB42272-4630-4bac-B1CD-F995FD91A50F") ,
	pointer_default(unique)
]
__interface IUIHittest : IDispatch
{
	HRESULT GetHitFrame (IUIFrame** ppFrame, BOOL bSolid) ;
} ;