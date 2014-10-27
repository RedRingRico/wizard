#include <stdio.h>
#include <conio.h>
#include <GitVersion.h>
#include <Video.h>
#include <Renderer.h>
#include <sys/nearptr.h>
#include <stdlib.h>
#include <Vector4.h>
#include <Matrix4x4.h>

int main( int p_Argc, char **p_ppArgv )
{
	unsigned short VGARow, VGAColumn;
	unsigned int Index;
	struct VECTOR4 Vertex0, Vertex1, Vertex2;
	struct VECTOR4 Vertex0T, Vertex1T, Vertex2T;
	struct MATRIX4X4 WorldMatrix, RotationMatrix, ViewMatrix, ProjectionMatrix;
	float Rotation = 0.0f;

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

	getch( );

	VID_SetVideoMode( VGA_TEXT_MODE );

	printf( "Show's over\n" );

	getch( );

	__djgpp_nearptr_disable( );

	return 0;
}

