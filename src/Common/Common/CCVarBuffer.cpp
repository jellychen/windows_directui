
#include "stdafx.h"
#include "CCVarBuffer.h"
#include "Include/Util/UtilTpl.h"

CCVarBuffer::CCVarBuffer()
{
}

CCVarBuffer::~CCVarBuffer()
{
}

HRESULT CCVarBuffer::GetSize(DWORD* pdwBufferSize)
{
	DEBUG_ASSERT(pdwBufferSize) ;
	IF_RETURN(NULL == pdwBufferSize, E_INVALIDARG) ;
	*pdwBufferSize = (DWORD)this->m_vecBufferPool.size() ;
	return S_OK ;
}

HRESULT CCVarBuffer::GetBuffer(BYTE** ppBytePtr)
{
	DEBUG_ASSERT(ppBytePtr) ;
	IF_RETURN(NULL == ppBytePtr, E_INVALIDARG) ;
	if (this->m_vecBufferPool.size() > 0)
	{
		*ppBytePtr = &m_vecBufferPool[0] ;
	}
	else
	{
		*ppBytePtr = NULL ;
	}
	return S_OK ;
}

HRESULT CCVarBuffer::CopyBuffer(ICVarBuffer* pBuffer)
{
	DEBUG_ASSERT(pBuffer) ;
	IF_RETURN(NULL == pBuffer, E_INVALIDARG) ;
	return pBuffer->SetBuffer(&m_vecBufferPool[0], (DWORD)this->m_vecBufferPool.size()) ;
}

HRESULT CCVarBuffer::CopyNewBuffer(ICVarBuffer** ppBuffer)
{
	DEBUG_ASSERT(ppBuffer) ;
	IF_RETURN(NULL == ppBuffer, E_INVALIDARG) ;
	*ppBuffer = NULL ;
	Common::Util::CreateObject(ppBuffer) ;
	if (*ppBuffer)
	{
		(*ppBuffer)->SetBuffer(&m_vecBufferPool[0], (DWORD)this->m_vecBufferPool.size()) ;
	}
	return E_FAIL ;
}

HRESULT CCVarBuffer::SetBuffer(BYTE* pBuffer, DWORD dwBufferLen)
{
	this->m_vecBufferPool.resize(dwBufferLen) ;
	memcpy(&m_vecBufferPool[0], pBuffer, (size_t)dwBufferLen) ;
	return S_OK ;
}

HRESULT CCVarBuffer::AppendBuffer(BYTE* pBuffer, DWORD dwBufferLen)
{
	if (0 == dwBufferLen)
	{
		return S_OK ;
	}

	DWORD dwSize = (DWORD)this->m_vecBufferPool.size() ;
	this->m_vecBufferPool.resize(dwSize+dwBufferLen) ;
	memcpy(&m_vecBufferPool[dwSize], pBuffer, dwBufferLen) ;
	return S_OK ;
}

HRESULT CCVarBuffer::Clear()
{
	this->m_vecBufferPool.clear() ;
	return S_OK ;
}