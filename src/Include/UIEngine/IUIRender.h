#pragma once

#include "Include/UIEngine/IUIFrame.h"
#include "Include/UIEngine/IUICanvas.h"

[
	object ,
	uuid("9017C760-2EDB-42fb-AB7F-F44D10D6C605") ,
	pointer_default(unique)
]
__interface IUIRender : IDispatch
{
	HRESULT Render      (IUICanvas* pCanvas) ;
	HRESULT Clear       () ;
} ;