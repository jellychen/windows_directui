#pragma once
#include "Include/UIEngine/IUIDraw.h"

[
	object ,
	uuid("5B8597E4-9AE6-4b34-ADEC-B3EB709E4833") ,
	pointer_default(unique)
]
__interface IUITooltips : IDispatch
{
	HRESULT SetTooltipsDraw		(IUIDraw* pDraw) ;
	HRESULT GetTooltipsDraw		(IUIDraw** ppDraw) ;
	HRESULT SetTooltipsPadding	(RECT rcPadding) ;
	HRESULT GetTooltipsPadding	(RECT* prcPadding) ;
	HRESULT SetTooltipsOffset	(POINT ptOffset) ;
	HRESULT GetTooltipsOffset	(POINT* pptOffset) ;
} ;