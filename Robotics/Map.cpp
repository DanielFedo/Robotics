/*
 * map.cpp
 *
 *  Created on: Jun 12, 2015
 *      Author: colman
 */

#include "Map.h"
#include "AStar/Point.h"
#include "Utils.h"

Map* Map::instance = NULL;

// Singleton implementation
Map* Map::getInstance()
{
	if (Map::instance == NULL)
	{
		Map::instance = new Map();
	}

	return Map::instance;
}

Map::Map()
{
	robotSizeInPixels = Utils::configurationManager->robotLength;
	mapResolutionCM = Utils::configurationManager->mapResolution;
	gridResolutionCM = 10;
}

// Get location in cm
Point * Map::getLocationInWorld(Point *locationInMap)
{
	double d = mapResolutionCM / gridResolutionCM;
	Point *newPoint = new Point(locationInMap->x * d, locationInMap->y * d, NULL);
	return newPoint;
}

// Get location in grid (pixels)
Point * Map::getLocationInMap(Point *locationInWorld)
{
	double d = mapResolutionCM / gridResolutionCM;
	Point *newPoint = new Point(locationInWorld->x / d, locationInWorld->y / d, NULL);

	return newPoint;
}

void Map::init(char *filename)
{
	// Load the map of the room
	this->loadPng(filename);

	// Expand the map relative to the the robot's size
	this->expand();

	// Load original map to a matrix
	this->loadMapToMatrix();

	// Convert the map to a grid
	this->convertToGrid();

	// Load the map into a matrix
	this->loadToMatrix();

	this->printMap();
}

// Loads the original map to a matrix
void Map::loadMapToMatrix()
{
	// Resize the matrix to match the image size
	originalMap.resize(this->width);

	for (int i = 0; i < this->height; i++)
	{
		originalMap[i].resize(this->width);
	}

	int r;
	int g;
	int b;
	Utils::CELL_STATUS cell;

	// Init the matrix values
	for (int i = 0; i < width * height * 4; i += 4)
	{
		r = image[i];
		g = image[i + 1];
		b = image[i + 2];

		// Black pixel
		if ((r == 0) & (g == 0) & (b == 0))
			cell = Utils::BLOCK;
		// White pixel
		else if ((r == 255) & (g == 255) & (b == 255))
			cell = Utils::FREE;
		// Unknown Pixel
		else
			cell = Utils::UNKNOWN;

		originalMap[(i / 4) / width][(i / 4) % width] = cell;

		// TODO: Remove in final version
		if ((i / 4) % width == 0)
			std::cout << std::endl;

		std::cout << cell;
	}
}

// Loads a png file into a matrix
void Map::loadToMatrix()
{
	// Resize the matrix to match the image size
	matrix.resize(this->gridHeight);

	for (int i = 0; i < this->gridHeight; i++)
	{
		matrix[i].resize(this->gridWidth);
	}

	int r;
	int g;
	int b;
	Utils::CELL_STATUS cell;

	// Init the matrix values
	for (int i = 0; i < gridWidth * gridHeight * 4; i += 4)
	{
		r = grid[i];
		g = grid[i + 1];
		b = grid[i + 2];

		// Black pixel
		if ((r == 0) & (g == 0) & (b == 0))
			cell = Utils::BLOCK;
		// White pixel
		else if ((r == 255) & (g == 255) & (b == 255))
			cell = Utils::FREE;
		// Unknown Pixel
		else
			cell = Utils::UNKNOWN;

		matrix[(i / 4) / gridWidth][(i / 4) % gridWidth] = cell;

		// TODO: Remove in final version
		if ((i / 4) % gridWidth == 0)
			std::cout << std::endl;

		std::cout << cell;
	}
}

// Converts the matrix back to a png
void Map::matrixToPng()
{
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			std::cout << (i * 4 * width) + (j * 4) << ",";

			if (matrix[i][j] == Utils::FREE)
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

// Expands the blocked cells on the matrix
// according to the size of the robot
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
			expandPixel(i, robotSizeInPixels + 10);
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

	//writePng("AfterExpandBLACK.jpg", image, width, height);
}

