#pragma once
#include <Windows.h>
#include "WindowsConsoleManager.h"
#include "ThreadManager.h"
#include "LogManager.h"
#include "StringManager.h"

using namespace Aurora;
	
ConsoleManager::ConsoleManager() : 
_initialized( false ),
_output( INVALID_HANDLE_VALUE ),
_input( INVALID_HANDLE_VALUE ),
_readByte( 0 ), _writeByte( 0 )
{
	
}

ConsoleManager::~ConsoleManager()
{
	Free();
}

UInt32 __stdcall ConsoleManager::ReadWorker( void* pArgs )
{
	if( pArgs )
	{
		auto pThis = reinterpret_cast<ConsoleManager*>(pArgs);
		WCHAR buffer[DEFAULT_SHORT_STR_LEN] = { 0 };
		DWORD readByte = 0;

		while( true )
		{
			AuroraStringManager->Clear( buffer, DEFAULT_SHORT_STR_LEN );
			ReadConsole( pThis->GetInputHandle(), buffer, (DEFAULT_SHORT_STR_LEN - 1), &readByte, NULL );
			if( 0 == wcscmp( buffer, L"exit\r" ) )
			{
				break;
			}

			Sleep( 1 );
		}
	}

	return 0;
}

void ConsoleManager::Alloc() noexcept
{
	if( 0 == AllocConsole() )
	{
		auto error = GetLastError();
		error;
		//return false;
	}
}

bool ConsoleManager::Init()
{
	_output = GetStdHandle( STD_OUTPUT_HANDLE );
	_input = GetStdHandle( STD_INPUT_HANDLE );

	GetConsoleScreenBufferInfo( _output, &_screenBuffer );
	_initialized = true;

	TryBeginInput();
	return _initialized;
}

bool ConsoleManager::TryBeginInput() noexcept
{
	auto begin = AuroraThreadManager->BeginThread( ReadWorker, this, L"Console Input" );
	if( INVALID_HANDLE_VALUE == begin )
	{
		AuroraLogManager->Error( L"[ConsoleManager::BeginInput()] ERROR BEGIN INPUT" );
		return false;
	}

	return true;
}

void ConsoleManager::SetTitle( const WCHAR* const pTitle ) noexcept
{
	if( true == _initialized )
	{
		SetConsoleTitle( pTitle );
	}
}

void ConsoleManager::Resize( Int16 w, Int16 h )
{
	SMALL_RECT rect;
	rect.Top = 1500;
	rect.Bottom = h;

	rect.Left = w;
	rect.Right = 4000;
	SetConsoleWindowInfo( _output, TRUE, &rect );
}

void ConsoleManager::EnableEdit() noexcept
{
	if( true == _initialized )
	{
		DWORD prev_mode;
		GetConsoleMode( _input, &prev_mode );
		SetConsoleMode( _input, prev_mode & ENABLE_QUICK_EDIT_MODE );
	}
}

void ConsoleManager::DisableEdit() noexcept
{
	if( true == _initialized )
	{
		DWORD prev_mode;
		GetConsoleMode( _input, &prev_mode );
		SetConsoleMode( _input, prev_mode &= ~ENABLE_QUICK_EDIT_MODE );
	}
}

void ConsoleManager::Free() noexcept
{
	if( FALSE == FreeConsole() )
	{

	}

	_initialized = false;
}

void ConsoleManager::Write( const WCHAR* const pText ) noexcept
{
	if( true == _initialized && pText )
	{
		WriteConsole( _output, pText, lstrlen( pText ), &_writeByte, NULL );
	}
}

void ConsoleManager::WriteLN( const WCHAR* const pText ) noexcept
{
	Write( pText );
	Write( L"\n" );
}

void ConsoleManager::WriteRedLN( const WCHAR* const pText ) noexcept
{
	SetConsoleTextAttribute( _output, ConsoleColor::RED );
	WriteLN( pText );
}

void ConsoleManager::WriteBlueLN( const WCHAR* const pText ) noexcept
{
	SetConsoleTextAttribute( _output, ConsoleColor::BLUE );
	WriteLN( pText );
}

void ConsoleManager::WriteGreenLN( const WCHAR* const pText ) noexcept
{
	SetConsoleTextAttribute( _output, ConsoleColor::GREEN );
	WriteLN( pText );
}

void ConsoleManager::WriteYellowLN( const WCHAR* const pText ) noexcept
{
	SetConsoleTextAttribute( _output, ConsoleColor::YELLOW );
	WriteLN( pText );
}

void ConsoleManager::WriteWhiteLN( const WCHAR* const pText ) noexcept
{
	SetConsoleTextAttribute( _output, ConsoleColor::WHITE );
	WriteLN( pText );
}

void ConsoleManager::WriteDarkGrayLN( const WCHAR* const pText ) noexcept
{
	SetConsoleTextAttribute( _output, ConsoleColor::DARKGRAY );
	WriteLN( pText );
}