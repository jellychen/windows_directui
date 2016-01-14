#include "stdafx.h"
#include "CBitmapCache.h"
#include "CCUITexture.h"

CCUITexture::CCUITexture()
{
	this->m_cstrImage       = _T("") ;
	this->m_hBitmap         = NULL ;
	this->m_szImage         = CSize(0, 0) ;
	this->m_bAlphaChannel   = FALSE ;
	this->m_bImageCached    = FALSE ;
	this->m_rcDrawGrid      = CRect(0, 0, 0, 0) ;
	this->m_rcDrawRect      = CRect(INT_MIN, INT_MIN, INT_MIN, INT_MIN) ;
}

CCUITexture::~CCUITexture()
{

}

HRESULT CCUITexture::FinalConstruct()
{
	Common::Util::GetService(&m_pFilerouteService) ;
	DEBUG_ASSERT(m_pFilerouteService) ;
	return S_OK ;
}

HRESULT CCUITexture::LoadFromFile(BSTR bstrFile)
{
	IF_RETURN(CString(bstrFile) == this->m_cstrImage, S_OK) ;
	DEBUG_ASSERT_MSG(NULL == this->m_hBitmap, _T("Please Call Free Texture Before...")) ;
	IF_RETURN(NULL != this->m_hBitmap, E_FAIL) ;

	this->m_cstrImage = bstrFile ;
	CBitmapCache::GetInstance().GetBitmap(m_cstrImage, &m_hBitmap, &m_szImage, &m_bAlphaChannel) ;

	if (this->m_hBitmap)
	{
		this->m_bImageCached = TRUE ;
		if (m_rcDrawRect.left == INT_MIN || m_rcDrawRect.right == INT_MIN
			|| m_rcDrawRect.top == INT_MIN || m_rcDrawRect.right == INT_MIN)
		{
			this->m_rcDrawRect = CRect(0, 0, m_szImage.cx, m_szImage.cy) ;
		}
		return S_OK ;
	}
	else if (this->m_pFilerouteService)
	{
		CComPtr<ICVarBuffer> pVarBuffer ;
		Common::Util::CreateObject(&pVarBuffer) ;

		this->m_pFilerouteService->ReadWholeFile(bstrFile, pVarBuffer) ;

		LPBYTE pBuffer = NULL ;
		DWORD  dwBufferLen = 0 ;
		if (pVarBuffer)
		{
			pVarBuffer->GetBuffer(&pBuffer) ;
			pVarBuffer->GetSize(&dwBufferLen) ;
		}

		BOOL bRet = this->_Load_image_buffer(pBuffer, dwBufferLen) ;

		if (bRet&& this->m_hBitmap)
		{
			this->m_bImageCached = TRUE ;
			CBitmapCache::GetInstance().AddBitmap(this->m_cstrImage, m_hBitmap, m_szImage, m_bAlphaChannel) ;
		}
		return bRet ? S_OK : E_FAIL ;
	}
	return E_FAIL ;
}

HRESULT CCUITexture::LoadFromComBuffer(ICVarBuffer* pVarBuffer)
{
	DEBUG_ASSERT(pVarBuffer) ;
	IF_RETURN(NULL == pVarBuffer, E_INVALIDARG) ;

	DEBUG_ASSERT_MSG(NULL == this->m_hBitmap, _T("Please Call Free Texture Before...")) ;
	IF_RETURN(NULL != this->m_hBitmap, E_FAIL) ;

	LPBYTE pBuffer = NULL ;
	DWORD  dwBufferLen = 0 ;
	pVarBuffer->GetBuffer(&pBuffer) ;
	pVarBuffer->GetSize(&dwBufferLen) ;
	return this->_Load_image_buffer(pBuffer, dwBufferLen) ? S_OK : E_FAIL ;
}

HRESULT CCUITexture::LoadFromBuffer(BYTE* pbBuffer, LONG lBufferLen)
{
	DEBUG_ASSERT(pbBuffer) ;
	IF_RETURN(NULL == pbBuffer, E_INVALIDARG) ;

	DEBUG_ASSERT_MSG(NULL == this->m_hBitmap, _T("Please Call Free Texture Before...")) ;
	IF_RETURN(NULL != this->m_hBitmap, E_FAIL) ;

	return this->_Load_image_buffer(pbBuffer, lBufferLen) ? S_OK : E_FAIL ;
}

