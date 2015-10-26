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
	int exp= -1000;
	
	SECTION("exact power of 2")
	{
		REQUIRE( nearestPowerOf2(2.f) == 2.f);
		REQUIRE( nearestPowerOf2(2.f, exp) == 2.f);
		REQUIRE( exp == 1);
	}
	
	SECTION("round down power of 2")
	{
		REQUIRE( nearestPowerOf2(6.f) == 4.f);
		REQUIRE( nearestPowerOf2(6.f, exp) == 4.f);
		REQUIRE( exp == 2);
	}
	
	SECTION("round up power of 2")
	{
		REQUIRE( nearestPowerOf2(6.0001f) == 8.f);
		REQUIRE( nearestPowerOf2(6.0001f, exp) == 8.f);
		REQUIRE( exp == 3);
	}
	
	SECTION("round down inverse power of 2")
	{
		REQUIRE( nearestPowerOf2(0.375f) == 0.25f);
		REQUIRE( nearestPowerOf2(0.375f, exp) == 0.25f);
		REQUIRE( exp == -2);
	}
	
	SECTION("round up inverse power of 2")
	{
		REQUIRE( nearestPowerOf2(0.375001f) == 0.5f);
		REQUIRE( nearestPowerOf2(0.375001f, exp) == 0.5f);
		REQUIRE( exp == -1);
	}
	
	SECTION("round down to 1/2")
	{
		REQUIRE( nearestPowerOf2(0.75f) == 0.5f);
		REQUIRE( nearestPowerOf2(0.75f, exp) == 0.5f);
		REQUIRE( exp == -1);
	}
	
	SECTION("round up to 1")
	{
		REQUIRE( nearestPowerOf2(0.75001f) == 1.f);
		REQUIRE( nearestPowerOf2(0.75001f, exp) == 1.f);
		REQUIRE( exp == 0);
	}
	
	SECTION("exactly 1")
	{
		REQUIRE( nearestPowerOf2(1.f) == 1.f);
		REQUIRE( nearestPowerOf2(1.f, exp) == 1.f);
		REQUIRE( exp == 0);
	}
	
	SECTION("round down to 1")
	{
		REQUIRE( nearestPowerOf2(1.5f) == 1.f);
		REQUIRE( nearestPowerOf2(1.5f, exp) == 1.f);
		REQUIRE( exp == 0);
	}
}