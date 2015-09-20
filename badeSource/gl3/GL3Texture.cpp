/*******************************************************************************
   Copyright (C) 2015 Dario Oliveri
   See copyright notice in License.md
*******************************************************************************/
#include "../Visitors.hpp"
#include "GL3Texture.hpp"

namespace Bade {
namespace GL3 {
	

	void GL3Texture::accept( TextureVisitor & visitor)  {
		visitor.visit(*this);
	}
	
	bool GL3Texture::isARenderTarget() const  {
		return false;
	}
		
	bool GL3Texture::hasMipmaps() const {
		return mipmaps;
	}
	
	InternalFormat GL3Texture::getInternalFormat() const {
		return format;		
	}

} // namespace GL3
} // namespace Bade