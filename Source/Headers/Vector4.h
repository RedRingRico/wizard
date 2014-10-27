#ifndef __WIZARD_VECTOR4_H__
#define __WIZARD_VECTOR4_H__

typedef struct VECTOR4
{
	float X;
	float Y;
	float Z;
	float W;
};

void VEC4_Add( struct VECTOR4 *p_pLeft, struct VECTOR4 *p_pRight,
	struct VECTOR4 *p_pOut );

#endif /* __WIZARD_VECTOR4_H__ */

