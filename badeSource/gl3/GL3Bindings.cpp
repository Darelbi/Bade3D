/*******************************************************************************
   Copyright (C) 2015 Dario Oliveri
   See copyright notice in LICENSE.md
*******************************************************************************/
#include "../BadeBindings.hpp"
#include "../PortableBindings.hpp"
#include <InfectorContainer.hpp>

namespace Bade {

	void BADE_API wireEngine( Infector::Container & ioc, bool threaded){
		
		portableWireEngine(ioc, threaded);
		
	}

} // namespace Bade 