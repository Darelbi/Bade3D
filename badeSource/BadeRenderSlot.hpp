/*******************************************************************************
   Copyright (C) 2015 Dario Oliveri
   See copyright notice in LICENSE.md
*******************************************************************************/
#pragma once
#include "BadeForwards.hpp"
#include "BadeStdVector.hpp"

namespace Bade {

	class BADE_API RenderSlot{
		
		StdVector< TexturePtr>	textureSlots;
		StdVector< UniformPtr>	uniformSlots;
		u8						rangeMin;
		u8					 	rangeMax;
		bool					optimized;
		
	public:
	
		/** Performance hint, if "unitNumber" for textures is within
			range (inclusive) adding a texture is very fast.*/
		setTextureUnitsRange( u8 min, u8 max);
	
		/** Add a texture to corresponding texture unit. It is asserted
			that you do not exceed Configuration::textureUnits value.*/
		addTexture( TexturePtr && texture, u8 unitNumber);
		
		/** Performance hint, if "unitNumber" for Uniforms is within
			range (inclusive) adding a Uniform is very fast.*/
		setUniformUnitsRange( u8 min, u8 max);
		
		/** Add a Uniform to corresponding uniform unit. It is asserted
			that you do not exceed Configuration::uniformUnits value.*/
		addUniform( UniformPtr && texture, u8 unitNumber);

	};
} // namespace Bade