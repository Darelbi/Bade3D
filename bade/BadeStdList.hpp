/*******************************************************************************
   Copyright (C) 2014-2015 Dario Oliveri
   See copyright notice in LICENSE.md
*******************************************************************************/
#pragma once
#include <list>

namespace Bade {
	
	// If someone want to plug here custom allocator...
	template< typename T>
	using StdList = std::list<T>;
	
}