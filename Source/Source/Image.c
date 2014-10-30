#include <Image.h>
#include <Video.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int IMG_Create( unsigned char *p_pPalette, unsigned short p_PaletteCount,
	unsigned short p_Width, unsigned short p_Height, struct IMAGE **p_ppImage )
{
	if( p_PaletteCount > 256 )
	{
		return 1;
	}

	if( p_pPalette == NULL )
	{
		return 1;
	}

	if( p_PaletteCount == 0 )
	{
		return 1;
	}

	if( p_PaletteCount > 1024 )
	{
		return 1;
	}

	if( p_Width == 0 )
	{
		return 1;
	}

	if( p_Height == 0 )
	{
		return 1;
	}

	( *p_ppImage ) = ( struct IMAGE * )malloc( sizeof( struct IMAGE ) );
	
	( *p_ppImage )->pData = ( unsigned char * )malloc( p_Width * p_Height );

	if( ( *p_ppImage )->pData == NULL )
	{
		return 1;
	}

	memcpy( ( *p_ppImage )->Palette, p_pPalette, p_PaletteCount * 3 );

	/* Set the palette mask to indicate the range of colours to replace
	 * As there are 32 colours per bank, use the integer value from the divide
	 * and if the modulo is not zero, add a one to indicate the next bank
	 */
	( *p_ppImage )->PaletteMask = ( p_PaletteCount / 32 ) +
		( p_PaletteCount % 32 > 0 ? 1 : 0 );

	( *p_ppImage )->Width = p_Width;
	( *p_ppImage )->Height = p_Height;

	return 0;
}

void IMG_Destroy( struct IMAGE **p_ppImage )
{
	if( ( *p_ppImage ) )
	{
		if( ( *p_ppImage )->pData )
		{
			free( ( *p_ppImage )->pData );
			( *p_ppImage )->pData = NULL;
		}
		
		free( ( *p_ppImage ) );
		( *p_ppImage ) = NULL;
	}
}

void IMG_Draw( unsigned short p_X, unsigned short p_Y, struct IMAGE *p_pImage )
{
	int Index;
	int Palette;
	short ScreenOffset = ( p_Y << 8 ) + ( p_Y << 6 ) + p_X;
	short ImageOffset = 0;

	VID_SetPaletteData( p_pImage->Palette, p_pImage->PaletteMask * 32 );

	for( Index = 0; Index < p_pImage->Height; ++Index )
	{
		VID_FillRasterLineOffset( ScreenOffset, p_pImage->Width,
			&p_pImage->pData[ ImageOffset ] );

		ImageOffset += p_pImage->Width;
		ScreenOffset += SCREEN_WIDTH;
	}
}

void IMG_DrawSub( unsigned short p_X, unsigned short p_Y,
	unsigned short p_XOffset, unsigned short p_YOffset, unsigned short p_Width,
	unsigned short p_Height, struct IMAGE *p_pImage )
{
	int Index;
	int Palette;
	short ScreenOffset = ( p_Y << 8 ) + ( p_Y << 6 ) + p_X;
	short ImageOffset = ( p_pImage->Width * p_YOffset ) + p_XOffset;

	VID_SetPaletteData( p_pImage->Palette, p_pImage->PaletteMask * 32 );

	for( Index = 0; Index < p_Height; ++Index )
	{
		VID_FillRasterLineOffset( ScreenOffset, p_Width,
			&p_pImage->pData[ ImageOffset ] );

		ImageOffset += p_pImage->Width;
		ScreenOffset += SCREEN_WIDTH;
	}
}

void IMG_DrawTransparent( unsigned short p_X, unsigned short p_Y,
	struct IMAGE *p_pImage )
{
	int Index;
	int Palette;
	short ScreenOffset = ( p_Y << 8 ) + ( p_Y << 6 ) + p_X;
	short ImageOffset = 0;

	VID_SetPaletteData( p_pImage->Palette, p_pImage->PaletteMask * 32 );

	for( Index = 0; Index < p_pImage->Height; ++Index )
	{
		VID_FillRasterLineTransparentOffset( ScreenOffset, p_pImage->Width,
			&p_pImage->pData[ ImageOffset ] );

		ImageOffset += p_pImage->Width;
		ScreenOffset += SCREEN_WIDTH;
	}
}

void IMG_DrawSubTransparent( unsigned short p_X, unsigned short p_Y,
	unsigned short p_XOffset, unsigned short p_YOffset, unsigned short p_Width,
	unsigned short p_Height, struct IMAGE *p_pImage )
{
	int Index;
	int Palette;
	short ScreenOffset = ( p_Y << 8 ) + ( p_Y << 6 ) + p_X;
	short ImageOffset = ( p_pImage->Width * p_YOffset ) + p_XOffset;

	VID_SetPaletteData( p_pImage->Palette, p_pImage->PaletteMask * 32 );

	for( Index = 0; Index < p_Height; ++Index )
	{
		VID_FillRasterLineTransparentOffset( ScreenOffset, p_Width,
			&p_pImage->pData[ ImageOffset ] );

		ImageOffset += p_pImage->Width;
		ScreenOffset += SCREEN_WIDTH;
	}
}

