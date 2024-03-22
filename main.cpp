#pragma once
#include "ImageData.h"
#include <iomanip>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

ImageData LoadData(string input)
{
	ImageData image;
	ImageData::Pixel current;
	ifstream file(input, ios_base::binary);
	//load image Header
	file.read(&image.Header.idLength, sizeof(image.Header.idLength));
	file.read(&image.Header.colorMapType, sizeof(image.Header.colorMapType));
	file.read(&image.Header.dataTypeCode, sizeof(image.Header.dataTypeCode));
	file.read((char*)&image.Header.colorMapOrigin, sizeof(image.Header.colorMapOrigin));
	file.read((char*)&image.Header.colorMapLength, sizeof(image.Header.colorMapLength));
	file.read(&image.Header.colorMapDepth, sizeof(image.Header.colorMapDepth));
	file.read((char*)&image.Header.xOrigin, sizeof(image.Header.xOrigin));
	file.read((char*)&image.Header.yOrigin, sizeof(image.Header.yOrigin));
	file.read((char*)&image.Header.width, sizeof(image.Header.width));
	file.read((char*)&image.Header.height, sizeof(image.Header.height));
	file.read(&image.Header.bitsPerPixel, sizeof(image.Header.bitsPerPixel));
	file.read(&image.Header.imageDescriptor, sizeof(image.Header.imageDescriptor));
	//load image pixels to Pixels vector 
	for (int i = 0; i < image.Header.width * image.Header.height; i++)
	{
		file.read((char*)&current.blue, sizeof(current.blue));
		file.read((char*)&current.green, sizeof(current.green));
		file.read((char*)&current.red, sizeof(current.red));
		image.Pixels.push_back(current);
	}
	file.close();
	return image;
}

void WriteData(ImageData& image, string outputname)
{
	ofstream file(outputname, ios_base::binary);
	file.write(&image.Header.idLength, sizeof(image.Header.idLength));
	file.write(&image.Header.colorMapType, sizeof(image.Header.colorMapType));
	file.write(&image.Header.dataTypeCode, sizeof(image.Header.dataTypeCode));
	file.write((char*)&image.Header.colorMapOrigin, sizeof(image.Header.colorMapOrigin));
	file.write((char*)&image.Header.colorMapLength, sizeof(image.Header.colorMapLength));
	file.write(&image.Header.colorMapDepth, sizeof(image.Header.colorMapDepth));
	file.write((char*)&image.Header.xOrigin, sizeof(image.Header.xOrigin));
	file.write((char*)&image.Header.yOrigin, sizeof(image.Header.yOrigin));
	file.write((char*)&image.Header.width, sizeof(image.Header.width));
	file.write((char*)&image.Header.height, sizeof(image.Header.height));
	file.write(&image.Header.bitsPerPixel, sizeof(image.Header.bitsPerPixel));
	file.write(&image.Header.imageDescriptor, sizeof(image.Header.imageDescriptor));
	for (int i = 0; i < image.Header.width * image.Header.height; i++)
	{
		file.write((char*)&image.Pixels[i].blue, sizeof(image.Pixels[i].blue));
		file.write((char*)&image.Pixels[i].green, sizeof(image.Pixels[i].green));
		file.write((char*)&image.Pixels[i].red, sizeof(image.Pixels[i].red));
	}
	file.close();
}

