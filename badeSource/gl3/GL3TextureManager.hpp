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
		ProxyPtr					asyncProxy;
		
	public:
	
		GL3TextureManager( ProxyPtr proxy);
	
		TexturePtr getTexture( 	BitmapImagePtr & image,
								bool mipmaps) override;
										
		void reloadTexture( BitmapImagePtr image,
							TexturePtr & texture) override;

		TexturePtr  shallowCopy( TexturePtr & texture) override;

		SamplerPtr 	getSampler( FilteringMode 		filtering,
								TextureWrap			wrap,
								float 				anisotropy) const
								override;
										
		TextureSlotPtr getTextureSlot( 	u8 textureUnit,
										TexturePtr & texture,
										SamplerPtr & sampler) override;
		
		void setTextureSlot( 	RenderSlot & slot,
								TextureSlotPtr & textureSlot) override;
									 
		TextureSlotPtr shallowCopy( TextureSlotPtr & textureSlot)  override;

		void freeUnusedTextures() override;
	};
} // namespace GL3
} // namespace Bade