HRESULT CCUITexture::SetDrawType(DWORD dwType)
{
	this->m_dwDrawType = dwType ;
	return S_OK ;
}

HRESULT CCUITexture::SetDrawType(BSTR bstrType)
{
	CString cstrType = bstrType ;
	if (0 == cstrType.CompareNoCase(_T("NORMAL")))
	{
		return this->SetDrawType(TEXTURE::DRAW::NORMAL) ;
	}
	else if (0 == cstrType.CompareNoCase(_T("STRETCH")))
	{
		return this->SetDrawType(TEXTURE::DRAW::STRETCH) ;
	}
	else if (0 == cstrType.CompareNoCase(_T("HOLE")))
	{
		return this->SetDrawType(TEXTURE::DRAW::HOLE) ;
	}
	else if (0 == cstrType.CompareNoCase(_T("REPEAT")))
	{
		return this->SetDrawType(TEXTURE::DRAW::REPEAT) ;
	}
	else if (0 == cstrType.CompareNoCase(_T("XREPEAT")))
	{
		return this->SetDrawType(TEXTURE::DRAW::XREPEAT) ;
	}
	else if (0 == cstrType.CompareNoCase(_T("YREPEAT")))
	{
		return this->SetDrawType(TEXTURE::DRAW::YREPEAT) ;
	}
	else if (0 == cstrType.CompareNoCase(_T("GRID")))
	{
		return this->SetDrawType(TEXTURE::DRAW::GRID) ;
	}
	return E_FAIL ;
}

HRESULT CCUITexture::GetDrawType(DWORD* pdwType)
{
	DEBUG_ASSERT(pdwType) ;
	IF_RETURN(NULL == pdwType, E_INVALIDARG) ;

	*pdwType = this->m_dwDrawType ;
	return S_OK ;
}

HRESULT CCUITexture::SetDrawRect(RECT rcDraw)
{
	this->m_rcDrawRect = rcDraw ;
	return S_OK ;
}

HRESULT CCUITexture::GetDrawRect(RECT* prcDraw)
{
	DEBUG_ASSERT(prcDraw) ;
	IF_RETURN(NULL == prcDraw, E_INVALIDARG) ;
	*prcDraw = this->m_rcDrawRect ;
	return S_OK ;
}

HRESULT CCUITexture::SetDrawGrid(RECT rcGrid)
{
	this->m_rcDrawGrid = rcGrid ;
	return S_OK ;
}

HRESULT CCUITexture::GetDrawGrid(RECT* prcGrid)
{
	DEBUG_ASSERT(prcGrid) ;
	IF_RETURN(NULL == prcGrid, E_INVALIDARG) ;
	*prcGrid = this->m_rcDrawGrid ;
	return S_OK ;
}

HRESULT CCUITexture::FreeTexture()
{
	if (this->m_hBitmap)
	{
		if (this->m_bImageCached)
		{
			CBitmapCache::GetInstance().DelBitmap(this->m_cstrImage) ;
		}
		else
		{
			::DeleteObject(this->m_hBitmap) ;
		}
	}

	this->m_cstrImage       = _T("") ;
	this->m_hBitmap         = NULL ;
	this->m_szImage         = CSize(0, 0) ;
	this->m_bAlphaChannel   = FALSE ;
	this->m_bImageCached    = FALSE ;
	this->m_rcDrawGrid      = CRect(0, 0, 0, 0) ;
	this->m_rcDrawRect      = CRect(INT_MIN, INT_MIN, INT_MIN, INT_MIN) ;

	return S_OK ;
}

HRESULT CCUITexture::GetSize(SIZE* pszDraw)
{
	DEBUG_ASSERT(pszDraw) ;
	IF_RETURN(NULL == pszDraw, E_INVALIDARG) ;
	pszDraw->cx = this->m_szImage.cx ;
	pszDraw->cy = this->m_szImage.cy ;
	return S_OK ;
}

HRESULT CCUITexture::DrawOnDC(HDC hDC, RECT rcDraw, BYTE cAlpha)
{
	this->_draw_image(hDC, this->m_hBitmap, rcDraw, 
		this->m_rcDrawRect, this->m_rcDrawGrid, this->m_bAlphaChannel, cAlpha) ;
	return S_OK ;
}

