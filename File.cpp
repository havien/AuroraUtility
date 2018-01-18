#pragma once
#include "File.h"
#include "StringManager.hpp"

using namespace Aurora;

File::File( const WCHAR* pFileName, const EFile type, const EFileOpenMode mode )
{
	AuroraStringManager->Clear( _name, static_cast<size_t>(MAX_PATH) );
	
	SetName( pFileName );

	switch( type )
	{
	case EFile::ANSI:
		break;
	case EFile::UTF8:
		break;
	case EFile::Binary:
		OpenBinary( mode );
		break;
	}
}

File::~File( void )
{
	if ( true == _stream.is_open() )
	{
		_stream.close();
	}
}

void File::SetName( const WCHAR* pFileName )
{
	if ( pFileName )
	{
		AuroraStringManager->Copy( _name, pFileName, MAX_PATH );
	}
}


bool File::OpenBinary( const EFileOpenMode mode )
{
	if( _stream.is_open() )
	{
		return false;
	}

	switch ( mode )
	{
	case EFileOpenMode::Read:
		break;
	case EFileOpenMode::Write:
		break;
	case EFileOpenMode::ReadWrite:
		_stream.open( _name, _stream.binary | _stream.trunc | _stream.in );
		break;
	}

	if ( !_stream.is_open() )
	{
		return false;
	}

	return true;
}

bool File::OpenBinary( const WCHAR* pFileName, const EFileOpenMode mode )
{
	if ( !pFileName )
	{
		return false;
	}

	SetName( pFileName );
	return OpenBinary( mode );
}