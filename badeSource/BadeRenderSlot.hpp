/*******************************************************************************
   Copyright (C) 2015 Dario Oliveri
   See copyright notice in LICENSE.md
*******************************************************************************/
#pragma once
#include "BadeForwards.hpp"
#include "BadeStdVector.hpp"

namespace Bade {
	
	struct BADE_API TextureSlot: public ManagedEntity {
	
	};
	
	enum struct DrawMode: u8{
		Points,
		Line,
		Triangles,
		LinesStrip,
		TriangleStrip
	};
	
	class BADE_API RenderSlot{

	public:
	
		StdVector< TextureSlotPtr>	textures;
		MeshBufferPtr				mesh;		//required for rendering
		IndexBufferPtr				indices;	//optional
		ShaderPtr					shader;		//required for rendering
		
		// Restart index is the index used for restarting the primitive
		// when you are rendering using a IndexBuffer and one of the 
		// *Strip modes. If either there is no IndexBuffer, or DrawMode
		// is not a "Strip" mode, restart index is ignored.
		u16				restartIndex	= 65535;
		DrawMode		mode			= DrawMode::Triangles;
	};	
} // namespace Bade