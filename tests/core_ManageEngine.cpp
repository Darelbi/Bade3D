/*******************************************************************************
   Copyright (C) 2015 Dario Oliveri
   See copyright notice in LICENSE.md
*******************************************************************************/
#include "Catch.hpp"
#include <ManageEngine.hpp>
#include <BadeForwards.hpp>

namespace {
	
	class Entity: public Bade::ManagedEntity{
	public:
		virtual int foo() = 0;
	};
	
	class ConcreteEntity: public Entity{
	
	public:
	
		ConcreteEntity(){}
		
		int foo() override{
			return 1234;
		}
	
	};
}

TEST_CASE( "Testing Bade::CommandQueue", "[core][internal]")
{
	using namespace Bade;
	
	ManageEngine< ConcreteEntity> engine;
	
	SECTION(" allocate 100 objects")
	{
		ManagedResource< ConcreteEntity> entities[100];
		
		for(int i=0; i<100; i++)
			entities[i] = engine.allocate();
		
		for(int i=0; i<100; i++)
			for(int j=0; j<100; j++)
				if(i!=j)
					REQUIRE( entities[i].get() != entities[j].get());
				else
					REQUIRE( entities[i].get() == entities[j].get());
				
		SECTION(" deallocation")
		{
			for(int i=0; i<100; i++)
			entities[i].reset(nullptr);
		
			engine.collectSome(50,[&](ConcreteEntity & instance){ REQUIRE ( instance.foo() == 1234);});
			
			SECTION(" reallocate")
			{
				for(int i=0; i<100; i++)
					entities[i] = engine.allocate();
		
				for(int i=0; i<100; i++)
					for(int j=0; j<100; j++)
						if(i!=j)
							REQUIRE( entities[i].get() != entities[j].get());
						else
							REQUIRE( entities[i].get() == entities[j].get());
			}
		}
	}
	
	
}