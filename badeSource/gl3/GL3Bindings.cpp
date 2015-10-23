/*******************************************************************************
   Copyright (C) 2015 Dario Oliveri
   See copyright notice in LICENSE.md
*******************************************************************************/
#include "../BadeBindings.hpp"

#include "../Assert.hpp"
#include "../PortableBindings.hpp"
#include "../QueueExecutor.hpp"

#include "GL3AsyncProxy.hpp"

#include <InfectorContainer.hpp>

namespace Bade {
	
	using namespace GL3;
	using namespace Infector;

	void BADE_API wireEngine( Infector::Container & ioc, bool threaded){
		
			if(threaded)
			{
				ioc.bindSingleAsNothing< GL3AsyncProxy>();
			}
			else
			{
				assert( false && "Single threaded rendering not implemented yet");
			}
		
		portableBindEngine( ioc, threaded);
		
			if(threaded)
			{
				ioc.wire< Shared<QueueExecutor> >();
			}
			else
			{
				assert( false && "Single threaded rendering not implemented yet");
			}
		
		portableWireEngine( ioc, threaded);	
	}

} // namespace Bade 