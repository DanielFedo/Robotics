using namespace std;

#include "lodepng.h"
#include <iostream>
#include "Map.h"
#include "AStar.h"

std::vector<unsigned char> image; //the raw pixels

int main()
{
	Map *map = new Map();
	const char* filename = "roboticLabMap.png";

	// Load the map of the room
	map->loadPng(filename);

	// Expand the map relative to the the robot's size
	map->expand();

	// Convert the map to a grid
	map->convertToGrid();

	// Load the map into a matrix
	map->loadToMatrix();

	AStar *astar = new AStar();
	std::list<Point*> path;

	int startLocationX = 362 / 4;
	int startLocationY = 305 / 4;
	int goalX = 169 / 4;
	int goalY = 138 / 4;

	path = astar->FindPath(startLocationX, startLocationY, goalX, goalY, map);

	std::list<Point*>::iterator listIterator;
	for (listIterator = path.begin(); listIterator != path.end() ;listIterator++)
	{
		std::cout << " [" << (*listIterator)->x << "," << (*listIterator)->y << "] " << endl;
	}

	return 0;
}
