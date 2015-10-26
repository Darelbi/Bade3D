/*******************************************************************************
   Copyright (C) 2015 Dario Oliveri
   See copyright notice in LICENSE.md
*******************************************************************************/
#include "GL3TextureManager.hpp"
#include "GL3Texture.hpp"
#include "GL3AsyncProxy.hpp"
#include "GL3Sampler.hpp"

#include "../Assert.hpp"
#include "../BadeSampler.hpp"
#include "../BadeTextureSlot.hpp"
#include "../BadeImageManager.hpp"
#include "../BadeBitmapImage.hpp"
#include "../BadeNumeric.hpp"		// nearestPowerOf2

namespace Bade {
namespace GL3 {


GL3TextureManager::GL3TextureManager( ProxyPtr proxy){
	asyncProxy = proxy;
	createSamplers();
}


TexturePtr GL3TextureManager::getTexture( 	BitmapImagePtr & image,
											bool mipmaps){
	auto texture = textures.allocate();

	asyncProxy->addEntity( textures.shallowCopyAsEntity( image));
	asyncProxy->addEntity( textures.shallowCopyAsEntity(texture));

	texture->width  = image->getWidth();
	texture->height = image->getHeight();
	texture->nativeHandle = 0;
	texture->mipmaps = mipmaps;
	texture->format = image->hasAlphaChannel()?
											InternalFormat::RGBA :
											InternalFormat::RGB;

	asyncProxy->loadBitmapTexture( texture.get(), image.get(), mipmaps, true, false);

	return textures.cast< Texture>( texture);
}


void GL3TextureManager::reloadTexture( 	BitmapImagePtr image,
										TexturePtr & texture){

	assert( ( texture->getInternalFormat() == InternalFormat::RGBA && image->hasAlphaChannel())  ||
			( texture->getInternalFormat() == InternalFormat::RGB && !image->hasAlphaChannel())	);

	asyncProxy->addEntity( textures.shallowCopyAsEntity( image));
	asyncProxy->addEntity( textures.shallowCopyAsEntity( texture));

	bool newSize = image->getWidth() != texture->getWidth() ||
					image->getHeight() != texture->getHeight();

	GL3Texture* gltexture = static_cast< GL3Texture*>( texture.get());
	gltexture->width  = image->getWidth();
	gltexture->height = image->getHeight();

	asyncProxy->loadBitmapTexture( 	gltexture,
									image.get(),
									texture->hasMipmaps(),
									false, newSize);
}


TexturePtr GL3TextureManager::shallowCopy( TexturePtr & texture){
	return textures.shallowCopy< Texture>( texture);
}


SamplerPtr GL3TextureManager::getSampler( 	FilteringMode 		filtering,
											TextureWrap			wrap,
											float 				anisotropy){

	anisotropy = clamp( nearestPowerOf2( anisotropy), 1., 16.);
	u8 hashCode = samplerHashCode( filtering, wrap, anisotropy);

	assert( samplersCache[hashCode]->hashCode() == hashCode);

	auto ptr = samplers.cast< Sampler>( samplersCache[hashCode]);
	return samplers.shallowCopy( ptr );
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
	textures.collectSome( textures.size(),
		[this]( GL3Texture& texture){
			if( texture.nativeHandle != 0)
				asyncProxy->deleteTexture( texture.nativeHandle);
		});
	textures.shrinkToFit();
}


void GL3TextureManager::createSampler( u8 idx, FilteringMode f, TextureWrap w, float a){

	auto ptr = samplers.allocate(f, w, a);
	assert( ptr->hashCode() == idx);
	samplersCache[idx] = samplers.shallowCopy< GL3Sampler>(ptr);
	asyncProxy->createSampler( samplersCache[idx].get());
}


void GL3TextureManager::createSamplers(){
	using f = Bade::FilteringMode;
	using w = Bade::TextureWrap;

	createSampler( 0, f::Anisotropic, w::Clamp,  1.f);
	createSampler( 1, f::Anisotropic, w::Repeat, 1.f);
	createSampler( 2, f::Anisotropic, w::Clamp,  2.f);
	createSampler( 3, f::Anisotropic, w::Repeat, 2.f);
	createSampler( 4, f::Anisotropic, w::Clamp,  4.f);
	createSampler( 5, f::Anisotropic, w::Repeat, 4.f);
	createSampler( 6, f::Anisotropic, w::Clamp,  8.f);
	createSampler( 7, f::Anisotropic, w::Repeat, 8.f);
	createSampler( 8, f::Anisotropic, w::Clamp,  16.f);
	createSampler( 9, f::Anisotropic, w::Repeat, 16.f);
	createSampler(10, f::Nearest,	  w::Clamp,  1);
	createSampler(11, f::Nearest,	  w::Repeat, 1);
	createSampler(12, f::Bilinear,	  w::Clamp,  1);
	createSampler(13, f::Bilinear,	  w::Repeat, 1);
	createSampler(14, f::Trilinear,	  w::Clamp,  1);
	createSampler(15, f::Trilinear,	  w::Repeat, 1);
}


void GL3TextureManager::destroySamplers(){
	for(int i=0; i<16; i++)
		samplersCache[ i].reset();

	samplers.collectSome( samplers.size(),
		[this]( GL3Sampler& sampler){
			asyncProxy->deleteSampler(sampler.nativeHandle);
		});
	textures.shrinkToFit();
}


GL3TextureManager::~GL3TextureManager(){
	freeUnusedTextures();
	destroySamplers();
}

} // namespace GL3
} // namespace Bade