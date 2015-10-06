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
	
	inline void grab(){ referenceIncrement(); }

	GL3Texture( const GL3Texture & other) = default;
	GL3Texture& operator =( const GL3Texture & other) = default;
	
	virtual bool isARenderTarget() const override;
		
	virtual bool hasMipmaps() const override;
	
	virtual InternalFormat getInternalFormat() const override;

	NativeHandle	nativeHandle;
	u32				engineHandle;
	bool    		mipmaps;
	InternalFormat  format;
};	
	
} // namespace GL3
} // namespace Bade