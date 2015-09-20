/*******************************************************************************
   Copyright (C) 2014-2015 Dario Oliveri
   See copyright notice in LICENSE.md
*******************************************************************************/
#pragma once
#include "BadeForwards.hpp"
 
namespace Bade {
	
	// Data place holders for vertex components
	
	
	template< typename T, unsigned int N>
	struct MiniArray{
		T data[N];
		
		MiniArray< T, N> &operator=(const MiniArray< T, N> & other) {
			for(int i=0; i< N; i++)
				this->data[i] = other.data[i];
			return *this;
		}
	};
	
	template< typename T>
	struct MiniArray< T, 1>{
		union{
			union { T X; T x; T R; T r; T U; T u;};
			T data[1];
		};
		
		template< typename K>
		MiniArray( K xx) : data{ xx} {
		}       
		
		MiniArray< T, 1> &operator=(const MiniArray< T, 1> & other) {
			x = other.x;
			return *this;
		}
	};

	template< typename T>
	struct MiniArray< T, 2>{
		union{
			union { T X; T x; T R; T r; T U; T u;};
			union { T Y; T y; T G; T g; T V; T v;};
			T data[2];
		};

		template< typename K>
		MiniArray( K xx, K yy) : data{ xx, yy} {
		}         
		
		MiniArray< T, 2> &operator=(const MiniArray< T, 2> & other) {
			x = other.x; y = other.y;
			return *this;
		}
	};

	template< typename T>
	struct MiniArray< T, 3>{
		union{
			union { T X; T x; T R; T r; T U; T u;};
			union { T Y; T y; T G; T g; T V; T v;};
			union { T Z; T z; T B; T b; T S; T s;};
			T data[3];
		};

		template< typename K>
		MiniArray( K xx, K yy, K zz) : data{ xx, yy, zz} {
		}     
		
		MiniArray< T, 3> &operator=(const MiniArray< T, 3> & other) {
			x = other.x; y = other.y; z = other.z;
			return *this;
		}
	};

	template< typename Tn>
	struct MiniArray< Tn, 4>{
		union{
			union { Tn X; Tn x; Tn R; Tn r; Tn U; Tn u;};
			union { Tn Y; Tn y; Tn G; Tn g; Tn V; Tn v;};
			union { Tn Z; Tn z; Tn B; Tn b; Tn S; Tn s;};
			union { Tn W; Tn w; Tn A; Tn a; Tn T; Tn t;};
			Tn data[4];
		};

		template< typename K>
		MiniArray( K xx, K yy, K zz, K ww) : data{ xx, yy, zz, ww} {
		}   
		
		MiniArray< Tn, 4> &operator=(const MiniArray< Tn, 4> & other) {
			x = other.x; y = other.y; z = other.z; w = other.w;
			return *this;
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

    using half2   = MiniArray< u16, 2>;
    using half4   = MiniArray< u16, 4>;

    using short2  = MiniArray< s16, 2>;
    using short4  = MiniArray< s16, 4>;

    using ushort2 = MiniArray< u16, 2>;
    using ushort4 = MiniArray< u16, 4>;

    using byte4   = MiniArray< s8, 4>;

    using ubyte4  = MiniArray< u8, 4>;
	
} // namespace Bade