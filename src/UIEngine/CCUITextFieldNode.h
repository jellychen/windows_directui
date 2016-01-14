#pragma once
#include <vector>

struct _TextNode
{
	CSize	m_szChar ;
	TCHAR	m_tcChar ;
} ;

struct _TextVerticalInfo
{
	INT		m_nLeftIndex ;
	INT		m_nRightIndex ;
	INT		m_nMaxHeight ;
	INT		m_nLineHeight ;
} ;

typedef std::vector<_TextNode>			VEC_CHAR ;
typedef std::vector<_TextVerticalInfo>	VEC_VERTICAL ;