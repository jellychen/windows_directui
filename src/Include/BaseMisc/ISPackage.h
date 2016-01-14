#pragma once
#include "Include/Common/ICStruct.h"

[
	object ,
	uuid("E0278C42-DB7A-47f3-87B7-86CC5E0070DF") ,
	pointer_default(unique)
]
__interface ISPackage : IDispatch
{
	HRESULT AddPackage      (BSTR bstrName, BSTR bstrPackage) ;
	HRESULT DelPackage      (BSTR bstrName) ;
	HRESULT FileExists      (BSTR bstrFile, BOOL* pbExists) ;
	HRESULT ReadWholeFile   (BSTR bstrFile, ICVarBuffer* pComBuffer) ;
} ;