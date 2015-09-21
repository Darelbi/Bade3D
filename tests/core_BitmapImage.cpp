#include "Catch.hpp"
#include "TestHelpers.hpp"
#include <BadeBitmapImage.hpp>

using namespace Bade;

namespace{ 
	void setTransparentRed( u8 & r, u8 & g, u8 & b, u8 &a){
		r=255;
		g=0;
		b=0;
		a=0;
	}
	
	void setWhite( u8 & r, u8 & g, u8 & b){
		r=255;
		g=255;
		b=255;
	}
	
	void setOpaque( u8 r, u8 g, u8  b, u8 & a){
		a=255;
	}
	
	bool testColor( BitmapImage &image, u8 r, u8 g, u8 b){
		for ( int i=0; i<image.getHeight(); i++){
			for( int j=0; j<image.getWidth(); j++){
				ColorRGB c = image.getPixel(j,i);
				if(
					( c.R != r) ||
					( c.G != g) ||
					( c.B != b)
				)
				return false;
			}
		}
		return true;
	}
	
	bool testColorAndAlpha( BitmapImage &image, u8 r, u8 g, u8 b, u8 a){
		for ( int i=0; i<image.getHeight(); i++){
			for( int j=0; j<image.getWidth(); j++){
				ColorRGBA c = image.getPixelA(j,i);
				if(
					( c.R != r) ||
					( c.G != g) ||
					( c.B != b) ||
					( c.A != a) 
				)
				return false;
			}
		}
		return true;
	}
}

TEST_CASE( "Testing Bade::BitmapImage with alpha channel", "[core][image]")
{
	int sizeX = 301;
	int sizeY = 199;
	BitmapImage image( sizeX, sizeY, true);
	
	REQUIRE( image.getWidth() == sizeX);
	REQUIRE( image.getHeight() == sizeY);
	REQUIRE( image.getLineSize() == sizeX*4);
	REQUIRE( image.getBytes() == sizeX*4*sizeY);
	REQUIRE( image.hasAlphaChannel() == true);
	
	SECTION( "check if setting red works")
	{
		image.foreachPixelRGBA ( setTransparentRed);
		REQUIRE( testColorAndAlpha( image, 255, 0, 0, 0));
			
		SECTION("check if alpha premultiplication works")
		{
			image.foreachPixelRGBA( 
				premultiplyColorBytes   // function in BadeBitmapImage.hpp
				) ;
				
			REQUIRE( testColorAndAlpha( image, 0, 0, 0, 0));
		
		
			SECTION( "check if setting white leaves alpha as is")
			{
				image.foreachPixelRGB( setWhite );
				REQUIRE( testColorAndAlpha( image, 255, 255, 255, 0));
				
				SECTION( "setOpaque")
				{
					image.foreachPixelRGBA( setOpaque);
					REQUIRE( testColor( image, 255, 255, 255));
					REQUIRE( testColorAndAlpha( image, 255, 255, 255, 255));
				}
			}
		}
	}	
}