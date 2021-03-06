/*******************************************************************************
   Copyright (C) 2015 Dario Oliveri
   See copyright notice in LICENSE.md
*******************************************************************************/
#pragma once
#include <string>

namespace Bade {
	
	// If someone want to plug here custom allocator...	
	template< typename T>
	using StdString = std::string<T>;
	
}