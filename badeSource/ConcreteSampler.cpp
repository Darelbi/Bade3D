/*******************************************************************************
   Copyright (C) 2014-2015 Dario Oliveri
   See copyright notice in LICENSE.md
*******************************************************************************/
#include "ConcreteSampler.hpp"

namespace Bade{
	
	FilteringMode ConcreteSampler::getFilteringMode() const{
		return FilteringMode::Bilinear;
	}

	TextureWrap ConcreteSampler::getTextureWrap() const{
		return TextureWrap::Clamp;
	}

	float ConcreteSampler::getAnisotropy() const{
		return 0;
	}
	
} // namespace Bade