// Expand a pixel on the map according to the given expansion radius
void Map::expandPixel(int location, int expansionPixels)
{
	int startLocation = (location - (width * expansionPixels * 4)) - (expansionPixels * 4);
	int endLocation = (location + (width * expansionPixels * 4)) + (expansionPixels * 4);

	for (int i = startLocation; i < endLocation; i += width * 4)
	{
		for (int j = 0;j < (expansionPixels * 2 + 1) * 4 && i > 0; j += 4)
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

// Write an array into a png
void Map::writePng(const char* filename, std::vector<unsigned char>& image, unsigned width, unsigned height)
{
	//Encode the image
	unsigned error = lodepng::encode(filename, image, width, height);

	//if there's an error, display it
	if(error) std::cout << "encoder error " << error << ": "<< lodepng_error_text(error) << std::endl;
}

// Prints the map to the console
void Map::printMap()
{
	for (int i = 0; i < gridHeight; i++)
	{
		for (int j = 0; j < gridWidth; j++)
		{
			std::cout <<  matrix[i][j] << "";
		}

		std::cout << std::endl;
	}

	//writePng("helloyair.png", image, width, height);
}

// Return if a cell on the grid is empty and free for the robot
bool Map::isCellFree(int x, int y)
{
	return (matrix[y][x] == Utils::FREE);
}

// Converts the map into a grid according to the given grid resolution
void Map::convertToGrid()
{
	// Define variables.
	double GridResolutionPixels = gridResolutionCM / mapResolutionCM; // 4 pixels
	std::vector<unsigned char> newImage(((int)((width * height * 4) / GridResolutionPixels)));
	bool foundBlack;
	unsigned int newLocation;
	unsigned int newRow;
	unsigned int newCol;
	unsigned int location;
	gridWidth = (width - 2) / GridResolutionPixels;
	gridHeight = height / GridResolutionPixels;

	// Going on the given map rows.
	for (int row = 0; row < height * width * 4; row += width * GridResolutionPixels * 4)
	{
		// Going on the given map columns.
		for (int col = 0; col < (width - 2) * 4; col += GridResolutionPixels *4)
		{
			// Calculating the current cell (location).
			location = row + col;

			foundBlack = false;

			// Going on the square which will be equal to one cell on the Grid Map.
			// Going on the rows.
			for (int y = 0; y < GridResolutionPixels; y++)
			{
				// Going on the columns.
				for (int x = 0; x < GridResolutionPixels; x++)
				{
					// Calculating how many cells we should skip in order to get to the cell.
					int shifting = location + (x + (y * width)) * 4;
					unsigned int r = image[shifting];
					unsigned int g = image[shifting + 1];
					unsigned int b = image[shifting + 2];

					// It's enough to find one black pixel on the current square,
					// in order to set the whole cell as black on the Grid Map.
					if (r == 0 && g == 0 && b == 0)
					{
						foundBlack = true;
					}
				}
			}

			// Calculating the current row,column and cell eventually on the Grid.
			newRow = (row / (int)(width * GridResolutionPixels * 4)) *
						((width-2)/GridResolutionPixels) * 4;
			newCol = (col / GridResolutionPixels);
			newLocation = newRow + newCol;

			// Paint the cell.
			if (foundBlack)
			{
				newImage[newLocation] = 0;
				newImage[newLocation + 1] = 0;
				newImage[newLocation + 2] = 0;
				newImage[newLocation + 3] = 255;
			}
			else
			{
				newImage[newLocation] = 255;
				newImage[newLocation + 1] = 255;
				newImage[newLocation + 2] = 255;
				newImage[newLocation + 3] = 255;
			}
		}
	}

	grid = newImage;
	//writePng("galvemoris.png", newImage, width / GridResolutionPixels, height / GridResolutionPixels);
}
