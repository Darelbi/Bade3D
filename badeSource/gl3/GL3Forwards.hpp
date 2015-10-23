/*******************************************************************************
   Copyright (C) 2015 Dario Oliveri
   See copyright notice in LICENSE.md
*******************************************************************************/
#pragma once
#include "../BadeForwards.hpp"

namespace Bade{
namespace GL3{
	
	class GL3AsyncProxy;
	class GL3Texture;
	
	using ProxyPtr = std::shared_ptr< GL3AsyncProxy>;
	
} // namespace GL3
} // namespace Bade