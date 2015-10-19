/*******************************************************************************
   Copyright (C) 2015 Dario Oliveri
   See copyright notice in LICENSE.md
*******************************************************************************/
#include "GL3AsyncProxy.hpp"
#include <iostream>

namespace Bade {
namespace GL3 {
	
	#ifdef GL
		#error "Check inclusion of GL headers."
	#endif
	#define GL gl::_detail
	
	template< typename T>
	struct parms{
		u8 * p;
		parms( u8* parms): p( parms){
			
		}
		
		T* operator-> ()
		{
			return reinterpret_cast< T *>(p);	
		}
		
		T& operator* ()
		{
			return *reinterpret_cast< T *>(p);
		}
	};
	
	
	void _enableScissorTest( u8*){
		GL::Enable( gl::SCISSOR_TEST);
	}
	void GL3AsyncProxy::enableScissorTest(){
		queue.pushCommand( _enableScissorTest);
	}
	
	
	void _setScissorRectangle( u8*p){
		parms< ushort4> parm{ p};
		GL::Scissor( parm->x, parm->y, parm->z, parm->w);
	}
	void GL3AsyncProxy::setScissorRectangle( const ushort4 & rect){
		queue.pushCommand( _setScissorRectangle, rect);
	}
	
	
	void _disableScissorTest( u8*){
		GL::Disable( gl::SCISSOR_TEST);
	}
	void GL3AsyncProxy::disableScissorTest(){
		queue.pushCommand( _disableScissorTest);
	}
	
	
	void _enableColorMask( u8*){
		GL::ColorMask( 1, 1, 1, 1);
	}
	void GL3AsyncProxy::enableColorMask(){
		queue.pushCommand( _enableColorMask);
	}
	
	
	void _setClearColor( u8*p){
		parms< float4> parm{ p};
		GL::ClearColor( parm->R, parm->G, parm->B, parm->A);
	}
	void GL3AsyncProxy::setClearColor( const float4 & color){
		queue.pushCommand( _setClearColor, color);
	}
	
	
	void _enableDepthMask( u8*){
		GL::DepthMask( 1);
	}
	void GL3AsyncProxy::enableDepthMask(){
		queue.pushCommand( _enableDepthMask);
	}
	
	
	void _enableStencilMask( u8*){
		GL::StencilMask( 0xFF);
	}
	void GL3AsyncProxy::enableStencilMask(){
		queue.pushCommand( _enableStencilMask);
	}
	

	struct clearBuffersParm{
		GLbitfield mask;
	};
	void _clearBuffers( u8* p){
		parms< clearBuffersParm> parm{ p};
		GL::Clear( parm->mask);
	}
	void GL3AsyncProxy::clearBuffers( bool color, bool depth, bool stencil){
		clearBuffersParm parm;
		parm.mask = color? 		gl::COLOR_BUFFER_BIT:0 |
					depth? 		gl::DEPTH_BUFFER_BIT:0 |
					stencil?	gl::STENCIL_BUFFER_BIT:0;
		queue.pushCommand( _enableStencilMask, parm);
	}
	
	
	void _disableColorMask( u8*){
		GL::ColorMask( 0, 0, 0, 0);
	}
	void GL3AsyncProxy::disableColorMask(){
		queue.pushCommand( _disableColorMask);
	}
	
	
	void _disableDepthTest( u8*){
		GL::Disable( gl::DEPTH_TEST);
	}
	void GL3AsyncProxy::disableDepthTest(){
		queue.pushCommand( _disableDepthTest);
	}
	
	
	void _enableDepthTest( u8*){
		GL::Enable( gl::DEPTH_TEST);
	}
	void GL3AsyncProxy::enableDepthTest(){
		queue.pushCommand( _enableDepthTest);
	}
	
	
	void _setDepthFunc( u8* p){
		parms< GLenum> parm{ p};
		GL::DepthFunc( *parm);
	}
	void GL3AsyncProxy::setDepthFunc( DepthTest test){
		GLenum func;
		switch(test){
			case DepthTest::DrawIfNearest: 			func = gl::LESS; break;
			case DepthTest::DrawIfNearestOrEqual: 	func = gl::LEQUAL; break;
			default: 								func = gl::ALWAYS; break;
		}
		queue.pushCommand( _setDepthFunc, func);
	}
	
	
	void _disableDepthMask( u8*){
		GL::DepthMask( 0);
	}
	void GL3AsyncProxy::disableDepthMask(){
		queue.pushCommand( _disableDepthMask);
	}
	
	
	void _enableWireframeMode( u8*){
		GL::PolygonMode( gl::FRONT_AND_BACK, gl::LINE);
	}
	void GL3AsyncProxy::enableWireframeMode(){
		queue.pushCommand( _enableWireframeMode);
	}
	
	
	void _disableWireframeMode( u8*){
		GL::PolygonMode( gl::FRONT_AND_BACK, gl::FILL);
	}
	void GL3AsyncProxy::disableWireframeMode(){
		queue.pushCommand( _disableWireframeMode);
	}
	
	
	void _disableBlending( u8*){
		GL::Disable( gl::BLEND);
	}
	void GL3AsyncProxy::disableBlending(){
		queue.pushCommand( _disableBlending);
	}
	
	
	void _enableBlending( u8*){
		GL::Enable( gl::BLEND);
	}
	void GL3AsyncProxy::enableBlending(){
		queue.pushCommand( _enableBlending);
	}
	
	
	struct blendFuncParm{
		GLenum sfactor;
		GLenum dfactor;
	};
	void _setBlendFunc( u8* p){
		parms< blendFuncParm> parm{ p};
		GL::BlendFunc( parm->sfactor, parm->dfactor);
	}
	void GL3AsyncProxy::setBlendFunc( BlendMode mode){
		blendFuncParm parm;
		switch( mode){
			case BlendMode::Transparent: 
					parm.sfactor = gl::ONE; 
					parm.dfactor = gl::ONE_MINUS_SRC_ALPHA; break;
			default: 
					parm.sfactor = gl::ONE; 
					parm.dfactor = gl::ZERO; break;
		}
		queue.pushCommand( _setBlendFunc, parm);
	}
	
	
	void _disableStencilTest( u8*){
		GL::Disable( gl::STENCIL_TEST);
	}
	void GL3AsyncProxy::disableStencilTest(){
		queue.pushCommand( _disableStencilTest);
	}
	
	
	void _enableStencilTest( u8*){
		GL::Enable( gl::STENCIL_TEST);
	}
	void GL3AsyncProxy::enableStencilTest(){
		queue.pushCommand( _enableStencilTest);
	}
	
