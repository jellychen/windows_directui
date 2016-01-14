#pragma once

namespace FONT_DRAW
{
	enum
	{
		DRAW_DEFAULT                    = 0x0   ,
		DRAW_SINGLEBITPERPIXELGRIDFIT           ,
		DRAW_SINGLEBITPERPIXEL                  ,
		DRAW_ANTIALIASGRIDFIT                   ,
		DRAW_ANTIALIAS                          ,
		DRAW_CLEARTYPEGRIDFIT                   ,
	} ;
}

[
	object ,
	uuid("2A179EB5-BEED-4582-9FA9-5CFCD150B4F3") ,
	pointer_default(unique)
]
__interface IUIFont : IDispatch
{
	HRESULT SetWidth            (INT nWidth) ;
	HRESULT GetWidth            (INT* pnWidth) ;
	HRESULT SetHeight           (INT nHeight) ;
	HRESULT GetHeight           (INT* pnHeight) ;
	HRESULT SetEscapement       (INT nEscapement) ;
	HRESULT GetEscapement       (INT* pnEscapement) ;
	HRESULT SetWeight           (INT nWeight) ;
	HRESULT GetWeight           (INT* pnWeight) ;
	HRESULT SetItalic           (BOOL bItatic) ;
	HRESULT GetItalic           (BOOL* pbItatic) ;
	HRESULT SetStrikout         (BOOL bStrikeout) ;
	HRESULT GetStrikeout        (BOOL* pbStrikeout) ;
	HRESULT SetUnderline        (BOOL bUnderline) ;
	HRESULT GetUnderline        (BOOL* pbUnderline) ;
	HRESULT SetOutPrecision     (BYTE cOutPrecision) ;
	HRESULT GetOutPrecision     (BYTE* pcOutPrecision) ;
	HRESULT SetClipPrecision    (BYTE cClipPrecision) ;
	HRESULT GetClipPrecision    (BYTE* pcClipPrecision) ;
	HRESULT SetQuality          (BYTE cQuality) ;
	HRESULT GetQuality          (BYTE* pcQuality) ;
	HRESULT SetOrientation      (INT nOrientation) ;
	HRESULT GetOrientation      (INT* pnOrientation) ;
	HRESULT SetFacename         (BSTR bstrFacename) ;
	HRESULT GetFacename         (BSTR* pbstrFacename) ;
	HRESULT SetCharset          (BYTE cCharset) ;
	HRESULT GetCharset          (BYTE* pcCharset) ;
	HRESULT SetPitchAndFamily   (BYTE cPitchAndFamily) ;
	HRESULT GetPitchAndFamily   (BYTE* pcPitchAndFamily) ;
	HRESULT SetDrawType         (DWORD dwDrawType) ;
	HRESULT GetDrawType         (DWORD* pdwDrawType) ;
	HRESULT GetLogFont          (LOGFONT* pLogFont) ;
	HRESULT GetHFont            (HFONT* phFont) ;
	HRESULT CloneFont           (IUIFont* pFont) ;
} ;