/*******************************************************************************
   Copyright (C) 2015 Dario Oliveri
   See copyright notice in LICENSE.md
*******************************************************************************/
#include "Catch.hpp"
#include "TestHelpers.hpp"
#include <CommandQueue.hpp>

using namespace Bade;

namespace {
	
	template< typename T>
	struct parms{
		u8 * p;
		parms( u8* parms): p( parms){
			
		}
		
		T* operator-> ()
		{
			return reinterpret_cast< T *>(p);	
		}
		
		T& operator* ()
		{
			return *reinterpret_cast< T *>(p);
		}
	};
	
	struct Fruits{
		double  pi      = 3.14;
		int 	apples  = 115;
		bool 	bananas = true;
	};
	
	bool functionCalled;
	int  callTimes;
	
	void function(u8 * arg){
		parms< Fruits> p(arg);
		
		// check that data was not altered, if assertion fails, we have a bug
		// in the most important engine feature.
		BADE_ASSERT(p->pi == 3.14);
		BADE_ASSERT(p->apples == 115);
		BADE_ASSERT(p->bananas == true);
		
		functionCalled = true;
		callTimes++;
	}
}

TEST_CASE( "Testing Bade::CommandQueue", "[core][internal]")
{	
	functionCalled 		= false;
	callTimes			= 0;
	CommandQueue   		queue;
	
	Fruits				fruit;
	
	SECTION( "queue call command once")
	{
		SECTION( "Executing empty queue gives no problem")
		{
			queue.executeAll();
			
			REQUIRE( functionCalled == false);
			REQUIRE( callTimes == 0);
		}
		
		
		queue.pushCommand(function,fruit);
		queue.executeAll();
		
		REQUIRE( functionCalled == true);
		REQUIRE( callTimes == 1);		
		
		SECTION( "adding another function increase count")
		{
			queue.pushCommand(function,fruit);
			queue.executeAll();

			REQUIRE( functionCalled == true);
			REQUIRE( callTimes == 3);
			
			SECTION( "resetting don't increase count")
			{
				functionCalled = false;
				queue.reset();
				queue.executeAll();
				
				REQUIRE( functionCalled == false);
				REQUIRE( callTimes == 3);	
			}
		}
		
		SECTION( "resetting don't increase count")
		{
			functionCalled = false;
			queue.reset();
			queue.executeAll();
			
			REQUIRE( functionCalled == false);
			REQUIRE( callTimes == 1);	
		}
	}
	
	SECTION(" testing command queue with many function calls"){
		for(int i=0;i <512; i++)
			queue.pushCommand(function,fruit);
		
		queue.executeAll();
		REQUIRE( functionCalled == true);
		REQUIRE( callTimes == 512);	
		
		SECTION("do queue work after resetting big work?"){
			queue.reset();
			
			for(int i=0;i <64; i++)
				queue.pushCommand(function,fruit);
		
			queue.executeAll();
			
			REQUIRE( callTimes == (512+64));	
			
			SECTION("do queue work after resetting big work 2?"){
				queue.reset();
				queue.reset();
				
				for(int i=0;i <64; i++)
					queue.pushCommand(function,fruit);
			
				queue.executeAll();
				
				REQUIRE( callTimes == (512+128));	
			}
		}
	}
	
}