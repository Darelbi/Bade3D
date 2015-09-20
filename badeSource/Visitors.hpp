/*******************************************************************************
   Copyright (C) 2015 Dario Oliveri
   See copyright notice in LICENSE.md
*******************************************************************************/
#pragma once

namespace Bade {

	namespace GL3{
		class GL3Texture;
		class GL3RenderTexture;
	}

	namespace GLES2{
		class GLES2Texture;
		class GLES2RenderTexture;
	}

	namespace vk{	// Vulkan
		class vkTexture;
		class vkRenderTexture;
	}

	namespace mt{	// Mantle
		class mtTexture;
		class mtRenderTexture;
	}

	namespace wp{	// WindowsPhone
		class wpTextures;
		class wpRenderTextures;
	}

	class TextureVisitor{
	public:
		virtual void visit( GL3::GL3Texture &) {};
		virtual void visit( GLES2::GLES2Texture &) {};
		virtual void visit( vk::vkTexture &) {};
		virtual void visit( mt::mtTexture &) {};
		virtual void visit( wp::wpTextures &) {};
		virtual ~TextureVisitor(){}
	};

	class RenderTextureVisitor{
	public:
		virtual void visit( GL3::GL3RenderTexture &) {};
		virtual void visit( GLES2::GLES2RenderTexture &) {};
		virtual void visit( vk::vkRenderTexture &) {};
		virtual void visit( mt::mtRenderTexture &) {};
		virtual void visit( wp::wpRenderTextures &) {};
		virtual ~RenderTextureVisitor(){}
	};

} // namespace Bade