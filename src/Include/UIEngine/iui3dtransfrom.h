#pragma once
#include "Include/UIEngine/IUICanvas.h"

[
	object ,
	uuid("BB28ACEF-069B-42c7-8A6F-5AA19FF41204") ,
	pointer_default(unique)
]
__interface IUI3DTransfrom : IDispatch
{
	HRESULT SetOffsetZ		(INT nOffsetZ) ;
	HRESULT GetOffsetZ		(INT* pnOffsetZ) ;
	HRESULT SetRotateX		(INT nRotateX) ;
	HRESULT GetRotateX		(INT* pnRotateX) ;
	HRESULT SetRotateY		(INT nRotateY) ;
	HRESULT GetRotateY		(INT* pnRotateY) ;
	HRESULT SetRotateZ		(INT nRotateZ) ;
	HRESULT GetRotateZ		(INT* pnRotateZ) ;
	HRESULT GetNeedTransfrom(BOOL* pbNeedTransfrom) ;
	HRESULT CanvasTransfrom	(IUICanvas* pInCanvas, IUICanvas* pOutCanvas) ;
} ;