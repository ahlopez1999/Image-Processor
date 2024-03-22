#pragma once
#include <vector>
using namespace std;

class ImageData
{
public:

	struct Header
	{
		char idLength = 0;
		char colorMapType = 0;
		char dataTypeCode = 0;
		short colorMapOrigin = 0;
		short colorMapLength = 0;
		char colorMapDepth = 0;
		short xOrigin = 0;
		short yOrigin = 0;
		short width = 0;
		short height = 0;
		char bitsPerPixel = 0;
		char imageDescriptor = 0;
	};

	struct Pixel
	{
		unsigned char blue = 0;
		unsigned char green = 0;
		unsigned char red = 0;
	};

	ImageData::Header Header;
	vector<Pixel> Pixels;
};