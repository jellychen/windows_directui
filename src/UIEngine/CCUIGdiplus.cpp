#include "stdafx.h"
#include "CCUIGdiplus.h"

static CCUIGdiplus _auto_gdiplus ;

CCUIGdiplus::CCUIGdiplus()
{
	Gdiplus::GdiplusStartupInput GdiplusStartupInput ;
	Gdiplus::Status sResult = Gdiplus::GdiplusStartup(&m_gdiplus_token, &GdiplusStartupInput, NULL) ;
	DEBUG_ASSERT(sResult == Gdiplus::Ok) ;
}

CCUIGdiplus::~CCUIGdiplus()
{
	Gdiplus::GdiplusShutdown(m_gdiplus_token) ;
}