#include <Video.h>
#include <dos.h>
#include <string.h>

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

void VID_ClearScreen( unsigned char p_Colour )
{
	memset( g_pVGA, p_Colour , SCREEN_WIDTH * SCREEN_HEIGHT );
}

