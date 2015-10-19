/*******************************************************************************
   Copyright (C) 2014-2015 Dario Oliveri
   See copyright notice in LICENSE.md
*******************************************************************************/
#pragma once
#include "BadeSampler.hpp"

namespace Bade{
	
	class BADE_API ConcreteSampler: public Sampler{
		
	public:
	
		FilteringMode getFilteringMode() const override;
		
		TextureWrap getTextureWrap() const override;
		
		float getAnisotropy() const override;
	};
} // namespace Bade