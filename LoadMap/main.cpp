using namespace std;

#include "lodepng.h"
#include <iostream>
#include "Map.h"

std::vector<unsigned char> image; //the raw pixels

int main()
{
	Map *map = new Map();
	const char* filename = "hospital_section.png";

	map->loadToMatrix(filename);

	map->printMap();

	return 0;
}
