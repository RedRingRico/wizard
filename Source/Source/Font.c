#include <Font.h>
#include <Image.h>

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

int FONT_CreateFont( struct IMAGE *p_pImage, struct GLYPH *p_pGlyphSet,
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

