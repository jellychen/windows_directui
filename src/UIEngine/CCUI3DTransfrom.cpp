#include "stdafx.h"
#include "3dTransform.h"
#include "CCUI3DTransfrom.h"

CCUI3DTransfrom::CCUI3DTransfrom()
{
	this->m_nOffsetZ = 0 ;
	this->m_nRotateX = 0 ;
	this->m_nRotateY = 0 ;
	this->m_nRotateZ = 0 ;
}

CCUI3DTransfrom::~CCUI3DTransfrom()
{
}

HRESULT CCUI3DTransfrom::SetOffsetZ(INT nOffsetZ)
{
	this->m_nOffsetZ = nOffsetZ ;
	return S_OK ;
}

HRESULT CCUI3DTransfrom::GetOffsetZ(INT* pnOffsetZ)
{
	DEBUG_ASSERT(pnOffsetZ) ;
	IF_RETURN(NULL == pnOffsetZ, E_INVALIDARG) ;

	*pnOffsetZ = this->m_nOffsetZ ;
	return S_OK ;
}

HRESULT CCUI3DTransfrom::SetRotateX(INT nRotateX)
{
	this->m_nRotateX = nRotateX ;
	return S_OK ;
}

HRESULT CCUI3DTransfrom::GetRotateX(INT* pnRotateX)
{
	DEBUG_ASSERT(pnRotateX) ;
	IF_RETURN(NULL == pnRotateX, E_INVALIDARG) ;

	*pnRotateX = this->m_nRotateX ;
	return S_OK ;
}

HRESULT CCUI3DTransfrom::SetRotateY(INT nRotateY)
{
	this->m_nRotateY = nRotateY ;
	return S_OK ;
}

HRESULT CCUI3DTransfrom::GetRotateY(INT* pnRotateY)
{
	DEBUG_ASSERT(pnRotateY) ;
	IF_RETURN(NULL == pnRotateY, E_INVALIDARG) ;

	*pnRotateY = this->m_nRotateY ;
	return S_OK ;
}

HRESULT CCUI3DTransfrom::SetRotateZ(INT nRotateZ)
{
	this->m_nRotateZ = nRotateZ ;
	return S_OK ;
}

HRESULT CCUI3DTransfrom::GetRotateZ(INT* pnRotateZ)
{
	DEBUG_ASSERT(pnRotateZ) ;
	IF_RETURN(NULL == pnRotateZ, E_INVALIDARG) ;

	*pnRotateZ = this->m_nRotateZ ;
	return S_OK ;
}

HRESULT CCUI3DTransfrom::GetNeedTransfrom(BOOL* pbNeedTransfrom)
{
	DEBUG_ASSERT(pbNeedTransfrom) ;
	IF_RETURN(NULL == pbNeedTransfrom, E_INVALIDARG) ;

	*pbNeedTransfrom = m_nOffsetZ||m_nRotateX||m_nRotateY||m_nRotateZ ;
	return S_OK ;
}

HRESULT CCUI3DTransfrom::CanvasTransfrom(IUICanvas* pInCanvas, IUICanvas* pOutCanvas)
{
	DEBUG_ASSERT(pInCanvas && pOutCanvas) ;
	IF_RETURN(NULL == pInCanvas || NULL == pOutCanvas, E_INVALIDARG) ;

	CSize szCanvasIn(0, 0), szCanvasOut(0, 0) ;
	pInCanvas->GetSize(&szCanvasIn) ;
	LPBYTE pBufferCanvasIn = NULL ;
	pInCanvas->GetMemBuffer(&pBufferCanvasIn) ;

	LPBYTE pBufferCanvasOut = NULL ;
	pOutCanvas->GetSize(&szCanvasOut) ;
	pOutCanvas->GetMemBuffer(&pBufferCanvasOut) ;

	IMAGE3D::C3DTransform _3dTransform ;
	_3dTransform.SetImage(pBufferCanvasIn, pBufferCanvasOut, szCanvasIn.cx, szCanvasIn.cy, 32) ;

	IMAGE3D::PARAM3DTRANSFORM _param ;
	_param.nOffsetZ = this->m_nOffsetZ ;
	_param.nRotateX = this->m_nRotateX ;
	_param.nRotateY = this->m_nRotateY ;
	_param.nRotateZ = this->m_nRotateZ ;
	_3dTransform.Render(_param) ;

	return S_OK ;
}