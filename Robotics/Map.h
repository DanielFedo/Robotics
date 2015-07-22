/*
 * Map.h
 *
 *  Created on: Jun 12, 2015
 *      Author: colman
 */

#ifndef MAP_H_
#define MAP_H_

#include "lodepng.h"
#include <iostream>
#include <vector>
#include "AStar/Point.h"

using namespace std;

class Map {
public:
	unsigned int width, height;
	unsigned int gridWidth, gridHeight;
	double mapResolutionCM;
	double gridResolutionCM;
	int robotSizeInPixels;

public:
	enum CellIndication {FREE = 0, BLOCK = 1, UNKNOWN = 2};

	vector< vector<CellIndication> > matrix;
	vector< vector<CellIndication> > newMatrix;
	vector<unsigned char> image;
	vector<unsigned char> grid;


	Map();

	void loadPng(const char* filename);
	void writePng(const char* filename, std::vector<unsigned char>& image, unsigned width, unsigned height);
	void loadToMatrix();
	void printMap();
	void expand();
	bool isCellFree(int x, int y);
	void convertToGrid();
	void matrixToPng();
	Point* getLocationInWorld(Point *locatioInMap);
	Point* getLocationInMap(Point *locatioInWorld);

private:
	void expandPixel(int location, int pixelAmount);
};

#endif /* MAP_H_ */
