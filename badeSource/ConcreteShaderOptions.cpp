/*******************************************************************************
   Copyright (C) 2015 Dario Oliveri
   See copyright notice in LICENSE.md
*******************************************************************************/
#include "Assert.hpp"
#include "ConcreteShaderOptions.hpp"
#include <cstring>

namespace Bade {
	
	void ConcreteShaderOptions::addVertexAttribute( 
						const char * 	name, 
						VertexAttribute attr,
						bool 			normalized)
	{
		searchForVertexName(name);
			
		for( TextureOption & elem: textureOptions)
			if( sameString( elem.name, name) )
				assert( false && "same name already used as texture hook" );
		
		vertexOptions.emplace_back( VertexOption{ name, attr, normalized});
	}

	void ConcreteShaderOptions::addTextureHook( 
						const char * 	name, 
						TextureType 	type, 
						u8 				textureUnit )
	{
		searchForVertexName(name);
		
		for( TextureOption & elem: textureOptions){
			if( sameString( elem.name, name) )
				assert( false && "same name on texture hook");
			
			if( elem.textureUnit == textureUnit)
				assert( false && "same texture unit reused");
		}
		
		textureOptions.emplace_back( TextureOption{ name, type, textureUnit});
	}
	
	void ConcreteShaderOptions::searchForVertexName( const char * name){
		assert( locked == false);
		
		for( VertexOption & elem : vertexOptions)
			if( sameString( elem.name, name) )
				assert( false && "same name already used as vertex attribute");
	}
	
	void ConcreteShaderOptions::lock(){
		assert( textureOptions.size()!=0 && vertexOptions.size()!=0);
		locked = true;
	}
	
	bool ConcreteShaderOptions::sameString( const char * str1, const char* str2){
		return std::strcmp(str1, str2) == 0;
	}
} // namespace Bade