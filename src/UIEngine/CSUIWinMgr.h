#pragma once
#include "Include/Common/ISService.h"
#include "Include/UIEngine/IUIWinMgr.h"
#include <map>

typedef std::map<LONG, CWeakPtr<IUIWin>> MAP_WIN_AGENT_POOL ;

[
	default(IUIWinMgr) ,
	threading(free) ,
	uuid("43605EC1-82A4-4ffd-8DBC-0D10B182A353") ,
	coclass
]
class ATL_NO_VTABLE CSUIWinMgr
	: public TCustomServiceImpl<IUIWinMgr>
{
public:
	DECLARE_PROTECT_FINAL_CONSTRUCT() ;
	CSUIWinMgr() ;
	virtual ~CSUIWinMgr() ;

public:
	HRESULT _call OnServiceInit     () ;
	HRESULT _call OnServiceUnInit   () ;
	HRESULT _call AddWindow         (IUIWin* pWin) ;
	HRESULT _call DelWindow         (IUIWin* pWin) ;
	HRESULT _call GetWindowByHWnd   (HWND hWnd, IUIWin** pWin) ;
	HRESULT _call GetAllWindows     (ICVarArray* pWinArray) ;
	HRESULT _call GetAllWindowsCount(INT* pnCount) ;

private:
	MAP_WIN_AGENT_POOL              m_mapWindowsAgentPool ;
} ;