void WriteChannel(ImageData& image, string channel, string outputname)
{
	ofstream file(outputname, ios_base::binary);
	file.write(&image.Header.idLength, sizeof(image.Header.idLength));
	file.write(&image.Header.colorMapType, sizeof(image.Header.colorMapType));
	file.write(&image.Header.dataTypeCode, sizeof(image.Header.dataTypeCode));
	file.write((char*)&image.Header.colorMapOrigin, sizeof(image.Header.colorMapOrigin));
	file.write((char*)&image.Header.colorMapLength, sizeof(image.Header.colorMapLength));
	file.write(&image.Header.colorMapDepth, sizeof(image.Header.colorMapDepth));
	file.write((char*)&image.Header.xOrigin, sizeof(image.Header.xOrigin));
	file.write((char*)&image.Header.yOrigin, sizeof(image.Header.yOrigin));
	file.write((char*)&image.Header.width, sizeof(image.Header.width));
	file.write((char*)&image.Header.height, sizeof(image.Header.height));
	file.write(&image.Header.bitsPerPixel, sizeof(image.Header.bitsPerPixel));
	file.write(&image.Header.imageDescriptor, sizeof(image.Header.imageDescriptor));
	if (channel == "red")
	{
		for (int i = 0; i < image.Header.width * image.Header.height; i++)
		{
			file.write((char*)&image.Pixels[i].red, sizeof(image.Pixels[i].red));
			file.write((char*)&image.Pixels[i].red, sizeof(image.Pixels[i].red));
			file.write((char*)&image.Pixels[i].red, sizeof(image.Pixels[i].red));
			image.Pixels[i].red = image.Pixels[i].red;
			image.Pixels[i].green = image.Pixels[i].red;
			image.Pixels[i].blue = image.Pixels[i].red;
		}
	}
	else if (channel == "green")
	{
		for (int i = 0; i < image.Header.width * image.Header.height; i++)
		{
			file.write((char*)&image.Pixels[i].green, sizeof(image.Pixels[i].green));
			file.write((char*)&image.Pixels[i].green, sizeof(image.Pixels[i].green));
			file.write((char*)&image.Pixels[i].green, sizeof(image.Pixels[i].green));
			image.Pixels[i].red = image.Pixels[i].green;
			image.Pixels[i].blue = image.Pixels[i].green;
		}
	}
	else if (channel == "blue")
	{
		for (int i = 0; i < image.Header.width * image.Header.height; i++)
		{
			file.write((char*)&image.Pixels[i].blue, sizeof(image.Pixels[i].blue));
			file.write((char*)&image.Pixels[i].blue, sizeof(image.Pixels[i].blue));
			file.write((char*)&image.Pixels[i].blue, sizeof(image.Pixels[i].blue));
			image.Pixels[i].red = image.Pixels[i].blue;
			image.Pixels[i].green = image.Pixels[i].blue;
		}
	}
	file.close();
}

void WriteCombined(ImageData& redchannel, ImageData& greenchannel, ImageData& bluechannel, string outputname)
{
	ofstream file(outputname, ios_base::binary);
	file.write(&redchannel.Header.idLength, sizeof(redchannel.Header.idLength));
	file.write(&redchannel.Header.colorMapType, sizeof(redchannel.Header.colorMapType));
	file.write(&redchannel.Header.dataTypeCode, sizeof(redchannel.Header.dataTypeCode));
	file.write((char*)&redchannel.Header.colorMapOrigin, sizeof(redchannel.Header.colorMapOrigin));
	file.write((char*)&redchannel.Header.colorMapLength, sizeof(redchannel.Header.colorMapLength));
	file.write(&redchannel.Header.colorMapDepth, sizeof(redchannel.Header.colorMapDepth));
	file.write((char*)&redchannel.Header.xOrigin, sizeof(redchannel.Header.xOrigin));
	file.write((char*)&redchannel.Header.yOrigin, sizeof(redchannel.Header.yOrigin));
	file.write((char*)&redchannel.Header.width, sizeof(redchannel.Header.width));
	file.write((char*)&redchannel.Header.height, sizeof(redchannel.Header.height));
	file.write(&redchannel.Header.bitsPerPixel, sizeof(redchannel.Header.bitsPerPixel));
	file.write(&redchannel.Header.imageDescriptor, sizeof(redchannel.Header.imageDescriptor));
	for (int i = 0; i < redchannel.Header.width * redchannel.Header.height; i++)
	{
		file.write((char*)&bluechannel.Pixels[i].blue, sizeof(bluechannel.Pixels[i].blue));
		file.write((char*)&greenchannel.Pixels[i].green, sizeof(greenchannel.Pixels[i].green));
		file.write((char*)&redchannel.Pixels[i].red, sizeof(redchannel.Pixels[i].red));
		redchannel.Pixels[i].red = redchannel.Pixels[i].red;
		redchannel.Pixels[i].green = greenchannel.Pixels[i].green;
		redchannel.Pixels[i].blue = bluechannel.Pixels[i].blue;
	}
	file.close();
}

