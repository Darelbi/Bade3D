/*******************************************************************************
   Copyright (C) 2014-2015 Dario Oliveri
   See copyright notice in LICENSE.md
*******************************************************************************/
#pragma once
#include <vector>

namespace Bade {
	
	// If someone want to plug here custom allocator...
	template< typename T>
	using StdVector = std::vector<T>; 
								   // I do not like "vector" but using
								   // "array" would be more even confusing since
								   // we also have std::array in standard lib
	
}