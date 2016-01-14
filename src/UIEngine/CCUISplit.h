#pragma once
#include "Include/UIEngine/IUISplit.h"

[
	default(IUISplit) ,
	threading(free) ,
	uuid("671957AE-3CF9-4eed-AC13-FD82E83E0CE4") ,
	coclass
]
class ATL_NO_VTABLE CCUISplit
	: public IDispatchImpl<IUISplit>
{
public:
	DECLARE_PROTECT_FINAL_CONSTRUCT() ;
	CCUISplit() ;
	virtual ~CCUISplit() ;

public:
	HRESULT _call AddRect       (RECT rcRect) ;
	HRESULT _call Split         (ICVarArray* pRectArray) ;
	HRESULT _call Split2        (IUIAddRect* pAddRect) ;
	HRESULT _call GetCount      (INT* pnCount) ;
	HRESULT _call GetByIndex    (INT nIndex, RECT* prcRect) ;
	HRESULT _call Clear         () ;

private:
	VOID    _dirty              (INT x, INT y, INT w, INT h, INT ind) ;
	BOOL    _size               (INT size) ;

private:
	INT*                        m_pRectArray ;
	INT                         m_nRectArrayLen ;
	INT                         m_nDirties ;
} ;