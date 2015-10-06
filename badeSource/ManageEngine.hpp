/*******************************************************************************
   Copyright (C) 2015 Dario Oliveri
   See copyright notice in LICENSE.md
*******************************************************************************/
#pragma once
#include "BadeForwards.hpp"
#include "BadeStdVector.hpp"
#include <utility>				// std::forward

namespace Bade {
	
	// TODO: keep array of free elements?
	
	// Reference count == 0 => ready to be replaced.
	// Reference count == 1 => to be freed on GPU side
	// Reference count == 2 => 1 reference from manager and 1 from user
	template< typename Entity>
	class ManageEngine{
		/**
		Be aware that if you add, or remove elements from the vector, or 
		[potentially] modify the vector in any way (such as calling reserve), 
		this pointer could become invalid and point to a deallocated area 
		of memory.	*/
		StdVector< Entity> 	entries;
		u32					free = 0;
		
	public:
	
	template< typename... Args>
	Entity* allocate( Args&&... args){
		if(free == 0){
			entries.emplace_back( std::forward< Args>( args)...);
			return &entries[ entries.size()-1];
		}		
		
		u32 index = findNextFree();
		
		entries[index].~Entity();
		
		new (&entries[index]) Entity( std::forward< Args>( args)...);
		return &entries[index];
	}
	
	u32 findNextFree(){
		for( u32 i=0; i<entries.size(); i++)
			if( entries[i].getReferenceCount() == 0)
				return i;
	}
	
	
		
		
		
		
	};
} // namespace Bade