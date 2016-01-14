#pragma once

__interface IUIFrame ;
[idl_quote("interface IUIFrame;")] ;

[
	object ,
	uuid("C20EECF0-B37D-4883-975F-3796B17ADC9E") ,
	pointer_default(unique)
]
__interface IUILayout : IDispatch
{
	HRESULT Layout		(IUIFrame* pFrame) ;
	HRESULT CalcSize	(IUIFrame* pFrame, SIZE szOld, SIZE* pOutSize) ;
} ;