void TestManip(ImageData& image)
{
	for (int i = 0; i < image.Header.width * image.Header.height; i++)
	{
		image.Pixels[i].red = 255;
		image.Pixels[i].green = 0;
		image.Pixels[i].blue = 0;
	}
}

void CompareTest(ImageData& output, ImageData& comparison)
{
	bool match = true;
	for (int i = 0; i < output.Header.width * output.Header.height; i++)
	{
		if (output.Pixels[i].red == comparison.Pixels[i].red && output.Pixels[i].green == comparison.Pixels[i].green && output.Pixels[i].blue == comparison.Pixels[i].blue)
		{
			match = true;
		}
		else
		{
			match = false;
			break;
		}
	}
	if (match == true)
	{
		cout << "Test passed" << endl;
	}
	else
	{
		cout << "Test failed" << endl;
	}
}

void Multiply(ImageData& toplayer, ImageData& bottomlayer)
{
	float redval;
	float greenval;
	float blueval;
	for (int i = 0; i < toplayer.Header.width * toplayer.Header.height; i++)
	{
		redval = (float)(toplayer.Pixels[i].red * bottomlayer.Pixels[i].red);
		redval /= 255;
		redval += 0.5;
		greenval = (float)(toplayer.Pixels[i].green * bottomlayer.Pixels[i].green);
		greenval /= 255;
		greenval += 0.5;
		blueval = (float)(toplayer.Pixels[i].blue * bottomlayer.Pixels[i].blue);
		blueval /= 255;
		blueval += 0.5;
		toplayer.Pixels[i].red = (unsigned char)redval;
		toplayer.Pixels[i].green = (unsigned char)greenval;
		toplayer.Pixels[i].blue = (unsigned char)blueval;
	}
}

void Subtract(ImageData& toplayer, ImageData& bottomlayer)
{
	int redval = 0;
	int greenval = 0;
	int blueval = 0;
	for (int i = 0; i < bottomlayer.Header.width * bottomlayer.Header.height; i++)
	{
		redval = (int)(bottomlayer.Pixels[i].red - toplayer.Pixels[i].red);
		if (redval < 0)
		{
			redval = 0;
		}
		if (redval > 255)
		{
			redval = 255;
		}
		greenval = (int)(bottomlayer.Pixels[i].green - toplayer.Pixels[i].green);
		if (greenval < 0)
		{
			greenval = 0;
		}
		if (greenval > 255)
		{
			greenval = 255;
		}
		blueval = (int)(bottomlayer.Pixels[i].blue - toplayer.Pixels[i].blue);
		if (blueval < 0)
		{
			blueval = 0;
		}
		if (blueval > 255)
		{
			blueval = 255;
		}
		toplayer.Pixels[i].red = (unsigned char)redval;
		toplayer.Pixels[i].green = (unsigned char)greenval;
		toplayer.Pixels[i].blue = (unsigned char)blueval;
	}
}

void Screen(ImageData& toplayer, ImageData& bottomlayer)
{
	float redval = 0;
	float greenval = 0;
	float blueval = 0;
	for (int i = 0; i < toplayer.Header.width * bottomlayer.Header.height; i++)
	{
		redval = (float)((255 - toplayer.Pixels[i].red) * (255 - bottomlayer.Pixels[i].red));
		redval /= 255;
		redval = 255 - redval;
		redval += 0.5;
		greenval = (float)((255 - toplayer.Pixels[i].green) * (255 - bottomlayer.Pixels[i].green));
		greenval /= 255;
		greenval = 255 - greenval;
		greenval += 0.5;
		blueval = (float)((255 - toplayer.Pixels[i].blue) * (255 - bottomlayer.Pixels[i].blue));
		blueval /= 255;
		blueval = 255 - blueval;
		blueval += 0.5;
		toplayer.Pixels[i].red = (unsigned char)redval;
		toplayer.Pixels[i].green = (unsigned char)greenval;
		toplayer.Pixels[i].blue = (unsigned char)blueval;
	}
}

