#ifndef __WIZARD_FONT_H__
#define __WIZARD_FONT_H__

#include <Image.h>

/* Only fixed-width fonts will be supported initially */

#pragma pcak( 1 )
struct GLYPH
{
	int				X;
	int				Y;
	int				Advance;
	int				Bearing;
	int				Width;
	int				Height;
	char			Character;
	struct GLYPH	*pNext;
};

struct FONT
{
	struct IMAGE *pImage;
	struct GLYPH *pGlyphSet;
};

#pragma pack( )

int FONT_AddGlyph( struct GLYPH *p_pGlyph, struct GLYPH *p_pGlyphSet );

int FONT_Create( struct IMAGE *p_pImage, struct GLYPH *p_pGlyphSet,
	struct FONT **p_ppFont );
void FONT_Destroy( struct FONT **p_ppFont );

#endif /* __WIZARD_FONT_H__ */

