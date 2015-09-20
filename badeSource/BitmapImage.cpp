/*******************************************************************************
   Copyright (C) 2014-2015 Dario Oliveri
   See copyright notice in LICENSE.md
*******************************************************************************/
#include "Assert.hpp"
#include "BadeBitmapImage.hpp"

namespace Bade{
	
	ColorRGB::ColorRGB( u8 r, u8 g, u8 b){
		R = r;
		G = g;
		B = b;
	}	

	ColorRGBA::ColorRGBA( u8 r, u8 g, u8 b, u8 a){
		R = r;
		G = g;
		B = b;
		A = a;
	}
	
	BitmapImage::BitmapImage( u16 w, u16 h, bool alpha)
		:width(w), height(h), channels( alpha?4:3)
	{
		assert( w<= 4096 && h<= 4096); //max size on some platforms
		lineSize = ( channels * width + 3) & ~3;
		pixels = new u8[ lineSize*height];
	}
	
	BitmapImage::~BitmapImage(){
		if(pixels!=nullptr)
			delete [] pixels;
	}
	
	bool BitmapImage::hasAlphaChannel() const{
		return channels == 4;
	}
	
	u16 BitmapImage::getWidth() const{
		return width;
	}
	
	u16 BitmapImage::getHeight() const{
		return height;
	}
	
	u16 BitmapImage::getLineSize() const{
		return lineSize;
	}
	
	u32 BitmapImage::getBytes() const{
		return getLineSize()*getHeight();
	}
	
	u32 BitmapImage::lookupPixel( u16 x, u16 y) const{
		assert( x<width && y<height);
		return y*lineSize + x*channels;
	}
	
	ColorRGB BitmapImage::getPixel ( u16 x, u16 y) const{
		u32 idx = lookupPixel(x,y);
		
		return 
			ColorRGB( pixels[idx], pixels[idx+1], pixels[idx+2]);
	}
	
	ForeignBuffer<u8> BitmapImage::getBitmapBuffer() const{
		return ForeignBuffer<u8>(pixels);
	}
	
	ColorRGBA BitmapImage::getPixelA( u16 x, u16 y) const{
		u32 idx = lookupPixel(x,y);
		
		return ColorRGBA(	pixels[idx], 
							pixels[idx+1], 
							pixels[idx+2], 
							pixels[idx+3]);
	}
	
	void BitmapImage::setPixel( ColorRGB c,  u16 x, u16 y){
		u32 idx = lookupPixel(x, y);
		
		pixels[idx]   = c.R;
		pixels[idx+1] = c.G;
		pixels[idx+2] = c.B;
	}
	
	void BitmapImage::setPixel( ColorRGBA c, u16 x, u16 y){
		u32 idx = lookupPixel(x, y);
		
		pixels[idx]   = c.R;
		pixels[idx+1] = c.G;
		pixels[idx+2] = c.B;
		pixels[idx+3] = c.A;
	}
	
	void BitmapImage::assertHasAlphaChannel() const{
		assert( hasAlphaChannel());
	}

} // namespace Bade