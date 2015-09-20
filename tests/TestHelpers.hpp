/*******************************************************************************
   Copyright (C) 2014-2015 Dario Oliveri
   See copyright notice in LICENSE.md
*******************************************************************************/
#pragma once
#include <chrono>
void badeAssert( const char* code, const char* file, const int line);

typedef std::chrono::high_resolution_clock Clock;

#define BADE_ASSERT(x)do{if(!(x))badeAssert(#x,__FILE__,__LINE__);}while(false)

