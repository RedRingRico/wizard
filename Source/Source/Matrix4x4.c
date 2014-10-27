#include <Matrix4x4.h>
#include <math.h>

void MAT44_Identity( struct MATRIX4X4 *p_pSelf )
{
	p_pSelf->M00 = p_pSelf->M11 = p_pSelf->M22 = p_pSelf->M33 = 1.0f;

	p_pSelf->M01 = p_pSelf->M02 = p_pSelf->M03 =
	p_pSelf->M10 = p_pSelf->M12 = p_pSelf->M13 =
	p_pSelf->M20 = p_pSelf->M21 = p_pSelf->M23 =
	p_pSelf->M30 = p_pSelf->M31 = p_pSelf->M32 = 0.0f;
}

void MAT44_MultiplyM44_M44( struct MATRIX4X4 *p_pLeft,
	struct MATRIX4X4 *p_pRight, struct MATRIX4X4 *p_pOut )
{
	p_pOut->M00 =	( p_pLeft->M00 * p_pRight->M00 ) +
					( p_pLeft->M01 * p_pRight->M10 ) +
					( p_pLeft->M02 * p_pRight->M20 ) +
					( p_pLeft->M03 * p_pRight->M30 );
	
	p_pOut->M01 =	( p_pLeft->M00 * p_pRight->M01 ) +
					( p_pLeft->M01 * p_pRight->M11 ) +
					( p_pLeft->M02 * p_pRight->M21 ) +
					( p_pLeft->M03 * p_pRight->M31 );
	
	p_pOut->M02 =	( p_pLeft->M00 * p_pRight->M02 ) +
					( p_pLeft->M01 * p_pRight->M12 ) +
					( p_pLeft->M02 * p_pRight->M22 ) +
					( p_pLeft->M03 * p_pRight->M32 );

	p_pOut->M03 =	( p_pLeft->M00 * p_pRight->M03 ) +
					( p_pLeft->M01 * p_pRight->M13 ) +
					( p_pLeft->M02 * p_pRight->M23 ) +
					( p_pLeft->M03 * p_pRight->M33 );

	p_pOut->M10 =	( p_pLeft->M10 * p_pRight->M00 ) +
					( p_pLeft->M11 * p_pRight->M10 ) +
					( p_pLeft->M12 * p_pRight->M20 ) +
					( p_pLeft->M13 * p_pRight->M30 );

	p_pOut->M11 =	( p_pLeft->M10 * p_pRight->M01 ) +
					( p_pLeft->M11 * p_pRight->M11 ) +
					( p_pLeft->M12 * p_pRight->M21 ) +
					( p_pLeft->M13 * p_pRight->M31 );
	
	p_pOut->M12 =	( p_pLeft->M10 * p_pRight->M02 ) +
					( p_pLeft->M11 * p_pRight->M12 ) +
					( p_pLeft->M12 * p_pRight->M22 ) +
					( p_pLeft->M13 * p_pRight->M32 );

	p_pOut->M13 =	( p_pLeft->M10 * p_pRight->M03 ) +
					( p_pLeft->M11 * p_pRight->M13 ) +
					( p_pLeft->M12 * p_pRight->M23 ) +
					( p_pLeft->M13 * p_pRight->M33 );
	
	p_pOut->M20 =	( p_pLeft->M20 * p_pRight->M00 ) +
					( p_pLeft->M21 * p_pRight->M10 ) +
					( p_pLeft->M22 * p_pRight->M20 ) +
					( p_pLeft->M23 * p_pRight->M30 );
	
	p_pOut->M21 =	( p_pLeft->M20 * p_pRight->M01 ) +
					( p_pLeft->M21 * p_pRight->M11 ) +
					( p_pLeft->M22 * p_pRight->M21 ) +
					( p_pLeft->M23 * p_pRight->M31 );
	
