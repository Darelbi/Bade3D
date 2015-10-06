/*******************************************************************************
   Copyright (C) 2015 Dario Oliveri
   See copyright notice in LICENSE.md
*******************************************************************************/
#pragma once
#include "BadeForwards.hpp"

namespace Bade {

	enum struct FilteringMode: u8{
        Nearest,
        Bilinear,
        Trilinear,
		Anisotropic
    };

	enum struct TextureWrap: u8{
        Clamp,
        Repeat
    };

	/** Subset of texture formats suitable for rendering to texture.*/
	enum struct InternalWriteFormat: u8{
        RGBA8,				// ubyte4
        RGBA16,				// ushort4
		Depth24Stencil8,	// 2 unsigned integers
		R11_G11_B10,        // 3 float values
		R16,				// half
		R16_G16				// half x 2
    };

	class BADE_API TextureManager{

	public:

		/* Creates a RGB or RGBA texture with 8 bits/channel from a image.
			By default mipmaps are created. Final texture will have alpha
			channel only if original image have that too.*/
		virtual TexturePtr getTexture( 	BitmapImagePtr & image,
										bool mipmaps = true) = 0;
										
		/** Update the image for a texture (faster if image is same size).
			You CANNOT change old texture parameters like InternalFormat 
			or mipmaps.*/
		virtual void reloadTexture( BitmapImagePtr image,
									TexturePtr & texture) = 0;

		/** Preferred way to reuse a existing texture. */
		virtual TexturePtr  shallowCopy( TexturePtr & texture) = 0;

		/** Retrieve a texture sampler object. */
		virtual SamplerPtr 	getSampler( FilteringMode 		filtering,
										TextureWrap			wrap,
										float 				anisotropy) const
										= 0;
		/**	Get a textureSlot*/							
		virtual TextureSlotPtr getTextureSlot( 	u8 textureUnit,
												TexturePtr & texture,
												SamplerPtr & sampler) = 0;
		
		/** Utility to performn sanity checking when adding a texture to 
			a slot. Cause assertion failure if same unit already used. */
		virtual void setTextureSlot( RenderSlot & slot,
									 TextureSlotPtr & textureSlot) = 0;
									 
		/** Preferred way to reuse a existing texture slot.*/
		virtual TextureSlotPtr shallowCopy( TextureSlotPtr & textureSlot)  = 0

		/** Free textures that are currently not referenced by the user*/
		virtual void freeUnusedTextures() = 0;

		/** Allow destruct derived classes from this pointer.*/
		virtual ~TextureManager(){}
	};
} // namespace Bade