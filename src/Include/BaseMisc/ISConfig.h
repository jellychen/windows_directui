#pragma once
#include "Include/Common/ICStruct.h"

[
	object ,
	uuid("C0CDE877-F263-4a13-B51A-C79844A99355") ,
	pointer_default(unique)
]
__interface ISConfig : IDispatch
{
	HRESULT LoadConfigFromFile      (BSTR bstrFile) ;
	HRESULT LoadConfigFromVarBuffer (ICVarBuffer* pVarBuffer) ;
	HRESULT LoadConfigFromBuffer    (BYTE* pbBuffer, LONG lBufferLen) ;
} ;