HRESULT CCUITexture::DrawOnCanvas(IUICanvas* pCanvas, RECT rcDraw, BYTE cAlpha)
{
	DEBUG_ASSERT(pCanvas) ;
	IF_RETURN(NULL == pCanvas, E_INVALIDARG) ;

	HDC hDC = NULL ;
	pCanvas->GetCanvasDC(&hDC) ;
	return this->DrawOnDC(hDC, rcDraw, cAlpha) ;
}

HRESULT CCUITexture::SetAttribute(ICVarData* pAttrData)
{
	SET_ATTR_CLASS_BEGIN(pAttrData, CCUITexture)
	SET_ATTR_BSTR       (DrawType)
	SET_ATTR_RECT       (DrawRect)
	SET_ATTR_RECT       (DrawGrid)
	SET_ATTR_END        ()

	CComBSTR bstrFileName ;
	if (SUCCEEDED(pAttrData->GetString(_T("File"), &bstrFileName)))
	{
		this->LoadFromFile(bstrFileName) ;
	}
	return S_OK ;
}

BOOL CCUITexture::_Load_image_buffer(BYTE* pbBuffer, LONG lBufferLen)
{
	IF_RETURN(NULL == pbBuffer || 0 == lBufferLen, FALSE) ;

	INT x = 0, y = 0, n = 0 ;
	LPBYTE pImageBuffer = stbi_load_from_memory(pbBuffer, lBufferLen, &x, &y, &n, 4) ;
	DEBUG_ASSERT(pImageBuffer) ;
	IF_RETURN(NULL == pImageBuffer, E_FAIL) ;

	BITMAPINFO bmi ;
	::ZeroMemory(&bmi, sizeof(bmi)) ;
	bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER) ;
	bmi.bmiHeader.biWidth = x ;
	bmi.bmiHeader.biHeight = -y ;
	bmi.bmiHeader.biPlanes = 1 ;
	bmi.bmiHeader.biBitCount = 32 ;
	bmi.bmiHeader.biCompression = BI_RGB ;
	bmi.bmiHeader.biSizeImage = x * y * 4 ;

	BOOL    bAlphaChannel = FALSE ;
	LPBYTE  pBitmapBuffer = NULL ;
	HBITMAP hBitmap = ::CreateDIBSection(NULL, 
		&bmi, DIB_RGB_COLORS, (VOID**)(&pBitmapBuffer), NULL, 0) ;
	DEBUG_ASSERT_MSG(hBitmap, _T("CreateDIBSection failed..")) ;
	IF_RETURN(NULL == hBitmap, E_FAIL) ;

	for (INT i = 0; i < x*y; ++i)
	{
		pBitmapBuffer[i*4 + 3] = pImageBuffer[i*4 + 3] ;
		if (255 > pBitmapBuffer[i*4 + 3])
		{
			pBitmapBuffer[i*4]      = (BYTE)(DWORD(pImageBuffer[i*4 + 2]) * pImageBuffer[i*4 + 3]/255) ;
			pBitmapBuffer[i*4 + 1]  = (BYTE)(DWORD(pImageBuffer[i*4 + 1]) * pImageBuffer[i*4 + 3]/255) ;
			pBitmapBuffer[i*4 + 2]  = (BYTE)(DWORD(pImageBuffer[i*4]) * pImageBuffer[i*4 + 3]/255) ;
			bAlphaChannel = TRUE ;
		}

		else
		{
			pBitmapBuffer[i*4]      = pImageBuffer[i*4 + 2] ;
			pBitmapBuffer[i*4 + 1]  = pImageBuffer[i*4 + 1] ;
			pBitmapBuffer[i*4 + 2]  = pImageBuffer[i*4] ; 
		}
	}
	stbi_image_free(pImageBuffer) ;

	this->m_hBitmap         = hBitmap ;
	this->m_szImage         = CSize(x, y) ;
	this->m_rcDrawRect      = CRect(0, 0, x, y) ;
	this->m_bAlphaChannel   = bAlphaChannel ;
	return TRUE ;
}

