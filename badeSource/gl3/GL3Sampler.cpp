/*******************************************************************************
   Copyright (C) 2015 Dario Oliveri
   See copyright notice in LICENSE.md
*******************************************************************************/
#include "GL3Sampler.hpp"
#include "../BadeNumeric.hpp"

namespace Bade {
namespace GL3 {

GL3Sampler::GL3Sampler( FilteringMode f, TextureWrap w, float aniso){
	filteringMode = f;
	textureWrap = w;
	anisotropicLevel = aniso;
}

FilteringMode GL3Sampler::getFilteringMode() const{
	return filteringMode;
}
		
TextureWrap GL3Sampler::getTextureWrap() const{
	return textureWrap;
}

float GL3Sampler::getAnisotropy() const{
	return anisotropicLevel;
}

// Aniso 1 Clamp		0
// Aniso 1 Wrap			1
// Aniso 2 Clamp		2
// Aniso 2 Wrap			3
// Aniso 4 Clamp 		4
// Aniso 4 Wrap			5
// Aniso 8 Clamp		6
// Aniso 8 Wrap			7
// Aniso 16 Clamp		8
// Aniso 16 Wrap		9
// Nearest Clamp		10
// Nearest Wrap			11
// Bilinear Clamp		12
// Bilinear Wrap		13
// Trilinear Clamp		14
// Trilinear Wrap		15

u8 samplerHashCode( FilteringMode filteringMode,
					TextureWrap textureWrap, 
					float anisotropicLevel)
{
	float aniso = clamp( anisotropicLevel, 1.f, 16.f);
	int exp;
	nearestPowerOf2( aniso, exp);

	u8 hashCode;
	if( filteringMode == FilteringMode::Anisotropic)
		hashCode = exp*2;
	else{
		hashCode = 10;
		switch( filteringMode){
			case FilteringMode::Bilinear:  hashCode+=2; break;
			case FilteringMode::Trilinear: hashCode+=4; break;
			default: break;
		}
	}
	
	if( textureWrap == TextureWrap::Repeat)
		hashCode++;
	
	return hashCode;
}

//perfect hash function
u8 GL3Sampler::hashCode() const{
	return samplerHashCode(	getFilteringMode(),
							getTextureWrap(),
							getAnisotropy());
}

} // namespace GL3
} // namespace Bade