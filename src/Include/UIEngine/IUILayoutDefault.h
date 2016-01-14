#pragma once
#include "Include/UIEngine/IUILayout.h"
#include "Include/UIEngine/IUIAttribute.h"
#include "Include/UIEngine/TUIV2v.h"

[
	object ,
	uuid("B4361B60-780F-4451-8168-7066A8739EB3") ,
	pointer_default(unique)
]
__interface IUILayoutDock : IUILayout
{

} ;

namespace LAYOUT
{
	enum ORIENTATION
	{
		ORIENTATION_NEAR		= 0x0	,
		ORIENTATION_FAR					,
	} ;
}

[
	object ,
	uuid("9933F090-96AC-43bd-948D-984D1EB8A68C") ,
	pointer_default(unique)
]
__interface IUILayoutVertical : IUILayout
{
	HRESULT SetOrientation      (INT nOrientation) ;
	HRESULT GetOrientation      (INT* pnOrientation) ;
	HRESULT SetFillItemIndex    (INT nItemIndex) ;
	HRESULT GetFillItemIndex    (INT* pnItemIndex) ;
} ;

[
	object ,
	uuid("FFD71F3B-DD35-47aa-90F4-581BC3761D75") ,
	pointer_default(unique)
]
__interface IUILayoutHorizontal : IUILayout
{
	HRESULT SetOrientation      (INT nOrientation) ;
	HRESULT GetOrientation      (INT* pnOrientation) ;
	HRESULT SetFillItemIndex    (INT nItemIndex) ;
	HRESULT GetFillItemIndex    (INT* pnItemIndex) ;
} ;