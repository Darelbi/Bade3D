/*******************************************************************************
   Copyright (C) 2014-2015 Dario Oliveri
   See copyright notice in LICENSE.md
*******************************************************************************/
#pragma once
#include "BadeForwards.hpp"

namespace Bade {
	
	class BADE_API ImageProxy: public ManagedEntity{
	public:
	
		/** Used internally (hides most stuff).*/
		virtual void accept( TextureVisitor &) = 0;
	
		virtual bool isARenderTarget() const = 0;
		
		virtual bool hasMipmaps() const = 0;
		
		virtual InternalFormat getInternalFormat() const = 0;
	};
	
} // namespace Bade