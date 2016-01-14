#include "stdafx.h"
#include "CCUIList.h"

CCUIList::CCUIList()
{

}

CCUIList::~CCUIList()
{

}

HRESULT CCUIList::FinalConstruct()
{
	Common::Util::CreateObject(&m_pScrollView) ;
	DEBUG_ASSERT(m_pScrollView) ;
	return S_OK ;
}

HRESULT CCUIList::SetVScroll(IUIScroll* pScroll)
{
	return S_OK ;
}

HRESULT CCUIList::GetVScroll(IUIScroll** ppScroll)
{
	return S_OK ;
}

HRESULT CCUIList::SetItemFixHeight(BOOL bFixHeight)
{
	return S_OK ;
}

HRESULT CCUIList::GetItemFixHeight(BOOL* pbFixHeight)
{
	return S_OK ;
}

HRESULT CCUIList::SetItemHeight(INT nHeight)
{
	return S_OK ;
}

HRESULT CCUIList::GetItemHeight(INT* pnHeight)
{
	return S_OK ;
}

HRESULT CCUIList::AddItem(IUIListItem* pListItem)
{
	return S_OK ;
}

HRESULT CCUIList::InsertItem(IUIListItem* pListItem)
{
	return S_OK ;
}

HRESULT CCUIList::DelItem(INT nIndex)
{
	return S_OK ;
}

HRESULT CCUIList::GetItemCount(INT* pCount)
{
	return S_OK ;
}

HRESULT CCUIList::GetItemByIndex(INT nIndex, IUIListItem** ppListItem)
{
	return S_OK ;
}

INT CCUIList::_calc_content_height()
{
	if (this->m_bFixHeight)
	{
		return (INT)this->m_vecItems.size() * this->m_nFixHeight ;
	}
	else
	{
		CSize _szFrame(0, 0) ;
		__self->GetSize(&_szFrame) ;
		CRect _rcPadding(0, 0, 0, 0) ;
		__self->GetPadding(&_rcPadding) ;
		CSize _szScroll(0, 0) ;
		if (this->m_pScrollView)
		{
			this->m_pScrollView->GetSize(&_szScroll) ;
		}

		INT _height = 0 ;
		INT _width = _szFrame.cx - _rcPadding.left - _rcPadding.right - _szScroll.cx ;

		for (size_t i = 0; i < this->m_vecItems.size(); ++i)
		{
			CComQIPtr<IUIFrameInternal> pFrameInternal = this->m_vecItems[i] ;
			IF_CONTINUE(NULL == pFrameInternal) ;

			pFrameInternal->SetEstimateSize(CSize(_width, -1)) ;
			CSize _szItem(0, 0) ;
			this->m_vecItems[i]->GetSize(&_szItem) ;
			_height += _szItem.cy ;
		}
		return _height ;
	}
	return 0 ;
}