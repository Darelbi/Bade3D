/*******************************************************************************
   Copyright (C) 2015 Dario Oliveri
   See copyright notice in LICENSE.md
*******************************************************************************/
#include "GL3TextureManager.hpp"
#include "GL3Texture.hpp"
#include "../BadeSampler.hpp"
#include "../BadeTextureSlot.hpp"
#include "../BadeImageManager.hpp"

namespace Bade {
namespace GL3 {

GL3TextureManager::GL3TextureManager(){

}

TexturePtr GL3TextureManager::getTexture( 	BitmapImagePtr & image,
											bool mipmaps){
	return nullptr;
}

void GL3TextureManager::reloadTexture( 	BitmapImagePtr image,
										TexturePtr & texture){

}

TexturePtr GL3TextureManager::shallowCopy( TexturePtr & texture){
	return nullptr;
}

SamplerPtr GL3TextureManager::getSampler( 	FilteringMode 		filtering,
											TextureWrap			wrap,
											float 				anisotropy) const{
	return nullptr;
}

TextureSlotPtr GL3TextureManager::getTextureSlot( 	u8 textureUnit,
													TexturePtr & texture,
													SamplerPtr & sampler){
	return nullptr;
}

void GL3TextureManager::setTextureSlot( RenderSlot & slot,
										TextureSlotPtr & textureSlot){

}

TextureSlotPtr GL3TextureManager::shallowCopy( TextureSlotPtr & textureSlot){
	return nullptr;
}

void GL3TextureManager::freeUnusedTextures(){
	textures.collectSome( textures.size(), []( GL3Texture&){} );
	textures.shrinkToFit();
}

} // namespace GL3
} // namespace Bade