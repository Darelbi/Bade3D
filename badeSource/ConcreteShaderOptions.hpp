/*******************************************************************************
   Copyright (C) 2015 Dario Oliveri
   See copyright notice in LICENSE.md
*******************************************************************************/
#pragma once
#include "BadeShaderOptions.hpp"
#include "BadeStdVector.hpp"

namespace Bade {
	
	struct VertexOption{
		const char * 	name;
		VertexAttribute attr;
		bool			normalized;
	};
	
	struct TextureOption{
		const char * 	name;
		TextureType		type;
		u8				textureUnit;
	};
	
	/** Options for generating a shader program. */
	class BADE_API ConcreteShaderOptions: public ShaderOptions{
		
		StdVector< VertexOption>	vertexOptions;
		StdVector< TextureOption>	textureOptions;
		bool						locked = false;

	public:

		ConcreteShaderOptions(){}

		/** Inside shaders normalized integer values becomes fixed point
			floats in range [-1,1] (signed integers) or [0,1] (unsigned)*/
		void addVertexAttribute( 
							const char * 	name, 
							VertexAttribute attr,
							bool 			normalized) override;

		void addTextureHook( 
							const char * 	name, 
							TextureType 	type, 
							u8 				textureUnit ) override;
							
		void lock();
							
		bool isLocked() override { return locked;}

		bool sameString( const char * str1, const char* str2);
							
		inline void grab() { referenceIncrement();}
		
	private:
	
		void searchForVertexName( const char * name);
	};
} // namespace Bade