#pragma once
#include "Include/UIEngine/IUIQuad.h"
#include "CCUIQuadDef.h"
#include <vector>
#include <map>

[
	default(IUIQuad) ,
	threading(free) ,
	uuid("2B4C05AC-7695-475b-9DA8-30164B71ECB7") ,
	coclass
]
class ATL_NO_VTABLE CCUIQuad
	: public IDispatchImpl<IUIQuad>
{
public:
	DECLARE_PROTECT_FINAL_CONSTRUCT() ;
	CCUIQuad() ;
	virtual ~CCUIQuad() ;
	HRESULT FinalConstruct() ;

public:
	HRESULT _call SynchFrame        (RECT rcFrame, IUIFrame* pFrame) ;
	HRESULT _call GetFrameRect      (IUIFrame* pFrame, RECT* prcRect) ;
	HRESULT _call FrameFromPoint    (POINT ptTarget, ICVarArray* pFrameArray) ;
	HRESULT _call FrameFromPoint2   (POINT ptTarget, IUIAddFrame* pAddFrame) ;
	HRESULT _call FrameFromRect     (RECT rcTarget, ICVarArray* pFrameArray) ;
	HRESULT _call FrameFromRect2    (RECT rcTarget, IUIAddFrame* pAddFrame) ;
	HRESULT _call EraseFrame        (IUIFrame* pFrame) ;
	HRESULT _call Clear             () ;

private:
	QUAD_NODE*  _build_quad_tree    (INT nDepth, CRect rcArea) ;
	BOOL        _free_quad_tree     (QUAD_NODE* pQuadNode) ;
	BOOL        _clear_quad_tree    (QUAD_NODE* pQuadNode) ;
	BOOL        _synch_frame        (QUAD_NODE* pQuadNode, CRect& rcFrame, IUIFrame* pFrame) ;
	BOOL        _find_frame_point   (QUAD_NODE* pQuadNode, POINT& ptTarget, ICVarArray* pFrameArray) ;
	BOOL        _find_frame_point2  (QUAD_NODE* pQuadNode, POINT& ptTarget, IUIAddFrame* pAddFrame) ;
	BOOL        _find_frame_rect    (QUAD_NODE* pQuadNode, CRect& rcFrame, ICVarArray* pFrameArray) ;
	BOOL        _find_frame_rect2   (QUAD_NODE* pQuadNode, CRect& rcFrame, IUIAddFrame* pAddFrame) ;

private:
	typedef std::map<LONG, QUAD_NODE*>  MAP_FRAME_POOL ;
	typedef std::map<LONG, CRect>       MAP_FRAME_RECR_POOL ;

private:
	QUAD_NODE*                      m_pQuadRoot ;
	MAP_FRAME_POOL                  m_mapFramePool ;
	MAP_FRAME_RECR_POOL             m_mapFrameRectPool ;
} ;