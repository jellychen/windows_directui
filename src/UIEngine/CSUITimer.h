#pragma once
#include "Include/UIEngine/IUITimer.h"
#include "Include/UIEngine/IUIExtWnd.h"
#include "Include/Common/ISService.h"
#include <map>
#include <set>
#include <vector>

class CUITimerItem
{
public:
	CUITimerItem()
	{
		this->m_bOnce           = TRUE ;
		this->m_dwIntervalTime  = 0 ;
		this->m_dwEndTime       = 0 ;
		this->m_nTimerId        = -1 ;
	}

public:
	BOOL                        m_bOnce ;
	DWORD                       m_dwIntervalTime ;
	DWORD                       m_dwEndTime ;
	INT                         m_nTimerId ;
	CComPtr<IUITimerCallback>   m_pTimerCallback ;
} ;

[
	default(IUITimer) ,
	threading(free) ,
	uuid("53B839C9-764B-4ec1-9580-A6168F24246C") ,
	coclass
]
class ATL_NO_VTABLE CSUITimer : public TCustomServiceImpl<IUITimer>
{
public:
	DECLARE_PROTECT_FINAL_CONSTRUCT() ;
	CSUITimer() ;
	virtual ~CSUITimer() ;

public:
	HRESULT _call OnInit			() ;
	HRESULT _call OnUnInit			() ;
	HRESULT _call SetTimerOut       (IUITimerCallback* pCallback, DWORD dwTime, INT nTimerId) ;
	HRESULT _call SetInterval       (IUITimerCallback* pCallback, DWORD dwTime, INT nTimerId) ;
	HRESULT _call Erase             (IUITimerCallback* pCallback, INT nTimerId) ;

public:
	HRESULT OnMessageCallback       (INT nMessageId, WPARAM wParam, LPARAM lParam) ;
	HRESULT AddNewItem              (IUITimerCallback* pTimerCallback, DWORD dwTime, INT nTimerId, BOOL bOnce) ;

private:
	HWND                                            m_hTimerWnd ;
	CWeakPtr<IUIExtWnd>								m_pExtWndService ;
	CComSinkExtWndCallbackPtr<CSUITimer>            m_pExtWndCallbackPtr ;
	BOOL                                            m_bTimerRunning ;
	typedef std::map<LONG, std::set<INT>>           MAP_TIMER_ID_POOL ;
	typedef std::vector<CUITimerItem>               VEC_TIMER_ITME ;
	typedef std::map<LONG, VEC_TIMER_ITME>          MAP_TIMER_POOL ;
	MAP_TIMER_ID_POOL                               m_mapTimerIdPool ;
	MAP_TIMER_POOL                                  m_mapTimerPool ;
} ;