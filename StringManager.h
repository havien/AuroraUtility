#pragma once

#include "Includes.h"
#include "AuroraDefine.h"
#include "AuroraSingleton.h"

using namespace std;
namespace Aurora
{
	template <typename T>
	class AuroraString
	{

	};

	class StringManager : public Singleton<StringManager>
	{
		friend class Singleton<StringManager>;
		
		explicit StringManager( void );
		NON_COPYABLE( StringManager );
	public:
		virtual ~StringManager( void );

		template <typename T>
		void Clear( T* pString, const size_t length );

		template <typename T>
		void Clear( T* pString, const Int16 length );

		template <typename T>
		void Clear( T* pString, const UInt16 length );

		void FormatString( OUT char* pOutString, char* szFormat, ... ) const;
		void FormatString( OUT WCHAR* pOutString, WCHAR* szFormat, ... ) const;
		
		void CharToWChar( const char* pSrc, OUT WCHAR* pDest ) const;
		void WCharToChar( const WCHAR* pSrc, OUT char* pDest ) const;
		void WideToString( const WCHAR* pSrc, OUT std::string &destString );

		static void CalCLength( const char* pSrc, char* pDest, OUT size_t& calcLength );
		void CalCLength( const WCHAR* pSrc, WCHAR* pDest, OUT size_t& calcLength ) const;

		void Copy( const char* pSrc, char* pDest, const size_t length ) const;
		void Copy( const WCHAR* pSrc, WCHAR* pDest, const size_t length ) const;

		void ClearAndCopy( const char* pSrc, char* pDest, const size_t length );
		void ClearAndCopy( const char* pSrc, char* pDest );
		
		void ClearAndCopy( const WCHAR* pSrc, WCHAR* pDest, const size_t length );
		void ClearAndCopy( const WCHAR* pSrc, WCHAR* pDest );

		void Tokenize( char* pStr, char* const pDelim, OUT vector<string>& outStrings ) const;
		void Tokenize( WCHAR* pStr, WCHAR* const pDelim, OUT vector<wstring>& outStrings ) const;
	};
}

#define AuroraStringManager Aurora::StringManager::Instance()