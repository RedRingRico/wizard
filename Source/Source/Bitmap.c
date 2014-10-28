#include <Bitmap.h>
#include <File.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int BMP_Load( const char *p_pFileName, struct IMAGE **p_ppImage )
{
	FILE *pBMPFile = NULL;
	FILE *pLOG = NULL;
	struct BITMAP_HEADER BitmapHeader;
	long FileSize;
	int WidthPadding;
	unsigned char PaletteData[ 768 ];
	int PaletteIndex;
	int BitmapRow;
	int UnpaddedLine;


	pLOG = fopen( "LOGFILE", "w" );


	if( FILE_Open( p_pFileName, "rb", &FileSize, &pBMPFile ) != 0 )
	{
		return 1;
	}

	/* This is necessary.  For some reason I haven't figured out, yet */
	fprintf( pLOG, "File pointer: %p\n", pBMPFile );

	if( FileSize < ( sizeof( struct BITMAP_HEADER ) ) )
	{
		FILE_Close( &pBMPFile );

		return 1;
	}


	if( fread( &BitmapHeader, sizeof( struct BITMAP_HEADER ), 1, pBMPFile ) ==
		0 )
	{
		FILE_Close( &pBMPFile );

		return 1;
	}

	if( ( BitmapHeader.Type[ 0 ] != 'B' ) &&
		( BitmapHeader.Type[ 1 ] != 'M' ) )
	{
		FILE_Close( &pBMPFile );

		return 1;
	}

	if( BitmapHeader.ColoursUsed > 256 )
	{
		FILE_Close( &pBMPFile );

		return 1;
	}

	/* If the width of the bitmap is not divisible by 4, get the remainder */
	WidthPadding = BitmapHeader.Width % 4;

	/* Read and convert the palette data */

	for( PaletteIndex = 0; PaletteIndex < BitmapHeader.ColoursUsed;
		++PaletteIndex )
	{
		/* Palette data is stored in the reverse order in a bitmap
		 * As there are 6 bits per pixel, move the byte along by two
		 */
		fread( &PaletteData[ ( PaletteIndex * 3 ) ], 3,
			BitmapHeader.ColoursUsed, pBMPFile );
		PaletteData[ ( PaletteIndex * 3 ) + 2 ] =
			PaletteData[ ( PaletteIndex * 3 ) + 2 ] >> 2;
		PaletteData[ ( PaletteIndex * 3 ) + 1 ] =
			PaletteData[ ( PaletteIndex * 3 ) + 1 ] >> 2;
		PaletteData[ ( PaletteIndex * 3 ) ] =
			PaletteData[ ( PaletteIndex * 3 ) ] >> 2;
	}

	if( IMG_Create( PaletteData, BitmapHeader.ColoursUsed, BitmapHeader.Width,
		BitmapHeader.Height, p_ppImage ) != 0 )
	{
		FILE_Close( &pBMPFile );

		return 1;
	}

	UnpaddedLine = BitmapHeader.Width - WidthPadding;

	/* Now for the grand finale, copy the image data, line-by-line (omitting
	 * the padding, of course)
	 */
	fclose( pLOG );

	for( BitmapRow = 0; BitmapRow < BitmapHeader.Height - 1; ++BitmapRow )
	{
		fread( &( *p_ppImage )->pData[ ( BitmapHeader.Width ) * BitmapRow ],
			sizeof( unsigned char ), BitmapHeader.Width, pBMPFile );

		fseek( pBMPFile, WidthPadding, SEEK_CUR );
	}

	FILE_Close( &pBMPFile );

	return 0;
}

