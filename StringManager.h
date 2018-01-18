#pragma once

#include "Includes.h"
#include "AuroraDefine.h"
#include "AuroraSingleton.h"

using namespace std;
namespace Aurora
{
	class StringManager : public Singleton<StringManager>
	{			
	public:
		explicit StringManager();
		virtual ~StringManager();

		template <typename T>
		void Clear( T* pStr, const size_t length )
		{
			if( pStr )
			{
				memset( (void *)pStr, 0, sizeof( T ) * length );
			}
		}

		template <typename T>
		void Clear( T* pString, const Int16 length )
		{
			Clear( pString, static_cast<size_t>(length) );
		}

		template <typename T>
		void Clear( T* pString, const UInt16 length )
		{
			Clear( pString, static_cast<size_t>(length) );
		}

		/*
		template <typename T>
		void Clear( T* pString, const size_t length );

		template <typename T>
		void Clear( T* pString, const Int16 length );

		template <typename T>
		void Clear( T* pString, const UInt16 length );*/

		void FormatString( OUT char* pOutStr, OUT size_t len, char* format, ... ) const;
		void FormatString( OUT WCHAR* pOutStr, OUT size_t len, const WCHAR* const format, ... ) const;
		
		void CharToWChar( const char* pSrc, OUT WCHAR* pDest ) const;
		void WCharToChar( const WCHAR* pSrc, OUT char* pDest ) const;
		void WideToString( const WCHAR* pSrc, OUT string &destString );

		static void CalCLength( const char* pSrc, char* pDest, OUT size_t& calcLength );
		void CalCLength( const WCHAR* pSrc, WCHAR* pDest, OUT size_t& calcLength ) const;

		void Copy( char* pDest, const char* pSrc, const size_t length ) const;
		void Copy( WCHAR* pDest, const WCHAR* pSrc, const size_t length ) const;

		void ClearAndCopy( const char* pSrc, char* pDest, const size_t length );
		void ClearAndCopy( char* pDest, const char* pSrc );
		
		void ClearAndCopy( const WCHAR* pSrc, WCHAR* pDest, const size_t length );
		void ClearAndCopy( const WCHAR* pSrc, WCHAR* pDest );

		void Tokenize( char* pStr, char* const pDelim, OUT vector<string>& outStrings ) const;
		void Tokenize( WCHAR* pStr, WCHAR* const pDelim, OUT vector<wstring>& outStrings ) const;
	};
}

#define AuroraStringManager Aurora::StringManager::Instance()