#pragma once
#include "FileManager.h"
#include "MiscManager.h"

using namespace Aurora;

FileManager::FileManager( void ) : 
_pWorkFile( nullptr ), 
_lastErrno( EINVAL )
{

}

FileManager::~FileManager( void )
{
	CloseFile();
}
	
bool FileManager::OpenFile( const WCHAR* pFileName, EFileOpenMode OpenMode )
{
	// ������ �۾� �� ������ �ִٰ� �Ǵ���?
	// �ݰ� �ٽ� ��.
	if( pFileName )
	{
		CloseFile();

		if( EFileOpenMode::ReadOnly == OpenMode )
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

bool FileManager::WriteFile( const WCHAR* pWrite )
{
	if( nullptr == _pWorkFile )
	{
		return false;
	}
	else if( nullptr != _pWorkFile )
	{
		// ������ �۾� �� ������ �ִٰ� �Ǵ���.
		// ��.
		int PutResult = fputws( pWrite, _pWorkFile );
		PRINT_NORMAL_LOG( L"Write File!! Result %d\n", PutResult );
		/*if( 0 > PutResult )
		{*/
				
		/*}*/
	}

	return true;
}

void FileManager::CloseFile( void )
{
	if( nullptr != _pWorkFile )
	{
		fclose( _pWorkFile );
		_pWorkFile = nullptr;
	}
}