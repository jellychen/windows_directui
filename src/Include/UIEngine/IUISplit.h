#pragma once
#include "Include/Common/ICStruct.h"


[
	object ,
	uuid("5F163E0C-84DB-48ab-9913-FF9DBB5F2428") ,
	pointer_default(unique)
]
__interface IUIAddRect : IDispatch
{
	HRESULT AddRectBegin        () ;
	HRESULT AddRect             (RECT rcRect) ;
	HRESULT AddRectEnd          () ;
} ;

[
	object ,
	uuid("5FE55867-4383-46d8-9DB5-BEC4D6926D8D") ,
	pointer_default(unique)
]
__interface IUISplit : IDispatch
{
	HRESULT AddRect             (RECT rcRect) ;
	HRESULT Split               (ICVarArray* pRectArray) ;
	HRESULT Split2              (IUIAddRect* pAddRect) ;
	HRESULT GetCount            (INT* pnCount) ;
	HRESULT GetByIndex          (INT nIndex, RECT* prcRect) ;
	HRESULT Clear               () ;
} ;