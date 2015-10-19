/*******************************************************************************
   Copyright (C) 2015 Dario Oliveri
   See copyright notice in LICENSE.md
*******************************************************************************/
#include "GL3State.hpp"

namespace Bade {
namespace GL3 {
		
	void GL3State::reinitialize(){
		scissorTest = false;
		scissorRectangle = ushort4( u16(65535), u16(65535), u16(65535), u16(65535));
		colorMask = true;
		colorCleared = false;
		depthMaskEnabled = true;
		depthTestEnabled = false;
		depthCleared = false;
		depthTest = DepthTest::DrawIfNearest;
		stencilMask = 0xFF;
		stencilTestEnabled = false;
		stencilCleared = false;
		stencilTest = StencilTest::DrawAlways;
		stencilVal = 0x00;
		stencilOp = StencilOp::Keep;
		wireframe = false;
		blendMode = BlendMode::Opaque;
		lastBlendMode = BlendMode::Opaque;
		clearColor = float4( 0.f, 0.f, 0.f, 0.f);
		activeTextureUnit = -1;
		
		for( int i=0; i<Configuration::textureUnits; i++){
			textures[i].unit		= 0;
			texturesCache[i].unit	= 0;
		}
	}
} // namespace GL3
} // namespace Bade