#pragma once

#include "Include/UIEngine/IUIRender.h"
#include "Include/UIEngine/IUIFrameInternal.h"
#include <vector>
#include <set>
#include <stack>
#include <algorithm>

typedef std::set<LONG>                  SET_LONG ;

struct RENDER_INFO
{
	INT             _nZOrder ;
	INT             _nIndex ;
} ;

typedef std::vector<RENDER_INFO>        VEC_INFO ;

struct FRAME_RENDER_NODE
{
	VEC_INFO            _vec_info ;
	CComPtr<IUIFrame>   _pFrame ;
} ;

typedef std::vector<FRAME_RENDER_NODE>  VEC_FRAME ;


[
	default(IUIRender) ,
	threading(free) ,
	uuid("88F1455C-4752-4ee6-83B6-66BF6F9E0F5C") ,
	coclass
]
class ATL_NO_VTABLE CCUIRender 
	: public IDispatchImpl<IUIRender>
	, public IDispatchImpl<IUIAddFrame>
{
public:
	DECLARE_PROTECT_FINAL_CONSTRUCT() ;
	CCUIRender() ;
	virtual ~CCUIRender() ;

public:
	HRESULT _call Render        (IUICanvas* pCanvas) ;
	HRESULT _call Clear         () ;
	HRESULT _call AddFrameBegin () ;
	HRESULT _call AddFrame      (IUIFrame* pFrame) ;
	HRESULT _call AddFrameEnd   () ;

private:
	VEC_FRAME                   m_vecFramePool ;
	SET_LONG                    m_setFramePool ;
} ;