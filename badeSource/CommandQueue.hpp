/*******************************************************************************
   Copyright (C) 2014-2015 Dario Oliveri
   See copyright notice in LICENSE.md
*******************************************************************************/
#pragma once
#include "BadeForwards.hpp"
#include <vector>
#include <utility>

namespace Bade {

	typedef void (*Command)( u8* parm);
	using   Callback = std::pair< Command, u32>;

	class CommandQueue{

		std::vector<u8>  		parms;
		std::vector<Callback>	commands;
		std::vector<EntityPtr>	entities;
		u32						currentByte = 0;
		u32						currentCommand = 0;

	public:

		CommandQueue();

		CommandQueue( CommandQueue &&) = default;
		CommandQueue& operator=( CommandQueue&&) = default;
		
		// store a entity to increase reference count as long as needed
		// to make it available for GPU.
		void addEntity( EntityPtr && entity);
		
		u32 getEntityCount();

		template< typename T>
		void pushCommand( 	Command	function,
							T		&parameter)
		{
			commands.emplace_back( std::make_pair( function, currentByte));

			for( int i=0; i<sizeof(T); i++, currentByte++)
				parms.emplace_back( ((u8*)&parameter)[i]);
		}
		
		void pushCommand( 	Command	function)
		{
			commands.emplace_back( std::make_pair( function, currentByte));
		}

		void executeAll();

		/** Clear data (make the buffer empty, but reallocation is delayed by 1 frame,
			if memory is used again we can skip one allocation.)*/
		void reset();

	};
} // namespace Bade