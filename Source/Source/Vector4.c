#include <Vector4.h>

void VEC4_Add( struct VECTOR4 *p_pLeft, struct VECTOR4 *p_pRight,
	struct VECTOR4 *p_pOut )
{
	p_pOut->X = p_pLeft->X + p_pRight->X;
	p_pOut->Y = p_pLeft->Y + p_pRight->Y;
	p_pOut->Z = p_pLeft->Z + p_pRight->Z;
	p_pOut->W = p_pLeft->W + p_pRight->W;
}

