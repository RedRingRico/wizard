#ifndef __WIZARD_BITMAP_H__
#define __WIZARD_BITMAP_H__

#include <Bitmap.h>
#include <Image.h>

#pragma pack( 1 )

struct BITMAP_HEADER
{
	char	Type[ 2 ];
	int		Size;
	int		Reserved;
	int		Offset;
	int		HeaderSize;
	int		Width;
	int		Height;
	short	Planes;
	short	BitsPerPixel;
	int		Compression;
	int		SizeImage;
	int		XPixelsPerMetre;
	int		YPixelsPerMetre;
	int		ColoursUsed;
	int		ColoursImportant;
};

#pragma pack( )

int BMP_Load( const char *p_pFileName, struct IMAGE **p_ppImage );

#endif /* __WIZARD_BITMAP_H__ */

