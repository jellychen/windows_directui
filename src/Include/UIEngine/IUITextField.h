#pragma once
#include "Include/UIEngine/IUIFont.h"
#include "Include/UIEngine/IUIControl.h"
#include "Include/UIEngine/IUIScroll.h"

[
	object ,
	uuid("DDB55AC5-C978-466c-B405-D242DCAC7B7F") ,
	pointer_default(unique)
]
__interface IUITextField : IUIControl
{
	HRESULT SetFont				(IUIFont* pFont)	;
	HRESULT GetFont				(IUIFont** ppFont)	;
	HRESULT SetLineHeight		(INT nLineHeight)	;
	HRESULT GetLineHeight		(INT* pnLineHeight) ;
	HRESULT SetReadOnly			(BOOL bReadOnly)	;
	HRESULT GetReadOnly			(BOOL* pbReadOnly)	;
	HRESULT SetMaxLength		(INT nMaxLength)	;
	HRESULT GetMaxLength		(INT* pnMaxLength)	;
	HRESULT SetPassWord			(BOOL bPassWord)	;
	HRESULT GetPassWord			(BOOL* pbPassWord)	;
	HRESULT SetOnlyNumber		(BOOL bOnlyNumber)	;
	HRESULT GetOnlyNumber		(BOOL* pbOnlyNumber);
	HRESULT SetEnableIME		(BOOL bEnableIME)	;
	HRESULT GetEnableIME		(BOOL* pbEnableIME)	;
	HRESULT SetWantTab			(BOOL bWantTab)		;
	HRESULT GetWantTab			(BOOL* pbWantTab)	;
	HRESULT SetWantReturn		(BOOL bWantReturn)	;
	HRESULT GetWantReturn		(BOOL* pbWantReturn);
	HRESULT SetSingleLine		(BOOL bSingleLine)	;
	HRESULT GetSingleLine		(BOOL* pbSingleLine);
	HRESULT SetTextColor		(COLORREF clrText)	;
	HRESULT GetTextColor		(COLORREF* pclrText);
	HRESULT SetHighTextColor	(COLORREF clrText)	;
	HRESULT GetHighTextColor	(COLORREF* pclrText);
	HRESULT SetHightMaskColor	(COLORREF clrMask)	;
	HRESULT GetHightMaskColor	(COLORREF* pclrMask);
	HRESULT SetPassWordChar		(TCHAR tcReplace)	;
	HRESULT GetPassWordChar		(TCHAR* ptcReplace) ;
	HRESULT SetText				(BSTR bstrText)		;
	HRESULT GetText				(BSTR* pbstrText)	;
	HRESULT SetSelectRange		(INT nLeft, INT nRight)		;
	HRESULT GetSelectRange		(INT* pnLeft, INT* pnRight) ;
	HRESULT SetScroll			(IUIScroll* pScroll) ;
	HRESULT GetScroll			(IUIScroll** ppScroll) ;
} ;