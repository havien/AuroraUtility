#pragma once
#include "StringManager.h"

using namespace Aurora;

StringManager::StringManager( void )
{

}

StringManager::~StringManager( void )
{

}

void StringManager::MakeString( OUT char* pOutString, char* szFormat, ... )
{
	//static LPCSTR szBuff[MAX_LONG_STRING_LEN] = { 0 };
	va_list args;

	va_start( args, szFormat );
	vsnprintf_s( (char*)pOutString, MAX_LONG_STRING_LEN, MAX_LONG_STRING_LEN, szFormat, args );
	va_end( args );

	//wprintf_s( (WCHAR* )&szBuff, LongStringLen );
	//return (char*)szBuff;
}

void StringManager::MakeString( OUT WCHAR* pOutString, WCHAR* szFormat, ... )
{
	//static LPCWSTR szBuff[MAX_LONG_STRING_LEN] = { 0 };
	va_list args;

	va_start( args, szFormat );
	_vsnwprintf_s( (WCHAR* )pOutString, MAX_LONG_STRING_LEN, MAX_LONG_STRING_LEN, szFormat, args );
	va_end( args );

	wprintf_s( (WCHAR* )&pOutString, MAX_LONG_STRING_LEN );
	//return (WCHAR* )szBuff;
}

void StringManager::WideToMultiByte( const WCHAR* pSrc, OUT char* pDest )
{
	if( pSrc/* && pDest */ )
	{
		// Convert the WCHAR string to a char* string. Record 
		//.the length of the original string and add 1 to it to
		//.account for the terminating null character.
		size_t origsize = wcslen( pSrc ) + 1;
		size_t convertedChars = 0;

		// Allocate two bytes in the multibyte output string for every wide
		// character in the input string (including a wide character
		// null). Because a multibyte character can be one or two bytes,
		// you should allot two bytes for each character. Having extra
		// space for the new string is not an error, but having
		// insufficient space is a potential security problem.
		const size_t newsize = (origsize * 2);

		// The new string will contain a converted copy of the original
		// string plus the type of string appended to it.
		//pDest = new char[newsize + strConcatsize];

		// Put a copy of the converted string into nstring
		wcstombs_s( &convertedChars, pDest, newsize, pSrc, _TRUNCATE );
	}
}

void StringManager::WideToString( const WCHAR* pSrc, OUT std::string &destString )
{
	//wide char array
	auto length = (wcslen( pSrc ) + 1);

	//convert from wide char to narrow char array
	char* pTempChar = new char[length];
	Clear( pTempChar, length );

	char DefChar = ' ';
	::WideCharToMultiByte( CP_ACP, 0, pSrc, -1, pTempChar, static_cast<Int32>(length), &DefChar, NULL );

	destString.assign( pTempChar );

	SAFE_DELETE_ARRAY_POINTER( pTempChar );
}
//
//template <typename T>
//void StringManager::Clear( T* pString, const size_t length )
//{
//	memset( static_cast<void *>(pString), 0, sizeof( T ) * length );
//}
//
//template <typename T>
//void StringManager::Clear( T* pString, const Int16 length )
//{
//	Clear( pString, static_cast<size_t>(length) );
//}
//
//template <typename T>
//void StringManager::Clear( T* pString, const UInt16 length )
//{
//	Clear( pString, static_cast<size_t>(length) );
//}

void StringManager::CalcLength( const char* pSrc, char* pDest, OUT size_t& calcLength )
{
	const auto srcLength = strlen( pSrc ) + 1;
	const auto destLength = strlen( pDest ) + 1;

	calcLength = destLength;
	if( srcLength > destLength )
	{
		calcLength = srcLength;
	}
}

void StringManager::CalcLength( const WCHAR* pSrc, WCHAR* pDest, OUT size_t& calcLength )
{
	const auto srcLength = wcslen( pSrc ) + 1;
	const auto destLength = wcslen( pDest ) + 1;

	calcLength = destLength;
	if( srcLength > destLength )
	{
		calcLength = srcLength;
	}
}

void StringManager::Copy( const char* pSrc, char* pDest, const size_t length )
{
	if( pSrc && pDest )
	{
		strcpy_s( pDest, length, pSrc );
	}
}

void StringManager::Copy( const WCHAR* pSrc, WCHAR* pDest, const size_t length )
{
	if( pSrc && pDest )
	{
		wcscpy_s( pDest, length, pSrc );
	}
}

void StringManager::ClearAndCopy( const char* pSrc, char* pDest, const size_t length )
{
	if( pDest && pSrc && (0 < length) )
	{
		Clear( pDest, length );
		Copy( pSrc, pDest, length );
	}
}

void StringManager::ClearAndCopy( const char* pSrc, char* pDest )
{
	if( pDest && pSrc )
	{
		size_t length = 0;
		CalcLength( pSrc, pDest, OUT length );
		
		Clear( pDest, length );
		Copy( pSrc, pDest, length );
	}
}

void StringManager::ClearAndCopy( const WCHAR* pSrc, WCHAR* pDest, const size_t length )
{
	if( pDest && pSrc && (0 < length) )
	{
		Clear( pDest, length );

		size_t calcLength = 0;
		CalcLength( pSrc, pDest, OUT calcLength );
		
		if( length == calcLength )
		{
			Copy( pSrc, pDest, length );
		}
		else
		{
			Copy( pSrc, pDest, calcLength );
		}
	}
}

void StringManager::ClearAndCopy( const WCHAR* pSrc, WCHAR* pDest )
{
	if( pDest && pSrc )
	{
		size_t calcLength = 0;
		CalcLength( pSrc, pDest, OUT calcLength );
		Clear( pDest, calcLength );
		Copy( pSrc, pDest, calcLength );
	}
}