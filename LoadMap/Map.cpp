/*
 * Map.cpp
 *
 *  Created on: Mar 31, 2015
 *      Author: colman
 */

#include "Map.h"

Map::Map() {
	// TODO Auto-generated constructor stub

}

Map::~Map() {
	// TODO Auto-generated destructor stub
}

// Loads a png file into a matrix
void Map::loadToMatrix(const char* filename)
{
	loadPng(filename);

	// Resize the matrix to match the image size
	matrix.resize(width);

	for (int i = 0; i < width; i++)
	{
		matrix[i].resize(height);
	}

	// Init the matrix values
	for (int i = 0; i < width * height * 4; i += 4)
	{
		CellIndication cell;

		unsigned int r = image[i];
		unsigned int g = image[i + 1];
		unsigned int b = image[i + 2];

		// Black pixel
		if ((r == 0) & (g == 0) & (b == 0))
			cell = BLOCK;
		// White pixel
		else if ((r == 255) & (g == 255) & (b == 255))
			cell = FREE;
		// Unknown Pixel
		else
			cell = UNKNOWN;

		matrix[(i / 4) / width][(i / 4) % width] = cell;
	}
}

void Map::expand()
{
	// Init the matrix values
	for (int i = 0; i < width * height * 4; i += 4)
	{

		unsigned int r = image[i];
		unsigned int g = image[i + 1];
		unsigned int b = image[i + 2];

		// If its a Black pixel - expand it
		if ((r == 0) & (g == 0) & (b == 0))
		{
			expandPixel(i, 3);
		}

	}

	//writePng("helloyair.png", image, width, height);
}

void Map::expandPixel(int location, int pixelRobot)
{
	int startLocation = (location - (width * pixelRobot * 4)) - (pixelRobot * 4);

	int endLocation = (startLocation + (pixelRobot * (2 + 1)) * width * 4);

	for (int i = startLocation; i < endLocation; i += width * 4)
	{
		for (int j = 0;j < (pixelRobot * 2 + 1) * 4 && i > 0; j += 4)
		{
			if (i + j + 3 < width * height *4)
			{
				image[i + j] = 0;
				image[i + j + 1] = 0;
				image[i + j + 2] = 0;
				image[i + j + 3] = 255;
			}
		}
	}
}

//Decode from disk to raw pixels with a single function call
void Map::loadPng(const char* filename)
{
  //decode the png file into the image variable
  unsigned error = lodepng::decode(image, width, height, filename);

  //if there's an error, display it
  if(error) std::cout << "decoder error " << error << ": " << lodepng_error_text(error) << std::endl;

  //the pixels are now in the vector "image", 4 bytes per pixel, ordered RGBARGBA..., use it as texture, draw it, ...
}

void Map::writePng(const char* filename, std::vector<unsigned char>& image, unsigned width, unsigned height)
{
	//Encode the image
	unsigned error = lodepng::encode(filename, image, width, height);

	//if there's an error, display it
	if(error) std::cout << "encoder error " << error << ": "<< lodepng_error_text(error) << std::endl;
}

// Prints the nap to the console
void Map::printMap()
{
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			std::cout <<  matrix[i][j] << " ";
		}

		std::cout << std::endl;
	}
}
