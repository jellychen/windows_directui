#include "stdafx.h"
#include "CSPackage.h"

CSPackage::CSPackage()
{
}

CSPackage::~CSPackage()
{
}

HRESULT CSPackage::OnInit()
{
	Common::Util::GetService(&m_pFilerouteService) ;
	DEBUG_ASSERT(m_pFilerouteService) ;
	return S_OK ;
}

HRESULT CSPackage::OnUnInit()
{
	return S_OK ;
}

HRESULT CSPackage::AddPackage(BSTR bstrSymbol, BSTR bstrPackage)
{
	IF_RETURN(!(this->m_pFilerouteService), E_FAIL) ;
	this->m_pFilerouteService->AddPackageSymbol(bstrSymbol) ;

	MAP_PACKAGE_POOL::iterator it = this->m_mapPackagePool.find(CString(bstrSymbol)) ;
	IF_RETURN(this->m_mapPackagePool.end() != it, E_FAIL) ;

	CString cstrSymbol(bstrSymbol) ;
	cstrSymbol.MakeLower() ;
	this->m_mapPackagePool[cstrSymbol]._file_pack = CString(bstrPackage) ;

	HANDLE  hFile = ::CreateFile(CString(bstrPackage),
		GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL) ;
	DEBUG_ASSERT(INVALID_HANDLE_VALUE != hFile) ;
	DEBUG_ASSERT_MSG(INVALID_HANDLE_VALUE != hFile, _T("Load File %s Failed!"), CString(bstrPackage)) ;
	IF_RETURN(INVALID_HANDLE_VALUE == hFile, E_FAIL) ;

	DWORD dwFileSize = ::GetFileSize(hFile, NULL) ;
	if (dwFileSize < MIN_PACKAGE_FILE_SIZE)
	{
		::CloseHandle(hFile) ;
		return E_FAIL ;
	}

	DWORD dwFileReadSize = 0 ;
	LPBYTE  pFileBuffer = new (std::nothrow) BYTE[PACKAGE_FILE_HEAD] ;
	DEBUG_ASSERT(NULL != pFileBuffer) ;
	if (NULL == pFileBuffer)
	{
		::CloseHandle(hFile) ;
		return E_FAIL ;
	}

	::ReadFile(hFile, pFileBuffer, PACKAGE_FILE_HEAD, &dwFileReadSize, NULL) ;
	::CloseHandle(hFile) ;
	if (dwFileReadSize != PACKAGE_FILE_HEAD)
	{
		DEBUG_ASSERT_MSG(FALSE, _T("dwFileReadSize != dwFileSize")) ;
		delete[] pFileBuffer ;
		return E_FAIL ;
	}

	do 
	{
		LPBYTE pFilePointer = pFileBuffer ;
		if (!(('U' == pFilePointer[0] || 'u' == pFilePointer[0])
			&& ('B' == pFilePointer[1] || 'b' == pFilePointer[1])
			&& ('D' == pFilePointer[2] || 'd' == pFilePointer[2])))
		{
			DEBUG_ASSERT_MSG(FALSE, _T("UBD sign not success!")) ;
			break ;
		}

		this->m_mapPackagePool[cstrSymbol]._file_info.clear() ;
		this->m_mapPackagePool[cstrSymbol]._file_list_load.clear() ;

		pFilePointer += PACKAGE_FILE_SIGN ;
		UINT32 un32Version = *((UINT32*)(pFilePointer)) ;

		pFilePointer += PACKAGE_FILE_VERSION ;
		UINT32* pFileUInt32Pointer = (UINT32*)(pFilePointer) ;

		for (UINT i = 0; i < PACKAGE_FILE_HASH_SIZE; ++i)
		{
			this->m_mapPackagePool[cstrSymbol]._file_info.push_back(*(pFileUInt32Pointer + i)) ;
			this->m_mapPackagePool[cstrSymbol]._file_list_load.push_back(FALSE) ;
		}

	} while (FALSE) ;

	return S_OK ;
}

HRESULT CSPackage::DelPackage(BSTR bstrName)
{
	MAP_PACKAGE_POOL::iterator it = this->m_mapPackagePool.find(CString(bstrName)) ;
	if (this->m_mapPackagePool.end() != it)
	{
		this->m_mapPackagePool.erase(it) ;
	}
	return S_OK ;
}

