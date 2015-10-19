#include "BadeBitmapImage.hpp"

#include "ManageEngine.hpp"
#include "PPMLoader.hpp"

#include <iostream>
#include <fstream>
#include <string>

namespace Bade{
namespace Deprecated{ //deprecated because originally created for quick tests
	
Bade::BitmapImagePtr
	LoadPPM_P3( Bade::ManageEngine< BitmapImage> & images, const char * filename)
{
	std::ifstream myfile;
	myfile.open(filename);
	
	char p3[2];
	
	u32 d, width, height;
	
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
	
	auto image = images.allocate( width, height, false);
	
	bool error = false;
	image->foreachPixelRGB( [&error, & myfile] ( u8 & r, u8 & g, u8 & b)
	{
		if( !(myfile>>r)) error = true;
		if( !(myfile>>g)) error = true;
		if( !(myfile>>b)) error = true;
	});
	
	if(error)
		return nullptr;
	
	return image;
}

} // namespace Deprecated
} // namespace Bade