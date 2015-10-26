/*******************************************************************************
   Copyright (C) 2015 Dario Oliveri
   See copyright notice in LICENSE.md
*******************************************************************************/
#include "BadeNumeric.hpp"
#include <cmath>

namespace Bade{

float nearestPowerOf2( float n){

    int exponent;
	// significand * 2^exponent = n
	// 0.500000000 * 2^4        = 8
	// 0.500000000 * 2^-2        = 1/8
	
	return nearestPowerOf2(n, exponent);
}

float nearestPowerOf2( float n, int & exp){
	
	const float significand = std::frexp( n, &exp);
	const float treshold = 0.75f;
	
	exp = significand <= treshold? exp-1 : exp;

	return std::ldexp( 1.0, exp);
}

float clamp( float val, float min, float max ){
	return val<min? min:
			val>max? max:
						 val;
}

} // namespace Bade