#include <Video.h>
#include <dos.h>
#include <string.h>

static unsigned char *g_pVGA;

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

void VID_PlotPixel( int p_X, int p_Y, unsigned char p_Colour )
{
	g_pVGA[ p_Y * SCREEN_WIDTH + p_X ] = p_Colour;
}

void VID_ClearScreen( unsigned char p_Colour )
{
	memset( g_pVGA, p_Colour , SCREEN_WIDTH * SCREEN_HEIGHT );
}

