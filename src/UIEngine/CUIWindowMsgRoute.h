#pragma once

#include "Include/Def/Require.h"
#include "Include/UIEngine/IUIFrame.h"
#include "Include/UIEngine/IUIControl.h"
#include "Include/UIEngine/IUIQuad.h"
#include "Include/UIEngine/IUIWin.h"
#include "Include/UIEngine/IUIMessageStream.h"
#include "Include/UIEngine/IUIMessageDef.h"
#include <vector>

typedef std::vector<CComPtr<IUIFrame>> VEC_FRAME ;

class CUIMsgRoute
{
public:
	CUIMsgRoute() ;

public:
	BOOL InitMsgRoute       (HWND hWnd, IUIWin* pTargeWin) ;
	BOOL DispatchMessage    (UINT uMsg, WPARAM wParam, LPARAM lParam) ;

private:
	BOOL MessageTarget      (IUIFrame* pTarget, tMsgArg* pArgs, UINT uMsg) ;
	BOOL AncestorFrames     (IUIFrame* pTarget, VEC_FRAME* pvecFrame) ;
	BOOL DispatchBtnMessage (WPARAM wParam, LPARAM lParam,
		BOOL bLeftBtn, BOOL bBtnDown, BOOL bNcMsg, UINT uMsg) ;
	BOOL DispatchMouseMove  (WPARAM wParam, LPARAM lParam, BOOL bNcMsg, UINT uMsg) ;
	BOOL DispatchMouseLeave (WPARAM wParam, LPARAM lParam, BOOL bNcMsg, UINT uMsg) ;
	BOOL DispatchMouseWheel (WPARAM wParam, LPARAM lParam, UINT uMsg) ;
	BOOL DispatchDBClick    (WPARAM wParam, LPARAM lParam, BOOL bNcMsg, UINT uMsg) ;
	BOOL DispatchKeyMessage (WPARAM wParam, LPARAM lParam, UINT uMsg) ;
	BOOL DispatchInActive   (WPARAM wParam, LPARAM lParam, UINT uMsg) ;
	BOOL DispatchFoucs      (WPARAM wParam, LPARAM lParam, UINT uMsg) ;
	BOOL DispatchCursor     (WPARAM wParam, LPARAM lParam, UINT uMsg) ;
	BOOL DispatchImeMessage (WPARAM wParam, LPARAM lParam, UINT uMsg) ;

	BOOL FrameFromPoint     (POINT ptTarget, IUIFrame** ppFrame) ;

private:
	HWND                    m_hWnd ;
	BOOL                    m_bTrackLeave ;
	CWeakPtr<IUIWin>		m_pHostWinAgent ;
	CWeakPtr<IUIFrame>		m_pBtnDownFrameAgent ;
	CWeakPtr<IUIFrame>		m_pMouseOnFrameAgent ;
} ;