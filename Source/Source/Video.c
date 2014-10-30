#include <Video.h>
#include <File.h>
#include <dos.h>
#include <string.h>
#include <stdio.h>

static unsigned char *g_pVGA = ( unsigned char * )0x00000000;

void VID_InitialiseVideo( int p_BaseAddress )
{
	g_pVGA = ( unsigned char * )p_BaseAddress;
}

void VID_SetVideoMode( unsigned char p_Mode )
{
	union REGS Registers;

	Registers.h.ah = SET_MODE;
	Registers.h.al = p_Mode;

	int86( VIDEO_INT, &Registers, &Registers );
}

void VID_GetVideoInformation( struct VIDEO_INFORMATION *p_pVideoInformation )
{
	if( p_pVideoInformation )
	{
		p_pVideoInformation->VGAAddress = g_pVGA;
		p_pVideoInformation->Width = SCREEN_WIDTH;
		p_pVideoInformation->Height = SCREEN_HEIGHT;
	}
}

void VID_PlotPixelDirect( int p_Offset, unsigned char p_Colour )
{
	g_pVGA[ p_Offset ] = p_Colour;
}

void VID_PlotPixel( int p_X, int p_Y, unsigned char p_Colour )
{
	g_pVGA[ p_Y * SCREEN_WIDTH + p_X ] = p_Colour;
}

void VID_FillRasterLineOffset( int p_Offset, int p_Width,
	unsigned char *p_pColourData )
{
	memcpy( &g_pVGA[ p_Offset ], p_pColourData, p_Width );
}

void VID_FillRasterLineXY( int p_X, int p_Y, int p_Width,
	unsigned char *p_pColourData )
{
	int ScreenOffset = ( p_Y << 8 ) + ( p_Y << 6 ) + p_X;

	memcpy( &g_pVGA[ ScreenOffset ], p_pColourData, p_Width );
}

void VID_FillRasterLineTransparentOffset( int p_Offset, int p_Width,
	unsigned char *p_pColourData )
{
	int Index;

	for( Index = 0; Index < p_Width; ++Index )
	{
		if( p_pColourData[ Index ] != 0xFF )
		{
			g_pVGA[ p_Offset ] = p_pColourData[ Index ];
		}

		++p_Offset;
	}
}

void VID_FillRasterLineTransparentXY( int p_X, int p_Y, int p_Width,
	unsigned char *p_pColourData )
{
	int Index;
	int ScreenOffset = ( p_Y << 8 ) + ( p_Y << 6 ) + p_X;

	for( Index = 0; Index < p_Width; ++Index )
	{
		if( p_pColourData[ Index ] != 0xFF )
		{
			g_pVGA[ ScreenOffset ] = p_pColourData[ Index ];
		}

		++ScreenOffset;
	}
}

void VID_ClearScreen( unsigned char p_Colour )
{
	memset( g_pVGA, p_Colour , SCREEN_WIDTH * SCREEN_HEIGHT );
}

void VID_SetPaletteData( unsigned char *p_pPalette, int p_PaletteCount )
{
	int Index;

	outp( PALETTE_INDEX, 0 );

	for( Index = 0; Index < p_PaletteCount; ++Index )
	{
		outp( PALETTE_DATA, p_pPalette[ ( Index * 3 ) ] );
		outp( PALETTE_DATA, p_pPalette[ ( Index * 3 ) + 1] );
		outp( PALETTE_DATA, p_pPalette[ ( Index * 3 ) + 2 ] );
	}
}

int VID_LoadPaletteData( const char *p_pFileName )
{
	FILE *pFile = NULL;
	int PaletteCount = 0;

	FILE_Open( p_pFileName, "rb", NULL, &pFile );

	fread( &PaletteCount, sizeof( int ), 1, pFile );

	if( ( PaletteCount > 0 ) && ( PaletteCount <= 256 ) )
	{
		int Index;
		unsigned char *pPalette =
			( unsigned char * )malloc( PaletteCount * 3 );
		fread( pPalette, PaletteCount, 3, pFile );

		outp( PALETTE_INDEX, 0 );

		for( Index = 0; Index < PaletteCount; ++Index )
		{
			outp( PALETTE_DATA, pPalette[ ( Index * 3 ) ] );
			outp( PALETTE_DATA, pPalette[ ( Index * 3 ) + 1 ] );
			outp( PALETTE_DATA, pPalette[ ( Index * 3 ) + 2 ] );
		}

		free( pPalette );
		pPalette = NULL;
	}

	FILE_Close( &pFile );

	return 0;
}

