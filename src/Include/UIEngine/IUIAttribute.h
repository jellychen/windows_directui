#pragma once
#include "Include/Common/ICStruct.h"

[
	object ,
	uuid("12EDDE47-9531-48a2-B9C0-460CCBD6D062") ,
	pointer_default(unique)
]
__interface IUIAttribute : IDispatch
{
	HRESULT SetAttribute    (ICVarData* pAttrData) ;
} ;