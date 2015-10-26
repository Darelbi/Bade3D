/*******************************************************************************
   Copyright (C) 2015 Dario Oliveri
   See copyright notice in LICENSE.md
*******************************************************************************/
#include "BadeNumeric.hpp"
#include <cmath>

namespace Bade{

float nearestPowerOf2( float n){

    int exponent;
	const float significand = std::frexp( n, &exponent);
	const float treshold = 0.75f;
	// significand * 2^exponent = n
	// 0.500000000 * 2^4        = 8
	// 0.500000000 * 2^-2        = 1/8
	
	if( significand <= treshold)
		return std::ldexp( 1.0, exponent-1);
	return std::ldexp( 1.0, exponent);
}

float clamp( float val, float min, float max ){
	return val<min? min:
			val>max? max:
						 val;
}

} // namespace Bade