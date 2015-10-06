/*******************************************************************************
   Copyright (C) 2015 Dario Oliveri
   See copyright notice in LICENSE.md
*******************************************************************************/
#pragma once
#include "../BadeTextureManager.hpp"
#include "../BadeStdVector.hpp"
#include "GL3Texture.hpp"

namespace Bade {
	
	class InterleavedRenderer;
	
namespace GL3 {
	
	using namespace std;
	
	/** The texture loading interface is highly incomplete, it just serves
		as proof of concept for now.*/
	class GL3TextureManager: public TextureManager{ //TODO: REFACTORING: TextureManager<GL3Texture>
		
		StdVector< GL3Texture>	referencedTextures;
		StdQueue< GL3Texture*>	streamRequests;
		
		ResourceQueuePtr 		resourceLoader;
		ImageManagerPtr			imageManager;
		
	public:
	
		GL3TextureManager(	ResourceQueuePtr	loader,
							ImageManagerPtr		imageManager);
	
		virtual TexturePtr getTexture( 	BitmapImagePtr & image,
										bool mipmaps = true) = 0;

		virtual void reloadTexture( BitmapImagePtr & image,
									TexturePtr & texture) = 0;
	
		virtual TexturePtr  clone( TexturePtr & texture) override;

		virtual SamplerPtr  clone( SamplerPtr & sampler) override;

		virtual SamplerPtr 	getSampler( FilteringMode 		filter,
										TextureWrap			wrap,
										float 				anisotropy) const
										override;
			
		virtual void freeUnusedTextures() override;
		
	private:
	
		u32 allocateTexture();
	};
} // namespace GL3
} // namespace Bade