/*******************************************************************************
   Copyright (C) 2014-2015 Dario Oliveri
   See copyright notice in LICENSE.md
*******************************************************************************/
#pragma once


// include GLES2 or GL3.3
#if defined ( EMSCRIPTEN) || defined ( __ANDROID__)

    /** Emscripten/Android GLES2 headers */
    #include <GLES2/gl2.h>

#elif defined ( TARGET_OS_IPHONE) || defined( TARGET_IPHONE_SIMULATOR)

    /** iOS headers for GLES2. */
    #include <OpenGLES/ES2/gl.h>

#else

    /** glLoadGen generated file, Desktop. */
    #include "gl3/gl_core_3_3.hpp"
	namespace Bade{
		using NativeHandle 	= GLuint;
		using NativeEnum	= GLenum;
		struct Graphics
		{
			static const NativeEnum texture0 = gl::TEXTURE0;
		};
	}
    
#endif

//  currently no WindowsPhone. it has no GL :/