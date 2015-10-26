/*******************************************************************************
   Copyright (C) 2015 Dario Oliveri
   See copyright notice in LICENSE.md
*******************************************************************************/
#pragma once
#include "Assert.hpp"
#include "BadeForwards.hpp"
#include "BadeStdVector.hpp"
#include <utility>				// std::forward
#include <type_traits>			// std::is_base_of

namespace Bade {
	
	using namespace std;
	
	// TODO: keep array of free elements?
	
	// Reference count == 0 => ready to be replaced.
	// Reference count == 1 => to be freed on GPU side
	// Reference count == 2 => 1 reference from manager and 1 from user
	// Reference count == N => 1 ref from manager and N-1 from user
	template< typename Entity>
	class ManageEngine{

		StdVector< ManagedResource< Entity> > 	
		
								entries;
		
		u32						free = 0;
		u32						firstFree = 0;
		u32						gcCounter = 0;
		
		
		template< typename... Args>
		ManagedResource< Entity> allocateImpl( Args&&... args){
			if(free == 0){

				entries.emplace_back( 
								ManagedResource< Entity>( new Entity(forward< Args>(args)...))
									);
				
				auto ptr = entries[ entries.size()-1].get();
				
				return ManagedResource< Entity>(
						ptr
					);
			}

			free--;
			
			u32 index = findNextFree();
			
			entries[index]-> ~Entity();
			
			// need a proper allocator in future 
			new ( entries[index].get() ) Entity( forward< Args>( args)...);
			return ManagedResource< Entity>(
						entries[index].get()
					);
		}
		
		void decreaseReferenceCount( u32 index){
			auto decrement =  ManagedResource< Entity>(
							entries[index].get()
						);
		}
	
	public:
	
		template< typename... Args>
		ManagedResource< Entity> allocate( Args&&... args){
			auto managed = allocateImpl( forward< Args>( args)...);
			managed->referenceIncrement(); //reference count == 2
			return managed;
		}
		
		// call only if there are free elements (free count > 1)
		u32 findNextFree(){
			
			for( u32 i= firstFree; i<entries.size(); i++)
				if( entries[i]->getReferenceCount() == 0){
					firstFree = i;
					return i;
				}
				
			for(u32 i=0; i<firstFree; i++)
				if( entries[i]->getReferenceCount() == 0){
					firstFree = i;
					return i;
				}
			
			assert( false && "no free elements but 'free' count was > 1");
		}
		
		
		template< typename Base>
		ManagedResource< Entity> shallowCopy( ManagedResource< Base> & ptr){
			
			static_assert( 	std::is_base_of< Base, Entity>::value ||
							std::is_same< Base, Entity>::value,
							"ManagedEntity must be the Interface of Entity");
			
			ptr->referenceIncrement();
			
			return ManagedResource< Entity>(
							static_cast< Entity*> ( ptr.get())
						);
		}
		
		template< typename Base>
		ManagedResource< Base> shallowCopyAbstract( ManagedResource< Base> & ptr){
			ptr->referenceIncrement();
			
			return ManagedResource< Base>(
							ptr.get()
						);
		}
		
		template< typename F>
		void collectSome( u32 quantity, F functor){
			if( quantity > entries.size())
				quantity = entries.size();
			
			for( u32 i=0; i<quantity; i++){
				
				gcCounter++;
				if(gcCounter >= entries.size())
					gcCounter = 0;
				
				if( entries[gcCounter]->getReferenceCount() == 1){
					free++;
				
					decreaseReferenceCount( gcCounter);
					
					functor( *entries[gcCounter].get() );
						
					firstFree = firstFree > gcCounter? gcCounter: firstFree;
				}
			}
		}
		
		void shrinkToFit(){
			u32 index = entries.size()-1;
			u32 count = 0;
			
			while( entries[ index]->getReferenceCount() == 0 ){
				entries[ index]->~Entity(); //call destructor 
				count++;
				
				if(index==0)
					break;
				
				index--;
			}
			
			entries.resize( entries.size() - count);
			entries.shrink_to_fit();
		}
		
		template< typename Derived>
		EntityPtr shallowCopyAsEntity( ManagedResource< Derived> & entity){
			static_assert( 	std::is_base_of< ManagedEntity, Derived>::value,
							"ManagedEntity must be the Interface of Entity");
							
			entity->referenceIncrement();
			
			return EntityPtr (
							static_cast< ManagedEntity*>( 
								entity.get()
								)
							);
		}
		
		//set to nullptr "entity" and cast it to its base class
		template< typename Base>
		ManagedResource< Base> cast( ManagedResource< Entity> & entity){
			static_assert( 	std::is_base_of< Base, Entity>::value,
							"Base must be the Interface of Entity");
							
			return ManagedResource< Base> (
							static_cast< Base*>( entity.release() )
							);
		}
		
		u32 size(){
			return entries.size();
		}
	};
} // namespace Bade