#pragma once

#include "Include/Def/Require.h"
#include "Include/Common/ICStruct.h"
#include <vector>

[
	default(ICVarBuffer) ,
	threading(free) ,
	uuid("6901067E-2592-45ae-92C8-ACE41E0F4C51") ,
	coclass
]
class ATL_NO_VTABLE CCVarBuffer : public IDispatchImpl<ICVarBuffer>
{
public:
	DECLARE_PROTECT_FINAL_CONSTRUCT() ;
	CCVarBuffer() ;
	virtual ~CCVarBuffer() ;

public:
	HRESULT _call GetSize			(DWORD* pdwBufferSize) ;
	HRESULT _call GetBuffer			(BYTE** ppBytePtr) ;
	HRESULT _call CopyBuffer		(ICVarBuffer* pBuffer) ;
	HRESULT _call CopyNewBuffer		(ICVarBuffer** ppBuffer) ;
	HRESULT _call SetBuffer			(BYTE* pBuffer, DWORD dwBufferLen) ;
	HRESULT _call AppendBuffer		(BYTE* pBuffer, DWORD dwBufferLen) ;
	HRESULT _call Clear				() ;

private:
	typedef std::vector<BYTE>       VEC_BUFFER_POOL ;
	VEC_BUFFER_POOL                 m_vecBufferPool ;
} ;