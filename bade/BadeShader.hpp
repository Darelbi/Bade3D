/*******************************************************************************
   Copyright (C) 2015 Dario Oliveri
   See copyright notice in LICENSE.md
*******************************************************************************/
#pragma once
#include "BadeMiniArrays.hpp"
#include "BadeVertexAttribute.hpp"

namespace Bade {
	
	class BADE_API Shader: public ManagedEntity{
		
	public:
	
		/** Get the pointer to a vertex component. */
		template< typename A>
		MaxiArray< A> getVertexComponent( const char * attributename);
	
	protected:
		
		virtual u8 ** getAttribute( const char * name, 
									VertexAttribute attr,
									u32 & stride ) = 0;
	
	};
	
	/// Templates specialitazions. Just boilerplate code ^^
#if 0
	template<>
	MaxiArray< float1> Shader::getVertexPtr( const char * name){
		u32 stride;
		u8** p = getAttribute( name, VertexAttribute::float1, stride);
		return MaxiArray< float1> ( stride, p);
	}
	
	template<>
	MaxiArray< float2> Shader::getVertexPtr( const char * name){
		u32 stride;
		u8** p = getAttribute( name, VertexAttribute::float2, stride);
		return MaxiArray< float2> ( stride, p);
	}
	
	template<>
	MaxiArray< float3> Shader::getVertexPtr( const char * name){
		u32 stride;
		u8** p = getAttribute( name, VertexAttribute::float3, stride);
		return MaxiArray< float3> ( stride, p);
	}
	
	template<>
	MaxiArray< float4> Shader::getVertexPtr( const char * name){
		u32 stride;
		u8** p = getAttribute( name, VertexAttribute::float4, stride);
		return MaxiArray< float4> ( stride, p);
	}
	
	template<>
	MaxiArray< int1> Shader::getVertexPtr( const char * name){
		u32 stride;
		u8** p = getAttribute( name, VertexAttribute::int1, stride);
		return MaxiArray< int1> ( stride, p);
	}
	
	template<>
	MaxiArray< int2> Shader::getVertexPtr( const char * name){
		u32 stride;
		u8** p = getAttribute( name, VertexAttribute::int2, stride);
		return MaxiArray< int2> ( stride, p);
	}
	
	template<>
	MaxiArray< int3> Shader::getVertexPtr( const char * name){
		u32 stride;
		u8** p = getAttribute( name, VertexAttribute::int3, stride);
		return MaxiArray< int3> ( stride, p);
	}
	
	template<>
	MaxiArray< int4> Shader::getVertexPtr( const char * name){
		u32 stride;
		u8** p = getAttribute( name, VertexAttribute::int4, stride);
		return MaxiArray< int4> ( stride, p);
	}	
	
	template<>
	MaxiArray< uint1> Shader::getVertexPtr( const char * name){
		u32 stride;
		u8** p = getAttribute( name, VertexAttribute::uint1, stride);
		return MaxiArray< uint1> ( stride, p);
	}
	
	template<>
	MaxiArray< uint2> Shader::getVertexPtr( const char * name){
		u32 stride;
		u8** p = getAttribute( name, VertexAttribute::uint2, stride);
		return MaxiArray< uint2> ( stride, p);
	}
	
	template<>
	MaxiArray< uint3> Shader::getVertexPtr( const char * name){
		u32 stride;
		u8** p = getAttribute( name, VertexAttribute::uint3, stride);
		return MaxiArray< uint3> ( stride, p);
	}
	
	template<>
	MaxiArray< half2> Shader::getVertexPtr( const char * name){
		u32 stride;
		u8** p = getAttribute( name, VertexAttribute::half2, stride);
		return MaxiArray< half2> ( stride, p);
	}
	
	template<>
	MaxiArray< half4> Shader::getVertexPtr( const char * name){
		u32 stride;
		u8** p = getAttribute( name, VertexAttribute::half4, stride);
		return MaxiArray< half4> ( stride, p);
	}
	
	template<>
	MaxiArray< short2> Shader::getVertexPtr( const char * name){
		u32 stride;
		u8** p = getAttribute( name, VertexAttribute::short2, stride);
		return MaxiArray< short2> ( stride, p);
	}
	
	template<>
	MaxiArray< short4> Shader::getVertexPtr( const char * name){
		u32 stride;
		u8** p = getAttribute( name, VertexAttribute::short4, stride);
		return MaxiArray< short4> ( stride, p);
	}
	
	template<>
	MaxiArray< ushort2> Shader::getVertexPtr( const char * name){
		u32 stride;
		u8** p = getAttribute( name, VertexAttribute::ushort2, stride);
		return MaxiArray< ushort2> ( stride, p);
	}
	
	template<>
	MaxiArray< ushort4> Shader::getVertexPtr( const char * name){
		u32 stride;
		u8** p = getAttribute( name, VertexAttribute::ushort4, stride);
		return MaxiArray< ushort4> ( stride, p);
	}
	
	template<>
	MaxiArray< byte4> Shader::getVertexPtr( const char * name){
		u32 stride;
		u8** p = getAttribute( name, VertexAttribute::byte4, stride);
		return MaxiArray< byte4> ( stride, p);
	}
	
	template<>
	MaxiArray< ubyte4> Shader::getVertexPtr( const char * name){
		u32 stride;
		u8** p = getAttribute( name, VertexAttribute::ubyte4, stride);
		return MaxiArray< ubyte4> ( stride, p);
	}
#endif
} // namespace Bade