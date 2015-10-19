/*******************************************************************************
   Copyright (C) 2015 Dario Oliveri
   See copyright notice in LICENSE.md
*******************************************************************************/
#pragma once
#include "BadeVertexAttribute.hpp"

namespace Bade {
	
	enum struct TextureType: u8{
		Texture2D,
		Cubemap
	};
	
	/** Options for generating a shader program. */
	class BADE_API ShaderOptions: public ManagedEntity{
		
	public:
	
		/** Inside shaders normalized integer values becomes fixed point
			floats in range [-1,1] (signed integers) or [0,1] (unsigned)*/
		virtual void addVertexAttribute( 
							const char * 	name, 
							VertexAttribute attr,
							bool 			normalized) = 0;
		
		virtual void addTextureHook( 
							const char * 	name, 
							TextureType 	type, 
							u8 				textureUnit ) = 0;
						
		/** Once used to compile a shader, the shader Options becomes
			immutable and this function will return true.*/
		virtual bool isLocked() = 0;
	};
} // namespace Bade