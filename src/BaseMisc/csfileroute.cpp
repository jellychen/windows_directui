#include "stdafx.h"
#include "CSFileroute.h"

CSFileroute::CSFileroute()
{
	TCHAR tcCurrentRoute[MAX_PATH + 1] = {0} ;
	::GetModuleFileName(NULL, tcCurrentRoute, MAX_PATH) ;
	_tcsrchr(tcCurrentRoute, _T('\\'))[0] = _T('\0') ;
	this->m_cstrCurrentRoute = tcCurrentRoute ;
}

CSFileroute::~CSFileroute()
{
}

HRESULT CSFileroute::OnInit()
{
	Common::Util::GetService(&m_pPackageService) ;
	DEBUG_ASSERT(m_pPackageService) ;
	return S_OK ;
}

HRESULT CSFileroute::OnUnInit()
{
	return S_OK ;
}

HRESULT CSFileroute::AddSymbol(BSTR bstrSymbol, BSTR bstrRoute)
{
	CString cstrSymbol(bstrSymbol) ;
	cstrSymbol.MakeLower() ;
	this->m_mapSymbolPool[cstrSymbol] = bstrRoute ;
	return S_OK ;
}

HRESULT CSFileroute::DelSymbol(BSTR bstrSymbol)
{
	CString cstrSymbol(bstrSymbol) ;
	cstrSymbol.MakeLower() ;
	MAP_SYMBOL_POOL::iterator it = this->m_mapSymbolPool.find(cstrSymbol) ;
	if (this->m_mapSymbolPool.end() != it)
	{
		this->m_mapSymbolPool.erase(it) ;
	}
	return S_OK ;
}

HRESULT CSFileroute::GetSymbol(BSTR bstrSymbol, BSTR* pbstrRoute)
{
	IF_RETURN(NULL == pbstrRoute, E_INVALIDARG) ;
	*pbstrRoute = NULL ;
	CString cstrSymbol(bstrSymbol) ;
	cstrSymbol.MakeLower() ;
	MAP_SYMBOL_POOL::iterator it = this->m_mapSymbolPool.find(cstrSymbol) ;
	if (this->m_mapSymbolPool.end() != it)
	{
		CComBSTR bstrRoute(it->second) ;
		bstrRoute.CopyTo(pbstrRoute) ;
		return S_OK ;
	}
	return E_FAIL ;
}

HRESULT CSFileroute::Convert(BSTR bstrRoute, BSTR* pbstrRoute)
{
	IF_RETURN(NULL == pbstrRoute, E_INVALIDARG) ;
	*pbstrRoute = NULL ;
	CString cstrRoute = bstrRoute ;
	INT intLeftPos = cstrRoute.Find(_T(':')) ;

	if (-1 == intLeftPos)
	{
		CComBSTR bstrRoute(cstrRoute) ;
		bstrRoute.CopyTo(pbstrRoute) ;
	}
	else
	{
		CString strSybmol = cstrRoute.Left(intLeftPos) ;
		strSybmol.MakeLower() ;

		MAP_SYMBOL_POOL::iterator it = this->m_mapSymbolPool.find(strSybmol) ;
		if (it == this->m_mapSymbolPool.end())
		{
			CComBSTR bstrRoute(cstrRoute) ;
			bstrRoute.CopyTo(pbstrRoute) ;
			return S_OK ;
		}

		CString strRightPath = cstrRoute.Right(cstrRoute.GetLength() - intLeftPos - 1) ;
		CString strFilePath = it->second + strRightPath ;
		CComBSTR bstrRoute(strFilePath) ;
		bstrRoute.CopyTo(pbstrRoute) ;
	}
	return S_OK ;
}

HRESULT CSFileroute::AddPackageSymbol(BSTR bstrSymbol)
{
	CString cstrSymbol(bstrSymbol) ;
	cstrSymbol.MakeLower() ;
	this->m_setSymbolPool.insert(cstrSymbol) ;
	return S_OK ;
}

HRESULT CSFileroute::DelPackageSymbol(BSTR bstrSymbol)
{
	CString cstrSymbol(bstrSymbol) ;
	cstrSymbol.MakeLower() ;
	SET_SYMBOL_PACKAGE::iterator it = this->m_setSymbolPool.find(cstrSymbol) ;
	if (this->m_setSymbolPool.end() != it)
	{
		this->m_setSymbolPool.erase(it) ;
	}
	return S_OK ;
}

