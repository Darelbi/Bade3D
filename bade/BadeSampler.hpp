/*******************************************************************************
   Copyright (C) 2015 Dario Oliveri
   See copyright notice in LICENSE.md
*******************************************************************************/
#pragma once
#include "BadeForwards.hpp"

namespace Bade {
	
	enum struct FilteringMode: u8{
        Nearest,
        Bilinear,
        Trilinear,
		Anisotropic
    };

	enum struct TextureWrap: u8{
        Clamp,
        Repeat
    };
	
	class BADE_API Sampler: public ManagedEntity{
	public:
	
		virtual FilteringMode getFilteringMode() const = 0;
		
		virtual TextureWrap getTextureWrap() const = 0;
		
		virtual float getAnisotropy() const = 0;
	};
} // namespace Bade