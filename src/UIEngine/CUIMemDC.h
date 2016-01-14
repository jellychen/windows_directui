#pragma once
#include <atltypes.h>

class CUIMemDC
{
public:
    CUIMemDC() ;
    virtual ~CUIMemDC() ;

public:
    operator HDC()		{return this->m_hDC ;}

public:
    BOOL    Create      (HDC hDC, CSize szMemDC) ;
    BOOL    IsVaild     () ;
    BOOL    Clear       () ;
    BOOL    Destory     () ;
    CSize   GetSize     () ;
    LPBYTE  GetMemBuffer() ;
    HBITMAP GetBitmap   () ;
    BOOL    AlphaOffset (INT nOffset) ;
    BOOL    FormatAlpha (BYTE cAlpha) ;

private:
    HDC     m_hDC ;
    HBITMAP m_hOldBitmap ;
    HBITMAP m_hCurrentBitmap ;
    LPBYTE  m_lpBitmapBuffer ;
    CSize   m_szBitmapSize ;
} ;
