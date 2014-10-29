#include <Text.h>
#include <Image.h>

int TEXT_DrawCharacter( int p_X, int p_Y, char p_Character,
	struct FONT *p_pFont )
{
	struct GLYPH *pGlyph;
	if( p_pFont == NULL )
	{
		return 1;
	}

	if( p_pFont->pGlyphSet == NULL )
	{
		return 1;
	}

	pGlyph = p_pFont->pGlyphSet;

	while( pGlyph->Character != p_Character )
	{
		if( pGlyph->pNext == NULL )
		{
			return 1;
		}
		pGlyph = pGlyph->pNext;
	}

	IMG_DrawSub( p_X, p_Y, pGlyph->X, pGlyph->Y, pGlyph->Width, pGlyph->Height,
		p_pFont->pImage );

	return 0;
}

