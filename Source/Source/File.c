#include <File.h>
#include <stdio.h>
#include <string.h>

int FILE_Open( const char *p_pFileName, const char *p_pFileMode,
	long *p_pFileSize, FILE **p_ppFile )
{
	if( p_pFileName == NULL )
	{
		return 1;
	}
	if( strlen( p_pFileName ) == 0 )
	{
		return 1;
	}

	if( p_pFileMode == NULL )
	{
		return 1;
	}

	if( strlen( p_pFileMode ) == 0 )
	{
		return 1;
	}

	if( ( ( *p_ppFile ) = fopen( p_pFileName, p_pFileMode ) ) == NULL )
	{
		return 1;
	}

	if( p_pFileSize )
	{
		fseek( ( *p_ppFile ), 0, SEEK_END );
		( *p_pFileSize ) = ftell( ( *p_ppFile ) );
		rewind( ( *p_ppFile ) );
	}

	return 0;
}

void FILE_Close( FILE **p_ppFile )
{
	if( ( *p_ppFile ) )
	{
		fclose( ( *p_ppFile ) );
		( *p_ppFile ) = NULL;
	}
}