HRESULT CSPackage::FileExists(BSTR bstrFile, BOOL* pbExists)
{
	DEBUG_ASSERT(pbExists) ;
	IF_RETURN(NULL == pbExists, E_INVALIDARG) ;
	*pbExists = FALSE ;

	CString cstrFile(bstrFile) ;
	cstrFile.MakeLower() ;
	INT intLeftPos = cstrFile.Find(_T(':')) ;
	IF_RETURN(-1 == intLeftPos, S_OK) ;

	CString strPackage ;
	CString strSybmol = cstrFile.Left(intLeftPos) ;


	MAP_PACKAGE_POOL::iterator it = this->m_mapPackagePool.find(strSybmol) ;
	IF_RETURN(this->m_mapPackagePool.end() == it, S_OK) ;

	CString cstrFileKey = cstrFile.Right(cstrFile.GetLength() - intLeftPos - 1) ;
	cstrFileKey.Replace(_T("/"), _T("|")) ;
	cstrFileKey.Replace(_T("\\"), _T("|")) ;

	UINT32 un32HashData = (UINT32)this->_string_hash(cstrFileKey) % PACKAGE_FILE_HASH_SIZE ;
	IF_RETURN(it->second._file_info.size() <= un32HashData, S_OK) ;

	if (FALSE == it->second._file_list_load[un32HashData])
	{
		UINT32 un32FileOffset = it->second._file_info[un32HashData] ;
		this->_load_file_list(strSybmol, it->second._file_pack, un32FileOffset) ;
	}

	MAP_FILE_TABLE_INFO::iterator it_file = it->second._file_list_info.find(cstrFileKey) ;
	if (it->second._file_list_info.end() == it_file)
	{
		*pbExists = FALSE ;
	}
	else
	{
		*pbExists = TRUE ;
	}

	return S_OK ;
}

HRESULT CSPackage::ReadWholeFile(BSTR bstrFile, ICVarBuffer* pComBuffer)
{
	DEBUG_ASSERT(pComBuffer) ;
	IF_RETURN(NULL == pComBuffer, E_INVALIDARG) ;

	CString cstrFile(bstrFile) ;
	cstrFile.MakeLower() ;
	INT intLeftPos = cstrFile.Find(_T(':')) ;
	IF_RETURN(-1 == intLeftPos, E_FAIL) ;

	CString strSybmol = cstrFile.Left(intLeftPos) ;
	MAP_PACKAGE_POOL::iterator it = this->m_mapPackagePool.find(strSybmol) ;
	IF_RETURN(this->m_mapPackagePool.end() == it, E_FAIL) ;

	CString cstrFileKey = cstrFile.Right(cstrFile.GetLength() - intLeftPos - 1) ;
	cstrFileKey.Replace(_T("/"), _T("|")) ;
	cstrFileKey.Replace(_T("\\"), _T("|")) ;

	UINT32 un32HashData = (UINT32)this->_string_hash(cstrFileKey) % PACKAGE_FILE_HASH_SIZE ;
	IF_RETURN(it->second._file_info.size() <= un32HashData, E_FAIL) ;

	if (FALSE == it->second._file_list_load[un32HashData])
	{
		UINT32 un32FileOffset = it->second._file_info[un32HashData] ;
		this->_load_file_list(strSybmol, it->second._file_pack, un32FileOffset) ;
	}

	MAP_FILE_TABLE_INFO::iterator it_file = it->second._file_list_info.find(cstrFileKey) ;
	IF_RETURN(it->second._file_list_info.end() == it_file, E_FAIL) ;

	HANDLE hFile = ::CreateFile(it->second._file_pack,
		GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL) ;
	DEBUG_ASSERT(INVALID_HANDLE_VALUE != hFile) ;
	DEBUG_ASSERT_MSG(INVALID_HANDLE_VALUE != hFile, _T("Load File %s Failed!"), it->second._file_pack) ;
	IF_RETURN(INVALID_HANDLE_VALUE == hFile, E_FAIL) ;

	DWORD dwRet = ::SetFilePointer(hFile, it_file->second._un32_start_address, NULL, FILE_CURRENT) ;
	IF_RETURN(HFILE_ERROR == dwRet, E_FAIL) ;

	LPBYTE pFileBuffer = new(std::nothrow) BYTE [it_file->second._un32_file_length] ;
	DWORD dwFileReadSize = 0 ;
	::ReadFile(hFile, pFileBuffer, it_file->second._un32_file_length, &dwFileReadSize, NULL) ;

	if (it_file->second._un32_file_length != dwFileReadSize)
	{
		::CloseHandle(hFile) ;
		delete[] pFileBuffer ;
		return E_FAIL ;
	}

	HRESULT hRet = pComBuffer->SetBuffer(pFileBuffer, dwFileReadSize) ;

	delete[] pFileBuffer ;
	::CloseHandle(hFile) ;
	return hRet ;
}

