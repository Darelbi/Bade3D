/*******************************************************************************
   Copyright (C) 2015 Dario Oliveri
   See copyright notice in LICENSE.md
*******************************************************************************/
#pragma once
#include "BadeForwards.hpp"

namespace Bade {
	
	enum struct TextureType: u8{
		Texture2D,
		Cubemap
	};
	
	enum struct VertexAttribute: u8{
		 //32 bit values.
        float1, float2, float3, float4,     /// FLOAT (map to f32) // AVOID FLOAT3 IN UNIFORM BUFFER
        int1,   int2,   int3,   int4,       /// INT    (map to s32)
        uint1,  uint2,  uint3,  uint4,      /// UNSIGNED INT (map to u32)

        //16 bit values
        half2,  half4,      /// HALF-FLOAT(map to u16)
        short2, short4,     /// SHORT     (map to s16)
        ushort2,ushort4,    /// UNSIGNED SHORT (map to u16)

        //8 bit values
        byte4,       /// BYTE      (map to s8)
        ubyte4      /// UNSIGNED BYTE  (map to u8)
	};
	
	/** Options for generating a shader program. */
	class BADE_API ShaderOptions: public ManagedEntity{
		
	public:
	
		virtual void addVertexAttribute( 
							const char * 	name, 
							VertexAttribute attr) = 0;
		
		void addTexture( 
							const char * 	name, 
							TextureType 	type, 
							u8 				textureUnit ) = 0;
	};
} // namespace Bade