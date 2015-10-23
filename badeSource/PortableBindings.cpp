/*******************************************************************************
   Copyright (C) 2015 Dario Oliveri
   See copyright notice in LICENSE.md
*******************************************************************************/
#include "PortableBindings.hpp"

#include "Assert.hpp"
#include "ConcreteImageManager.hpp"
#include "ConcreteRenderer.hpp"

#include <InfectorContainer.hpp>

namespace Bade {
	using namespace Infector;

	void portableBindEngine( Infector::Container & ioc, bool threaded){

		ioc.bindSingleAs< ConcreteImageManager,
												ImageManager>();
												
		if(threaded)
		{
			ioc.bindSingleAs< ConcreteRenderer,
												Renderer>();

			ioc.bindSingleAsNothing< QueueExecutor>();
		}
		else
		{
			assert( false && "Single threaded rendering not implemented yet");
		}
	}

	void portableWireEngine( Container & ioc, bool threaded){

		ioc.wire< ConcreteImageManager>();
		
		if(threaded)
		{
			ioc.wire< ConcreteRenderer,
												Shared < QueueExecutor> >();
												
			ioc.wire< QueueExecutor>();
		}
		else
		{
			assert( false && "Single threaded rendering not implemented yet");
		}
	}
} // namespace Bade