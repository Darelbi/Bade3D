/*******************************************************************************
   Copyright (C) 2015 Dario Oliveri
   See copyright notice in LICENSE.md
*******************************************************************************/
#pragma once

namespace Infector {
	class Container;
}

namespace Bade {
	
	void portableBindEngine( Infector::Container & ioc, bool threaded);

	void portableWireEngine( Infector::Container & ioc, bool threaded);
	
} // namespace Bade