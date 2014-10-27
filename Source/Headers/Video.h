#ifndef __WIZARD_VIDEO_H__
#define __WIZARD_VIDEO_H__

#define VIDEO_INT			0x10
#define WRITE_DOT			0x0C
#define SET_MODE			0x00
#define VGA_COLOUR_MODE_256	0x13
#define VGA_TEXT_MODE		0x03
#define SCREEN_WIDTH		320
#define SCREEN_HEIGHT		200
#define VGA_BASE_ADDRESS	0xA0000

void VID_InitialiseVideo( int p_BaseAddress );
void VID_SetVideoMode( unsigned char p_Mode );
void VID_PlotPixel( int p_X, int p_Y, unsigned char p_Colour );
void VID_ClearScreen( unsigned char p_Colour );

#endif /* __WIZARD_VIDEO_H__ */