void Overlay(ImageData& toplayer, ImageData& bottomlayer)
{
	float redval = 0;
	float greenval = 0;
	float blueval = 0;
	for (int i = 0; i < toplayer.Header.width * toplayer.Header.height; i++)
	{
		if ((float)bottomlayer.Pixels[i].red <= 255/2 && (float)bottomlayer.Pixels[i].green <= 255/2 && (float)bottomlayer.Pixels[i].blue <= 255/2)
		{
			redval = (float)(2 * toplayer.Pixels[i].red * bottomlayer.Pixels[i].red);
			redval /= 255;
			redval += 0.5;
			greenval = (float)(2 * toplayer.Pixels[i].green * bottomlayer.Pixels[i].green);
			greenval /= 255;
			greenval += 0.5;
			blueval = (float)(2 * toplayer.Pixels[i].blue * bottomlayer.Pixels[i].blue);
			blueval /= 255;
			blueval += 0.5;
		}
		else
		{
			redval = (float)(2 * (255 - toplayer.Pixels[i].red) * (255 - bottomlayer.Pixels[i].red));
			redval /= 255;
			redval = 255 - redval;
			redval += 0.5;
			greenval = (float)(2 * (255 - toplayer.Pixels[i].green) * (255 - bottomlayer.Pixels[i].green));
			greenval /= 255;
			greenval = 255 - greenval;
			greenval += 0.5;
			blueval = (float)(2 * (255 - toplayer.Pixels[i].blue) * (255 - bottomlayer.Pixels[i].blue));
			blueval /= 255;
			blueval = 255 - blueval;
			blueval += 0.5;
		}
		toplayer.Pixels[i].red = (unsigned char)redval;
		toplayer.Pixels[i].green = (unsigned char)greenval;
		toplayer.Pixels[i].blue = (unsigned char)blueval;
	}
}

void AddtoChannel(ImageData& image, string channel, int value)
{
	int greenval = 0;
	int redval = 0;
	int blueval = 0;
	if (channel == "green")
	{
		for (int i = 0; i < image.Header.width * image.Header.height; i++)
		{
			greenval = (int)(image.Pixels[i].green) + value;
			if (greenval > 255)
			{
				greenval = 255;
			}
			image.Pixels[i].green = (unsigned char)greenval;
		}
	}
	else if (channel == "red")
	{
		for (int i = 0; i < image.Header.width * image.Header.height; i++)
		{
			redval = (int)(image.Pixels[i].green) + value;
			if (redval > 255)
			{
				redval = 255;
			}
			image.Pixels[i].red = (unsigned char)redval;
		}
	}
	else if (channel == "blue")
	{
		for (int i = 0; i < image.Header.width * image.Header.height; i++)
		{
			blueval = (int)(image.Pixels[i].green) + value;
			if (blueval > 255)
			{
				blueval = 255;
			}
			image.Pixels[i].blue = (unsigned char)blueval;
		}
	}
}

void ScaleChannel(ImageData& image, string channel, float factor)
{
	float redval = 0;
	float greenval = 0;
	float blueval = 0;
	if (channel == "red")
	{
		for (int i = 0; i < image.Header.width * image.Header.height; i++)
		{
			redval = (float)image.Pixels[i].red / 255;
			redval *= factor;
			redval *= 255;
			redval += 0.5;
			if (redval > 255)
			{
				redval = 255;
			}
			image.Pixels[i].red = (unsigned char)redval;
		}
	}
	else if (channel == "green")
	{
		for (int i = 0; i < image.Header.width * image.Header.height; i++)
		{
			greenval = (float)image.Pixels[i].green / 255;
			greenval *= factor;
			greenval *= 255;
			greenval += 0.5;
			if (greenval > 255)
			{
				greenval = 255;
			}
			image.Pixels[i].green = (unsigned char)greenval;
		}
	}
	else if (channel == "blue")
	{
		for (int i = 0; i < image.Header.width * image.Header.height; i++)
		{
			blueval = (float)image.Pixels[i].blue / 255;
			blueval *= factor;
			blueval *= 255;
			blueval += 0.5;
			if (blueval > 255)
			{
				blueval = 255;
			}
			image.Pixels[i].blue = (unsigned char)blueval;
		}
	}
}