	struct stencilFuncParm{
		GLenum func;
		GLint  ref;
	};
	void _setStencilFunc( u8* p){
		parms< stencilFuncParm> parm{ p};
		GL::StencilFunc( parm->func, parm->ref, 0xFF);
	}
	void GL3AsyncProxy::setStencilFunc( StencilTest test, u8 val){
		stencilFuncParm parm;
		parm.ref = val;
		switch(test){
			case StencilTest::DrawIfGreaterThanVal:	
								parm.func = gl::GREATER; break;
			case StencilTest::DrawIfSmallerThanVal:	
								parm.func = gl::LESS; break;
			case StencilTest::DrawIfEqualToVal:		
								parm.func = gl::EQUAL; break;
			case StencilTest::DrawIfNotVal:			
								parm.func = gl::NOTEQUAL; break;
			default:								
								parm.func = gl::ALWAYS; break;
		}
		queue.pushCommand( _setStencilFunc, parm);
	}
	
	
	void _setStencilOp( u8* p){
		parms< GLenum> parm{ p};
		GL::StencilOp( gl::KEEP, gl::KEEP, *parm);
	}
	void GL3AsyncProxy::setStencilOp( StencilOp op){
		GLenum zspass;
		switch(op){
			case StencilOp::Invert:		zspass = gl::INVERT; break;
			case StencilOp::ToVal:		zspass = gl::REPLACE; break;
			case StencilOp::ToZero:		zspass = gl::ZERO ; break;
			case StencilOp::Increment:	zspass = gl::INCR; break;
			case StencilOp::Decrement:	zspass = gl::DECR ; break;
			default:  					zspass = gl::KEEP; break;
		}
		queue.pushCommand( _setStencilOp, zspass);
	}
	
	
	void _useProgram( u8* p){
		parms< NativeHandle> parm{ p};
		GL::UseProgram(*parm);
	}
	void GL3AsyncProxy::useProgram( NativeHandle program){
		queue.pushCommand( _useProgram, program);
	}
	
	
	void _activeTextureUnit( u8* p){
		parms< NativeEnum> parm{ p};
		GL::ActiveTexture(*parm);
	}
	void GL3AsyncProxy::activeTextureUnit( u32 unit){
		NativeEnum textureUnit = Graphics::texture0 + unit;
		queue.pushCommand( _activeTextureUnit, textureUnit);
	}
	
	
	struct bindSamplerParm{
		NativeHandle	unit;
		NativeHandle	sampler;
	};
	void _bindSampler( u8* p){
		parms< bindSamplerParm> parm{ p};
		GL::BindSampler( parm->unit, parm->sampler);
	}
	void GL3AsyncProxy::bindSampler( NativeHandle unit, NativeHandle sampler ){
		bindSamplerParm parm;
		parm.unit = unit;
		parm.sampler = sampler;
		queue.pushCommand( _bindSampler, parm);
	}
	
	
	struct bindTextureParm{
		NativeEnum 		target;
		NativeHandle	texture;
	};
	void _bindTexture( u8* p){
		parms< bindTextureParm> parm{ p};
		GL::BindTexture( parm->target, parm->texture);
	}
	void GL3AsyncProxy::bindTexture( NativeEnum target, NativeHandle texture){
		bindTextureParm parm;
		parm.target = target;
		parm.texture = texture;
		queue.pushCommand( _bindTexture, parm);
	}
	
	
	void _setVao( u8* p){
		parms< NativeHandle> parm{ p};
		GL::BindVertexArray( *parm);
	}
	void GL3AsyncProxy::setVao( NativeHandle vao){
		queue.pushCommand( _setVao, vao);
	}
	#undef GL
} // namespace GL3
} // namespace Bade