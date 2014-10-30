#include <Font.h>
#include <Image.h>
#include <File.h>
#include <stdio.h>
#include <string.h>

int FONT_AddGlyph( struct GLYPH *p_pGlyph, struct GLYPH *p_pGlyphSet )
{
	if( p_pGlyph == NULL )
	{
		return 1;
	}

	if( p_pGlyphSet == NULL )
	{
		return 1;
	}

	/* Find the last element in the list */
	while( p_pGlyphSet->pNext != NULL )
	{
		p_pGlyphSet->pNext = p_pGlyphSet->pNext->pNext;
	}

	p_pGlyphSet->pNext = p_pGlyph;

	/* Make sure it's ended properly */
	p_pGlyphSet->pNext->pNext = NULL;
	
	return 0;
}

int FONT_Create( struct IMAGE *p_pImage, struct GLYPH *p_pGlyphSet,
	struct FONT **p_ppFont )
{
	if( p_pImage == NULL )
	{
		return 1;
	}

	if( p_pGlyphSet == NULL )
	{
		return 1;
	}

	( *p_ppFont ) = ( struct FONT * )malloc( sizeof( struct FONT ) );

	( *p_ppFont )->pImage = p_pImage;
	( *p_ppFont )->pGlyphSet = p_pGlyphSet;

	return 0;
}

void FONT_Destroy( struct FONT **p_ppFont )
{
	if( ( *p_ppFont ) != NULL )
	{
		free( ( *p_ppFont ) );
	}
}

int FONT_Load( const char *p_pFileName, struct FONT **p_ppFont )
{
	FILE *pFontFile;

	if( *( p_ppFont ) )
	{
		FONT_Destroy( p_ppFont );
	}

	if( p_pFileName == NULL )
	{
		return 1;
	}

	if( strlen( p_pFileName ) == 0 ) 
	{
		return 1;
	}

	/* Other than checking if the file exists, there is very little error
	 * checking, so be careful!
	 *
	 * Font file resources are as follows:
	 * Glyph set
	 * ---------
	 *  Number of glyphs in the set
	 *  foreach glyph in glyphset
	 *    Read: x, y, advance, bearing, width, height, character
	 *    Append new glyph to last glyph read
	 *
	 * Glyph set data is stored as binary data, use glyphbin to convert the
	 * glyph set into a binary file.  If not already performed, bmp2img will
	 * convert a bitmap (.BMP) file to an IMAGE-based file.  When both the
	 * glyphs and image are ready, use the glyphimg program to merge the image
	 * and glyph set into a font file
	 *
	 * IMAGE-formatted image data
	 */

	return 0;
}

