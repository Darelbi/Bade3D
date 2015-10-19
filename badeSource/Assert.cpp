#include "Assert.hpp"
#include <iostream>
#include <exception>

namespace Bade{
	void failure( const char* code, const char* file, const int line){
		std::cerr<<"---------------------------------------------"<<std::endl;
		std::cerr<<"\nAssertion Failed:"<<std::endl;
		std::cerr<<"CODE: "<<code<<std::endl;
		std::cerr<<"FILE: "<<file<<std::endl;
		std::cerr<<"LINE: "<<line<<std::endl;
		std::cerr<<"---------------------------------------------"<<std::endl;
		
		// TODO: Some users want exceptions disabled
		throw std::runtime_error("Assertion failed, check std::err log");
	}
}