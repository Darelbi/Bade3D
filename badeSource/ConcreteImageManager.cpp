/*******************************************************************************
   Copyright (C) 2015 Dario Oliveri
   See copyright notice in LICENSE.md
*******************************************************************************/
#include "ConcreteImageManager.hpp"
#include "BadeBitmapImage.hpp"
#include "PPMLoader.hpp"

namespace Bade {
	// This method is mostly for testing. I needed a way to load data :)
	BitmapImagePtr ConcreteImageManager::
					loadPPMImage( const char * filename){
						
		auto a = Deprecated::LoadPPM_P3( images, filename);
		
		images.shallowCopyAsEntity(a);
		
		return a;
	}
	
	void ConcreteImageManager::freeUnusedImages(){
		images.collectSome( images.size(), []( BitmapImage&){} );
		images.shrinkToFit();
	}
} // namespace Bade