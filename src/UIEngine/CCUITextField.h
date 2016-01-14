#pragma once
#include "Include/Util/Utiltpl.h"
#include "Include/Common/ICVarData.h"
#include "Include/UIEngine/TUIV2v.h"
#include "Include/UIEngine/IUICaret.h"
#include "Include/UIEngine/IUITextField.h"
#include "Include/UIEngine/TUICustomControl.h"
#include "Include/UIEngine/TUIUtil.h"
#include "CCUITextFieldNode.h"
#include <GdiPlus.h>

[
	default(IUITextField) ,
	threading(free) ,
	uuid("73DD2117-8AC6-4935-AE8A-F15DF376589D") ,
	coclass
]
class ATL_NO_VTABLE CCUITextField
	: public TUICustomControl<IUITextField, IUIControl>
{
public:
	DECLARE_PROTECT_FINAL_CONSTRUCT() ;
	CCUITextField() ;
	virtual ~CCUITextField() ;
	HRESULT FinalConstruct() ;
public:
	HRESULT _call SetFont			(IUIFont* pFont)	;
	HRESULT _call GetFont			(IUIFont** ppFont)	;
	HRESULT _call SetLineHeight		(INT nLineHeight)	;
	HRESULT _call GetLineHeight		(INT* pnLineHeight) ;
	HRESULT _call SetReadOnly		(BOOL bReadOnly)	;
	HRESULT _call GetReadOnly		(BOOL* pbReadOnly)	;
	HRESULT _call SetMaxLength		(INT nMaxLength)	;
	HRESULT _call GetMaxLength		(INT* pnMaxLength)	;
	HRESULT _call SetPassWord		(BOOL bPassWord)	;
	HRESULT _call GetPassWord		(BOOL* pbPassWord)	;
	HRESULT _call SetOnlyNumber		(BOOL bOnlyNumber)	;
	HRESULT _call GetOnlyNumber		(BOOL* pbOnlyNumber);
	HRESULT _call SetEnableIME		(BOOL bEnableIME)	;
	HRESULT _call GetEnableIME		(BOOL* pbEnableIME)	;
	HRESULT _call SetWantTab		(BOOL bWantTab)		;
	HRESULT _call GetWantTab		(BOOL* pbWantTab)	;
	HRESULT _call SetWantReturn		(BOOL bWantReturn)	;
	HRESULT _call GetWantReturn		(BOOL* pbWantReturn);
	HRESULT _call SetSingleLine		(BOOL bSingleLine)	;
	HRESULT _call GetSingleLine		(BOOL* pbSingleLine);
	HRESULT _call SetTextColor		(COLORREF clrText)	;
	HRESULT _call GetTextColor		(COLORREF* pclrText);
	HRESULT _call SetHighTextColor	(COLORREF clrText)	;
	HRESULT _call GetHighTextColor	(COLORREF* pclrText);
	HRESULT _call SetHightMaskColor	(COLORREF clrMask)	;
	HRESULT _call GetHightMaskColor	(COLORREF* pclrMask);
	HRESULT _call SetPassWordChar	(TCHAR tcReplace)	;
	HRESULT _call GetPassWordChar	(TCHAR* ptcReplace) ;
	HRESULT _call SetText			(BSTR bstrText)		;
	HRESULT _call GetText			(BSTR* pbstrText)	;
	HRESULT _call SetSelectRange	(INT nLeft, INT nRight)		;
	HRESULT _call GetSelectRange	(INT* pnLeft, INT* pnRight) ;
	HRESULT _call SetScroll			(IUIScroll* pScroll) ;
	HRESULT _call GetScroll			(IUIScroll** ppScroll) ;

public:
	HRESULT _call Layout			() ;
	HRESULT _call Render			(IUICanvas* pCanvas, RECT rcRender, INT nState) ;
	HRESULT _call OnMessage			(IUIFrame* pTarget, tMsgArg* pArg) ;
	HRESULT _call SetPadding		(RECT rcPadding) ;
	HRESULT _call ControlFocusChange(BOOL bFoucs) ;

private:
	BOOL	ReChar					() ;
	BOOL	LayoutChar				() ;
	CRect	CalcRenderRect			() ;
	CSize	CalcCharSize			(TCHAR tcChar) ;
	CSize	CalcDefautCharSize		() ;
	BOOL	CanVisibleChar			(TCHAR tcChar) ;
	BOOL	CalcCharInfo			(TCHAR tcChar, _TextNode& _node) ;
	INT		CalcCharIndex			(INT x, INT y, BOOL* pbSide, INT* pLine, INT* pCaretTop, INT* pCaretLeft) ;
	BOOL	MoveCaretIndex			(INT nIndex, BOOL bSide, BOOL bRight = TRUE) ;
	BOOL	CalcIndexInLine			(INT nIndexLeft, INT nIndexRight) ;
	BOOL	IsIndexIsLineStart		(INT nIndex) ;
	BOOL	IsIndexIsLineEnd		(INT nIndex) ;
	BOOL	MoveCaretLeft			() ;
	BOOL	MoveCaretRight			() ;
	BOOL	MoveCaretUp				() ;
	BOOL	MoveCaretDown			() ;
	BOOL	CalcSelectRange			(INT* pnLeft, INT* pnRight) ;
	BOOL	ClearSelectRange		() ;
	CString GetSelectString			() ;
	BOOL	DeleteSelect			(BOOL bInvalidate = TRUE) ;
	BOOL	DeleteCurrentCaretPos	(BOOL bInvalidate = TRUE) ;
	BOOL	InsertChar				(TCHAR tcChar) ;
	BOOL	InsertString			(CString strInsert) ;
	BOOL	SelectAllText			() ;
	BOOL	MakeSureCaretInScrope	() ;
	CString GetStringFromClipboard	() ;
	BOOL	PutStringToClipboard	(CString strClipboard) ;

private:
	VOID	OnKeyDown				(IUIFrame* pTarget, tMsgArg* pArg) ;
	VOID	OnKeyUp					(IUIFrame* pTarget, tMsgArg* pArg) ;
	VOID	OnLButtonDown			(IUIFrame* pTarget, tMsgArg* pArg) ;
	VOID	OnLButtonUp				(IUIFrame* pTarget, tMsgArg* pArg) ;
	VOID	OnMouseMove				(IUIFrame* pTarget, tMsgArg* pArg) ;
	VOID	OnCursor				(IUIFrame* pTarget, tMsgArg* pArg) ;
	VOID	OnChar					(IUIFrame* pTarget, tMsgArg* pArg) ;
	VOID	OnImeStartComposition	(IUIFrame* pTarget, tMsgArg* pArg) ;

private:
	HDC								m_hTempeDC ;
	HFONT							m_hOldFont ;
	CString							m_strEdit ;
	CComPtr<IUIFont>				m_pFont ;
	CComPtr<IUICaret>				m_pCaret ;
	INT								m_nLineHeight ;
	INT								m_nMaxLength ;
	INT								m_nLeftSelect ;
	INT								m_nRightSelect ;
	BOOL							m_bLeftButtonDwon ;
	VEC_CHAR						m_vecChar ;
	VEC_VERTICAL					m_vecVertical ;
	BOOL							m_bReadOnly ;
	BOOL							m_bPasswd ;
	TCHAR							m_tcPasswdChar ;
	BOOL							m_bNumberOnly ;
	BOOL							m_bEnableIME ;
	BOOL							m_bWantTab ;
	BOOL							m_bWantReturn ;
	BOOL							m_bSingleLine ;
	CPoint							m_ptLayoutOffset ;
	INT								m_nCaretIndex ;
	BOOL							m_bCaretSide ;
	INT								m_nCaretLine ;
	INT								m_nSelectLeft ;
	BOOL							m_bSelectLeftSide ;
	INT								m_nSelectRight ;
	BOOL							m_bSelectRightSide ;
	CSize							m_szTextFieldSize ;
	COLORREF						m_clrTextColor ;
	COLORREF						m_clrHighTextColor ;
	COLORREF						m_clrHighTextMaskColor ;
	INT								m_nNeedFieldHeight ;
	BOOL							m_bShowScroll ;
	CComPtr<IUIScroll>				m_pScroll ;
} ;