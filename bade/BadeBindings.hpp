/*******************************************************************************
   Copyright (C) 2014-2015 Dario Oliveri
   See copyright notice in LICENSE.md
*******************************************************************************/
#pragma once
#include "BadeTypes.hpp"
#include <memory>

// Forward declarations
namespace Infector { //providing bindings for another framework is trivial
	class Container;
	class Context;
}

namespace Bade {

	/** Simple function. Add engine to your container.  */
	void BADE_API wireEngine( Infector::Container & ioc);

} // namespace Bade 