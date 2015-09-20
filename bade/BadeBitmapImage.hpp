/*******************************************************************************
   Copyright (C) 2014-2015 Dario Oliveri
   See copyright notice in LICENSE.md
*******************************************************************************/
#pragma once
#include "BadeForwards.hpp"

namespace Bade{
	
	struct BADE_API ColorRGB{
		u8	R;
		u8	G;
		u8	B;
		ColorRGB( u8 R, u8 G, u8 B);
	};
	
	struct BADE_API ColorRGBA{
		u8	R;
		u8	G;
		u8	B;
		u8  A;
		ColorRGBA( u8 R, u8 G, u8 B, u8 A);
	};
	
	// This class represent a standard image where each color channel
	// is 1 byte and we have 3 (Red, Green, Blue) or 4 (RGB + Alpha)
	// color channels where each channel value is a unsinged integer 
	// number going from 0 to 255.
	
	// Alpha 0 => transparent .. Alpha 255 => full opaque
	class BADE_API BitmapImage{
		
		u8* pixels = nullptr;
		u16	width;
		u16 height;
		u16 lineSize;
		u16	channels;
	
	public:
	
		BitmapImage( u16 w, u16 h, bool alpha);
		~BitmapImage();
		
		bool hasAlphaChannel() const;
		
		u16 getWidth() const;
		u16 getHeight() const;
		u16 getLineSize() const;
		u32 getBytes() const;
		
		ColorRGB 	getPixel ( u16 x, u16 y) const;
		ColorRGBA 	getPixelA( u16 x, u16 y) const;
		
		/** Like raw pointer, but disallow accidental buffer deletion.*/
		ForeignBuffer<u8>	getBitmapBuffer() const;
		
		void 		setPixel( ColorRGB,  u16 x, u16 y);
		void 		setPixel( ColorRGBA, u16 x, u16 y);
		
		/** Call a user provided function on every pixel of a image. This is
			the fastest way to transform RGB components of a image.
			Will works ALSO for images with alpha (alpha not changed) */
		template< typename Functor >
		inline void foreachPixelRGB( Functor func){
			u8* data = pixels;
			for(u16 j=0; j<height; j++, data+= lineSize)
				for( u16 i=0; i<width; i+=channels)
					func( data[i], data[i+1], data[i+2]);
		}
		
		/** Call a user provided function on every pixel of a image. This is
			the fastest way to transform RGBA components of a image.
			Will work ONLY for images with alpha channel.*/
		template< typename Functor >
		inline void foreachPixelRGBA( Functor func){
			
			assertHasAlphaChannel();
			
			u8* data = pixels;
			const u32 size = width*height;
			for( u32 i=0; i<size; data += 4)
				func( data[0], data[1], data[2], data[3]);
		}
		
	private:
	
		void assertHasAlphaChannel() const;
		u32  lookupPixel( u16 x, u16 y) const;
	};
	
	/// UTILITY FUNCTIONS
	
	// return 0 only if color and alpha are 0
	// return 255 only if color and alpha are 255
	// faster than dividing by 255. still behave like rounding.
	inline u8 premultiplyByte( u32 color, u32 alpha){
		return (u8)((color*alpha+255)/256);
	}
	
	// USAGE: image->foreachPixelRGBA ( premultiplyColorBytes);
	inline void premultiplyColorBytes( u8 & r, u8 & g, u8 & b, u8 a){
		r = premultiplyByte( r, a);
		g = premultiplyByte( g, a);
		b = premultiplyByte( b, a);
	}
	
} // namespace Bade