BOOL CCUITexture::_draw_image(HDC hDC , HBITMAP hBitmap , const CRect& rcPaint ,
							 const CRect& rcBmpPart , const CRect& rcCorners, BOOL alphaChannel, BYTE cAlpha)
{
	DEBUG_ASSERT_MSG((::GetObjectType(hDC) == OBJ_DC || ::GetObjectType(hDC) == OBJ_MEMDC), _T("error hdc")) ;
	IF_RETURN(::GetObjectType(hDC) != OBJ_DC && ::GetObjectType(hDC) != OBJ_MEMDC, FALSE) ;
	DEBUG_ASSERT_MSG(hBitmap, _T("error bitmap")) ;
	IF_RETURN(NULL == hBitmap, FALSE) ;

	HDC hCloneDC = ::CreateCompatibleDC(hDC) ;
	HBITMAP hOldBitmap = (HBITMAP) ::SelectObject(hCloneDC, hBitmap) ;
	::SetStretchBltMode(hDC, COLORONCOLOR) ;
	::SetBkMode(hDC , TRANSPARENT) ;
	CRect rcDest , rcSrc ;
	CRect rcPaintArea = rcPaint , rcBmpArea = rcBmpPart , rcCornerArea = rcCorners ;
	BLENDFUNCTION bf = { AC_SRC_OVER, 0, cAlpha, AC_SRC_ALPHA } ;

	if (this->m_dwDrawType & TEXTURE::DRAW::HOLE)
	{

		if (rcBmpArea.Width() >= rcPaintArea.Width())
		{
			rcSrc.left = rcBmpArea.left + (rcBmpArea.Width() - rcPaintArea.Width()) / 2 ;
			rcSrc.right = rcSrc.left + rcPaintArea.Width() ;
			rcDest.left = rcPaintArea.left ;
			rcDest.right = rcPaintArea.right ;
		}
		else 
		{
			rcSrc.left = rcBmpArea.left ;
			rcSrc.right = rcBmpArea.right ;
			rcDest.left = rcPaintArea.left + (rcPaintArea.Width() - rcBmpArea.Width()) / 2 ;
			rcDest.right = rcDest.left + rcBmpArea.Width() ;
		}

		if (rcBmpArea.Height() >= rcPaintArea.Height())
		{
			rcDest.top = rcPaintArea.top ;
			rcDest.bottom = rcPaintArea.bottom ;
			rcSrc.top = rcBmpArea.top + (rcBmpArea.Height() - rcPaintArea.Height()) / 2 ;
			rcSrc.bottom = rcSrc.top + rcPaintArea.Height() ;
		}
		else
		{
			rcDest.top = rcPaintArea.top + (rcPaintArea.Height() - rcBmpArea.Height()) / 2 ;
			rcDest.bottom = rcDest.top + rcBmpArea.Height() ;
			rcSrc.top = rcBmpArea.top ;
			rcSrc.bottom = rcBmpArea.bottom ;
		}

		if (alphaChannel || cAlpha < 255)
		{
			::AlphaBlend(hDC, rcDest.left, rcDest.top, rcDest.Width(), rcDest.Height(), hCloneDC,
				rcSrc.left, rcSrc.top, rcSrc.Width(), rcSrc.Height() , bf) ;
		}
		else 
		{
			::BitBlt(hDC, rcDest.left, rcDest.top, rcDest.Width(), rcDest.Height(), hCloneDC, 
				rcSrc.left, rcSrc.top, SRCCOPY) ;
		}
	}
	else if (this->m_dwDrawType & TEXTURE::DRAW::STRETCH)
	{
		rcDest = rcPaintArea ;
		rcSrc = rcBmpArea ;

		if (alphaChannel || cAlpha < 255)
		{
			AlphaBlend(hDC, rcDest.left, rcDest.top, rcDest.Width(), rcDest.Height(), hCloneDC,
				rcSrc.left, rcSrc.top, rcSrc.Width(), rcSrc.Height() , bf) ;
		}
		else 
		{
			::StretchBlt(hDC , rcDest.left, rcDest.top, rcDest.Width(), rcDest.Height(), hCloneDC,
				rcSrc.left, rcSrc.top, rcSrc.Width(), rcSrc.Height(), SRCCOPY) ;
		}
	}
	else if (this->m_dwDrawType & TEXTURE::DRAW::REPEAT)
	{
		if (this->m_dwDrawType & TEXTURE::DRAW::XREPEAT
			&& this->m_dwDrawType & TEXTURE::DRAW::YREPEAT)
		{
			DWORD dwHori = ceil((DOUBLE)rcPaintArea.Width() / (DOUBLE)rcPaintArea.Height()) ;
			DWORD dwVeri = ceil((DOUBLE)rcPaintArea.Height()/ (DOUBLE)rcPaintArea.Height()) ;

			for (DWORD i = 0 ; i < dwHori ; i++)
			{
				for (DWORD j = 0 ;j < dwVeri ; j++)
				{
					rcSrc.left = rcBmpArea.left ;
					rcSrc.top = rcBmpArea.top ;
					rcDest.left = i * rcBmpArea.left ;
					rcDest.top = j * rcBmpArea.top ;
					if (i == dwHori -1)
					{
						DWORD dwLastHori = rcPaintArea.Width() - i * rcBmpArea.Width() ;
						rcSrc.right = rcSrc.left + dwLastHori ;
						rcDest.right = rcDest.left + dwLastHori ;
					}
					else 
					{
						rcSrc.right = rcBmpArea.right ;
						rcDest.right = rcDest.left + rcBmpArea.Width() ;
					}

					if (j == dwVeri -1)
					{
						DWORD dwLastVeri = rcPaintArea.Height() - i * rcBmpArea.Height() ;
						rcSrc.bottom = rcSrc.top + dwLastVeri ;
						rcDest.bottom = rcDest.top + dwLastVeri ;
					}
					else
					{
						rcSrc.bottom = rcBmpArea.bottom ;
						rcSrc.bottom = rcDest.top + rcBmpArea.Height() ;
					}

					if (alphaChannel || cAlpha < 255)
					{
						::AlphaBlend(hDC, rcDest.left, rcDest.top, rcDest.Width(), rcDest.Height(), hCloneDC,
							rcSrc.left, rcSrc.top, rcSrc.Width(), rcSrc.Height() , bf) ;
					}
					else 
					{
						::BitBlt(hDC , rcDest.left, rcDest.top, rcDest.Width(), rcDest.Height(), hCloneDC,
							rcSrc.left, rcSrc.top, SRCCOPY) ;
					}

				}
			}
		}
		else if (this->m_dwDrawType & TEXTURE::DRAW::XREPEAT)
		{
		}
		else if (this->m_dwDrawType & TEXTURE::DRAW::YREPEAT)
		{

		}
	}
	else if (this->m_dwDrawType & TEXTURE::DRAW::GRID)
	{
		// left - top
		if (rcCornerArea.left > 0 && rcCornerArea.top > 0)
		{
			rcSrc.left = rcBmpArea.left ;
			rcSrc.top = rcBmpArea.top ;
			rcSrc.right = rcSrc.left + rcCornerArea.left ;
			rcSrc.bottom = rcSrc.top + rcCornerArea.top ;

			rcDest.left = rcPaintArea.left ; 
			rcDest.top = rcPaintArea.top ;
			rcDest.right = rcPaintArea.left + rcSrc.Width() ;
			rcDest.bottom = rcPaintArea.top + rcSrc.Height() ;

			if (alphaChannel || cAlpha < 255)
			{
				::AlphaBlend(hDC, rcDest.left, rcDest.top, rcDest.Width(), rcDest.Height(), hCloneDC,
					rcSrc.left, rcSrc.top, rcSrc.Width(), rcSrc.Height() , bf) ;
			}
			else 
			{
				::BitBlt(hDC, rcDest.left, rcDest.top, rcDest.Width(), rcDest.Height(), hCloneDC, 
					rcSrc.left, rcSrc.top, SRCCOPY) ;
			}
		}

		// top mid
		if (rcCorners.top > 0 && (rcBmpArea.Width() - rcCorners.left - rcCorners.right) > 0)
		{
			rcSrc.left = rcBmpArea.left + rcCorners.left ;
			rcSrc.top = rcBmpArea.top ;
			rcSrc.right = rcBmpArea.right - rcCorners.right ;
			rcSrc.bottom = rcBmpArea.top + rcCornerArea.top ; 

			rcDest.left = rcPaintArea.left + rcCorners.left ;
			rcDest.top = rcPaintArea.top ;
			rcDest.right = rcPaintArea.right - rcCorners.right ;
			rcDest.bottom = rcPaintArea.top + rcCornerArea.top ;

			if (alphaChannel || cAlpha < 255)
			{
				::AlphaBlend(hDC, rcDest.left, rcDest.top, rcDest.Width(), rcDest.Height(), hCloneDC,
					rcSrc.left, rcSrc.top, rcSrc.Width(), rcSrc.Height() , bf) ;
			}
			else 
			{
				::StretchBlt(hDC, rcDest.left, rcDest.top, rcDest.Width(), rcDest.Height(), hCloneDC,
					rcSrc.left, rcSrc.top, rcSrc.Width(), rcSrc.Height(), SRCCOPY) ;
			}
		}

		// right top
		if (rcCornerArea.top > 0 && rcCornerArea.right > 0)
		{
			rcSrc.left = rcBmpArea.right - rcCornerArea.right ;
			rcSrc.top = rcBmpArea.top ;
			rcSrc.bottom = rcBmpArea.top + rcCornerArea.top ;
			rcSrc.right = rcBmpArea.right ;

			rcDest.left = rcPaintArea.right - rcCornerArea.right ;
			rcDest.top = rcPaintArea.top ;
			rcDest.bottom = rcPaintArea.top + rcCornerArea.top ;
			rcDest.right = rcPaintArea.right ;

			if (alphaChannel || cAlpha < 255)
			{
				::AlphaBlend(hDC, rcDest.left, rcDest.top, rcDest.Width(), rcDest.Height(), hCloneDC,
					rcSrc.left, rcSrc.top, rcSrc.Width(), rcSrc.Height() , bf) ;
			}
			else 
			{
				::BitBlt(hDC, rcDest.left, rcDest.top, rcDest.Width(), rcDest.Height(), hCloneDC, 
					rcSrc.left, rcSrc.top, SRCCOPY) ;
			}
		}

		// left mid
		if (rcCorners.left > 0 )
		{
			rcSrc.left = rcBmpArea.left ;
			rcSrc.right = rcBmpArea.left + rcCornerArea.left ;
			rcSrc.top = rcBmpArea.top + rcCornerArea.top ;
			rcSrc.bottom = rcBmpArea.bottom - rcCornerArea.bottom ;

			rcDest.left = rcPaintArea.left ;
			rcDest.right = rcPaintArea.left + rcCornerArea.left ;
			rcDest.top = rcPaintArea.top + rcCornerArea.top ;
			rcDest.bottom = rcPaintArea.bottom - rcCornerArea.bottom ;

			if (alphaChannel || cAlpha < 255)
			{
				::AlphaBlend(hDC, rcDest.left, rcDest.top, rcDest.Width(), rcDest.Height(), hCloneDC,
					rcSrc.left, rcSrc.top, rcSrc.Width(), rcSrc.Height() , bf) ;
			}
			else 
			{
				::StretchBlt(hDC, rcDest.left, rcDest.top, rcDest.Width(), rcDest.Height(), hCloneDC,
					rcSrc.left, rcSrc.top, rcSrc.Width(), rcSrc.Height(), SRCCOPY) ;
			}
		}

		// left bottom
		if (rcCornerArea.bottom > 0 && rcCornerArea.left > 0)
		{
			rcSrc.left = rcBmpArea.left ;
			rcSrc.right = rcBmpArea.left + rcCornerArea.left ;
			rcSrc.top = rcBmpArea.bottom - rcCornerArea.bottom ;
			rcSrc.bottom = rcBmpArea.bottom ;

			rcDest.left = rcPaintArea.left ;
			rcDest.right = rcPaintArea.left + rcCornerArea.left ;
			rcDest.top = rcPaintArea.bottom - rcCornerArea.bottom ;
			rcDest.bottom = rcPaintArea.bottom ;

			if (alphaChannel || cAlpha < 255)
			{
				::AlphaBlend(hDC, rcDest.left, rcDest.top, rcDest.Width(), rcDest.Height(), hCloneDC,
					rcSrc.left, rcSrc.top, rcSrc.Width(), rcSrc.Height() , bf) ;
			}
			else 
			{
				::BitBlt(hDC, rcDest.left, rcDest.top, rcDest.Width(), rcDest.Height(), hCloneDC, 
					rcSrc.left, rcSrc.top, SRCCOPY) ;
			}
		}

		// botton mid
		if (rcCorners.bottom > 0)
		{
			rcSrc.left = rcBmpArea.left + rcCornerArea.left ;
			rcSrc.top = rcBmpArea.bottom - rcCornerArea.bottom ;
			rcSrc.right = rcBmpArea.right - rcCornerArea.right ;
			rcSrc.bottom = rcBmpArea.bottom ;

			rcDest.left = rcPaintArea.left + rcCornerArea.left ;
			rcDest.top = rcPaintArea.bottom - rcCornerArea.bottom ;
			rcDest.right = rcPaintArea.right - rcCornerArea.right ;
			rcDest.bottom = rcPaintArea.bottom ;

			if (alphaChannel || cAlpha < 255)
			{
				::AlphaBlend(hDC, rcDest.left, rcDest.top, rcDest.Width(), rcDest.Height(), hCloneDC,
					rcSrc.left, rcSrc.top, rcSrc.Width(), rcSrc.Height() , bf) ;
			}
			else 
			{
				::StretchBlt(hDC, rcDest.left, rcDest.top, rcDest.Width(), rcDest.Height(), hCloneDC,
					rcSrc.left, rcSrc.top, rcSrc.Width(), rcSrc.Height(), SRCCOPY) ;
			}
		}

		// right bottom
		if (rcCorners.right > 0 && rcCorners.bottom > 0)
		{
			rcSrc.left = rcBmpArea.right - rcCornerArea.right ;
			rcSrc.right = rcBmpArea.right ;
			rcSrc.top = rcBmpArea.bottom - rcCornerArea.bottom ;
			rcSrc.bottom = rcBmpArea.bottom ;

			rcDest.left = rcPaintArea.right - rcCornerArea.right ;
			rcDest.right = rcPaintArea.right ;
			rcDest.top = rcPaintArea.bottom - rcCornerArea.bottom ;
			rcDest.bottom = rcPaintArea.bottom ;


			if (alphaChannel || cAlpha < 255)
			{
				::AlphaBlend(hDC, rcDest.left, rcDest.top, rcDest.Width(), rcDest.Height(), hCloneDC,
					rcSrc.left, rcSrc.top, rcSrc.Width(), rcSrc.Height() , bf) ;
			}
			else 
			{
				::BitBlt(hDC, rcDest.left, rcDest.top, rcDest.Width(), rcDest.Height(), hCloneDC, 
					rcSrc.left, rcSrc.top, SRCCOPY) ;
			}
		}

		// right mid
		if (rcCornerArea.right > 0)
		{
			rcSrc.left = rcBmpArea.right - rcCornerArea.right ;
			rcSrc.top = rcBmpArea.top + rcCornerArea.top ;
			rcSrc.right = rcBmpArea.right ;
			rcSrc.bottom = rcBmpArea.bottom - rcCornerArea.bottom ;

			rcDest.left = rcPaintArea.right - rcCornerArea.right ;
			rcDest.top = rcPaintArea.top + rcCornerArea.top ;
			rcDest.right = rcPaintArea.right ;
			rcDest.bottom = rcPaintArea.bottom - rcCornerArea.bottom ;

			if (alphaChannel || cAlpha < 255)
			{
				::AlphaBlend(hDC, rcDest.left, rcDest.top, rcDest.Width(), rcDest.Height(), hCloneDC,
					rcSrc.left, rcSrc.top, rcSrc.Width(), rcSrc.Height() , bf) ;
			}
			else 
			{
				::StretchBlt(hDC, rcDest.left, rcDest.top, rcDest.Width(), rcDest.Height(), hCloneDC,
					rcSrc.left, rcSrc.top, rcSrc.Width(), rcSrc.Height(), SRCCOPY) ;
			}
		}

		// centre
		{
			rcSrc.left = rcBmpArea.left + rcCornerArea.left ;
			rcSrc.right = rcBmpArea.right - rcCornerArea.right ;
			rcSrc.top = rcBmpArea.top + rcCornerArea.top ;
			rcSrc.bottom = rcBmpArea.bottom - rcCornerArea.bottom ;

			rcDest.left = rcPaintArea.left + rcCornerArea.left ;
			rcDest.right = rcPaintArea.right - rcCornerArea.right ;
			rcDest.top = rcPaintArea.top + rcCornerArea.top ;
			rcDest.bottom = rcPaintArea.bottom - rcCornerArea.bottom ;

			if (alphaChannel || cAlpha < 255)
			{
				::AlphaBlend(hDC, rcDest.left, rcDest.top, rcDest.Width(), rcDest.Height(), hCloneDC,
					rcSrc.left, rcSrc.top, rcSrc.Width(), rcSrc.Height() , bf) ;
			}
			else 
			{
				::StretchBlt(hDC, rcDest.left, rcDest.top, rcDest.Width(), rcDest.Height(), hCloneDC,
					rcSrc.left, rcSrc.top, rcSrc.Width(), rcSrc.Height(), SRCCOPY) ;
			}
		}
	}

	::SelectObject(hCloneDC, hOldBitmap);
	::DeleteDC(hCloneDC);
	return TRUE ;
}
