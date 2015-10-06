/*******************************************************************************
   Copyright (C) 2015 Dario Oliveri
   See copyright notice in LICENSE.md
*******************************************************************************/
#pragma once
#include "../BadeMeshBuffer.hpp"


namespace Bade {
namespace GL3 {
	
	class BADE_API GL3MeshBuffer: public MeshBuffer{
		
	public: 

		NativeHandle			vao = 0;
	};

} // namespace GL3
} // namespace Bade