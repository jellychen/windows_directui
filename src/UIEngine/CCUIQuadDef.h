#pragma once
#include "Include/Def/Require.h"
#include "Include/UIEngine/IUIFrame.h"
#include <vector>

#define QUAD_DEPTH                  7
#define QUAD_MAX_SIZE               3000

namespace QUAD
{
	enum
	{
		LEFT_UP             = 0 ,
		RIGHT_UP            = 1 ,
		LEFT_BOTTOM         = 2 ,
		RIGHT_BOTTOM        = 3 ,
	} ;
}

struct QUAD_FRAME_INFO
{
	CRect                   rcFrameRect ;
	CWeakPtr<IUIFrame>		pFrameAgent ;
} ;

typedef std::vector<QUAD_FRAME_INFO> VEC_QUAD_FRAME_POOL ;

struct QUAD_NODE
{
	CRect                   rcQuadNodeRect ;
	VEC_QUAD_FRAME_POOL     vecFramePool ;
	BOOL                    bHaveChildren ;
	QUAD_NODE*              pQuadChildren[4] ;
} ;