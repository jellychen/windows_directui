#pragma once
#include "Include/Util/Utiltpl.h"
#include "Include/Common/ICStruct.h"
#include "Include/BaseMisc/ISFileroute.h"
#include "Include/UIEngine/IUIAttribute.h"
#include "Include/UIEngine/IUITexture.h"
#include "Include/UIEngine/TUIV2v.h"
#include "Include/ThridParty/StbImage/stb_image.h"
#include <cmath>

[
	default(IUITexture) ,
	threading(free) ,
	uuid("431A3385-CAAF-4354-98CC-7FE3AA4889D6") ,
	coclass
]
class ATL_NO_VTABLE CCUITexture
	: public IDispatchImpl<IUITexture>
	, public IDispatchImpl<IUIAttribute>
{
public:
	DECLARE_PROTECT_FINAL_CONSTRUCT() ;
	CCUITexture() ;
	virtual ~CCUITexture() ;
	HRESULT FinalConstruct() ;

public:
	HRESULT _call LoadFromFile      (BSTR bstrFile) ;
	HRESULT _call LoadFromComBuffer (ICVarBuffer* pBuffer) ;
	HRESULT _call LoadFromBuffer    (BYTE* pbBuffer, LONG lBufferLen) ;
	HRESULT _call SetDrawType       (DWORD dwType) ;
	HRESULT _call SetDrawType       (BSTR bstrType) ;
	HRESULT _call GetDrawType       (DWORD* pdwType) ;
	HRESULT _call SetDrawRect       (RECT rcDraw) ;
	HRESULT _call GetDrawRect       (RECT* prcDraw) ;
	HRESULT _call SetDrawGrid       (RECT rcGrid) ;
	HRESULT _call GetDrawGrid       (RECT* prcGrid) ;
	HRESULT _call FreeTexture       () ;
	HRESULT _call GetSize           (SIZE* pszDraw) ;
	HRESULT _call DrawOnDC          (HDC hDC, RECT rcDraw, BYTE cAlpha) ;
	HRESULT _call DrawOnCanvas      (IUICanvas* pCanvas, RECT rcDraw, BYTE cAlpha) ;

	HRESULT _call SetAttribute      (ICVarData* pAttrData) ;
private:
	BOOL    _Load_image_buffer      (BYTE* pbBuffer, LONG lBufferLen) ;
	BOOL    _draw_image             (HDC hDC , HBITMAP hBitmap , 
		const CRect& rcPaint , const CRect& rcBmpPart , 
		const CRect& rcCorners, BOOL alphaChannel, BYTE cAlpha) ;

private:
	CWeakPtr<ISFileroute>			m_pFilerouteService ;
	CString                         m_cstrImage ;
	HBITMAP                         m_hBitmap ;
	CSize                           m_szImage ;
	BOOL                            m_bAlphaChannel ;
	BOOL                            m_bImageCached ;
	CRect                           m_rcDrawRect ;
	CRect                           m_rcDrawGrid ;
	DWORD                           m_dwDrawType ;
} ;