	p_pOut->M22 =	( p_pLeft->M20 * p_pRight->M02 ) +
					( p_pLeft->M21 * p_pRight->M12 ) +
					( p_pLeft->M22 * p_pRight->M22 ) +
					( p_pLeft->M23 * p_pRight->M32 );

	p_pOut->M23 =	( p_pLeft->M20 * p_pRight->M03 ) +
					( p_pLeft->M21 * p_pRight->M13 ) +
					( p_pLeft->M22 * p_pRight->M23 ) +
					( p_pLeft->M23 * p_pRight->M33 );
	
	p_pOut->M30 =	( p_pLeft->M30 * p_pRight->M00 ) +
					( p_pLeft->M31 * p_pRight->M10 ) +
					( p_pLeft->M32 * p_pRight->M20 ) +
					( p_pLeft->M33 * p_pRight->M30 );

	p_pOut->M31 =	( p_pLeft->M30 * p_pRight->M01 ) +
					( p_pLeft->M31 * p_pRight->M11 ) +
					( p_pLeft->M32 * p_pRight->M21 ) +
					( p_pLeft->M33 * p_pRight->M31 );

	p_pOut->M32 =	( p_pLeft->M30 * p_pRight->M02 ) +
					( p_pLeft->M31 * p_pRight->M12 ) +
					( p_pLeft->M32 * p_pRight->M22 ) +
					( p_pLeft->M33 * p_pRight->M32 );

	p_pOut->M33 =	( p_pLeft->M30 * p_pRight->M03 ) +
					( p_pLeft->M31 * p_pRight->M13 ) +
					( p_pLeft->M32 * p_pRight->M23 ) +
					( p_pLeft->M33 * p_pRight->M33 );
}

void MAT44_MultiplyM44_V4( struct MATRIX4X4 *p_pMatrix,
	struct VECTOR4 *p_pVector, struct VECTOR4 *p_pOut )
{
	p_pOut->X = ( p_pMatrix->M00 * p_pVector->X ) +
				( p_pMatrix->M10 * p_pVector->Y ) +
				( p_pMatrix->M20 * p_pVector->Z ) +
				( p_pMatrix->M30 * p_pVector->W );
	
	p_pOut->Y = ( p_pMatrix->M01 * p_pVector->X ) +
				( p_pMatrix->M11 * p_pVector->Y ) +
				( p_pMatrix->M21 * p_pVector->Z ) +
				( p_pMatrix->M31 * p_pVector->W );
	
	p_pOut->Z = ( p_pMatrix->M02 * p_pVector->X ) +
				( p_pMatrix->M12 * p_pVector->Y ) +
				( p_pMatrix->M22 * p_pVector->Z ) +
				( p_pMatrix->M32 * p_pVector->W );
	
	p_pOut->W = ( p_pMatrix->M03 * p_pVector->X ) +
				( p_pMatrix->M13 * p_pVector->Y ) +
				( p_pMatrix->M23 * p_pVector->Z ) +
				( p_pMatrix->M33 * p_pVector->W );
}

void MAT44_RotateY( float p_Angle, struct MATRIX4X4 *p_pMatrix )
{
	float Sin = 0.0f;
	float Cos = 0.0f;

	Sin = sinf( p_Angle );
	Cos = cosf( p_Angle );

	p_pMatrix->M11 = 1.0f;

	/*
	 * ^ (X)  = -sin cos
	 * |
	 * |
	 * ----> (Z) = cos sin
	 */

	p_pMatrix->M00 = -Sin;
	p_pMatrix->M02 = Cos;

	p_pMatrix->M20 = Cos;
	p_pMatrix->M22 = Sin;


	p_pMatrix->M01 = p_pMatrix->M03 = p_pMatrix->M13 = p_pMatrix->M23 =
	p_pMatrix->M10 = p_pMatrix->M12 = p_pMatrix->M21 =
	p_pMatrix->M30 = p_pMatrix->M31 = p_pMatrix->M32 = 0.0f;
}

