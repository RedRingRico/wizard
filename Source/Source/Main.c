#include <stdio.h>
#include <conio.h>
#include <GitVersion.h>

int main( int p_Argc, char **p_ppArgv )
{
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

	getch( );

	return 0;
}

