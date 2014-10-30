#ifndef __WIZARD_IMAGE_H__
#define __WIZARD_IMAGE_H__

#include <stddef.h>

struct IMAGE
{
	unsigned short	Width;
	unsigned short	Height;
	unsigned char	*pData;
};

int IMG_Create( unsigned short p_Width, unsigned short p_Height,
	struct IMAGE **p_ppImage );
void IMG_Destroy( struct IMAGE **p_ppImage );

void IMG_Draw( unsigned short p_X, unsigned short p_Y,
	struct IMAGE *p_pImage );

void IMG_DrawSub( unsigned short p_X, unsigned short p_Y,
	unsigned short p_XOffset, unsigned short p_YOffset, unsigned short p_Width,
	unsigned short p_Height, struct IMAGE *p_pImage );

void IMG_DrawTransparent( unsigned short p_X, unsigned short p_Y,
	struct IMAGE *p_pImage );

void IMG_DrawSubTransparent( unsigned short p_X, unsigned short p_Y,
	unsigned short p_XOffset, unsigned short p_YOffset, unsigned short p_Width,
	unsigned short p_Height, struct IMAGE *p_pImage );

#endif /* __WIZARD_IMAGE_H__ */

