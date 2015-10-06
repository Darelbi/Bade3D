/*******************************************************************************
   Copyright (C) 2015 Dario Oliveri
   See copyright notice in LICENSE.md
*******************************************************************************/
#include "Catch.hpp"
#include "TestHelpers.hpp"
#include <ConcreteShaderOptions.hpp>

using namespace Bade;

TEST_CASE( "Testing Bade::CommandQueue", "[core][internal]")
{
	ConcreteShaderOptions options;

	SECTION( "check locking on empty options throws")
	{
		REQUIRE( options.isLocked() == false);
		REQUIRE_THROWS( options.lock());
		REQUIRE( options.isLocked() == false);
	}

	SECTION( "adding some data")
	{
		REQUIRE_NOTHROW(
			options.addVertexAttribute( "pos", VertexAttribute::float3, false)
			);
		
		REQUIRE_NOTHROW(
			options.addTextureHook( "diffuse", TextureType::Texture2D, 0)
			);
		
		
		SECTION( "check locking on non-empty options works")
		{
			REQUIRE_NOTHROW( options.lock() );
			REQUIRE( options.isLocked() == true);
		}
	}
}