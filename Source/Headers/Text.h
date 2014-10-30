#ifndef __WIZARD_TEXT_H__
#define __WIZARD_TEXT_H__

#include <Font.h>

int TEXT_DrawCharacter( int p_X, int p_Y, char p_Character, int *p_pAdvance, 
	struct FONT *p_pFont );

int TEXT_DrawString( int p_X, int p_Y, const char *p_pString,
	struct FONT *p_pFont );

#endif /* __WIZARD_TEXT_H__ */