void Invert(ImageData& newimage, ImageData& original)
{
	int index = 0;
	for (int i = (original.Header.width * original.Header.height) - 1; i > -1; i--)
	{
		newimage.Pixels[index].red = original.Pixels[i].red;
		newimage.Pixels[index].green = original.Pixels[i].green;
		newimage.Pixels[index].blue = original.Pixels[i].blue;
		index++;
	}
}

int main()
{
	ImageData tlayer;
	ImageData blayer;
	ImageData comparison;
	system("mkdir output");

	tlayer = LoadData("input/layer1.tga");
	blayer = LoadData("input/pattern1.tga");
	Multiply(tlayer, blayer);
	WriteData(tlayer, "output/part1.tga");
	
	comparison = LoadData("examples/EXAMPLE_part1.tga");
	CompareTest(tlayer, comparison);
	

	tlayer = LoadData("input/layer2.tga");
	blayer = LoadData("input/car.tga");
	Subtract(tlayer, blayer);
	WriteData(tlayer, "output/part2.tga");
	
	comparison = LoadData("examples/EXAMPLE_part2.tga");
	CompareTest(tlayer, comparison);
	

	tlayer = LoadData("input/layer1.tga");
	blayer = LoadData("input/pattern2.tga");
	Multiply(tlayer, blayer);
	ImageData temp = tlayer;
	ImageData text = LoadData("input/text.tga");
	Screen(text, temp);
	WriteData(text, "output/part3.tga");
	
	comparison = LoadData("examples/EXAMPLE_part3.tga");
	CompareTest(text, comparison);
	

	tlayer = LoadData("input/layer2.tga");
	blayer = LoadData("input/circles.tga");
	Multiply(tlayer, blayer);
	temp = LoadData("input/pattern2.tga");
	Subtract(temp, tlayer);
	WriteData(temp, "output/part4.tga");
	
	comparison = LoadData("examples/EXAMPLE_part4.tga");
	CompareTest(temp, comparison);
	

	tlayer = LoadData("input/layer1.tga");
	blayer = LoadData("input/pattern1.tga");
	Overlay(tlayer, blayer);
	WriteData(tlayer, "output/part5.tga");
	
	comparison = LoadData("examples/EXAMPLE_part5.tga");
	CompareTest(tlayer, comparison);
	

	tlayer = LoadData("input/car.tga");
	AddtoChannel(tlayer, "green", 200);
	WriteData(tlayer, "output/part6.tga");
	
	comparison = LoadData("examples/EXAMPLE_part6.tga");
	CompareTest(tlayer, comparison);
	

	tlayer = LoadData("input/car.tga");
	ScaleChannel(tlayer, "red", 4);
	ScaleChannel(tlayer, "blue", 0);
	WriteData(tlayer, "output/part7.tga");
	
	comparison = LoadData("examples/EXAMPLE_part7.tga");
	CompareTest(tlayer, comparison);
	

	tlayer = LoadData("input/car.tga");
	blayer = LoadData("input/car.tga");
	temp = LoadData("input/car.tga");
	WriteChannel(tlayer, "red", "output/part8_r.tga");
	WriteChannel(blayer, "green", "output/part8_g.tga");
	WriteChannel(temp, "blue", "output/part8_b.tga");
	
	comparison = LoadData("examples/EXAMPLE_part8_r.tga");
	CompareTest(tlayer, comparison);
	comparison = LoadData("examples/EXAMPLE_part8_g.tga");
	CompareTest(blayer, comparison);
	comparison = LoadData("examples/EXAMPLE_part8_b.tga");
	CompareTest(temp, comparison);
	

	tlayer = LoadData("input/layer_red.tga");
	blayer = LoadData("input/layer_green.tga");
	temp = LoadData("input/layer_blue.tga");
	WriteCombined(tlayer, blayer, temp, "output/part9.tga");
	
	comparison = LoadData("examples/EXAMPLE_part9.tga");
	CompareTest(tlayer, comparison);
	

	tlayer = LoadData("input/text2.tga");
	temp = LoadData("input/text2.tga");
	Invert(tlayer, temp);
	WriteData(tlayer, "output/part10.tga");
	
	comparison = LoadData("examples/EXAMPLE_part10.tga");
	CompareTest(tlayer, comparison);
}