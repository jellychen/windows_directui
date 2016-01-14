#include "stdafx.h"
#include "CCUISplit.h"

CCUISplit::CCUISplit()
{
	this->m_nDirties = 0 ;
	this->m_nRectArrayLen = 40 ;
	this->m_pRectArray = new INT[40] ;
}

CCUISplit::~CCUISplit()
{
	if (this->m_pRectArray)
	{
		delete this->m_pRectArray ;
	}
}

HRESULT CCUISplit::AddRect(RECT rcRect)
{
	DEBUG_ASSERT(this->m_pRectArray) ;
	IF_RETURN(NULL == this->m_pRectArray, E_FAIL) ;

	this->_dirty(rcRect.left, rcRect.top, rcRect.right, rcRect.bottom, 0) ;
	return S_OK ;
}

HRESULT CCUISplit::Split(ICVarArray* pRectArray)
{
	DEBUG_ASSERT(pRectArray) ;
	IF_RETURN(NULL == pRectArray, E_INVALIDARG) ;

	for (INT i = 0; i < this->m_nDirties; ++i)
	{
		INT nIndex = i * 4 ;
		CRect       _rc ;
		_rc.left    = this->m_pRectArray[nIndex] ;
		_rc.top     = this->m_pRectArray[nIndex + 1] ;
		_rc.right   = this->m_pRectArray[nIndex + 2] ;
		_rc.bottom  = this->m_pRectArray[nIndex + 3] ;
		pRectArray->AddRect(_rc) ;
	}
	return S_OK ;
}

HRESULT CCUISplit::Split2(IUIAddRect* pAddRect)
{
	DEBUG_ASSERT(pAddRect) ;
	IF_RETURN(NULL == pAddRect, E_INVALIDARG) ;

	pAddRect->AddRectBegin() ;
	for (INT i = 0; i < this->m_nDirties; ++i)
	{
		INT nIndex = i * 4 ;
		CRect       _rc ;
		_rc.left    = this->m_pRectArray[nIndex] ;
		_rc.top     = this->m_pRectArray[nIndex + 1] ;
		_rc.right   = this->m_pRectArray[nIndex + 2] ;
		_rc.bottom  = this->m_pRectArray[nIndex + 3] ;
		pAddRect->AddRect(_rc) ;
	}
	pAddRect->AddRectEnd() ;
	return S_OK ;
}

HRESULT CCUISplit::GetCount(INT* pnCount)
{
	DEBUG_ASSERT(pnCount) ;
	IF_RETURN(NULL == pnCount, E_INVALIDARG) ;
	*pnCount = this->m_nDirties ;
	return S_OK ;
}

HRESULT CCUISplit::GetByIndex(INT nIndex, RECT* prcRect)
{
	DEBUG_ASSERT(prcRect) ;
	IF_RETURN(NULL == prcRect, E_INVALIDARG) ;
	DEBUG_ASSERT(nIndex < this->m_nDirties) ;
	IF_RETURN(nIndex >= this->m_nDirties, E_INVALIDARG) ;

	INT _nIndex = nIndex * 4 ;
	prcRect->left   = this->m_pRectArray[_nIndex] ;
	prcRect->top    = this->m_pRectArray[_nIndex + 1] ;
	prcRect->right  = this->m_pRectArray[_nIndex + 2] ;
	prcRect->bottom = this->m_pRectArray[_nIndex + 3] ;
	return S_OK ;
}

HRESULT CCUISplit::Clear()
{
	this->m_nDirties = 0 ;
	if (NULL != this->m_pRectArray)
	{
		delete this->m_pRectArray ;
	}
	this->m_nRectArrayLen = 40 ;
	this->m_pRectArray = new INT[40] ;
	return S_OK ;
}

VOID CCUISplit::_dirty(INT x, INT y, INT w, INT h, INT ind)
{
	INT _n = 0 ;
	IF_RETURN_VOID(w <= x || h <= y) ;

	for (INT i = ind; i < this->m_nDirties; ++i)
	{
		_n = 4 * i ;
		IF_CONTINUE(this->m_pRectArray[_n] == INT_MIN) ;

		INT _x  = this->m_pRectArray[_n] ;
		INT _y  = this->m_pRectArray[_n + 1] ;
		INT _w  = this->m_pRectArray[_n + 2] ;
		INT _h  = this->m_pRectArray[_n + 3] ;
		IF_CONTINUE(x >= _w || y >= _h || w <= _x || h <= _y) ;

		if (x < _x)
		{
			if (y < _y)
			{
				if (w > _w)
				{
					if (h > _h)
					{
						this->m_pRectArray[_n] = INT_MIN ;
						continue ;
					}
					this->m_pRectArray[_n + 1] = h ;
					continue ;
				}
				else
				{
					if (h > _h)
					{
						this->m_pRectArray[_n] = w ;
						continue ;
					}

					this->_dirty(x, y, w, _y, i + 1) ;
					this->_dirty(x, _y, _x, h, i + 1) ;
					return ;
				}
			}
			else 
			{
				if (w > _w)
				{
					if (h > _h)
					{
						this->m_pRectArray[_n + 3] = y ;
						continue ;
					}
					this->_dirty(x, y, _x, h, i + 1) ;
					this->_dirty(_w, y, w, h, i + 1) ;
					return ;
				}
				else
				{
					if (h > _h)
					{
						this->_dirty(x, y, _x, h, i + 1) ;
						this->_dirty(_x, _h, w, h, i + 1) ;
						return ;
					}
					w = _x ;
					continue ;
				}
			}
		}
		else
		{
			if (y < _y)
			{
				if (w > _w)
				{
					if (h > _h)
					{
						this->m_pRectArray[_n + 2] = x ;
						continue ;
					}
					this->_dirty(x, y, w, _y, i + 1) ;
					this->_dirty(_w, _y, w, h, i + 1) ;
					return ;
				}
				else
				{
					if (h > _h)
					{
						this->_dirty(x, y, w, _y, i + 1) ;
						this->_dirty(x, _h, w, h, i + 1) ;
						return ;
					}
					h = _y ;
					continue ;
				}
			}
			else
			{
				if (w > _w)
				{
					if (h > _h)
					{
						this->_dirty(x, _h, w, h, i + 1) ;
						this->_dirty(_w, y, w, _h, i + 1) ;
						return ;
					}
					x = _w ;
					continue ;
				}
				else
				{
					if (h > _h)
					{
						y = _h ;
						continue ;
					}
					return ;
				}
			}
		}
	}

	_n = this->m_nDirties * 4 ;
	this->_size(_n) ;
	this->m_pRectArray[_n]  = x ;
	this->m_pRectArray[_n + 1] = y ;
	this->m_pRectArray[_n + 2] = w ;
	this->m_pRectArray[_n + 3] = h ;
	this->m_nDirties++ ;
}

BOOL CCUISplit::_size(INT size)
{
	if (size >= this->m_nRectArrayLen)
	{
		INT* pTemp = new (std::nothrow) INT[this->m_nRectArrayLen * 2] ;
		DEBUG_ASSERT(pTemp) ;
		IF_RETURN(NULL == pTemp, FALSE) ;
		memcpy((void*)pTemp, (void*)this->m_pRectArray, this->m_nRectArrayLen*sizeof(INT)) ;
		this->m_nRectArrayLen = this->m_nRectArrayLen * 2 ;
		DEBUG_ASSERT(this->m_pRectArray) ;
		delete this->m_pRectArray ;
		this->m_pRectArray = pTemp ;
	}
	return TRUE ;
}