#include "stdafx.h"
#include "CBitmapCache.h"

BOOL CBitmapCache::AddBitmap(CString cstrKey, HBITMAP hBitmap, SIZE szBitmap, BOOL bAlphaChannel)
{
	MAP_BITMAP_POOL::iterator it = this->m_mapBitmapPool.find(cstrKey) ;
	if (this->m_mapBitmapPool.end() != it)
	{
		DEBUG_ASSERT_MSG(FALSE, _T("Error !!!  BitmapCache Error!! Add Error!!"))
			return FALSE ;
	}

	BitmapObject _object ;
	_object._dwUseage = 1 ;
	_object._bitmap = hBitmap ;
	_object._szBitmap = szBitmap ;
	_object._bAlphaChannel = bAlphaChannel ;

	this->m_mapBitmapPool[cstrKey] = _object ;
	return TRUE ;
}

BOOL CBitmapCache::GetBitmap(CString cstrKey, HBITMAP* phBitmap, SIZE* pszBitmap, BOOL* pbAlphaChannel)
{
	MAP_BITMAP_POOL::iterator it = this->m_mapBitmapPool.find(cstrKey) ;
	if (this->m_mapBitmapPool.end() != it)
	{
		it->second._dwUseage++ ;
		*phBitmap       = it->second._bitmap ;
		*pszBitmap      = it->second._szBitmap ;
		*pbAlphaChannel = it->second._bAlphaChannel ;
		return TRUE ;
	}

	*phBitmap = NULL ;
	return FALSE ;
}

BOOL CBitmapCache::DelBitmap(CString cstrKey)
{
	IF_RETURN(cstrKey.IsEmpty(), TRUE) ;
	MAP_BITMAP_POOL::iterator it = this->m_mapBitmapPool.find(cstrKey) ;
	if (this->m_mapBitmapPool.end() != it)
	{
		it->second._dwUseage-- ;
		if (0 == it->second._dwUseage)
		{
			::DeleteObject(it->second._bitmap) ;
			this->m_mapBitmapPool.erase(it) ;
		}

		return TRUE ;
	}

	DEBUG_ASSERT_MSG(FALSE, _T("Error !!!  BitmapCache Error!! DEL Error!!"))
	return FALSE ;
}