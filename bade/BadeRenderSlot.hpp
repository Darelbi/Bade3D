/*******************************************************************************
   Copyright (C) 2015 Dario Oliveri
   See copyright notice in LICENSE.md
*******************************************************************************/
#pragma once
#include "BadeForwards.hpp"
#include "BadeStdVector.hpp"

namespace Bade {

	class BADE_API RenderSlot{
		
		u8						rangeMin;
		u8					 	rangeMax;
		bool					optimized;
		
	public:
	
		// a Shader object. You can generate it with the ShaderManager
		ShaderPtr				programSlot;
	
		// values after Configuration::textureUnits are ignored
		StdVector< TexturePtr>	textureSlots;
		
		// values after Configuration::uniformUnits are ignored
		StdVector< UniformPtr>	uniformSlots;
	};
} // namespace Bade