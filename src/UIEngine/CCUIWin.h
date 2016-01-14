#pragma once
#include "Include/Util/Utiltpl.h"
#include "Include/UIEngine/IUIWin.h"
#include "Include/UIEngine/IUIMsgLoop.h"
#include "Include/UIEngine/IUISplit.h"
#include "Include/UIEngine/IUIQuad.h"
#include "Include/UIEngine/IUIHittest.h"
#include "Include/UIEngine/IUICanvas.h"
#include "Include/UIEngine/IUIWinMgr.h"
#include "Include/UIEngine/IUIRender.h"
#include "Include/UIEngine/TUICustomControl.h"
#include "Include/UIEngine/IUI3DTransfrom.h"
#include "Include/UIEngine/IUITimer.h"
#include "CUIWindowDef.h"
#include "CUIWindowMsgRoute.h"
#include <map>
#include <vector>
typedef std::map<LONG, CComPtr<IUIWindowMessageCallback>>	MAP_MESSAGE_CALLBACK ;
typedef std::vector<CWeakPtr<IUIFrame>>						VEC_FRAME_AGENT ;

[
	default(IUIWin) ,
	threading(free) ,
	uuid("FA0ED798-DEBF-42e2-BA6A-9AB45A9F147B") ,
	coclass
]
class ATL_NO_VTABLE CCUIWin
	: public TUICustomControl<IUIWin, IUIControl>
	, public CWindowImpl<CCUIWin>
{
public:
	DECLARE_PROTECT_FINAL_CONSTRUCT() ;
	CCUIWin() ;
	virtual ~CCUIWin() ;
	HRESULT FinalConstruct() ;

public:
	HRESULT _call SetTitle				(BSTR bsTitle) ;
	HRESULT _call GetTitle				(BSTR* bsTitle) ;
	HRESULT _call SetLayerWin			(BOOL bLayerWin) ;
	HRESULT _call GetLayerWin			(BOOL* pbLayerWin) ;
	HRESULT _call SetWindowAlpha		(BYTE cAlpha) ;
	HRESULT _call GetWindowAlpha		(BYTE* pcAlpha) ;
	HRESULT _call GetHWnd				(HWND* pHWnd) ;
	HRESULT _call SetWinSize			(SIZE szWin) ;
	HRESULT _call GetWinSize			(SIZE* pszWin) ;
	HRESULT _call SetMinWinSize			(SIZE szWin) ;
	HRESULT _call GetMinWinSize			(SIZE* pszWin) ;
	HRESULT _call SetMaxWinSize			(SIZE szWin) ;
	HRESULT _call GetMaxWinSize			(SIZE* pszWin) ;
	HRESULT _call SetFixSize			(BOOL bFixSize) ;
	HRESULT _call GetFixSize			(BOOL* pbFixSize) ;
	HRESULT _call SetWinLocation		(POINT ptLocation) ;
	HRESULT _call GetWinLocation		(POINT* pptLocation) ;
	HRESULT _call SetFixLocation		(BOOL bFixLocation) ;
	HRESULT _call GetFixLocation		(BOOL* pbFixLocation) ;
	HRESULT _call SetWindowBorder		(RECT rcBorder) ;
	HRESULT _call GetWindowBorder		(RECT* prcBorder) ;
	HRESULT _call SetWindowOutBorder	(RECT rcBorder) ;
	HRESULT _call GetWindowOutBorder	(RECT* prcBorder) ;
	HRESULT _call SetTopMost			(BOOL bTopMost) ;
	HRESULT _call GetTopMoust			(BOOL* pbTopMost) ;
	HRESULT _call SetToolWindow			(BOOL bToolWindow) ;
	HRESULT _call GetToolWindow			(BOOL* pbToolWindow) ;
	HRESULT _call GetStyle				(DWORD* pdwStyle) ;
	HRESULT _call GetStyleEx			(DWORD* pdwStyleEx) ;
	HRESULT _call ModifyStyle			(DWORD dwRmove, DWORD dwAdd, UINT uFlags) ;
	HRESULT _call ModifyStyleEx			(DWORD dwRmove, DWORD dwAdd, UINT uFlags) ;
	HRESULT _call SendMessage			(UINT uMsg, WPARAM wParam, LPARAM lParam) ;
	HRESULT _call PostMessage			(UINT uMsg, WPARAM wParam, LPARAM lParam) ;
	HRESULT _call SetWinCenter			() ;
	HRESULT _call BringToTop			() ;
	HRESULT _call SetActiveWindow		() ;
	HRESULT _call RefreshWindow			() ;
	HRESULT _call GetCaptureFrame		(IUIFrame** ppFrame) ;
	HRESULT _call FrameFromPoint		(POINT ptTarget, IUIFrame** ppFrame) ;
	HRESULT _call SetFoucsControl		(IUIControl* pControl) ;
	HRESULT _call GetFoucsControl		(IUIControl** ppControl) ;
	HRESULT _call AddMessageCallback	(IUIWindowMessageCallback* pCallback) ;
	HRESULT _call DelMessageCallback	(IUIWindowMessageCallback* pCallback) ;
	HRESULT _call HandleWinMessage		(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL* pbHandle, LRESULT* pResult) ;
	HRESULT _call SetWinIcon			(BOOL bBig, HICON hIcon) ;
	HRESULT _call CreateWin				(IUIWin* pParent, ICVarData* pArg) ;
	HRESULT _call ShowWin				(INT nShowCmd) ;
	HRESULT _call DoModal				(IUIWin* pParent, INT nShowCmd) ;
	HRESULT _call DestoryWin			() ;
	HRESULT _call IdleDestoryWin		() ;

public:
	HRESULT _call SetCapture			(BOOL bCapture) ;
	HRESULT _call SetEnable             (BOOL bEnable) ;
	HRESULT _call GetAbsolutLocation    (POINT* pptLocation) ;
	HRESULT _call GetScreenLocation     (POINT* pptLocation) ;
	HRESULT _call GetAbsolutVisibleRect (RECT* prcRect) ;
	HRESULT _call GetShowAlpha          (BYTE* pcAlpha) ;
	HRESULT _call GetMousePosInternal   (POINT* pptPoint) ;
	HRESULT _call SetCaptureInternal    (BOOL bCapture, IUIFrame* pFrame) ;
	HRESULT _call GetCaptureInternal    (IUIFrame** ppFrame) ;
	HRESULT _call SynchronizeInternal   (IUIFrame* pFrame, BOOL bErase) ;
	HRESULT _call InvalidateInternal    (IUIFrame* pFrame) ;
	HRESULT _call InvalidateRect        (RECT rcInvalidate) ;
	HRESULT _call InvalidateLayout      (IUIFrame* pFrame) ;
	HRESULT _call SetAttribute          (ICVarData* pAttrData) ;
	HRESULT _call SetControlFoucs       (IUIControl* pControl) ;
	HRESULT _call GetControlFoucs       (IUIControl** ppControl) ;

public:
	BOOL    ProcessWindowMessage    (HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT& lResult, DWORD dwMsgMapID) ;

private:
	LRESULT OnCreate					(LPCREATESTRUCT lpCreateStruct) ;
	LRESULT OnActivate					(UINT unState, BOOL bMinimized, BOOL& bHandled) ;
	LRESULT OnNcCalcSize				(BOOL bCalc, LPARAM lParam, BOOL& bHandled) ;
	LRESULT OnGetMinMaxInfo				(LPMINMAXINFO lpmmInfo, BOOL& bHandled) ;
	LRESULT OnNcHitTest					(WPARAM wParam, LPARAM lParam, POINT pt, BOOL& bHandled) ;
	LRESULT OnNcPaint					(LONG hRGN, BOOL& bHandled) ;
	LRESULT OnNcLBtnDown				(UINT uArg, POINT pt, BOOL& bHandled) ;
	LRESULT OnNCDestroy					(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) ;
	LRESULT OnEraseBkgnd				(HDC hDC, BOOL& bHandled) ;
	LRESULT OnPaint						(HDC hDC, BOOL& bHandled) ;
	LRESULT OnSize						(UINT uType, SIZE szWnd, BOOL& bHandled) ;
	LRESULT OnMoving					(RECT* prcWnd, BOOL& bHandled) ;
	LRESULT OnKeyDown					(UINT unChar, UINT unRepCnt, UINT unFlags, BOOL& bHandled) ;
	LRESULT OnMouseMove					(UINT unFlags, POINT pt, BOOL& bHandled) ;
	LRESULT OnMouseLeave				(BOOL& bHandled) ;
	LRESULT OnDestory					(BOOL& bHandled) ;

private:
	BOOL	CheckWndAutoSize			() ;
	BOOL	RenderWnd					() ;

private: // test
	int RotateX ;
	int OffsetZ ;
	HRESULT OnTimer(INT nTimerId)
	{
		RotateX += 2 ;
		//this->m_p3DTransfrom->SetRotateX(RotateX%360) ;
		//m_p3DTransfrom->SetRotateY(RotateX) ;
		//m_p3DTransfrom->SetRotateZ(RotateX) ;

		OffsetZ += 50 ;
		//m_p3DTransfrom->SetOffsetZ(-OffsetZ+ 900) ;
		__self->Invalidate() ;
		return S_OK ;
	}
	CComSinkTimerCallbackPtr<CCUIWin>		m_pTimerCallback ;


private:
	BOOL								m_bTopMost ;
	BOOL								m_bLayerWin ;
	BOOL								m_bToolWin ;
	BOOL								m_bFixSize ;
	BOOL								m_bFixLocation ;
	BOOL								m_bDoModal ;
	CWeakPtr<IUIWin>					m_pDoModalWinAgent ;
	BOOL								m_bNeedRePaint ;
	CSize								m_szWin ;
	CSize								m_szWinMinSize ;
	CSize								m_szWinMaxSize ;
	CPoint								m_ptWinLocation ;
	CRect								m_rcWinBorder ;
	CRect								m_rcWinOutBorder ;
	BYTE								m_cWinAlpha ;
	CComPtr<IUI3DTransfrom>				m_p3DTransfrom ;
	CWeakPtr<IUIFrame>					m_pCatureFrameAgent ;
	CWeakPtr<IUIControl>				m_pFoucsControl ;
	CComPtr<IUIQuad>					m_pQuadTree ;
	CComPtr<IUISplit>					m_pSplit ;
	CComPtr<IUIHittest>					m_pHittest ;
	CComPtr<IUICanvas>					m_pWinCanvas ;
	CWeakPtr<IUIWinMgr>					m_pWinMgr ;
	CComPtr<IUIRender>					m_pRender ;
	CUIMsgRoute							m_pMessageRoute ;
	MAP_MESSAGE_CALLBACK				m_mapWindowMessageCallbackPool ;
	VEC_FRAME_AGENT						m_vecFrameAgent ;
} ;	