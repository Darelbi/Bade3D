/*******************************************************************************
   Copyright (C) 2015 Dario Oliveri
   See copyright notice in LICENSE.md
*******************************************************************************/
#pragma once
#include "BadeForwards.hpp"
#include "BadeStdList.hpp"

namespace Bade {

	/** For now this class just compile a List of RenderPasses and all added
		render slots. In future I will allow to recompile only stuff that
		changes. THIS IS A PROTOTYP INTERFACE. SORRY ;_(
	*/
	class RenderQueue{

	public:
	
		/** Setup a new RenderQueue. */	
		virtual void compileStates( StdList< RenderPass> & passes) = 0;

		virtual ~RenderQueue(){}
	};
} // namespace Bade