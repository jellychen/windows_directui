#pragma once
#include "Include/UIEngine/IUIDraw.h"

namespace TEXTURE
{
	namespace DRAW
	{
		enum
		{
			NORMAL          = 0X0000 ,
			STRETCH         = 0X0001 ,
			HOLE            = 0X0002 ,
			REPEAT          = 0X0004 ,
			XREPEAT         = 0X0008 ,
			YREPEAT         = 0X0010 ,
			GRID            = 0X0020 ,
		} ;
	}
}

[
	object ,
	uuid("674A3F15-17D1-4d06-B96D-0F11ED0E6670") ,
	pointer_default(unique)
]
__interface IUITexture : IUIDraw
{
	HRESULT LoadFromFile        (BSTR bstrFile) ;
	HRESULT LoadFromComBuffer   (ICVarBuffer* pVarBuffer) ;
	HRESULT LoadFromBuffer      (BYTE* pbBuffer, LONG lBufferLen) ;
	HRESULT SetDrawType         (DWORD dwType) ;
	HRESULT GetDrawType         (DWORD* pdwType) ;
	HRESULT SetDrawRect         (RECT rcDraw) ;
	HRESULT GetDrawRect         (RECT* prcDraw) ;
	HRESULT SetDrawGrid         (RECT rcGrid) ;
	HRESULT GetDrawGrid         (RECT* prcGrid) ;
	HRESULT FreeTexture         () ;
} ;