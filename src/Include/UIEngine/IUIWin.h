#pragma once
#include "Include/Def/Def.h"
#include "Include/Common/ICStruct.h"
#include "Include/UIEngine/IUICanvas.h"
#include "Include/UIEngine/IUIControl.h"

namespace WINDOW
{
	const TCHAR tcWinTitle[]	= _T("TITLE") ;
	const TCHAR tcWinRect[]		= _T("RECT") ;
	const TCHAR tcWinStyle[]	= _T("STYLE") ;
	const TCHAR tcWinStyleEx[]	= _T("STYLEEX") ;
}

__interface IUIWindowMessageCallback ;
[idl_quote("interface IUIWindowMessageCallback")] ;

[
	object ,
	uuid("C7A57F75-5780-454f-95DA-977F7C256B60") ,
	pointer_default(unique)
]
__interface IUIWin : IUIControl
{
	HRESULT SetTitle			(BSTR bsTitle) ;
	HRESULT GetTitle			(BSTR* bsTitle) ;
	HRESULT SetLayerWin			(BOOL bLayerWin) ;
	HRESULT GetLayerWin			(BOOL* pbLayerWin) ;
	HRESULT SetWindowAlpha		(BYTE cAlpha) ;
	HRESULT GetWindowAlpha		(BYTE* pcAlpha) ;
	HRESULT GetHWnd				(HWND* pHWnd) ;
	HRESULT SetWinSize			(SIZE szWin) ;
	HRESULT GetWinSize			(SIZE* pszWin) ;
	HRESULT SetMinWinSize		(SIZE szWin) ;
	HRESULT GetMinWinSize		(SIZE* pszWin) ;
	HRESULT SetMaxWinSize		(SIZE szWin) ;
	HRESULT GetMaxWinSize		(SIZE* pszWin) ;
	HRESULT SetFixSize			(BOOL bFixSize) ;
	HRESULT GetFixSize			(BOOL* pbFixSize) ;
	HRESULT SetWinLocation		(POINT ptLocation) ;
	HRESULT GetWinLocation		(POINT* pptLocation) ;
	HRESULT SetFixLocation		(BOOL bFixLocation) ;
	HRESULT GetFixLocation		(BOOL* pbFixLocation) ;
	HRESULT SetWindowBorder		(RECT rcBorder) ;
	HRESULT GetWindowBorder		(RECT* prcBorder) ;
	HRESULT SetWindowOutBorder	(RECT rcBorder) ;
	HRESULT GetWindowOutBorder	(RECT* prcBorder) ;
	HRESULT SetTopMost			(BOOL bTopMost) ;
	HRESULT GetTopMoust			(BOOL* pbTopMost) ;
	HRESULT SetToolWindow		(BOOL bToolWindow) ;
	HRESULT GetToolWindow		(BOOL* pbToolWindow) ;
	HRESULT GetStyle            (DWORD* pdwStyle) ;
	HRESULT GetStyleEx          (DWORD* pdwStyleEx) ;
	HRESULT ModifyStyle         (DWORD dwRmove, DWORD dwAdd, UINT uFlags) ;
	HRESULT ModifyStyleEx       (DWORD dwRmove, DWORD dwAdd, UINT uFlags) ;
	HRESULT SendMessage         (UINT uMsg, WPARAM wParam, LPARAM lParam) ;
	HRESULT PostMessage         (UINT uMsg, WPARAM wParam, LPARAM lParam) ;
	HRESULT SetWinCenter        () ;
	HRESULT BringToTop          () ;
	HRESULT SetActiveWindow     () ;
	HRESULT RefreshWindow       () ;
	HRESULT GetCaptureFrame     (IUIFrame** ppFrame) ;
	HRESULT FrameFromPoint      (POINT ptTarget, IUIFrame** ppFrame) ;
	HRESULT SetFoucsControl		(IUIControl* pControl) ;
	HRESULT GetFoucsControl		(IUIControl** ppControl) ;

	HRESULT AddMessageCallback  (IUIWindowMessageCallback* pCallback) ;
	HRESULT DelMessageCallback  (IUIWindowMessageCallback* pCallback) ;
	HRESULT HandleWinMessage    (UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL* pbHandle, LRESULT* pResult) ;

	HRESULT SetWinIcon          (BOOL bBig, HICON hIcon) ;
	HRESULT CreateWin			(IUIWin* pParent, ICVarData* pArg) ;
	HRESULT ShowWin				(INT nShowCmd) ;
	HRESULT DoModal				(IUIWin* pParent, INT nShowCmd) ;
	HRESULT DestoryWin			() ;
	HRESULT IdleDestoryWin		() ;
} ;

[
	object ,
	uuid("3E3F424A-58B8-47ae-9636-0978405A3A58") ,
	pointer_default(unique)
]
__interface IUIWindowPrePaint : IDispatch
{
	HRESULT PreWindowPaint      (IUICanvas* pCanvasIn, IUICanvas** ppCanvasOut) ;
} ;


[
	object ,
	uuid("1E0D4853-A7CA-435f-9B80-382E8E940CCE") ,
	pointer_default(unique)
]
__interface IUIWindowMessageCallback : IDispatch
{
	HRESULT OnWindowMessage     (HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) ;
} ;

COMMON_SINK_BEGIN(CComSinkUIWindowMessageCallback)
COMMON_SINK_FUNC(OnWindowMessage, (HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam), (hWnd, uMsg, wParam, lParam))
COMMON_SINK_END()
DECLARE_COMMON_SINK_PTR(CComSinkUIWindowMessageCallback, IUIWindowMessageCallback)