/*******************************************************************************
   Copyright (C) 2015 Dario Oliveri
   See copyright notice in LICENSE.md
*******************************************************************************/
#include "Catch.hpp"
#include <BadeNumeric.hpp>
using namespace Bade;

TEST_CASE( "Testing BadeNumeric.hpp :: Clamp", "[core][math]")
{
	SECTION("No Clamping")
	{
		REQUIRE( clamp(3.f,2.f,4.f) == 3.f);
	}
	
	SECTION("Clamping min")
	{
		REQUIRE( clamp(1.f,2.f,4.f) == 2.f);
	}
	
	SECTION("Clamp max")
	{
		REQUIRE( clamp(5.f,2.f,4.f) == 4.f);
	}
}

TEST_CASE( "Testing BadeNumeric.hpp :: NearestPowerOf2", "[core][math]")
{
	SECTION("exact power of 2")
	{
		REQUIRE( nearestPowerOf2(2.f) == 2.f);
	}
	
	SECTION("round down power of 2")
	{
		REQUIRE( nearestPowerOf2(6.f) == 4.f);
	}
	
	SECTION("round up power of 2")
	{
		REQUIRE( nearestPowerOf2(6.0001f) == 8.f);
	}
	
	SECTION("round down inverse power of 2")
	{
		REQUIRE( nearestPowerOf2(0.375f) == 0.25f);
	}
	
	SECTION("round up inverse power of 2")
	{
		REQUIRE( nearestPowerOf2(0.375001f) == 0.5f);
	}
}