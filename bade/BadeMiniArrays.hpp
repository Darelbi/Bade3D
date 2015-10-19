/*******************************************************************************
   Copyright (C) 2015 Dario Oliveri
   See copyright notice in LICENSE.md
*******************************************************************************/
#pragma once
#include "BadeForwards.hpp"
 
namespace Bade {
	
	// Data place holders for vertex components
	
	
	template< typename T, unsigned int N, bool Alias = false>
	struct MiniArray{
		T data[N];
		
		MiniArray< T, N> &operator=(const MiniArray< T, N> & other) {
			for(int i=0; i< N; i++)
				this->data[i] = other.data[i];
			return *this;
		}
	};
	
	template< typename T, bool Alias>
	struct MiniArray< T, 1, Alias>{
		union{
			union { T X; T x; T R; T r; T U; T u;};
			T data[1];
		};
		
		MiniArray( T xx) : data{ xx} {
		}       
		
		MiniArray< T, 1> &operator=(const MiniArray< T, 1> & other) {
			x = other.x;
			return *this;
		}
	};

	template< typename T, bool Alias>
	struct MiniArray< T, 2, Alias>{
		union{
			union { T X; T x; T R; T r; T U; T u;};
			union { T Y; T y; T G; T g; T V; T v;};
			T data[2];
		};

		MiniArray( T xx, T yy) : data{ xx, yy} {
		}         
		
		MiniArray< T, 2> &operator=(const MiniArray< T, 2> & other) {
			x = other.x; y = other.y;
			return *this;
		}
	};

	template< typename T, bool Alias>
	struct MiniArray< T, 3, Alias>{
		union{
			union { T X; T x; T R; T r; T U; T u;};
			union { T Y; T y; T G; T g; T V; T v;};
			union { T Z; T z; T B; T b; T S; T s;};
			T data[3];
		};
		
		MiniArray( T xx, T yy, T zz) : data{ xx, yy, zz} {
		}     
		
		MiniArray< T, 3> &operator=(const MiniArray< T, 3> & other) {
			x = other.x; y = other.y; z = other.z;
			return *this;
		}
	};

	template< typename Tn, bool Alias>
	struct MiniArray< Tn, 4, Alias>{
		union{
			union { Tn X; Tn x; Tn R; Tn r; Tn U; Tn u;};
			union { Tn Y; Tn y; Tn G; Tn g; Tn V; Tn v;};
			union { Tn Z; Tn z; Tn B; Tn b; Tn S; Tn s;};
			union { Tn W; Tn w; Tn A; Tn a; Tn T; Tn t;};
			Tn data[4];
		};

		MiniArray( Tn xx, Tn yy, Tn zz, Tn ww) : data{ xx, yy, zz, ww} {
		}   
		
		MiniArray< Tn, 4> &operator=( const MiniArray< Tn, 4> & other) {
			x = other.x; y = other.y; z = other.z; w = other.w;
			return *this;
		}
	};
	
	
	// Array of miniarrays. Syntactic convenience over custom vertex formats
	// Are valid as long as the Shader generated them is alive
	// (Just store maxiarrays and their shader in same scope/lifetime)
	// To save performance there's no check against "maximum" index
	// and you have to reset arrays each time you reallocate them
	template< typename M>
	class MaxiArray{
		
		using u8Ptr = u8*;
		u8Ptr 	dataPointer;
		u8Ptr * pointerLocation;
		u32 	stride;
	
	public:
	
		MaxiArray( u32 vertexStride, u8Ptr * pointer){
			pointerLocation = pointer;
			stride = vertexStride;
			reset();
		}
		
		// If array size is changed we reallocate it and that
		// changes the pointed address
		void reset(){
			dataPointer = *pointerLocation;
		}
		
		// PREFER THIS METHOD
		M & operator[](const u32 index){
			return *reinterpret_cast<M*>( dataPointer + stride*index);
		}

		// may allow the compiler to optimize many arrays on same Shader
		M & operator()(const u32 vertexStride, const u32 index){
			return *reinterpret_cast<M*>( dataPointer + vertexStride*index);
		}	
	};

	// Graphics Vector types
	using float1  = MiniArray< float, 1>;
    using float2  = MiniArray< float, 2>;
    using float3  = MiniArray< float, 3>;
    using float4  = MiniArray< float, 4>;

    using int1    = MiniArray< s32, 1>;
    using int2    = MiniArray< s32, 2>;
    using int3    = MiniArray< s32, 3>;
    using int4    = MiniArray< s32, 4>;

    using uint1   = MiniArray< u32, 1>;
    using uint2   = MiniArray< u32, 2>;
    using uint3   = MiniArray< u32, 3>;
    using uint4   = MiniArray< u32, 4>;

    using half2   = MiniArray< u16, 2, true>;
    using half4   = MiniArray< u16, 4, true>;

    using short2  = MiniArray< s16, 2>;
    using short4  = MiniArray< s16, 4>;

    using ushort2 = MiniArray< u16, 2>;
    using ushort4 = MiniArray< u16, 4>;

    using byte4   = MiniArray< s8, 4>;

    using ubyte4  = MiniArray< u8, 4>;
	
} // namespace Bade