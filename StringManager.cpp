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

void StringManager::FormatString( OUT char* pOutStr, OUT size_t len, char* format, ... ) const
{
	va_list args;

	va_start( args, format );
	vsnprintf_s( pOutStr, _TRUNCATE, len, format, args );
	va_end( args );
}

void StringManager::FormatString( OUT WCHAR* pOutString, OUT size_t len, const WCHAR* const format, ... ) const
{
	if( pOutString )
	{
		va_list args;

		va_start( args, format );
		auto rtn = _vsnwprintf_s( pOutString, _TRUNCATE, len, format, args );
		if( -1 == rtn )
		{
			// error.
		}

		va_end( args );
	}
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

void StringManager::WideToString( const WCHAR* pSrc, OUT string &destString )
{
	//wide char array
	auto length = (wcslen( pSrc ) + 1);

	//convert from wide char to narrow char array
	auto pTempChar = new char[length];
	Clear( pTempChar, length );

	auto DefChar = ' ';
	::WideCharToMultiByte( CP_ACP, 0, pSrc, -1, pTempChar, static_cast<Int32>(length), &DefChar, NULL );

	destString.assign( pTempChar );

	SafeDeleteArray( pTempChar );
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

void StringManager::Copy( char* pDest, const char* pSrc, const size_t length ) const
{
	length;
	if( pSrc && pDest )
	{
		strcpy_s( pDest, _TRUNCATE, pSrc );
	}
}

void StringManager::Copy( WCHAR* pDest, const WCHAR* pSrc, const size_t length ) const
{
	length;
	if( pSrc && pDest )
	{
		wcscpy_s( pDest, _TRUNCATE, pSrc );
	}
}

void StringManager::ClearAndCopy( const char* pSrc, char* pDest, const size_t length )
{
	if( pDest && pSrc && (0 < length) )
	{
		Clear( pDest, length );
		Copy( pDest, pSrc, length );
	}
}

void StringManager::ClearAndCopy( char* pDest, const char* pSrc )
{
	if( pDest && pSrc )
	{
		size_t length = 0;
		CalCLength( pSrc, pDest, OUT length );
		
		Clear( pDest, length );
		Copy( pDest, pSrc, length );
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
			Copy( pDest, pSrc, length );
		}
		else
		{
			Copy( pDest, pSrc, calcLength );
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
		Copy( pDest, pSrc, calcLength );
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
			outStrings.emplace_back( string( pToken ) );
			pToken = strtok_s( nullptr, pDelim, &buffer );
		}
	}
}

void StringManager::Tokenize( WCHAR* pStr, WCHAR* const pDelim, OUT vector<wstring>& outStrings ) const
{
	if( pStr && pDelim )
	{
		WCHAR* buffer = nullptr;
		auto pToken = wcstok_s( pStr, pDelim, &buffer );
		while ( pToken ) 
		{
			outStrings.emplace_back( wstring( pToken ) );
			pToken = wcstok_s( nullptr, pDelim, &buffer );
		}
	}
}
