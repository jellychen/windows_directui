#pragma once
#include "Include/UIEngine/IUIControl.h"
#include "Include/UIEngine/TUICustomControl.h"

template<typename IActual, typename IBase>
class TUICustomWin
	: public TUICustomControl<IUIWin, IUIControl>
{
public:
	HRESULT _call SetTitle(BSTR bsTitle)
	{
		return this->m_pRawObject->SetTitle(bsTitle) ;
	}

	HRESULT _call GetTitle(BSTR* bsTitle) ;
	HRESULT _call SetLayerWin(BOOL bLayerWin) ;
	HRESULT _call GetLayerWin(BOOL* pbLayerWin) ;
	HRESULT _call SetWindowAlpha(BYTE cAlpha) ;
	HRESULT _call GetWindowAlpha(BYTE* pcAlpha) ;
	HRESULT _call GetHWnd(HWND* pHWnd) ;
	HRESULT _call SetWinSize(SIZE szWin) ;
	HRESULT _call GetWinSize(SIZE* pszWin) ;
	HRESULT _call SetMinWinSize(SIZE szWin) ;
	HRESULT _call GetMinWinSize(SIZE* pszWin) ;
	HRESULT _call SetMaxWinSize(SIZE szWin) ;
	HRESULT _call GetMaxWinSize(SIZE* pszWin) ;
	HRESULT _call SetFixSize(BOOL bFixSize) ;
	HRESULT _call GetFixSize(BOOL* pbFixSize) ;
	HRESULT _call SetWinLocation(POINT ptLocation) ;
	HRESULT _call GetWinLocation(POINT* pptLocation) ;
	HRESULT _call SetFixLocation(BOOL bFixLocation) ;
	HRESULT _call GetFixLocation(BOOL* pbFixLocation) ;
	HRESULT _call SetWindowBorder(RECT rcBorder) ;
	HRESULT _call GetWindowBorder(RECT* prcBorder) ;
	HRESULT _call SetWindowOutBorder(RECT rcBorder) ;
	HRESULT _call GetWindowOutBorder(RECT* prcBorder) ;
	HRESULT _call SetTopMost(BOOL bTopMost) ;
	HRESULT _call GetTopMoust(BOOL* pbTopMost) ;
	HRESULT _call SetToolWindow(BOOL bToolWindow) ;
	HRESULT _call GetToolWindow(BOOL* pbToolWindow) ;
	HRESULT _call GetStyle(DWORD* pdwStyle) ;
	HRESULT _call GetStyleEx(DWORD* pdwStyleEx) ;
	HRESULT _call ModifyStyle(DWORD dwRmove, DWORD dwAdd, UINT uFlags) ;
	HRESULT _call ModifyStyleEx(DWORD dwRmove, DWORD dwAdd, UINT uFlags) ;
	HRESULT _call SendMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) ;
	HRESULT _call PostMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) ;
	HRESULT _call SetWinCenter() ;
	HRESULT _call BringToTop() ;
	HRESULT _call SetActiveWindow() ;
	HRESULT _call RefreshWindow() ;
	HRESULT _call GetCaptureFrame(IUIFrame** ppFrame) ;
	HRESULT _call FrameFromPoint(POINT ptTarget, IUIFrame** ppFrame) ;
	HRESULT _call SetFoucsControl(IUIControl* pControl) ;
	HRESULT _call GetFoucsControl(IUIControl** ppControl) ;
	HRESULT _call AddMessageCallback(IUIWindowMessageCallback* pCallback) ;
	HRESULT _call DelMessageCallback(IUIWindowMessageCallback* pCallback) ;
	HRESULT _call HandleWinMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL* pbHandle, LRESULT* pResult) ;
	HRESULT _call SetWinIcon(BOOL bBig, HICON hIcon) ;
	HRESULT _call CreateWin(IUIWin* pParent, ICVarData* pArg) ;
	HRESULT _call ShowWin(INT nShowCmd) ;
	HRESULT _call DoModal(IUIWin* pParent, INT nShowCmd) ;
	HRESULT _call DestoryWin() ;
	HRESULT _call IdleDestoryWin() ;
} ;