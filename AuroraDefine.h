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

	typedef unsigned char Byte;
	typedef short I16;
	typedef unsigned short UI16;
	typedef int I32;
	typedef unsigned int UI32;
	typedef __int64 I64;
	typedef unsigned __int64 UI64;

	constexpr UInt16 MAX_FILE_EXTENSION_LEN = 16 + 1;
	
	constexpr UInt16 MAX_DATETIME_STRING_LEN = 19 + 1;
	constexpr UInt16 MAX_TIME_STRING_LEN = 24;
	constexpr UInt16 MAX_THREAD_NAME_LEN = 40;

	constexpr UInt16 NORMAL_QUEUE_SIZE = 1024;

	constexpr UInt16 DEFAULT_TINY_STR_LEN = 32;
	constexpr UInt16 DEFAULT_SHORT_STR_LEN = DEFAULT_TINY_STR_LEN << 1;
	constexpr UInt16 DEFAULT_NORMAL_STR_LEN = DEFAULT_SHORT_STR_LEN << 1;
	constexpr UInt16 DEFAULT_BIG_STR_LEN = DEFAULT_NORMAL_STR_LEN << 1;
	constexpr UInt16 DEFAULT_BIGGER_STR_LEN = DEFAULT_BIG_STR_LEN << 1;
	constexpr UInt16 DEFAULT_BIGGEST_STR_LEN = DEFAULT_BIGGER_STR_LEN << 1;

	enum class ELogPrintType : Byte
	{
		None,
		Normal,
		Write,
	};

	enum class EFile : Byte
	{
		ANSI,
		UTF8,
		Binary,
	};

	enum class EFileOpenMode : Byte
	{
		Read,
		Write,
		ReadWrite,
	};

	namespace LogSystem
	{
		enum class ELogType : Byte
		{
			Info = 0,
			Trace,
			Warning,
			Critical,
			Size
		};
	}

	template <typename T>
	void SafeDelete( T* p )
	{
		if( p )
		{ 
			delete p; 
			p = nullptr; 
		}
	}

	template <typename T>
	void SafeDeleteArray( T* p )
	{
		if( p )
		{ 
			delete[] p; 
			p = nullptr; 
		}
	}
}