/*******************************************************************************
   Copyright (C) 2015 Dario Oliveri
   See copyright notice in LICENSE.md
*******************************************************************************/
#pragma once
#include <memory>

#ifndef BADE_API

	#define BADE_API
	
    #if defined( __WIN32__ ) || defined( _WIN32 )
            /**
                On Windows we need special threatment for DLLs.
            */    
            #ifdef BADE_BUILD_DLL
                    #undef BADE_API
                    #define BADE_API __declspec(dllexport)
            #elif defined (BADE_USE_DLL)
                    #undef BADE_API
                    #define BADE_API __declspec(dllimport)
            #endif
    #endif
#endif

// This file greatly help reducing the numbers of headers to include
// effectively helping making other classes more readable

namespace Bade{

#ifdef _MSC_VER

    /* Unsigned integers. */
    typedef unsigned __int64    u64;
    typedef unsigned __int32	u32;
    typedef unsigned __int16	u16;
    typedef unsigned __int8		u8;

    /* Signed integers. */
    typedef __int16			s16;
    typedef __int32			s32;
    typedef __int64         s64;
    typedef __int8			s8;

#else

    /* Unsigned integers. */
    typedef unsigned long long u64;
    typedef unsigned int       u32;
    typedef unsigned short     u16;
    typedef unsigned char      u8;

    /* Signed integers. */
    typedef long long   s64;
    typedef int         s32;
    typedef short       s16;
    typedef signed char s8;

#endif

    /* Char. */
    //typedef char    c8; //just use "const char *" if needed
	
	template< typename T=int>
	class ManageEngine;
	
	// Managed types: low overhead reference counting.
	class BADE_API ManagedEntity{
		u32 referenceCount = 1;
		friend struct ManagedDeleter;
		
		template <typename T>
		friend class ManageEngine;
		inline void referenceIncrement(){ referenceCount++; }
	public:
		inline u32 getReferenceCount(){ return referenceCount;}
	};

	struct ManagedDeleter { // Do not delete the object. Managers will delete it.
		void operator()( ManagedEntity * entity) { entity->referenceCount--; }
	};
	
	template< typename T>
	struct NoDeleter {
		void operator() ( T* data) {}
	};
	
	// Compile time configuration of the engine. 
	// If you change ANY of the values you have to RECOMPILE the engine and
	// any application using it. 
	struct BADE_API Configuration
	{
		static const u32	textureUnits 	 = 32;
		static const u32	uniformUnits 	 = 32;
		static const u32	vertexAttributes = 8;
	};
	
	// Forward declarations
	class RenderQueue;
	class RenderPass;
	class RenderSlot;
	class TextureSlot;
	
	class TextureManager;
	class ImageManager;
	class ShaderManager;

	struct ColorRGB;
	struct ColorRGBA;
	class BitmapImage;

	class Texture;
	class Sampler;
	class MeshBuffer;
	class IndexBuffer;
	
	class VertexMain;
	class FragmentMain;
	class Shader;
	class ShaderOptions;

	class TextureVisitor;
	class RenderTextureVisitor;
	
	//Forwards declaration of enums
		
	enum struct InternalFormat: u8; //BadeTexture.hpp
		
	enum struct InternalWriteFormat: u8; //BadeTextureManager.hpp
	enum struct FilteringMode: u8;
	enum struct TextureWrap: u8;
	
	enum struct TextureType: u8;	//BadeShaderOptions.hpp
	enum struct VertexAttribute: u8; 
	
	//Forward declarations of smart pointer types
	using RenderQueuePtr	= std::shared_ptr< RenderQueue>;
	using ImageManagerPtr	= std::shared_ptr< ImageManager>;
	using TextureManagerPtr = std::shared_ptr< TextureManager>;
	using ShaderManagerPtr	= std::shared_ptr< ShaderManager>;
	
	/** ForeignBuffer allows accessing data in pointer arrays but prevent
		accidental deletion. Makes clear you do not own the pointer.*/
	template< typename T>
	using ForeignBuffer		= std::unique_ptr< T[],				NoDeleter<T>>;
	
	template< typename T>
	using ManagedResource 	= std::unique_ptr< T, 				ManagedDeleter>;
	
	//
	//  RESOURCES: whethever you have any of the following pointers
	//	that's mean you have actually allocated somewhere a resource
	//	on GPU or on SYSTEM. Each "managed unique_ptr" can be copied
	// 	using only the corresponding manager (You cannot accidentally
	//	create a resource leak because you need a explicit dependency
	//	on its manager when you want to reuse same resource)
	//
	using EntityPtr			= ManagedResource< ManagedEntity>;
	using BitmapImagePtr	= ManagedResource< BitmapImage >;
	using TexturePtr		= ManagedResource< Texture >;
	using SamplerPtr		= ManagedResource< Sampler >;
	using MeshBufferPtr		= ManagedResource< MeshBuffer >;
	using IndexBufferPtr	= ManagedResource< IndexBuffer >;
	using ShaderPtr			= ManagedResource< Shader >;
	using ShaderOptionsPtr	= ManagedResource< ShaderOptions >;
	using TextureSlotPtr	= ManagedResource< TextureSlot >;
	
} // namespace Bade