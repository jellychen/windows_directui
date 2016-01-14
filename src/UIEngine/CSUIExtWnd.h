#pragma once
#include "Include/Def/Require.h"
#include "Include/Common/ISService.h"
#include "Include/UIEngine/IUIExtWnd.h"
#include <map>
#include <set>

typedef std::map<LONG, CComPtr<IUIExtWndCallback>>  MAP_CALLBACK ;
typedef std::map<INT, MAP_CALLBACK>                 MAP_CALLBACK_POOL ;

[
	default(IUIExtWnd) ,
	threading(free) ,
	uuid("BFB0B72B-2498-4745-B7EB-E5F8E580CCB9") ,
	coclass
]
class ATL_NO_VTABLE CSUIExtWnd 
	: public TCustomServiceImpl<IUIExtWnd>
{
public:
	DECLARE_PROTECT_FINAL_CONSTRUCT() ;
	CSUIExtWnd() ;
	virtual ~CSUIExtWnd() ;

public:
	HRESULT _call OnInit			() ;
	HRESULT _call OnUnInit			() ;
	HRESULT _call GetExtHWnd        (HWND* pHWnd) ;
	HRESULT _call PostMessage       (INT nMsg, WPARAM wParam, LPARAM lParam) ;
	HRESULT _call SendMessage       (INT nMsg, WPARAM wParam, LPARAM lParam) ;
	HRESULT _call RegisterCallback  (INT nMessageId, IUIExtWndCallback* pCallback) ;
	HRESULT _call UnRegisterCallback(INT nMessageId, IUIExtWndCallback* pCallback) ;

public:
	LRESULT OnMessage               (HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) ;

private:
	HWND                            m_hExtWnd ;
	MAP_CALLBACK_POOL               m_mapCallback ;
} ;