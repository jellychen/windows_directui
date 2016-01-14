#pragma once

typedef struct _CGID
{
	GUID _guid_a, _guid_b ;
} CGID, *PCGID ;

bool operator < (const GUID& left, const GUID& right) ;
bool operator < (const CGID& left, const CGID& right) ;