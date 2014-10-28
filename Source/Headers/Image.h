#ifndef __WIZARD_IMAGE_H__
#define __WIZARD_IMAGE_H__

#include <stddef.h>

struct IMAGE
{
	/* The palette will be replaced with an ID to a palette, which will allow
	 * for a minimal amount of palette switching
	 * Each bank holds 96 bytes ( RGB ) 96 / 3 == 32
	 */
	unsigned char	Palette[ 8 ][ 96 ];
	/* The PaletteMask is defined as follows:
	 * Bit	Range
	 * ------------
	 * 0	0-31
	 * 1	32-63
	 * 2	64-95
	 * 3	96-127
	 * 4	128-159
	 * 5	160-191
	 * 6	192-223
	 * 7	223-256
	 * Depending on which palette bits are set, they are copied when needed
	 * This means that if only one colour is set, values 1-31 wll contain
	 * garbage
	 */
	unsigned char	PaletteMask;
	/* The punch through colour is defined as the value not visible (such as a
	 * background for a sprite)
	 */
	unsigned char	PunchThroughColour;
	unsigned short	Width;
	unsigned short	Height;
	unsigned char	*pData;
};

int IMG_Create( unsigned char *p_pPalette, unsigned short p_PaletteCount,
	unsigned short p_Width, unsigned short p_Height, struct IMAGE **p_ppImage );
void IMG_Destroy( struct IMAGE **p_ppImage );

void IMG_Draw( unsigned short p_X, unsigned short p_Y, unsigned short p_Width,
	unsigned short p_Height, struct IMAGE *p_pImage );

#endif /* __WIZARD_IMAGE_H__ */

