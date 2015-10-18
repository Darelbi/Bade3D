/*******************************************************************************
   Copyright (C) 2015 Dario Oliveri
   See copyright notice in LICENSE.md
*******************************************************************************/
#pragma once
#include "BadeImageManager.hpp"
#include "ManageEngine.hpp"

namespace Bade {
	
	class BADE_API ConcreteImageManager: public ImageManager{
	
		ManageEngine< BitmapImage> images;
		
	public:
	
		ConcreteImageManager(){ }
	
		// This method is mostly for testing. I needed a way to load data :)
		BitmapImagePtr loadPPMImage( const char * filename) override;
		
		void freeUnusedImages() override;
	
	};
} // namespace Bade