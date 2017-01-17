#pragma once

#include "Includes.h"
#include "AuroraDefine.h"
#include "AuroraSingleton.h"

namespace Aurora
{
	template <typename T>
	class AuroraString
	{

	};

	class StringManager : public Singleton<StringManager>
	{
		friend class Singleton<StringManager>;
	private:
		StringManager( void );

		NON_COPYABLE( StringManager );
	public:
		virtual ~StringManager( void );

		void MakeString( OUT char* pOutString, char* szFormat, ... );
		void MakeString( OUT WCHAR* pOutString, WCHAR* szFormat, ... );
		
		void WideToMultiByte( const WCHAR* pSrc, OUT char* pDest );
		void WideToString( const WCHAR* pSrc, OUT std::string &destString );
		
		template <typename T>
		void Clear( T* pString, const size_t length )
		{
			memset( static_cast<void*>(pString), 0, sizeof( T ) * length );
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

		void CalcLength( const char* pSrc, char* pDest, OUT size_t& calcLength );
		void CalcLength( const WCHAR* pSrc, WCHAR* pDest, OUT size_t& calcLength );

		void Copy( const char* pSrc, char* pDest, const size_t length );
		void Copy( const WCHAR* pSrc, WCHAR* pDest, const size_t length );

		void ClearAndCopy( const char* pSrc, char* pDest, const size_t length );
		void ClearAndCopy( const char* pSrc, char* pDest );
		
		void ClearAndCopy( const WCHAR* pSrc, WCHAR* pDest, const size_t length );
		void ClearAndCopy( const WCHAR* pSrc, WCHAR* pDest );
	};

	#define AuroraStringManager StringManager::Instance()
}