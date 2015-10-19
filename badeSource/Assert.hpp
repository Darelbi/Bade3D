/*******************************************************************************
   Copyright (C) 2015 Dario Oliveri
   See copyright notice in LICENSE.md
*******************************************************************************/
#pragma once
#include "BadeForwards.hpp"

namespace Bade{
	void BADE_API failure( const char* code, const char* file, const int line);
}

#define assert(x){do{if(!(x))Bade::failure(#x,__FILE__,__LINE__);}while(false);}
