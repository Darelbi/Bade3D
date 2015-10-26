/*******************************************************************************
   Copyright (C) 2015 Dario Oliveri
   See copyright notice in LICENSE.md
*******************************************************************************/
#pragma once
#include "../BadeTextureManager.hpp"
#include "../BadeStdVector.hpp"
#include "../ManageEngine.hpp"
#include "GL3Forwards.hpp"


namespace Bade {	
namespace GL3 {
	
	class GL3Texture;
	using namespace std;
	
	/** The texture loading interface is highly incomplete, it just serves
		as proof of concept for now.*/
	class GL3TextureManager: public TextureManager{
		
		ManageEngine< GL3Texture>	textures;
		ManageEngine< GL3Sampler>	samplers;
	
		GL3SamplerPtr				samplersCache[16];
		
		ProxyPtr					asyncProxy;
		
		void createSampler( u8 idx, FilteringMode f, TextureWrap w, float a);
		void createSamplers();
		void destroySamplers();
		
	public:
	
		GL3TextureManager( ProxyPtr proxy);
	
		TexturePtr getTexture( 	BitmapImagePtr & image,
								bool mipmaps) override;
										
		void reloadTexture( BitmapImagePtr image,
							TexturePtr & texture) override;

		TexturePtr  shallowCopy( TexturePtr & texture) override;

		SamplerPtr 	getSampler( FilteringMode 		filtering,
								TextureWrap			wrap,
								float 				anisotropy)	override;
										
		TextureSlotPtr getTextureSlot( 	u8 textureUnit,
										TexturePtr & texture,
										SamplerPtr & sampler) override;
		
		void setTextureSlot( 	RenderSlot & slot,
								TextureSlotPtr & textureSlot) override;
									 
		TextureSlotPtr shallowCopy( TextureSlotPtr & textureSlot)  override;

		void freeUnusedTextures() override;
		
		~GL3TextureManager();
	};
} // namespace GL3
} // namespace Bade