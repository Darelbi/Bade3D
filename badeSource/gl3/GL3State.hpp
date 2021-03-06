/*******************************************************************************
   Copyright (C) 2015 Dario Oliveri
   See copyright notice in LICENSE.md
*******************************************************************************/
#pragma once
#include "../BadeRenderPass.hpp"
#include "../BadeRenderSlot.hpp"
#include "../BadeTextureSlot.hpp"
#include "../PortableGraphics.hpp" // GL header


namespace Bade {
namespace GL3 {
	
	class GL3TextureUnit: public TextureSlot{
	public:
		NativeHandle	texture = 0;
		NativeHandle	sampler = 0;
		NativeEnum		target;
		u8				unit;
		bool			used = false;
	};
	
	struct BADE_API GL3State{
		
		bool				scissorTest = false;
		ushort4				scissorRectangle = ushort4( u16(65535), u16(65535), u16(65535), u16(65535));
		
		bool 				colorMask  = true;
		bool				colorCleared = false;
		float4				clearColor = float4( 0.f, 0.f, 0.f, 0.f); 	// RGBA values
		
		bool				depthMaskEnabled = true;
		bool				depthTestEnabled = false;
		bool				depthCleared = false;
		DepthTest			depthTest = DepthTest::DrawIfNearest;
		
		GLuint				stencilMask = 0xFF;
		bool				stencilTestEnabled = false;
		bool				stencilCleared = false;
		StencilTest			stencilTest = StencilTest::DrawAlways;
		u8					stencilVal = 0 ;
		StencilOp			stencilOp = StencilOp::Keep; //TODO: BUG need stencil test separed
		
		bool				wireframe = false;
		BlendMode   		blendMode = BlendMode::Opaque;
		BlendMode   		lastBlendMode = BlendMode::Opaque;
		
		
		//---
		int					activeTextureUnit = -1;
			
		NativeHandle		vao = 0;
		NativeHandle		program = 0;
		
		GL3TextureUnit		textures[ Configuration::textureUnits];
		
		GL3TextureUnit		texturesCache[ Configuration::textureUnits];
		
		void reinitialize();
	};

} // namespace GL3
} // namespace Bade