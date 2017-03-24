#pragma once

#include "Includes.h"
#include <fstream>

#include "AuroraDefine.h"

namespace Aurora
{
	class File
	{
	public:
		explicit File( const WCHAR* pFileName, const EFile type, const EFileOpenMode mode );
		~File( void );

		void SetName( const WCHAR* pFileName );
		bool OpenBinary( const EFileOpenMode mode );
		bool OpenBinary( const WCHAR* pFileName, const EFileOpenMode mode );
	private:
		WCHAR _name[MAX_PATH];
		std::wfstream _stream;
	};
}
