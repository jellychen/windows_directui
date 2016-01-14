#pragma once

class CCVarDataKeyString
{
public:
	CCVarDataKeyString(const TCHAR* str)
	{
		this->m_cstrData = str ;
	}

	CCVarDataKeyString(CString str)
	{
		this->m_cstrData = str ;
	}

	bool operator< (const CCVarDataKeyString& rhs) const
	{
		return this->m_cstrData < rhs.m_cstrData ;
	}

	size_t GetStrHash() const
	{
		size_t hash_data = 5381 ;
		for (int i = 0 ; i < this->m_cstrData.GetLength(); ++i)
		{
			hash_data = ((hash_data << 5) + hash_data) + (size_t)m_cstrData.GetAt(i) ;
		}
		return hash_data ;
	}

public:
	CString     m_cstrData ;
} ;


class CCVarDataKeyStringHash
{
public:
	enum
	{
		min_buckets = 50 ,
		bucket_size = 2 ,
	} ;

	size_t operator()(const CCVarDataKeyString& litstr) const
	{
		return litstr.GetStrHash() ;
	}

	bool operator()(const CCVarDataKeyString& left, const CCVarDataKeyString& right) const
	{
		return left < right ;
	}
} ;