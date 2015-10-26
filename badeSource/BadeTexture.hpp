/*******************************************************************************
   Copyright (C) 2015 Dario Oliveri
   See copyright notice in LICENSE.md
*******************************************************************************/
#pragma once
#include "BadeForwards.hpp"

namespace Bade {
	
	/** GPU internal representation of color values.*/
	enum struct InternalFormat: u8{ 
		R5G6B5,				// 3 unsigned integers packed in 32 bit
		RGB,				// 3 x ubytes
        RGBA,				// ubyte4
        RGBA16,				// ushort4
		Depth24Stencil8,	// 2 unsigned integers
		R11_G11_B10,        // 3 x float values
		R16,				// half
		R16_G16,			// half2
		
		// Compressed formats (pixel width x pixel heights = bits)
		
		DXT1, // 4x4 =64 --->  RGB 
		DXT3, // 4x4 =128--->  RGBA, preserve sharp alpha transitions (masks)
		DXT5, // 4x4 =128--->  RGBA, preserve smooth alpha transitions (clouds)
									
		// Compressed formats for mobile
		
		ETC   // 4x4 =64 --->  RGB
    };
	
	class BADE_API Texture: public ManagedEntity{
	public:
	
		virtual bool isARenderTarget() const = 0;
		
		virtual bool hasMipmaps() const = 0;
		
		virtual InternalFormat getInternalFormat() const = 0;
		
		virtual u32 getWidth() const = 0;
		
		virtual u32 getHeight() const = 0;
	};
} // namespace Bade