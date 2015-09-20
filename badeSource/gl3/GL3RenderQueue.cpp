/*******************************************************************************
   Copyright (C) 2015 Dario Oliveri
   See copyright notice in LICENSE.md
*******************************************************************************/
#include "GL3RenderQueue.hpp"
#include "GL3AsyncProxy.hpp"

namespace Bade {
namespace GL3 {

	GL3RenderQueue::GL3RenderQueue(  ProxyPtr proxy){
		asyncProxy = proxy;
	}
	
	void GL3RenderQueue::compileStates( StdList< RenderPass> & passes){
		
		lastState = baseState;
		
		for( RenderPass & pass: passes){

			minimizeClearStates( lastState, pass);
			
			if(pass.slots.size()==0)
				continue;
			
			markDirtyBuffers( lastState);
			
			minimizePassStates( lastState, pass);
		
			for( RenderSlot & slot : pass.slots){
				// RENDER SLOT (TODO:)
				
			}
		}
	}
	
	// ===========================================================
	// 	BEWARE, HERE STARTS THE RE-USABLE MESS OF NON-TRIVIAL-CODE
	// ===========================================================
	
	void GL3RenderQueue::minimizeClearStates(	
										GL3State & lastState,
										const RenderPass & pass)
	{
		// https://www.opengl.org/wiki/Framebuffer#Buffer_clearing
		if(lastState.scissorTest != pass.scissorTest){
			if(pass.scissorTest)
			{
				asyncProxy->enableScissorTest();
				
				lastState.scissorTest = true;
				
				for(int i = 0; i<4; i++)
					if(pass.scissorRectangle.data[i] != lastState.scissorRectangle.data[i]){
						asyncProxy->setScissorRectangle( pass.scissorRectangle);
						break;
					}
						
			}
			else
			{
				asyncProxy->disableScissorTest();
				
				lastState.scissorTest = false;
			}
		}
		
		bool clearColorRequested = pass.clearColor;
		bool clearDepthRequested = pass.clearDepth;
		bool clearStencilRequested = pass.clearStencil;

		if( lastState.colorCleared) //avoid clearing twice
			clearColorRequested = false;

		if(lastState.depthCleared && lastState.stencilCleared)
		{
			// avoid clearing twice only if both already cleared
			//(because clearing both is more efficient than clearing
			// just one: ATI 03_clever_shader_tricks.pdf)
			clearDepthRequested = false;
			clearStencilRequested = false;
		}

		// Clear COLOR state minimizing
		if( clearColorRequested){
			if( lastState.colorMask == false)
			{
				asyncProxy->enableColorMask();

				lastState.colorMask = true;
			}
			
			if( lastState.clearColor.r != pass.color.r ||
				lastState.clearColor.g != pass.color.g ||
				lastState.clearColor.b != pass.color.b ||
				lastState.clearColor.a != pass.color.a )
			{
				asyncProxy->setClearColor( pass.color);
			}
		}

		// Clear DEPTH state minimizing
		if( clearDepthRequested){
			if( lastState.depthMaskEnabled == false )
			{
				asyncProxy->enableDepthMask();

				lastState.depthMaskEnabled = true;
			}
		}

		// Clear STENCIL state minimizing
		if(clearStencilRequested){
			if( lastState.stencilMask == 0x00)
			{
				asyncProxy->enableStencilMask();

				lastState.stencilMask = 0xFF;
			}
		}

		// FINALLY CLEAR BUFFERS:
		// The pixel ownership test,the scissor test, dithering,
		// and the buffer writemasks affect the operation of glClear
		if(clearColorRequested||clearDepthRequested||clearStencilRequested)
			asyncProxy->clearBuffers( 	clearColorRequested,
										clearDepthRequested,
										clearStencilRequested);
										
		if(clearColorRequested)
			lastState.colorCleared = true;
		
		if(clearDepthRequested)
			lastState.depthCleared = true;
		
		if(clearStencilRequested)
			lastState.stencilCleared = true;
	}

