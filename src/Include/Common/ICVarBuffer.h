#pragma once

[
	object ,
	uuid("40FCDBD4-2A5D-46cd-97E7-0E5F27AD3432") ,
	pointer_default(unique)
]
__interface ICVarBufferReader : IDispatch
{
	HRESULT GetSize				(DWORD* pdwBufferSize) ;
	HRESULT GetBuffer           (BYTE** ppBytePtr) ;
} ;

[
	object ,
	uuid("0C420062-4108-495d-A93F-EDBB57350DE5") ,
	pointer_default(unique)
]
__interface ICVarBuffer : ICVarBufferReader
{
	HRESULT CopyBuffer          (ICVarBuffer* pBuffer) ;
	HRESULT CopyNewBuffer		(ICVarBuffer** ppBuffer) ;
	HRESULT SetBuffer           (BYTE* pBuffer, DWORD dwBufferLen) ;
	HRESULT AppendBuffer		(BYTE* pBuffer, DWORD dwBufferLen) ;
	HRESULT Clear               () ;
} ;