#pragma once
#include "StringManager.h"
#include <iostream>

using namespace Aurora;

StringManager::StringManager( void )
{

}

StringManager::~StringManager( void )
{

}

template <typename T>
void StringManager::Clear( T* pString, const size_t length )
{
	auto realLen = length; realLen;
	memset( static_cast<void *>(pString), 0, sizeof( T ) * length );
}

template <typename T>
void StringManager::Clear( T* pString, const Int16 length )
{
	Clear( pString, static_cast<size_t>(length) );
}

template <typename T>
void StringManager::Clear( T* pString, const UInt16 length )
{
	Clear( pString, static_cast<size_t>(length) );
}

void StringManager::FormatString( OUT char* pOutString, char* szFormat, ... ) const
{
	va_list args;

	va_start( args, szFormat );
	vsnprintf_s( static_cast<char*>(pOutString), MAX_LONG_STRING_LEN, MAX_LONG_STRING_LEN, szFormat, args );
	va_end( args );
}

void StringManager::FormatString( OUT WCHAR* pOutString, WCHAR* szFormat, ... ) const
{
	va_list args;

	va_start( args, szFormat );
	_vsnwprintf_s( static_cast<WCHAR*>(pOutString), MAX_LONG_STRING_LEN, MAX_LONG_STRING_LEN, szFormat, args );
	va_end( args );

	wprintf_s( reinterpret_cast<WCHAR*>(&pOutString), MAX_LONG_STRING_LEN );
}

void StringManager::CharToWChar( const char* pSrc, OUT WCHAR* pDest ) const
{
	if( pSrc && pDest )
	{
		size_t convertedCharsw = 0;
		auto size = (strlen( pSrc ) + 1) * 2;
		auto result = mbstowcs_s( &convertedCharsw, pDest, size, pSrc, size );
		if ( 0 != result )
		{

		}
	}
}

void StringManager::WCharToChar( const WCHAR* pSrc, OUT char* pDest ) const
{
	if( pSrc && pDest )
	{
		size_t convertedChars = 0;
		auto size = (wcslen( pSrc ) + 1);
		auto result = wcstombs_s( &convertedChars, pDest, size, pSrc, size );
		if ( 0 != result )
		{

		}		
	}
}

void StringManager::WideToString( const WCHAR* pSrc, OUT std::string &destString )
{
	//wide char array
	auto length = (wcslen( pSrc ) + 1);

	//convert from wide char to narrow char array
	auto pTempChar = new char[length];
	Clear( pTempChar, length );

	auto DefChar = ' ';
	::WideCharToMultiByte( CP_ACP, 0, pSrc, -1, pTempChar, static_cast<Int32>(length), &DefChar, NULL );

	destString.assign( pTempChar );

	SAFE_DELETE_ARRAY_POINTER( pTempChar );
}

void StringManager::CalCLength( const char* pSrc, char* pDest, OUT size_t& calcLength )
{
	const auto srcLength = strlen( pSrc ) + 1;
	const auto destLength = strlen( pDest ) + 1;

	calcLength = destLength;
	if( srcLength > destLength )
	{
		calcLength = srcLength;
	}
}

void StringManager::CalCLength( const WCHAR* pSrc, WCHAR* pDest, OUT size_t& calcLength ) const
{
	const auto srcLength = wcslen( pSrc ) + 1;
	const auto destLength = wcslen( pDest ) + 1;

	calcLength = destLength;
	if( srcLength > destLength )
	{
		calcLength = srcLength;
	}
}

void StringManager::Copy( const char* pSrc, char* pDest, const size_t length ) const
{
	if( pSrc && pDest )
	{
		strcpy_s( pDest, length, pSrc );
	}
}

void StringManager::Copy( const WCHAR* pSrc, WCHAR* pDest, const size_t length ) const
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
		CalCLength( pSrc, pDest, OUT length );
		
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
		CalCLength( pSrc, pDest, OUT calcLength );
		
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
		CalCLength( pSrc, pDest, OUT calcLength );
		Clear( pDest, calcLength );
		Copy( pSrc, pDest, calcLength );
	}
}

void StringManager::Tokenize( char* pStr, char* const pDelim, OUT vector<string>& outStrings ) const
{
	if ( pStr && pDelim )
	{
		char* buffer = nullptr;
		auto pToken = strtok_s( pStr, pDelim, &buffer );
		while ( pToken )
		{
			outStrings.emplace_back( std::string( pToken ) );
			pToken = strtok_s( nullptr, pDelim, &buffer );
		}
	}
}

void StringManager::Tokenize( WCHAR* pStr, WCHAR* const pDelim, OUT vector<wstring>& outStrings ) const
{
	if( pStr && pDelim )
	{
		wchar_t* buffer = nullptr;
		auto pToken = wcstok_s( pStr, pDelim, &buffer );
		while ( pToken ) 
		{
			outStrings.emplace_back( std::wstring( pToken ) );
			pToken = wcstok_s( nullptr, pDelim, &buffer );
		}
	}
}
