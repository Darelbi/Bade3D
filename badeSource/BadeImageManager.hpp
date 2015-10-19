/*******************************************************************************
   Copyright (C) 2015 Dario Oliveri
   See copyright notice in LICENSE.md
*******************************************************************************/
#pragma once
#include "BadeForwards.hpp"

namespace Bade {
	
	class BADE_API ImageManager{
	
	public:
	
		// This method is mostly for testing. I needed a way to load data :)
		virtual BitmapImagePtr loadPPMImage( const char * filename) = 0;
		
		virtual void freeUnusedImages() = 0;
		
		virtual ~ImageManager(){}
		
	};
} // namespace Bade