#include "Catch.hpp"
#include <BadeForwards.hpp>
using namespace Bade;


// This test file have 2 equivalent color conversion routines.
// Instead of using sophisticaed dithering to preserve original
// image we use simple routines that have nice desirable properties.
// sophisticated dithering will be eventually added in an image manipulator
namespace {
	
	u8 bit8_to_bit5(u8 color){
		return color>>3;
	}

	u8 bit5_to_bit8(u8 color){
		return ((color&0x07) + (color<<3));
	}

	u8 bit8_to_bit6(u8 color){
		return color>>2;
	}

	u8 bit6_to_bit8(u8 color){
		return ((color&0x03) + (color<<2)); 
	}
}


TEST_CASE( "Testing Color conversion", "[core][algorithm][color]")
{
	bool bit6[64];
	bool bit5[32];
	
	for(int i =0; i<32; i++)
		bit5[i] = false;
	
	for(int i =0; i<64; i++)
		bit6[i] = false;
	
	SECTION( "check multiple conversions have a finited loss of precision")
	{
		u8 oldb5 = 0;
		u8 oldb6 = 0;
		for(u8 i=0; ; i++)
		{
			u8 b5 = bit8_to_bit5(i);
			
			REQUIRE(b5 >=0);
			REQUIRE(b5 <=31);
			bit5[b5] = true;
			
			u8 b8 = bit5_to_bit8(b5); 
			
			REQUIRE(b5>=oldb5);
			REQUIRE( bit8_to_bit5(b8) == b5);
			
			u8 b6 = bit8_to_bit6(i);
			   b8 = bit6_to_bit8(b6);
			   
			REQUIRE(b6 >=0);
			REQUIRE(b6 <=63);
			bit6[b6] = true;
			
			REQUIRE(b6>=oldb6);
			REQUIRE( bit8_to_bit6(b8) == b6);
			
			oldb5 = b5;
			oldb6 = b6;
			
			if(i==255)
				break;
		}
		
		SECTION("check all low precision values are generated")
		{
			for(u8 i =0; i<32; i++)
				REQUIRE( bit5[i] == true);
		
			for(u8 i =0; i<64; i++)
				REQUIRE( bit6[i] == true);
			
		}
	}
	
}

/**
	| 0 | 1 | .................................... | 255 |
	| 0      | 1    |............................... | 63 |
	
	| 0 | 1 | .................................... | 255 |
	| 0      | 1    |............................... | 31 |
	
	Wanted properties  
	- Black mapped to black in both directions
	- White mapped to White in both directions
	- All packed colors can be generated
	- Consecutive mappings do not cause additional loss of color
	- Low instruction count
	- Better precision possible
	
	(Color*a +b)/ c
	
	X / c  => 255
	b < c => 0 <==> Color == 0
	//5 bit
	Color*a+b = 255*c
	
	(C*a + (d/4)) /d
	(31*a + d/4) /d = 255
	31*a +d/4 = 255*d
	31*a = 255*d -d/4
	31*a = d(255-1/4)
	124*a = 1020 -1
	124*a = d1019
	d = 124*a/1019
	
	(C*a + (254d/255)) /d
	(31*a +(254d/255)) /d = 255
	31*a +(254d/255) = 255*d
	31*a = 255*d -(254d/255)
	31*a = d(255-254/255)
	7905*a = 65025 -254
	7905*a = d64771
	d = 7905*a/64771
	//6 bit
	
	(C*a + (d/3)) /d
	(63*a + d/3) /d = 255
	63*a +d/3 = 255*d
	63*a = 255*d -d/3
	63*a = d(255-1/3)
	189*a = 765 -1
	189*a = d764
	d = 189*a/764
	
	(C*a + (254d/255)) /d
	(63*a +(254d/255)) /d = 255
	63*a +(254d/255) = 255*d
	63*a = 255*d -(254d/255)
	63*a = d(255-254/255)
	16065*a = 65025 -254
	16065*a = d64771
	d = 16065*a/64771
	
	
*/

namespace {
	u8 pack5( u8 channel8bit)
	{
		//if(channel8bit>248 || (channel8bit&0x07)<4)
			return channel8bit>>3;
		
		//return (channel8bit+4)>>3;
	}

	u8 unpack5( u8 channel5bit){
		//return ( channel5bit*509 + 31 )/62;
		return ( u32(channel5bit)*64771u + 7874u) /7905u;
	}

	u8 pack6( u8 channel8bit){
		//if(channel8bit>252 || (channel8bit&0x03)<2)
			return channel8bit>>2;
		
		//return (channel8bit+2)>>2;
	}

	u8 unpack6( u8 channel6bit){
		//return ( channel6bit*509 + 63)/126;
		return ( u32(channel6bit)*64771u + 16002u)/16065u;
	}
}


TEST_CASE( "Testing Color conversion algorithm 2", "[core][algorithm][color]")
{
	bool bit6[64];
	bool bit5[32];
	
	for(int i =0; i<32; i++)
		bit5[i] = false;
	
	for(int i =0; i<64; i++)
		bit6[i] = false;
	
	SECTION( "check multiple conversions have a finited loss of precision")
	{
		u8 oldb5 = 0;
		u8 oldb6 = 0;
		for(u8 i=0; ; i++)
		{
			u8 b5 = pack5(i);
			
			REQUIRE(b5 >=0);
			REQUIRE(b5 <=31);
			bit5[b5] = true;
			
			u8 b8 = unpack5(b5); 
			
			REQUIRE(b5>=oldb5);
			REQUIRE( pack5(b8) == b5);
			
			u8 b6 = pack6(i);
			   b8 = unpack6(b6);
			   
			REQUIRE(b6 >=0);
			REQUIRE(b6 <=63);
			bit6[b6] = true;
			
			REQUIRE(b6>=oldb6);
			REQUIRE( pack6(b8) == b6);
			
			oldb5 = b5;
			oldb6 = b6;
			
			if(i==255)
				break;
		}
		
		SECTION("check all low precision values are generated")
		{
			for(u8 i =0; i<32; i++)
				REQUIRE( bit5[i] == true);
		
			for(u8 i =0; i<64; i++)
				REQUIRE( bit6[i] == true);
			
		}
	}
	
}

TEST_CASE("checking for equality 2 conversion functions", "[core][algorithm][color]")
{
	for(u8 i=0; ; i++){
		
		if(pack6(i) != bit8_to_bit6(i)){
			WARN("i: "<<(s32) i<<" different result: "<< (s32)pack6(i)<< " and " << (s32)bit8_to_bit6(i));
		}
		
		if(pack5(i) != bit8_to_bit5(i)){
			WARN("i: "<<(s32) i<<" different result: "<< (s32)pack5(i)<< " and " << (s32)bit8_to_bit5(i));
		}
		
		REQUIRE(pack6(i) == bit8_to_bit6(i));
		REQUIRE(pack5(i) == bit8_to_bit5(i));
		
		if( i==255)
			break;
	}
}

