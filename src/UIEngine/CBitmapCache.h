#pragma once
#include <map>

struct BitmapObject
{
	DWORD       _dwUseage ;
	HBITMAP     _bitmap ;
	SIZE        _szBitmap ;
	BOOL        _bAlphaChannel ;

} ;

class CBitmapCache
{
public:
	BOOL AddBitmap  (CString cstrKey, HBITMAP hBitmap, SIZE szBitmap, BOOL bAlphaChannel) ;
	BOOL GetBitmap  (CString cstrKey, HBITMAP* phBitmap, SIZE* pszBitmap, BOOL* pbAlphaChannel) ;
	BOOL DelBitmap  (CString cstrKey) ;

public:
	static CBitmapCache& GetInstance()
	{
		static CBitmapCache _bitmap_instance ;
		return _bitmap_instance ;
	}

	typedef std::map<CString, BitmapObject> MAP_BITMAP_POOL ;
	MAP_BITMAP_POOL                         m_mapBitmapPool ;
} ;