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
	// Resize the matrix to match the image size
	matrix.resize(width);

	for (int i = 0; i < width; i++)
	{
		matrix[i].resize(height);
	}

	int r;
	int g;
	int b;
	CellIndication cell;

	// Init the matrix values
	for (int i = 0; i < width * height * 4; i += 4)
	{
		r = image[i];
		g = image[i + 1];
		b = image[i + 2];

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

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			std::cout <<  matrix[i][j] << "";
		}

		std::cout << std::endl;
	}
}

void Map::matrixToPng()
{
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			std::cout << (i * 4 * width) + (j * 4) << ",";

			if (matrix[i][j] == FREE)
			{
				image[(i * 4 * width) + (j * 4)] = 255;
				image[(i * 4 * width) + (j * 4) + 1] = 255;
				image[(i * 4 * width) + (j * 4) + 2] = 255;
				image[(i * 4 * width) + (j * 4) + 3] = 255;
			}
			else
			{
				image[(i * 4 * width) + (j * 4)] = 0;
				image[(i * 4 * width) + (j * 4) + 1] = 0;
				image[(i * 4 * width) + (j * 4) + 2] = 0;
				image[(i * 4 * width) + (j * 4) + 3] = 255;
			}
		}

		std::cout << std::endl;
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

	writePng("AfterExpandRED.jpg", image, width, height);

	// Transform red to black
	for (int i = 0; i < width * height * 4; i += 4)
	{
		unsigned int r = image[i];
		unsigned int g = image[i + 1];
		unsigned int b = image[i + 2];

		// If its a red pixel - make it black
		if ((r == 255) & (g == 0) & (b == 0))
		{
			image[i] = 0;
		}
	}

	writePng("AfterExpandBLACK.jpg", image, width, height);
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
				image[i + j] = 255;
				image[i + j + 1] = 0;
				image[i + j + 2] = 0;
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
			std::cout <<  matrix[i][j] << "";
		}

		std::cout << std::endl;
	}

	writePng("helloyair.png", image, width, height);
}

bool Map::isCellFree(int x, int y)
{
	if (matrix[x][y] == FREE)
		return true;
	else
		return false;
}

void Map::convertToGrid()
{
	double widthOfRoomInCM = 4000;
	int sizeOfPixelInCM = widthOfRoomInCM / width + 0.6;
	int squareCM = 10;
	int numberOfPixelsInSquare = squareCM / sizeOfPixelInCM + 0.6;

	bool isSquareFree;



	// Resize the new matrix
	newMatrix.resize(width / numberOfPixelsInSquare);

	for (int i = 0; i < width / numberOfPixelsInSquare; i++)
	{
		newMatrix[i].resize(height / numberOfPixelsInSquare);
	}

	for (int i = 0; i <= height - numberOfPixelsInSquare; i += numberOfPixelsInSquare)
	{
		for (int j = 0; j <= width - numberOfPixelsInSquare; j += numberOfPixelsInSquare)
		{
			// Scan the square
			isSquareFree = true;

			for (int ii = 0; ii < numberOfPixelsInSquare; ii++)
			{
				for (int jj = 0; jj < numberOfPixelsInSquare; jj++)
				{
					if (matrix[i + ii][j + jj] != FREE)
						isSquareFree = false;
				}
			}

			if (isSquareFree)
				newMatrix[i / numberOfPixelsInSquare][j / numberOfPixelsInSquare] = FREE;
			else
				newMatrix[i / numberOfPixelsInSquare][j / numberOfPixelsInSquare] = BLOCK;
		}
	}

	width = width / numberOfPixelsInSquare;
	height = height / numberOfPixelsInSquare;

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			std::cout <<  newMatrix[i][j] << "";
		}
		std::cout << std::endl;
	}
}
