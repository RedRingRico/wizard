#ifndef __WIZARD_MATRIX4X4_H__
#define __WIZARD_MATRIX4X4_H__

#include <Vector4.h>

struct MATRIX4X4
{
	float M00, M01, M02, M03;
	float M10, M11, M12, M13;
	float M20, M21, M22, M23;
	float M30, M31, M32, M33;
};

void MAT44_Identity( struct MATRIX4X4 *p_pSelf );

void MAT44_MultiplyM44_M44( struct MATRIX4X4 *p_pLeft,
	struct MATRIX4X4 *p_pRight, struct MATRIX4X4 *p_pOut );
void MAT44_MultiplyM44_V4( struct MATRIX4X4 *p_pMatrix,
	struct VECTOR4 *p_pVector, struct VECTOR4 *p_pOut );

void MAT44_RotateY( float p_Angle, struct MATRIX4X4 *p_pMatrix );

#endif /* __WIZARD_MATRIX4X4_H__ */