	void GL3RenderQueue::minimizePassStates(	
										GL3State & lastState,
										const RenderPass & pass)
	{
		// COLOR WRITE states minimizing
		if( pass.colorWrite){
			if(lastState.colorMask == false)
			{
				asyncProxy->enableColorMask();

				lastState.colorMask = true;
			}
		}
		else{
			if(lastState.colorMask == true)
			{
				asyncProxy->disableColorMask();

				lastState.colorMask = false;
			}
		}

		// DEPTH_TEST always need to be enabled, unless we have GL_ALWAYS
		// as depth func and we don't need depth writing.
		if(pass.depthWrite==false && pass.depthTest==DepthTest::DrawAlways){
			if( lastState.depthTestEnabled)
			{
				asyncProxy->disableDepthTest();

				lastState.depthTestEnabled = false;
			}
		}else{
			if( lastState.depthTestEnabled == false) 
			{
				asyncProxy->enableDepthTest();

				lastState.depthTestEnabled = true;
			}

			// setup depth func
			if( lastState.depthTest != pass.depthTest)
			{
				asyncProxy->setDepthFunc( pass.depthTest);

				lastState.depthTest = pass.depthTest;
			}
			
			// depth write
			if(lastState.depthMaskEnabled != pass.depthWrite){
				if(pass.depthWrite)
				{
					asyncProxy->enableDepthMask();
					
					lastState.depthMaskEnabled = true;
				}
				else
				{
					asyncProxy->disableDepthMask();
					
					lastState.depthMaskEnabled = false;
				}
			}
		}	
		
		
		// POLYGON FILLING MODE (FILL OR LINE)
		if( pass.wireframe != lastState.wireframe){
			if( pass.wireframe)
			{
				asyncProxy->enableWireframeMode();
				
				lastState.wireframe = true;
			}
			else
			{
				asyncProxy->disableWireframeMode();
				
				lastState.wireframe = false;
			}
		}
		
		// BLEND MODE
		if(lastState.blendMode != pass.blendMode){
			if(pass.blendMode == BlendMode::Opaque)
			{
				asyncProxy->disableBlending();
			}
			else
			{
				if( lastState.blendMode ==  BlendMode::Opaque)
				{
					asyncProxy->enableBlending();
				}
				
				if(lastState.lastBlendMode != pass.blendMode)
				{
					// NO NEED FOR SEPARATE ALPHA (till now^^)
					// glBlendEquation( GL_FUNC_ADD ); // DEFAULT : NO NEED TO SET
					// glBlendFunc( GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
					asyncProxy->setBlendFunc( pass.blendMode);  
					lastState.lastBlendMode = pass.blendMode;   
				}
			}
			
			lastState.blendMode = pass.blendMode;
		}
		
		// STENCIL FUNCTION
		// Stenciling always needed unless is DrawAlways
		// and operation is Keep
		if( 	( pass.stencilTest	== StencilTest::DrawAlways)
			&& 	( pass.stencilOp	== StencilOp::Keep ) ){
			if( lastState.stencilTestEnabled)
			{
				asyncProxy->disableStencilTest();
				
				lastState.stencilTestEnabled = false;
			}
		}else{
			if( lastState.stencilTestEnabled==false)
			{
				asyncProxy->enableStencilTest();
				
				lastState.stencilTestEnabled = true;
			}
			
			if( lastState.stencilTest != pass.stencilTest
				|| lastState.stencilVal != pass.stencilVal)
			{
				asyncProxy->setStencilFunc( pass.stencilTest,  pass.stencilVal);
				
				lastState.stencilTest = pass.stencilTest;
				lastState.stencilVal = pass.stencilVal;
			}
			
			if( lastState.stencilOp != pass.stencilOp)
			{
				asyncProxy->setStencilOp( pass.stencilOp);
				
				lastState.stencilOp = pass.stencilOp;
			}
		}
	}
	
	void GL3RenderQueue::markDirtyBuffers( GL3State & lastState){
		
		//dirty only if rendering happens wich is when we have render slots.
		//if no rendering happens we can just avoid clearing buffers
		//again (would be a no-op)
		
		//TODO: check if clear value is changed.
		
		if(lastState.colorMask)
			lastState.colorCleared = false;
		
		if(lastState.depthMaskEnabled)
			lastState.depthCleared = false;
		
		if(lastState.stencilMask != 0x00)
			lastState.stencilCleared = false;
	}

} // namespace GL3
} // namespace Bade