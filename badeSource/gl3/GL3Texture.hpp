/*******************************************************************************
   Copyright (C) 2015 Dario Oliveri
   See copyright notice in License.md
*******************************************************************************/
#pragma once
#include "../PortableGraphics.hpp"
#include "../BadeTexture.hpp"

namespace Bade {
namespace GL3 {
	
class GL3Texture: public Texture{
	
public:
	
	bool isARenderTarget() const override;
		
	bool hasMipmaps() const override;
	
	InternalFormat getInternalFormat() const override;
	
	u32 getWidth() const override;
		
	u32 getHeight() const override;

	u32				width;
	u32				height;
	NativeHandle	nativeHandle;
	bool    		mipmaps;
	InternalFormat  format;
};	
	
} // namespace GL3
} // namespace Bade