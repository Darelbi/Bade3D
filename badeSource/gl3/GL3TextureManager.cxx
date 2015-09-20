/*******************************************************************************
   Copyright (C) 2015 Dario Oliveri
   See copyright notice in LICENSE.md
*******************************************************************************/
#include "GL3TextureManager.hpp"
#include "../BadeImageManager.hpp"

namespace Bade {
namespace GL3 {
	
GL3TextureManager::GL3TextureManager(
					ResourceQueuePtr	newloader,
					ImageManagerPtr		newimageManager)
{
	resourceLoader	= newloader;
	imageManager	= newimageManager;
}

u32 GL3TextureManager::allocateTexture(){
	//push new or overwrite old
	
}

TexturePtr GL3TextureManager::getTexture( 	BitmapImagePtr & image,
											bool mipmaps = true)
{
	u32 textureIndex = allocateTexture();
	
	GL3Texture * texture = &referencedTextures[textureIndex];
	
	texture->mipmaps 		= mipmaps;
	texture->engineHandel 	= textureIndex;
	texture->nativeHandle	= 0;
	texture->format			= image->hasAlphaChannel() ? 
								InternalFormat. RGBA : InternalFormat. RGB;
								
	// funzione che opera su un buffer condiviso ..  non può essere GL3texture
	// perchè è soggetto a race condition. 
	// Quindi deve essere creato ad hoc (sigh)
	
								glGenTextures(1, &texture_id);
	glBindTexture(GL_TEXTURE_2D, texture_id);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, // target
		0,  // level, 0 = base, no minimap,
		GL_RGBA, // internalformat
		res_texture->w,  // width
		res_texture->h,  // height
		0,  // border, always 0 in OpenGL ES
		GL_RGBA,  // format
		GL_UNSIGNED_BYTE, // type
		res_texture->pixels);
								
	return TexturePtr(texture);
}

void GL3TextureManager::reloadTexture(	BitmapImagePtr & image,
										TexturePtr & texture)
{
	
}
	
TexturePtr GL3TextureManager::getTexture( 	const BitmapImage & image,
											bool mipmaps)
{
	u32 textureIndex = allocateTexture();
	
	GL3Texture * texture = &referencedTextures[textureIndex];
	
	texture->mipmaps 		= mipmaps;
	texture->engineHandel 	= textureIndex;
	texture->nativeHandle	= 0;
	texture->format			= image.hasAlphaChannel() ? 
								InternalFormat. RGBA : InternalFormat. RGB;
								
	return TexturePtr(texture);
}
	
TexturePtr  GL3TextureManager::clone( TexturePtr & texture){
	
}

SamplerPtr  GL3TextureManager::clone( SamplerPtr & sampler){
	
}

SamplerPtr 	GL3TextureManager::getSampler( 	FilteringMode 		filter,
											TextureWrap			wrap,
											float 				anisotropy) const
{
	
}
										
										
void GL3TextureManager::freeUnusedTextures(){
	
} 
	
} // namespace GL3
} // namespace Bade