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
#include "Utils.h"


using namespace std;

class Map {
public:
	unsigned int width, height;
	unsigned int gridWidth, gridHeight;
	double mapResolutionCM;
	double gridResolutionCM;
	int robotSizeInPixels;

	vector< vector<Utils::CELL_STATUS> > matrix;
	vector< vector<Utils::CELL_STATUS> > newMatrix;
	vector<unsigned char> image;
	vector<unsigned char> grid;
	static Map* instance;

	static Map* getInstance();

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
