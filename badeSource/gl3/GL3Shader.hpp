/*******************************************************************************
   Copyright (C) 2015 Dario Oliveri
   See copyright notice in LICENSE.md
*******************************************************************************/
#pragma once
#include "../PortableGraphics.hpp"
#include "../BadeShader.hpp"
#include "../BadeStdVector.hpp"
#include "GL3State.hpp"
#include <utility>

namespace Bade {
namespace GL3 {
	
	class BADE_API GL3Shader: public Shader{
		

	public: 
	
		
		bool isTextureUnitUsed( int textureUnit);
		
		StdVector< GL3TextureUnit>	textures;
		
		NativeHandle				program = 0;
	};

} // namespace GL3
} // namespace Bade