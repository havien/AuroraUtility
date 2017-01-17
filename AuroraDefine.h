#pragma once

namespace Aurora
{
	typedef unsigned char Byte;
	typedef short Int16;
	typedef unsigned short UInt16;
	typedef int Int32;
	typedef unsigned int UInt32;
	typedef __int64 Int64;
	typedef unsigned __int64 UInt64;

	const UInt16 MAX_TINY_STRING_LEN = 32;
	const UInt16 MAX_SHORT_STRING_LEN = 128;
	const UInt16 MAX_NORMAL_STRING_LEN = 256;
	const UInt16 MAX_LONG_STRING_LEN = 1024;
	const UInt16 MAX_SUPER_STRING_LEN = 2048;
	
	const UInt16 MAX_DATETIME_STRING_LEN = 19 + 1;
	const UInt16 MAX_THREAD_NAME_LEN = 40;

	const UInt16 NORMAL_QUEUE_SIZE = 1024;

	enum class ELogPrintType : Byte
	{
		None,
		Normal,
		WriteLog,
	};

#define SAFE_DELETE( p ) if( p ) { delete p; p = nullptr; }
#define SAFE_DELETE_ARRAY_POINTER( p ) if( p ) { delete [] p; p = nullptr; }
#define NON_COPYABLE( arg ) arg( const arg& copyArg ); const arg& operator=( const arg& );
}