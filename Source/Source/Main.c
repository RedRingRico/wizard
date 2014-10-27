#include <stdio.h>
#include <conio.h>
#include <GitVersion.h>
#include <Video.h>
#include <sys/nearptr.h>
#include <stdlib.h>

int main( int p_Argc, char **p_ppArgv )
{
	unsigned short VGARow, VGAColumn;
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

	VID_SetVideoMode( VGA_TEXT_MODE );

	printf( "Show's over\n" );

	getch( );

	__djgpp_nearptr_disable( );

	return 0;
}

