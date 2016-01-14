#pragma once
#include "Include/UIEngine/IUIControl.h"
#include "Include/UIEngine/TUICustomFrame.h"
#include "Include/UIEngine/IUIExtension.h"
#include "Include/UIEngine/IUIExtensionDef.h"

[
	default(IUIControl) ,
	threading(free) ,
	uuid("FFC6EA36-F6C6-4cdf-A24E-1AC035C66C97") ,
	coclass
]
class ATL_NO_VTABLE CCUIControl
	: public TUICustomFrame<IUIControl, IUIFrame>
{
public:
	DECLARE_PROTECT_FINAL_CONSTRUCT() ;
	CCUIControl() ;
	virtual ~CCUIControl() ;
	HRESULT FinalConstruct() ;

public:
	HRESULT _call SetFocus          (BOOL bFocus) ;
	HRESULT _call GetFocus          (BOOL* pbFocus) ;
	HRESULT _call SetAutoCapture	(BOOL bAutoCapture) ;
	HRESULT _call GetAutoCapture	(BOOL* pbAutoCapture) ;
	HRESULT _call SetControlFoucs   (IUIControl* pControl) ;
	HRESULT _call GetControlFoucs   (IUIControl** ppControl) ;
	HRESULT _call ControlFocusChange(BOOL bFoucs) ;
	HRESULT _call SetToolTips		(BSTR bstrToolTips) ;
	HRESULT _call GetToolTips		(BSTR* pbstrToolTips) ;

public:
	//HRESULT _call CalcSize		(SIZE szOld, SIZE* pszCalcOut) ;
	HRESULT _call OnMessage			(IUIFrame* pTarget, tMsgArg* pArg) ;
	HRESULT _call SetAttribute		(ICVarData* pAttrData) ;

private:
	CString							m_cstrTooltips ;
	BOOL							m_bAutoCapture ;
};