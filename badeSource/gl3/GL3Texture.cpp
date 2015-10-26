/*******************************************************************************
   Copyright (C) 2015 Dario Oliveri
   See copyright notice in License.md
*******************************************************************************/
#include "GL3Texture.hpp"

namespace Bade {
namespace GL3 {
	
	bool GL3Texture::isARenderTarget() const  {
		return false;
	}
		
	bool GL3Texture::hasMipmaps() const {
		return mipmaps;
	}
	
	InternalFormat GL3Texture::getInternalFormat() const {
		return format;		
	}
	
	u32 GL3Texture::getWidth() const{
		return width;
	}
		
	u32 GL3Texture::getHeight() const{
		return height;
	}

} // namespace GL3
} // namespace Bade