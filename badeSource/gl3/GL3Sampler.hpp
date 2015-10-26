/*******************************************************************************
   Copyright (C) 2015 Dario Oliveri
   See copyright notice in LICENSE.md
*******************************************************************************/
#pragma once
#include "../BadeSampler.hpp"
#include "../PortableGraphics.hpp"

namespace Bade {
namespace GL3{
	
	u8 samplerHashCode( FilteringMode f, TextureWrap w, float aniso);
	
	class GL3Sampler: public Sampler{
	
	public:
	
		GL3Sampler( FilteringMode f, TextureWrap w, float aniso);
	
		FilteringMode getFilteringMode() const override;
		
		TextureWrap getTextureWrap() const override;
		
		float getAnisotropy() const override;
		
		u8 	hashCode() const;
	
		NativeHandle	nativeHandle;
		FilteringMode	filteringMode;
		TextureWrap 	textureWrap;
		float 			anisotropicLevel;
	};	
	
} // namespace GL3
} // namespace Bade