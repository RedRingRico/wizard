#ifndef __WIZARD_VIDEO_H__
#define __WIZARD_VIDEO_H__

#define VIDEO_INT			0x10
#define WRITE_DOT			0x0C
#define SET_MODE			0x00
#define VGA_COLOUR_MODE_256	0x13
#define VGA_TEXT_MODE		0x03
#define SCREEN_WIDTH		320
#define SCREEN_HEIGHT		200
#define PALETTE_INDEX		0x03C8
#define PALETTE_DATA		0x03C9
#define VGA_BASE_ADDRESS	0xA0000

struct VIDEO_INFORMATION
{
	int				VGAAddress;
	unsigned short	Width;
	unsigned short	Height;
};

void VID_InitialiseVideo( int p_BaseAddress );
void VID_SetVideoMode( unsigned char p_Mode );
void VID_GetVideoInformation( struct VIDEO_INFORMATION *p_pVideoInformation );
void VID_PlotPixelDirect( int p_Offset, unsigned char p_Colour );
void VID_PlotPixel( int p_X, int p_Y, unsigned char p_Colour );
void VID_FillRasterLineOffset( int p_Offset, int p_Width,
	unsigned char *p_pColourData );
void VID_FillRasterLineXY( int p_X, int p_Y, int p_Width,
	unsigned char *p_pColourData );
void VID_FillRasterLineTransparentOffset( int p_Offset, int p_Width,
	unsigned char *p_pColourData );
void VID_FillRasterLineTransparentXY( int p_X, int p_Y, int p_Width,
	unsigned char *p_pColourData );
void VID_ClearScreen( unsigned char p_Colour );
void VID_SetPaletteData( unsigned char *p_pPalette, int p_PaletteCount );
int VID_LoadPaletteData( const char *p_pFileName );

#endif /* __WIZARD_VIDEO_H__ */

