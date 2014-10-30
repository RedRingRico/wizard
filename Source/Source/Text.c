#include <Text.h>
#include <Image.h>
#include <string.h>
#include <stdint.h>

int TEXT_DrawCharacter( int p_X, int p_Y, char p_Character, int *p_pAdvance, 
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

	IMG_DrawSub( p_X, p_Y - pGlyph->Bearing, pGlyph->X, pGlyph->Y,
		pGlyph->Width, pGlyph->Height, p_pFont->pImage );

	if( p_pAdvance )
	{
		( *p_pAdvance ) = pGlyph->Advance;
	}

	return 0;
}

int TEXT_DrawString( int p_X, int p_Y, const char *p_pString,
	struct FONT *p_pFont )
{
	size_t Char = 0;
	size_t Length;
	int XOffset = 0;
	int Advance = 0;

	if( p_pString == NULL )
	{
		return 1;
	}

	Length = strlen( p_pString );

	if( Length == 0 )
	{
		return 1;
	}

	for( Char = 0; Char < Length; ++Char )
	{
		TEXT_DrawCharacter( p_X + XOffset, p_Y, p_pString[ Char ], &Advance,
			p_pFont );

		XOffset += Advance;
	}

	return 0;
}

