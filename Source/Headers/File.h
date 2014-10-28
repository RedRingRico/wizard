#ifndef __WIZARD_FILE_H__
#define __WIZARD_FILE_H__

#include <stdio.h>

int FILE_Open( const char *p_pFileName, const char *p_pFileMode,
	long *p_pFileSize, FILE **p_ppFile );
void FILE_Close( FILE **p_ppFile );

#endif /* __WIZARD_FILE_H__ */

