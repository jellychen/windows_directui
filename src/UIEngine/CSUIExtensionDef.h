#pragma once

bool operator < (const _GUID& left, const _GUID& right)
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