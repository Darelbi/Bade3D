/*******************************************************************************
   Copyright (C) 2015 Dario Oliveri
   See copyright notice in LICENSE.md
*******************************************************************************/
#pragma once
#include "../BadeShaderManager.hpp"
#include "../BadeStdVector.hpp"
#include "../ConcreteShaderOptions.hpp"


namespace Bade {
	
namespace GL3 {

	class GL3TextureManager: public TextureManager{	
	
	StdVector< ConcreteShaderOptions>	shaderOptions;
	
	public:
	
	};
} // namespace GL3
} // namespace Bade
	