#pragma once
#include "Include/Common//ICStruct.h"

namespace XML
{
	const TCHAR XML_TAG[]       = _T("#T") ;
	const TCHAR XML_VALUE[]     = _T("#V") ;
	const TCHAR XML_ATTR[]      = _T("#A") ;
	const TCHAR XML_CHILDREN[]  = _T("#C") ;
}

[
	object ,
	uuid("5894C945-9FAC-44a6-9D2D-23777CB7F94D") ,
	pointer_default(unique)
]
__interface ICXml : IDispatch
{
	HRESULT LoadXmlFromFile         (BSTR bstrFile) ;
	HRESULT LoadXmlFromVarBuffer    (ICVarBuffer* pVarBuffer) ;
	HRESULT LoadXmlFromBuffer       (BYTE* pbBuffer, LONG lBufferLen) ;
	HRESULT GetXmlData              (ICVarData** pOutXmlData) ;
	HRESULT Clear                   () ;
} ;