HRESULT CSFileroute::FileExists(BSTR bstrFile, BOOL* pbExists)
{
	IF_RETURN(NULL == pbExists, E_INVALIDARG) ;
	*pbExists = FALSE ;

	CString strFileInSystem ;
	if (this->FileInSystem(CString(bstrFile), strFileInSystem))
	{
		WIN32_FIND_DATA wfd ;
		HANDLE hFileFind = ::FindFirstFile(LPCTSTR(strFileInSystem), &wfd) ;
		if (hFileFind != INVALID_HANDLE_VALUE)
		{
			*pbExists = TRUE ;
			::CloseHandle(hFileFind) ;
		}
		return S_OK ;
	}
	else if (this->m_pPackageService)
	{
		return this->m_pPackageService->FileExists(bstrFile, pbExists) ;
	}
	return E_FAIL ;
}

HRESULT CSFileroute::ReadWholeFile(BSTR bstrFile, ICVarBuffer* pComBuffer)
{
	DEBUG_ASSERT(pComBuffer) ;
	IF_RETURN(NULL == pComBuffer, E_INVALIDARG) ;

	CString strFileInSystem ;
	if (this->FileInSystem(CString(bstrFile), strFileInSystem))
	{
		HANDLE hFile = ::CreateFile(CString(strFileInSystem),
			GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL) ;
		DEBUG_ASSERT_MSG(INVALID_HANDLE_VALUE != hFile, _T("Load File %s Failed.."), CString(strFileInSystem)) ;
		IF_RETURN(INVALID_HANDLE_VALUE == hFile, E_FAIL) ;

		DWORD dwFileSize = ::GetFileSize(hFile, NULL) ;
		DEBUG_ASSERT_MSG(dwFileSize, _T("sizeof file %s == 0.."), CString(strFileInSystem)) ;
		if (0 == dwFileSize)
		{
			::CloseHandle(hFile) ;
			return E_FAIL ;
		}

		LPBYTE lpFileBuffer = new(std::nothrow)BYTE[dwFileSize] ;
		DEBUG_ASSERT_MSG(lpFileBuffer, _T("new memory failed..")) ;
		if (NULL == lpFileBuffer)
		{
			::CloseHandle(hFile) ;
			return E_FAIL ;
		}

		DWORD dwFileReadSize = 0 ;
		::ReadFile(hFile, lpFileBuffer, dwFileSize, &dwFileReadSize, NULL) ;
		::CloseHandle(hFile) ;
		if (dwFileReadSize != dwFileSize)
		{
			DEBUG_ASSERT_MSG(FALSE, _T("dwFileReadSize != dwFileSize")) ;
			delete[] lpFileBuffer ;
			return E_FAIL ;
		}

		pComBuffer->SetBuffer(lpFileBuffer, dwFileReadSize) ;
		delete[] lpFileBuffer ;
		return S_OK ;
	}
	else if (this->m_pPackageService)
	{
		return this->m_pPackageService->ReadWholeFile(bstrFile, pComBuffer) ;
	}
	return E_FAIL ;
}

BOOL CSFileroute::FileInSystem(CString& strFile, CString& strFileInSystem)
{
	INT intLeftPos = strFile.Find(_T(':')) ;
	if (-1 == intLeftPos)
	{
		strFileInSystem = strFile ;
	}
	else
	{
		CString strSybmol = strFile.Left(intLeftPos) ;
		strSybmol.MakeLower() ;

		SET_SYMBOL_PACKAGE::iterator it = this->m_setSymbolPool.find(strSybmol) ;
		if (this->m_setSymbolPool.end() != it)
		{
			return FALSE ;
		}

		MAP_SYMBOL_POOL::iterator iter = this->m_mapSymbolPool.find(strSybmol) ;
		if (iter != this->m_mapSymbolPool.end())
		{
			strFileInSystem = iter->second ;
			strFileInSystem += strFile.Right(strFile.GetLength() - intLeftPos - 1) ;
		}
		else
		{
			strFileInSystem = strFile ;
		}
		return TRUE ;
	}
	return TRUE ;
}