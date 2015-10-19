/*******************************************************************************
   Copyright (C) 2015 Dario Oliveri
   See copyright notice in LICENSE.md
*******************************************************************************/
#pragma once
#include "../BadeRenderPass.hpp"
#include "../CommandQueue.hpp"
#include "../PortableGraphics.hpp"

namespace Bade {
namespace GL3 {
	
	void _enableScissorTest( u8*);
	
	void _setScissorRectangle( u8*);
	
	void _disableScissorTest( u8*);
	
	void _enableColorMask( u8*);
	
	void _setClearColor( u8*);
	
	void _enableDepthMask( u8*);
	
	void _enableStencilMask( u8*);
	
	struct clearBuffersParm;
	void _clearBuffers( u8*);
	
	void _disableColorMask( u8*);
	
	void _disableDepthTest( u8*);
	
	void _enableDepthTest( u8*);
	
	void _setDepthFunc( u8*);
	
	void _disableDepthMask( u8*);
	
	void _enableWireframeMode( u8*);
	
	void _disableWireframeMode( u8*);
	
	void _disableBlending( u8*);
		
	void _enableBlending( u8*);
	
	struct blendFuncParm;
	void _setBlendFunc( u8*);
	
	void _disableStencilTest( u8*);
	
	void _enableStencilTest( u8*);
	
	struct stencilFuncParm;
	void _setStencilFunc( u8*);
		
	void _setStencilOp( u8*);
	
	void _useProgram( u8*);
	
	// TODO: "vectorize": 10 texture units => 10 functions
	void _activeTextureUnit( u8*);
	
	// TODO: "vectorize": 10 texture units => 10 functions
	struct bindSamplerParm;
	void _bindSampler( u8*);
	
	// TODO: "vectorize": 2 texture types => 2 functions
	struct bindTextureParm;
	void _bindTexture( u8*);
	
	void _setVao( u8*);
	
	class GL3AsyncProxy{
		
		CommandQueue	queue;
		
	public:
	
		void enableScissorTest();
		
		void setScissorRectangle( const ushort4 & rect);
		
		void disableScissorTest();
		
		void enableColorMask();
		
		void setClearColor( const float4 & color);
		
		void enableDepthMask();
		
		void enableStencilMask();
		
		void clearBuffers( bool color, bool depth, bool stencil);
		
		void disableColorMask();
		
		void disableDepthTest();
		
		void enableDepthTest();
		
		void setDepthFunc( DepthTest);
		
		void disableDepthMask();
		
		void enableWireframeMode();
		
		void disableWireframeMode();
		
		void disableBlending();
		
		void enableBlending();
		
		void setBlendFunc( BlendMode);
		
		void disableStencilTest();
		
		void enableStencilTest();
		
		void setStencilFunc( StencilTest, u8);
		
		void setStencilOp( StencilOp);
		
		void useProgram( NativeHandle program);
		
		void activeTextureUnit( u32 unit);
		
		void bindSampler( NativeHandle unit, NativeHandle sampler );
		
		void bindTexture( NativeEnum target, NativeHandle texture);
		
		void setVao( NativeHandle vao);
	};
} // namespace GL3
} // namespace Bade