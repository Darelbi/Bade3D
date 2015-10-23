/*******************************************************************************
   Copyright (C) 2015 Dario Oliveri
   See copyright notice in LICENSE.md
*******************************************************************************/
#pragma once
#include "../BadeRenderQueue.hpp"

#include "GL3Forwards.hpp"
#include "GL3State.hpp"


namespace Bade {
namespace GL3 {

	/** This is the place where Main Thread communicates with Render thread.
		You just add some renderpasses and then submit them for rendering.
	*/
	class GL3RenderQueue: public RenderQueue{

		bool						firstRun = true;
		GL3State					baseState;
		GL3State					lastState;
		RenderPass			       *currentState; //pointer avoid copying

		ProxyPtr					asyncProxy;

		void minimizeClearStates(	GL3State & lastState,
									const RenderPass & pass);

		void minimizePassStates(	GL3State & lastState,
									const RenderPass & pass);

		void minimizeSlotStates(	GL3State & lastState,
									const RenderSlot & slot);

		void markDirtyBuffers(		GL3State & lastState);

	public:

		GL3RenderQueue( ProxyPtr proxy);

		bool GPUResourceUpdate() override;
		
		// resource loading is performed before compiling so that
		// all referenced Ids are valid (unless resource loading failed)
		bool compileStates( StdList< RenderPass> & passes) override;

	};

} // namespace GL3
} // namespace Bade