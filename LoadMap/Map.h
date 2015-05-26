/*
 * Map.h
 *
 *  Created on: Mar 31, 2015
 *      Author: colman
 */

#ifndef MAP_H_
#define MAP_H_

#include "lodepng.h"
#include <iostream>

class Map {
	unsigned int width, height;

public:
	enum CellIndication {FREE = 0, BLOCK = 1, UNKNOWN = 2};

	std::vector< std::vector<CellIndication> > matrix;
	std::vector<unsigned char> image;


	Map();
	virtual ~Map();

	void loadPng(const char* filename);
	void writePng(const char* filename, std::vector<unsigned char>& image, unsigned width, unsigned height);
	void loadToMatrix(const char* filename);
	void printMap();
	void expand();

private:
	void expandPixel(int location, int pixelAmount);
};

#endif /* MAP_H_ */
