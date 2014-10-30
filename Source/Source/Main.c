#include <stdio.h>
#include <conio.h>
#include <GitVersion.h>
#include <Video.h>
#include <Renderer.h>
#include <sys/nearptr.h>
#include <stdlib.h>
#include <Vector4.h>
#include <Matrix4x4.h>
#include <Bitmap.h>
#include <Image.h>
#include <Text.h>

int main( int p_Argc, char **p_ppArgv )
{
	unsigned short VGARow, VGAColumn;
	unsigned int Index;
	struct VECTOR4 Vertex0, Vertex1, Vertex2;
	struct VECTOR4 Vertex0T, Vertex1T, Vertex2T;
	struct MATRIX4X4 WorldMatrix, RotationMatrix, ViewMatrix, ProjectionMatrix;
	float Rotation = 0.0f;
	struct IMAGE *pTestImage = NULL;
	struct GLYPH *pGlyph;
	struct FONT *pFont;

	if( __djgpp_nearptr_enable( ) == 0 )
	{
		printf( "Could not access the first 640KiB of memory\n" );
		return 1;
	}

	VID_InitialiseVideo( VGA_BASE_ADDRESS + __djgpp_conventional_base );

	printf( "Wizard\n" );
#if defined WIZ_BUILD_DEBUG
	printf( "Debug\n" );
#elif defined WIZ_BUILD_RELEASE
	printf( "Release\n" );
#elif defined WIZ_BUILD_PROFILE
	printf( "Profile\n" );
#else
#error Unknown build type
#endif
	printf( "Git version: %s\n", GIT_BUILD_VERSION );
	printf( "Git branch:  %s\n", GIT_BRANCH );
	printf( "Git tag:     %s\n", GIT_TAG_NAME );

	printf( "\nPress enter to advance each screen\n" );

	getch( );

	VID_SetVideoMode( VGA_COLOUR_MODE_256 );

	VID_ClearScreen( 0x01 );

	getch( );

	for( VGAColumn = 0; VGAColumn < 320; ++VGAColumn )
	{
		VID_PlotPixel( VGAColumn, SCREEN_HEIGHT / 2, 0x02 );
	}

	getch( );

	REN_DrawLine( 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0x04 );
	REN_DrawLine( SCREEN_WIDTH, 0, 0, SCREEN_HEIGHT, 0x04 );

	getch( );

	/*
	Vertex0.X = 0.0f;
	Vertex0.Y = 1.0f;
	Vertex0.Z = -1.0f;
	Vertex0.W = 0.0f;

	Vertex1.X = 1.0f;
	Vertex1.Y = 0.0f;
	Vertex1.Z = -1.0f;
	Vertex1.W = 0.0f;

	Vertex2.X = -1.0f;
	Vertex2.Y = 0.0f;
	Vertex2.Z = -1.0f;
	Vertex2.W = 0.0f;

	MAT44_Identity( &WorldMatrix );
	MAT44_Identity( &RotationMatrix );
	MAT44_Identity( &ViewMatrix );
	MAT44_Identity( &ProjectionMatrix );

	for( Index = 0; Index < 300; ++Index )
	{
		VID_ClearScreen( 0x00 );
		MAT44_RotateY( Rotation, &RotationMatrix );
		Rotation += 0.1f;
	}

	VID_ClearScreen( 0x00 );

	getch( );*/

	VID_ClearScreen( 0x00 );

	if( BMP_Load( "BAKED\\FONTS\\UM18PX.BMP", &pTestImage ) != 0 )
	{
		VID_SetVideoMode( VGA_TEXT_MODE );

		printf( "Failed to load bitmap\n" );

		getch( );

		__djgpp_nearptr_disable( );

		return 1;
	}

	IMG_Draw( 0, 0, pTestImage );
	IMG_DrawTransparent( 150, 0, pTestImage );

	getch( );

	VID_ClearScreen( 0x01 );

	/* I desprately need to create a font format */
	pGlyph = ( struct GLYPH * )malloc( sizeof( struct GLYPH ) * 10 );

	pGlyph[ 0 ].Character = 'T';
	pGlyph[ 0 ].X = 54;
	pGlyph[ 0 ].Y = 18;
	pGlyph[ 0 ].Advance = 9;
	pGlyph[ 0 ].Bearing = 11;
	pGlyph[ 0 ].Width = 8;
	pGlyph[ 0 ].Height = 11;
	pGlyph[ 0 ].pNext = &pGlyph[ 1 ];

	pGlyph[ 1 ].Character = 'e';
	pGlyph[ 1 ].X = 37;
	pGlyph[ 1 ].Y = 39;
	pGlyph[ 1 ].Advance = 8;
	pGlyph[ 1 ].Bearing = 8;
	pGlyph[ 1 ].Width = 7;
	pGlyph[ 1 ].Height = 8;
	pGlyph[ 1 ].pNext = &pGlyph[ 2 ];

	pGlyph[ 2 ].Character = 's';
	pGlyph[ 2 ].X = 46;
	pGlyph[ 2 ].Y = 57;
	pGlyph[ 2 ].Advance = 8;
	pGlyph[ 2 ].Bearing = 8;
	pGlyph[ 2 ].Width = 7;
	pGlyph[ 2 ].Height = 8;
	pGlyph[ 2 ].pNext = &pGlyph[ 3 ];

	pGlyph[ 3 ].Character = 't';
	pGlyph[ 3 ].X = 55;
	pGlyph[ 3 ].Y = 55;
	pGlyph[ 3 ].Advance = 8;
	pGlyph[ 3 ].Bearing = 10;
	pGlyph[ 3 ].Width = 7;
	pGlyph[ 3 ].Height = 10;
	pGlyph[ 3 ].pNext = &pGlyph[ 4 ];

	pGlyph[ 4 ].Character = 'i';
	pGlyph[ 4 ].X = 73;
	pGlyph[ 4 ].Y = 35;
	pGlyph[ 4 ].Advance = 8;
	pGlyph[ 4 ].Bearing = 12;
	pGlyph[ 4 ].Width = 7;
	pGlyph[ 4 ].Height = 12;
	pGlyph[ 4 ].pNext = &pGlyph[ 5 ];

	pGlyph[ 5 ].Character = 'n';
	pGlyph[ 5 ].X = 1;
	pGlyph[ 5 ].Y = 57;
	pGlyph[ 5 ].Advance = 8;
	pGlyph[ 5 ].Bearing = 8;
	pGlyph[ 5 ].Width = 7;
	pGlyph[ 5 ].Height = 8;
	pGlyph[ 5 ].pNext = &pGlyph[ 6 ];

	pGlyph[ 6 ].Character = 'g';
	pGlyph[ 6 ].X = 55;
	pGlyph[ 6 ].Y = 39;
	pGlyph[ 6 ].Advance = 9;
	pGlyph[ 6 ].Bearing = 8;
	pGlyph[ 6 ].Width = 8;
	pGlyph[ 6 ].Height = 11;
	pGlyph[ 6 ].pNext = &pGlyph[ 7 ];

	pGlyph[ 7 ].Character = ' ';
	pGlyph[ 7 ].X = 0;
	pGlyph[ 7 ].Y = 0;
	pGlyph[ 7 ].Advance = 6;
	pGlyph[ 7 ].Bearing = 0;
	pGlyph[ 7 ].Width = 1;
	pGlyph[ 7 ].Height = 1;
	pGlyph[ 7 ].pNext = &pGlyph[ 8 ];

	pGlyph[ 8 ].Character = 'F';
	pGlyph[ 8 ].X = 46;
	pGlyph[ 8 ].Y = 0;
	pGlyph[ 8 ].Advance = 8;
	pGlyph[ 8 ].Bearing = 11;
	pGlyph[ 8 ].Width = 7;
	pGlyph[ 8 ].Height = 11;
	pGlyph[ 8 ].pNext = &pGlyph[ 9 ];

	pGlyph[ 9 ].Character = 'o';
	pGlyph[ 9 ].X = 10;
	pGlyph[ 9 ].Y = 57;
	pGlyph[ 9 ].Advance = 8;
	pGlyph[ 9 ].Bearing = 8;
	pGlyph[ 9 ].Width = 7;
	pGlyph[ 9 ].Height = 8;
	pGlyph[ 9 ].pNext = NULL;

	if( FONT_Create( pTestImage, pGlyph, &pFont ) != 0 )
	{
		VID_SetVideoMode( VGA_TEXT_MODE );

		printf( "Failed to create font\n" );

		getch( );

		__djgpp_nearptr_disable( );
	}

	TEXT_DrawString( 10, 20, "Testing Font", pFont );

	getch( );

	FONT_Destroy( &pFont );

	IMG_Destroy( &pTestImage );

	VID_SetVideoMode( VGA_TEXT_MODE );

	printf( "Show's over\n" );

	getch( );

	__djgpp_nearptr_disable( );

	return 0;
}

