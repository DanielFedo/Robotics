using namespace std;

#include "lodepng.h"
#include <iostream>
#include "Map.h"

std::vector<unsigned char> image; //the raw pixels

int main()
{
	Map *map = new Map();
	const char* filename = "hospital_section.png";

	map->loadPng(filename);

	//map->expand();

	map->loadToMatrix(filename);

	map->matrixToPng();

	map->printMap();

	map->convertToGrid();



	map->printMap();

	int robotWidth =50;

	return 0;
}
