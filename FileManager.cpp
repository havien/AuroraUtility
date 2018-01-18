#pragma once
#include "FileManager.h"
#include "StringManager.h"

using namespace std;
using namespace Aurora;

FileManager::FileManager(): 
_pWorkFile( nullptr ), 
_lastErrno( EINVAL )
{

}

FileManager::~FileManager( void )
{
	Close();
}

bool FileManager::IsOpen( const WCHAR* pFileName, const EFileOpenMode mode )
{
	mode;
	if ( !pFileName )
	{
		return false;
	}

	return true;
}

bool FileManager::Open( const WCHAR* pFileName, EFileOpenMode OpenMode )
{
	// 이전에 작업 된 파일이 있다고 판단함?
	// 닫고 다시 염.
	if( pFileName )
	{
		Close();

		if( EFileOpenMode::Read == OpenMode )
		{
			_lastErrno = _wfopen_s( &_pWorkFile, pFileName, L"r" );
		}
		else if( EFileOpenMode::ReadWrite == OpenMode )
		{
			_lastErrno = _wfopen_s( &_pWorkFile, pFileName, L"a+" );
		}
		else
		{
			_lastErrno = EINVAL;
		}

		if( 0 != _lastErrno )
		{
			return false;
		}

		return true;
	}

	return false;
}

bool FileManager::Write( const WCHAR* pWrite )
{
	if( nullptr == _pWorkFile )
	{
		return false;
	}
	else if( nullptr != _pWorkFile )
	{
		pWrite;
		// 이전에 작업 된 파일이 있다고 판단함.
		// 씀.
		//int PutResult = fputws( pWrite, _pWorkFile );
		//AuroraLogManager->Trace( L"Write File!! Result %d", PutResult );
		/*if( 0 > PutResult )
		{*/
				
		/*}*/
	}

	return true;
}

void FileManager::Close( void )
{
	if( nullptr != _pWorkFile )
	{
		fclose( _pWorkFile );
		_pWorkFile = nullptr;
	}
}

int FileManager::Rename( const char* pPath, const char* pOld, const char* pNew ) const
{
	if( pPath && pOld && pNew )
	{
		char pathOld[MAX_PATH*2] = { 0 };
		char pathNew[MAX_PATH*2] = { 0 };

		AuroraStringManager->FormatString( pathOld, (MAX_PATH * 2), "%s%s", pPath, pOld );
		AuroraStringManager->FormatString( pathNew, (MAX_PATH * 2), "%s%s", pPath, pNew );

		return rename( pathOld, pathNew );
	}

	return -1;
}

void FileManager::DetermineExtension( const char* pFileName, OUT char* pExtension ) const
{
	if( !pFileName )
	{
		return;
	}

	char* buffer = nullptr;
	auto token = strtok_s( const_cast<char *>(pFileName), ".", &buffer );
	while ( token )
	{
		token = strtok_s( nullptr, ".", &buffer );
		if( '\0' != token )
		{
			AuroraStringManager->Copy( token, pExtension, 15 );
		}
	}
}
