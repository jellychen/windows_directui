#pragma once
#include "Include/Common/ISService.h"
#include "Include/UIEngine/IUIMsgLoop.h"
#include <map>

typedef std::map<LONG, CComPtr<IUIMsgLoopCallback>> MAP_CALLBACK ;

[
	default(IUIMsgLoop) ,
	threading(free) ,
	uuid("70348E9C-1F85-4052-BD93-45DCEA342B3C") ,
	coclass
]
class ATL_NO_VTABLE CSUIMsgLoop
	: public TCustomServiceImpl<IUIMsgLoop>
{
public:
	DECLARE_PROTECT_FINAL_CONSTRUCT() ;
	CSUIMsgLoop() ;
	virtual ~CSUIMsgLoop() ;

public:
	HRESULT _call OnInit				() ;
	HRESULT _call OnUnInit				() ;
	
	HRESULT _call StartLoop             () ;
	HRESULT _call QuitCurrentLoop       () ;
	HRESULT _call ShouldQuitLoop        () ;
	HRESULT _call ForceQuitAllLoop		() ;
	HRESULT _call SetMsgLoopFunction	(IUIMsgLoopFunction* pMsgLoop) ;
	HRESULT _call RegisterLoopCallback  (IUIMsgLoopCallback* pCallback) ;
	HRESULT _call UnRegisterLoopCallback(IUIMsgLoopCallback* pCallback) ;
	HRESULT _call NotifyMsgArrive       (MSG* pMsg) ;
	HRESULT _call NotifyMsgComplete     (MSG* pMsg) ;

private:
	VOID	_message_loop				() ;


private:
	CComPtr<IUIMsgLoopFunction>         m_pMsgLoopFunction ;
	MAP_CALLBACK                        m_mapLoopCallback ;
	DWORD                               m_dwQuitRef ;
	BOOL								m_bForceQuitAllLoop ;
	INT									m_nCurrentLoopIndex ;
} ;