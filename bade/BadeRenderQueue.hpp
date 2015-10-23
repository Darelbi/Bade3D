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
		changes. THIS IS A PROTOTYPE INTERFACE. SORRY ;_(
	*/
	class RenderQueue{

	public:
	
		/** Perform deferred loading requests (when you want just to update
			and not to re-compile states)*/
		virtual bool GPUResourceUpdate() = 0;
	
		/** Setup a new RenderQueue. If this returns false you should get
			the error log and see what's wrong.*/	
		virtual bool compileStates( StdList< RenderPass> & passes) = 0;

		virtual ~RenderQueue(){}
	};
} // namespace Bade