size_t CSPackage::_string_hash(CString cstrKey)
{
	register size_t _hash = 0 ;
	for (INT i = 0 ; i < cstrKey.GetLength(); ++i)
	{
		_hash = _hash * 131 + (size_t)(cstrKey[i]) ;
	}
	return _hash ;
}

BOOL CSPackage::_load_file_list(CString cstrSymbol, CString cstrFile, UINT32 un32Offset)
{
	IF_RETURN(0 == un32Offset, FALSE) ;
	HANDLE hFile = ::CreateFile(CString(cstrFile),
		GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL) ;
	DEBUG_ASSERT(INVALID_HANDLE_VALUE != hFile) ;
	DEBUG_ASSERT_MSG(INVALID_HANDLE_VALUE != hFile, _T("Load File %s Failed!"), cstrFile) ;
	IF_RETURN(INVALID_HANDLE_VALUE == hFile, FALSE) ;

	DWORD dwRet = ::SetFilePointer(hFile, un32Offset, NULL, FILE_CURRENT) ;
	IF_RETURN(HFILE_ERROR == dwRet, FALSE) ;

	LPBYTE  pFileInfoListSize = NULL ;
	pFileInfoListSize = new (std::nothrow) BYTE[PACKAGE_FILE_LIST_SIZE] ;
	DEBUG_ASSERT(NULL != pFileInfoListSize) ;
	if (NULL == pFileInfoListSize)
	{
		::CloseHandle(hFile) ;
	}

	DWORD dwFileReadSize = 0 ;
	::ReadFile(hFile, pFileInfoListSize, PACKAGE_FILE_LIST_SIZE, &dwFileReadSize, NULL) ;

	if (PACKAGE_FILE_LIST_SIZE != dwFileReadSize)
	{
		::CloseHandle(hFile) ;
		delete[] pFileInfoListSize ;
		return FALSE ;
	}

	DWORD dwFileListSize       = *((UINT32*)(pFileInfoListSize)) ;
	DWORD dwFileListBufferSize = dwFileListSize * (sizeof(FILE_INFO_PAKAGE)) ;
	delete[] pFileInfoListSize ;

	LPBYTE pFileListBuffer = new (std::nothrow)BYTE[dwFileListBufferSize] ;
	DEBUG_ASSERT(NULL != pFileListBuffer) ;
	if (NULL == pFileListBuffer)
	{
		::CloseHandle(hFile) ;
		delete[] pFileListBuffer ;
		return FALSE ;
	}

	dwFileReadSize = 0 ;
	::ReadFile(hFile, pFileListBuffer, dwFileListBufferSize, &dwFileReadSize, NULL) ;
	if (dwFileReadSize != dwFileListBufferSize)
	{
		::CloseHandle(hFile) ;
		delete[] pFileListBuffer ;
		return FALSE ;
	}

	// Ë³Ðò½âÎöFileList
	FILE_INFO_PAKAGE* pFileInfoPointer = (FILE_INFO_PAKAGE*)pFileListBuffer ;
	for (DWORD i = 0; i < dwFileListSize; ++i)
	{
		CString _str_file_name ;
		for (INT j = 0; j < PACKAGE_FILE_NAME_SIZE; ++j)
		{
			TCHAR tcChar = pFileInfoPointer->_str_file_name[j] ;
			IF_BREAK(0 == tcChar) ;
			_str_file_name += tcChar ;
		}

		FILE_INFO _info ;
		_info._un32_start_address   = pFileInfoPointer->_un32_start_address ;
		_info._un32_file_length     = pFileInfoPointer->_un32_file_length ;
		this->m_mapPackagePool[cstrSymbol]._file_list_info[_str_file_name] = _info ;

		pFileInfoPointer++ ;
	}

	::CloseHandle(hFile) ;
	return TRUE ;
}