#include "stdafx.h"
#include "CUIMemDC.h"


CUIMemDC::CUIMemDC()
{
    this->m_hDC             = 0 ;
    this->m_hOldBitmap      = NULL ;
    this->m_hCurrentBitmap  = NULL ;
    this->m_lpBitmapBuffer  = NULL ;
    this->m_szBitmapSize    = CSize(0, 0) ;
}

CUIMemDC::~CUIMemDC()
{
    this->Destory() ;
}

BOOL CUIMemDC::Create(HDC hDC, CSize szSize)
{
    this->Destory() ;
    BITMAPINFOHEADER bih = {0} ;
    bih.biSize = sizeof(BITMAPINFOHEADER) ;
    bih.biWidth = szSize.cx ;
    bih.biHeight = szSize.cy ;
    bih.biPlanes = 1 ;
    bih.biBitCount = 32 ;
    bih.biCompression= BI_RGB ;
    bih.biSizeImage = szSize.cx * szSize.cy * 4 ;

    this->m_hCurrentBitmap = ::CreateDIBSection(hDC, 
        (PBITMAPINFO)(&bih), DIB_RGB_COLORS, (VOID**)&m_lpBitmapBuffer, NULL, 0) ;

    if (NULL == this->m_hCurrentBitmap)
    {
        return FALSE ;
    }

    this->m_hDC = ::CreateCompatibleDC(hDC) ;
    this->m_hOldBitmap = (HBITMAP)::SelectObject(m_hDC, m_hCurrentBitmap) ;
    this->m_szBitmapSize.cx = szSize.cx ;
    this->m_szBitmapSize.cy = szSize.cy ;

    return TRUE ;
}

BOOL CUIMemDC::IsVaild()
{
    return (this->m_hDC && this->m_hCurrentBitmap) ;
}

BOOL CUIMemDC::Clear()
{
    if (this->m_lpBitmapBuffer)
    {
        memset(this->m_lpBitmapBuffer, 0, m_szBitmapSize.cx * m_szBitmapSize.cy * 4) ;
    }
    return TRUE ;
}

BOOL CUIMemDC::Destory()
{
    if (this->m_hOldBitmap)
    {
        ::SelectObject(m_hDC, m_hOldBitmap) ;
        this->m_hOldBitmap = NULL ;
    }

    if (this->m_hDC)
    {
        ::DeleteDC(this->m_hDC) ;
        this->m_hDC = NULL ;
    }

    if (this->m_hCurrentBitmap)
    {
        ::DeleteObject(this->m_hCurrentBitmap) ;
        this->m_hCurrentBitmap = NULL ;
    }

    this->m_lpBitmapBuffer = NULL ;
    this->m_szBitmapSize.cx = 0 ;
    this->m_szBitmapSize.cy = 0 ;

    return TRUE ;
}

CSize CUIMemDC::GetSize()
{
    return this->m_szBitmapSize ;
}

LPBYTE CUIMemDC::GetMemBuffer()
{
    return this->m_lpBitmapBuffer ;
}

HBITMAP CUIMemDC::GetBitmap()
{
    return this->m_hCurrentBitmap ;
}

BOOL CUIMemDC::AlphaOffset(INT nOffset)
{
    for (INT i = 0; i < m_szBitmapSize.cx * m_szBitmapSize.cy; ++i)
    {
        this->m_lpBitmapBuffer[i*4 + 3] += nOffset ;
    }
    return TRUE ;
}

BOOL CUIMemDC::FormatAlpha(BYTE cAlpha)
{
    for (INT i = 0; i < m_szBitmapSize.cx * m_szBitmapSize.cy; ++i)
    {
        this->m_lpBitmapBuffer[i*4 + 3] = cAlpha ;
    }
    return TRUE ;
}