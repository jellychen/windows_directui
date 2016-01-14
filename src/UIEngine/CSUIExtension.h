#pragma once
#include "Include/Def/Require.h"
#include "Include/Common/ISService.h"
#include "Include/UIEngine/IUIExtension.h"
#include <map>

[
	default(IUIExtensionCenter) ,
	threading(free) ,
	uuid("E50AE8D8-3BEB-4e6a-8E47-1DB0FE7DB9B4") ,
	coclass
]
class ATL_NO_VTABLE CSUIExtensionCenter
	: public TCustomServiceImpl<IUIExtensionCenter>
{
public:
	DECLARE_PROTECT_FINAL_CONSTRUCT() ;
	CSUIExtensionCenter() ;
	virtual ~CSUIExtensionCenter() ;

public:
	HRESULT _call CallExtension				(REFIID iid, IUIFrame* pFrame, ICVarData* pArg) ;
	HRESULT _call AddExtensionListener		(REFIID iid, IUIExtensionCallback* pCallback) ;
	HRESULT _call DelExtensionListener		(REFIID iid, IUIExtensionCallback* pCallback) ;
	HRESULT _call AddGlobalExtensionListener(IUIExtensionCallback* pCallback) ;
	HRESULT _call DelGlobalExtensionListener(IUIExtensionCallback* pCallback) ;

private:
	typedef std::map<LONG, CComPtr<IUIExtensionCallback>>	MAP_CALLBACK ;
	typedef std::map<IID, MAP_CALLBACK>						MAP_EXTENSION ;
	MAP_CALLBACK											m_mapGlobalExtension ;
	MAP_EXTENSION											m_mapExtension ;
} ;
