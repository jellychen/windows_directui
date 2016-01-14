#pragma once
#include "Include/Common/ICStruct.h"
#include "Include/UIEngine/TUIV2v.h"
#include "Include/UIEngine/IUIFont.h"
#include "Include/UIEngine/IUIAttribute.h"

[
	default(IUIFont) ,
	threading(free) ,
	uuid("0AD9ACD4-96AE-4960-AD07-16F7D631079A") ,
	coclass
]
class ATL_NO_VTABLE CCUIFont 
	: public IDispatchImpl<IUIFont>
	, public IDispatchImpl<IUIAttribute>
{
public:
	DECLARE_PROTECT_FINAL_CONSTRUCT() ;
	CCUIFont() ;
	virtual ~CCUIFont() ;

public:
	HRESULT _call SetWidth          (INT nWidth) ;
	HRESULT _call GetWidth          (INT* pnWidth) ;
	HRESULT _call SetHeight         (INT nHeight) ;
	HRESULT _call GetHeight         (INT* pnHeight) ;
	HRESULT _call SetEscapement     (INT nEscapement) ;
	HRESULT _call GetEscapement     (INT* pnEscapement) ;
	HRESULT _call SetWeight         (INT nWeight) ;
	HRESULT _call GetWeight         (INT* pnWeight) ;
	HRESULT _call SetItalic         (BOOL bItatic) ;
	HRESULT _call GetItalic         (BOOL* pbItatic) ;
	HRESULT _call SetStrikout       (BOOL bStrikeout) ;
	HRESULT _call GetStrikeout      (BOOL* pbStrikeout) ;
	HRESULT _call SetUnderline      (BOOL bUnderline) ;
	HRESULT _call GetUnderline      (BOOL* pbUnderline) ;
	HRESULT _call SetOutPrecision   (BYTE cOutPrecision) ;
	HRESULT _call GetOutPrecision   (BYTE* pcOutPrecision) ;
	HRESULT _call SetClipPrecision  (BYTE cClipPrecision) ;
	HRESULT _call GetClipPrecision  (BYTE* pcClipPrecision) ;
	HRESULT _call SetQuality        (BYTE cQuality) ;
	HRESULT _call GetQuality        (BYTE* pcQuality) ;
	HRESULT _call SetOrientation    (INT nOrientation) ;
	HRESULT _call GetOrientation    (INT* pnOrientation) ;
	HRESULT _call SetFacename       (BSTR bstrFacename) ;
	HRESULT _call GetFacename       (BSTR* pbstrFacename) ;
	HRESULT _call SetCharset        (BYTE cCharset) ;
	HRESULT _call GetCharset        (BYTE* pcCharset) ;
	HRESULT _call SetPitchAndFamily (BYTE cPitchAndFamily) ;
	HRESULT _call GetPitchAndFamily (BYTE* pcPitchAndFamily) ;
	HRESULT _call SetDrawType       (DWORD dwDrawType) ;
	HRESULT _call SetDrawType       (BSTR bstrDrawType) ;
	HRESULT _call GetDrawType       (DWORD* pdwDrawType) ;
	HRESULT _call GetLogFont        (LOGFONT* pLogFont) ;
	HRESULT _call GetHFont          (HFONT* phFont) ;
	HRESULT _call CloneFont         (IUIFont* pFont) ;
	HRESULT _call SetAttribute      (ICVarData* pAttrData) ;

private:
	INT                             m_nFontHeight ;
	INT                             m_nFontWidth ;
	INT                             m_nEscapement ;
	INT                             m_nWeight ;
	BOOL                            m_bItatic ;
	BOOL                            m_bStrikeout ;
	BOOL                            m_bUnderline ;
	BYTE                            m_cOutPrecision ;
	BYTE                            m_cClipPrecision ;
	BYTE                            m_cQuality ;
	INT                             m_nOrientation ;
	CString                         m_cstrFacename ;
	BYTE                            m_cCharset ;
	BYTE                            m_cPitchAndFamily ;
	DWORD                           m_dwDrawType ;
	BOOL                            m_bFontAttrChange ;
	HFONT                           m_hFont ;
};