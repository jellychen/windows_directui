#pragma once
#include "Include/Common/ICStruct.h"
#include "Include/UIEngine/IUIElement.h"

[
	object ,
	uuid("7743D14E-67B4-4114-BC58-26B2DF9644D7") ,
	pointer_default(unique)
]
__interface IUIFactory : IDispatch
{
	HRESULT SetTagIID					(BSTR bstrTagName, REFIID iid) ;
	HRESULT GetTagIID					(BSTR bstrTagName, IID* piid) ;
	HRESULT DelTagIID					(BSTR bstrTagName) ;
	HRESULT Clear						() ;

	HRESULT LoadTagConfigFromFile		(BSTR bstrFile) ;
	HRESULT LoadTagConfigFromBuffer		(BYTE* pBuffer, DWORD dwLen) ;
	HRESULT LoadTagConfigFromVarBuffer	(ICVarBuffer* pVarBuffer) ;
	HRESULT CreateFromFile				(BSTR bstrFile, BSTR bstrTag, IUIElement** ppElement) ;
	HRESULT CreateFromBuffer			(BYTE* pBuffer, DWORD dwLen, BSTR bstrTag, IUIElement** ppElement) ;
	HRESULT CreateFromVarBuffer			(ICVarBuffer* pVarBuffer, BSTR bstrTag, IUIElement** ppElement) ;
	HRESULT InitFromFile				(BSTR bstrFile, BSTR bstrTag, IUIElement* pElement) ;
	HRESULT InitFromBuffer				(BYTE* pBuffer, DWORD dwLen, BSTR bstrTag, IUIElement* pElement) ;
	HRESULT InitFromVarBuffer			(ICVarBuffer* pVarBuffer, BSTR bstrTag, IUIElement* pElement) ;
} ;