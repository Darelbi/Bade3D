/*******************************************************************************
   Copyright (C) 2014-2015 Dario Oliveri
   See copyright notice in LICENSE.md
*******************************************************************************/
#include "CommandQueue.hpp"
#include <atomic>
#include <utility>

namespace Bade {

	CommandQueue::CommandQueue(){

		// make sure CommandQueue is fully initialized before main
		// thread and render thread starts to race against command queues.
		std::atomic_thread_fence( std::memory_order_seq_cst );
	}

	void CommandQueue::executeAll(){
		for(auto f: commands)
			 f.first( &parms.data()[  f.second]);
	}

	void CommandQueue::reset(){

		if(currentByte < ( parms.capacity()/4+1)
		){
			parms.resize( parms.capacity()/2+1);
			parms.shrink_to_fit();
		}

		if(currentCommand < ( commands.capacity()/4+1)
		){
			commands.resize( commands.capacity()/2+1);
			commands.shrink_to_fit();
		}

		parms.resize(0);
		commands.resize(0);

		currentByte = 0;
		currentCommand = 0;
	}
} // namespace Bade
