/*******************************************************************************
   Copyright (C) 2015 Dario Oliveri
   See copyright notice in LICENSE.md
*******************************************************************************/
#pragma once
#include "CommandQueue.hpp"
#include <mutex>
#include <condition_variable>

namespace Bade{
	
	class QueueExecutor;
	using QueueExecutorPtr = std::shared_ptr< QueueExecutor>;
	
	/** This class just executes prepared commands */
	class QueueExecutor{
	
		CommandQueue			currentlyRendered;
		CommandQueue			nextToBeRendered;
		
		std::condition_variable condition;
		std::mutex 				renderMutex;
		bool					commandsExecuted = false;
		bool					commandsUpdated = false;
		bool					executeOnlyOnce = false;
	
	public:
	
		QueueExecutor();
		
		/** Execute once the next command queue.
			@Returns true if the queue was rendered once and we are
			waiting for something that needs continuos rendering.*/
		bool render();
		
		/** Sends a new Command queue for rendering: automatically clean
			the argument so you can use it again.
			If this submit is a "resource loading" queue, tell that
			so that engine will execute it exactly once.*/
		void submitRendering( CommandQueue &, bool resourceLoading);
	};
} // namespace Bade