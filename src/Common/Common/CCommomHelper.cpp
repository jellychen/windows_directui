
#include "stdafx.h"
#include "CCommomHelper.h"

bool operator < (const GUID& left, const GUID& right)
{
	if (left.Data1 < right.Data1) return true ;
	else if (left.Data1 > right.Data1) return false ;
	if (left.Data2 < right.Data2) return true ;
	else if (left.Data2 > right.Data2) return false ;
	if (left.Data3 < right.Data3) return true ;
	else if (left.Data3 > right.Data3) return false ;

	for (UINT i = 0; i < 8; ++i)
	{
		if (left.Data4[i] < right.Data4[i]) return true ;
		else if (left.Data4[i] > right.Data4[i]) return false ;
	}

	return false ;
}

bool operator < (const CGID& left, const CGID& right)
{
	if (IsEqualGUID(left._guid_a, right._guid_a)
		&& IsEqualGUID(left._guid_b, right._guid_b))
	{
		return false ;
	}

	if (left._guid_a < right._guid_a) return true ;
	else return false ;

	if (left._guid_b < right._guid_b) return true ;
	else return false ;

	return false ;
}