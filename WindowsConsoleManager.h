#pragma once

#include "Includes.h"
#include "AuroraDefine.h"
#include "AuroraSingleton.h"

namespace Aurora
{
	enum ConsoleColor
	{
		BLACK = 0,
		DARKBLUE = FOREGROUND_BLUE,
		DARKGREEN = FOREGROUND_GREEN,
		DARKCYAN = FOREGROUND_GREEN | FOREGROUND_BLUE,
		DARKRED = FOREGROUND_RED,
		DARKMAGENTA = FOREGROUND_RED | FOREGROUND_BLUE,
		DARKYELLOW = FOREGROUND_RED | FOREGROUND_GREEN,
		DARKGRAY = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE,
		GRAY = FOREGROUND_INTENSITY,
		BLUE = FOREGROUND_INTENSITY | FOREGROUND_BLUE,
		GREEN = FOREGROUND_INTENSITY | FOREGROUND_GREEN,
		CYAN = FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE,
		RED = FOREGROUND_INTENSITY | FOREGROUND_RED,
		MAGENTA = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE,
		YELLOW = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN,
		WHITE = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE,
	};

	class ConsoleManager : public Singleton<ConsoleManager>
	{
		friend class Singleton<ConsoleManager>;
	private:
		ConsoleManager();
	public:
		virtual ~ConsoleManager();

		static UInt32 __stdcall ReadWorker( void* pArgs );

		void Alloc() noexcept;
		bool Init();
		bool TryBeginInput() noexcept;

		void SetTitle( const WCHAR* const pTitle ) noexcept;
		void Resize( Int16 w, Int16 h );
		
		void EnableEdit() noexcept;
		void DisableEdit() noexcept;
		void Free() noexcept;

		void Write( const WCHAR* const pText ) noexcept;
		void WriteLN( const WCHAR* const pText ) noexcept;
		
		void WriteRedLN( const WCHAR* const pText ) noexcept;
		void WriteBlueLN( const WCHAR* const pText ) noexcept;
		void WriteGreenLN( const WCHAR* const pText ) noexcept;
		
		void WriteYellowLN( const WCHAR* const pText ) noexcept;
		void WriteWhiteLN( const WCHAR* const pText ) noexcept;
		void WriteDarkGrayLN( const WCHAR* const pText ) noexcept;

		HANDLE GetInputHandle() noexcept { return _input; }
		DWORD GetReadByte() noexcept { return _readByte; }
	private:
		bool _initialized;
		HANDLE _output;
		HANDLE _input;

		DWORD _readByte;
		DWORD _writeByte;
		
		CONSOLE_SCREEN_BUFFER_INFO _screenBuffer;
	};
}

#define AuroraConsoleManager Aurora::ConsoleManager::Instance()