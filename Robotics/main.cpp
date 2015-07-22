using namespace std;

#include "lodepng.h"
#include <iostream>
#include "Map.h"
#include "AStar/PathPlanner.h"
#include "WaypointsManager.h"
#include "Manager.h"

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

	PathPlanner *astar = new PathPlanner();
	std::list<Point*> path;

	//WaypointsManager wayPoint = new WaypointsManager();

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

	// Create our robot
	Robot *robot = new Robot();

	Manager *manager = new Manager(robot);
	manager->Run();

	return 0;
}