/*******************************************************************************
   Copyright (C) 2014-2015 Dario Oliveri
   See copyright notice in LICENSE.md
*******************************************************************************/
#pragma once

namespace Bade {
	
	/** Renderer of the engine, must be used within rendering thread and
		using a valid graphics context (you should provide it). */
	class Renderer{
	
	public:
	
		/** Perform rendering:
			1) Be sure the same GL context is active at every call
			2) You should "SwapBuffers" after this call.	*/
		virtual void render() = 0;
		
		/** Allow destruct derived classes from this pointer.*/
		virtual ~Renderer(){}
	};
} // namespace Bade