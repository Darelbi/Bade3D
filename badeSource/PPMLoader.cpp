#include "PPMLoader.hpp"
#include "Assert.hpp"
#include <iostream>
#include <fstream>
#include <string>

namespace Bade{
namespace Deprecated{ //deprecated because originally created for quick tests
	
u8* LoadPPM_P3(const c8 * filename, u32 width, u32 height)
{
	std::ifstream myfile;
	myfile.open(filename);
	
	char p3[2];
	
	u32 d;
	
	if(! (myfile >> p3[0]) )
		return nullptr;
	
	if(! (myfile >> p3[1]) )
		return nullptr;
	
	if( p3[0] != 'P' || p3[1] !='3')
		return nullptr;
	
	// I KNOW comments are NOT handled. Sorry :)
	
	if(! (myfile>> width))
		return nullptr;
	
	if(! (myfile>> height))
		return nullptr;
		
	if(! (myfile>> d))
		return nullptr;
	
	if(d!=255)
		return nullptr;		
	
	u32 lineBytes = 3*width;
	u32 lineSize = (lineBytes | 0x03) + 1; //next multiple of 4 for w*3
	u32 padding  = lineSize - lineBytes; // by default OpenGL has 4 bytes alignment
	u32 imageSize = lineSize*height;
	
	u8 * image = new u8[imageSize];
	
	for(int i=0; i<imageSize; ){
		for(int j=0; j<lineBytes; j++,i++){
			u32 color;
			if( !(myfile>>color)){
				delete [] image;
				return nullptr;
			}
			image[i] = color;
		}
		i+=padding;
	}
	
	return image;
}

} // namespace Deprecated
} // namespace Bade