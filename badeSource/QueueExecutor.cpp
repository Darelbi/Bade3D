/*******************************************************************************
   Copyright (C) 2014-2015 Dario Oliveri
   See copyright notice in LICENSE.md
*******************************************************************************/
#include "QueueExecutor.hpp"
#include <utility> // swap
#include <atomic>  // thread fence

namespace Bade{

	using namespace std;
	
	QueueExecutor::QueueExecutor(){
		
		// make sure InterleavedRenderer is fully initialized before main
		// thread and render thread starts to race against command queues.
		atomic_thread_fence( memory_order_seq_cst );
	}
	
	//Beware before entering here: Boolean hell!
	
	bool QueueExecutor::render(){
		
		bool execute = true;
		bool haveExtraStuffToDo = false;

		{lock_guard< mutex> guard( renderMutex);

			if(commandsUpdated)
				swap( nextToBeRendered, currentlyRendered);

			commandsUpdated = false;
			
			if( executeOnlyOnce && commandsExecuted)
				execute = false;
			
			haveExtraStuffToDo = executeOnlyOnce;
		}

		if( execute)
			currentlyRendered.executeAll(); //eventually write nativeHandles

		renderMutex.lock();
		commandsExecuted = true; // bool flag
		renderMutex.unlock();

		condition.notify_one(); // glSwapbuffer while other thread progress
		
		return haveExtraStuffToDo;
	}

	void QueueExecutor::submitRendering( CommandQueue & nextQueue, bool res){

		unique_lock< mutex> guard( renderMutex); //lock acquired
		
		while( commandsExecuted == false)
			condition.wait( guard); //allow progress of other thread

		executeOnlyOnce = res;
		commandsExecuted = false;
		commandsUpdated = true;

		swap( nextQueue, nextToBeRendered);
		guard.unlock();
	}

} // namespace Bade