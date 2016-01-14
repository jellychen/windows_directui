#pragma once
#include "Include/Common/ICStruct.h"

[
	object ,
	uuid("1E2A247A-3BE1-4fcb-87D7-31C740C08BD3") ,
	pointer_default(unique)
]
__interface ISFileroute : IDispatch
{
	HRESULT AddSymbol           (BSTR bstrSymbol, BSTR bstrRoute) ;
	HRESULT DelSymbol           (BSTR bstrSymbol) ;
	HRESULT GetSymbol           (BSTR bstrSymbol, BSTR* pbstrRoute) ;
	HRESULT Convert             (BSTR bstrRoute, BSTR* pbstrRoute) ;
	HRESULT AddPackageSymbol    (BSTR bstrSymbol) ;
	HRESULT DelPackageSymbol    (BSTR bstrSymbol) ;
	HRESULT FileExists          (BSTR bstrFile, BOOL* pbExists) ;
	HRESULT ReadWholeFile       (BSTR bstrFile, ICVarBuffer* pComBuffer) ;
} ;