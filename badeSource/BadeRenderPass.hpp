/*******************************************************************************
   Copyright (C) 2015 Dario Oliveri
   See copyright notice in LICENSE.md
*******************************************************************************/
#pragma once
#include "BadeForwards.hpp"
#include "BadeStdVector.hpp"
#include "BadeMiniArrays.hpp"
#include "BadeRenderSlot.hpp"

namespace Bade {

	/** Alpha blending: please read blending tutorial ;).*/
    enum struct BlendMode: u8{ 
        Transparent, //Additive & Transparent
        Opaque
    };
	
	/** When to drawing something based on depth*/
	enum struct DepthTest: u8{ 
        DrawIfNearest,
        DrawIfNearestOrEqual,
        DrawAlways
    };
	
	/** Compare stencil buffer pixels with given Val.*/
	enum struct StencilTest: u8{
		DrawAlways,
        DrawIfGreaterThanVal,
        DrawIfSmallerThanVal,
        DrawIfEqualToVal,
		DrawIfNotVal
    };
	
	/** Function applied to stencil buffer pixels.*/
	enum struct StencilOp: u8{
		Keep,
		Invert,
		ToVal,
		ToZero,
		Increment,
		Decrement
	};
	
	class BADE_API RenderPass{
		
	public:
	
		RenderPass( RenderPass && other) = default;
		RenderPass &operator=( RenderPass && other) = default;
	
		// alpha 0 is transparent
		float4	color			= float4( 0.f, 0.f, 0.f, 0.f);			

		bool clearColor			= false;
		bool clearDepth			= false;
		bool clearStencil		= false;
	
		bool colorWrite 		= true;
		bool depthWrite 		= true;
		bool wireframe			= false;
		
		bool scissorTest		= false;

		// origin in lower left corner, Y increase UP, X increase Right
		// (x,y, height, width)
		ushort4	scissorRectangle= ushort4( u16(0), u16(0), u16(0), u16(0));
		
								// origin in lower left corner
								// y increase UP
								// x increase right

		BlendMode   blendMode   = BlendMode::Opaque;
		DepthTest	depthTest	= DepthTest::DrawIfNearest;
		StencilTest	stencilTest = StencilTest::DrawAlways;
		StencilOp	stencilOp	= StencilOp::Keep;
		u8			stencilVal  = 0;

		const char *name		= nullptr; // debugging name
		
		StdVector< RenderSlot>	slots;
	};	
} // namespace Bade