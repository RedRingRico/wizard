#include <Renderer.h>
#include <Video.h>
#include <math.h>

#define SIGN( x )( ( x < 0 ) ? -1 : ( ( x > 0 ) ? 1 : 0 ) )

void REN_DrawLine( int p_X1, int p_Y1, int p_X2, int p_Y2,
	unsigned char p_Colour )
{
	int Index, dX, dY, SdX, SdY, dXAbs, dYAbs, X, Y, pX, pY;

	dX = p_X2 - p_X1;
	dY = p_Y2 - p_Y1;
	dXAbs = abs( dX );
	dYAbs = abs( dY );
	SdX = SIGN( dX );
	SdY = SIGN( dY );
	X = dYAbs >> 1;
	Y = dXAbs >> 1;
	pX = p_X1;
	pY = p_Y1;

	VID_PlotPixelDirect( ( pY << 8 ) + ( pY << 6 ) + pX, p_Colour );

	if( dXAbs > dYAbs )
	{
		for( Index = 0; Index < dXAbs; ++Index )
		{
			Y += dYAbs;
			if( Y >= dXAbs )
			{
				Y -= dXAbs;
				pY += SdY;
			}
			pX += SdX;
			VID_PlotPixel( pX, pY, p_Colour );
		}
	}
	else
	{
		for( Index = 0; Index < dYAbs; ++Index )
		{
			X += dXAbs;
			if( X >= dYAbs )
			{
				X -= dYAbs;
				pX += SdX;
			}
			pY += SdY;
			VID_PlotPixel( pX, pY, p_Colour );
		}
	}
}

