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
	Map *map = Map::getInstance();
	char* filename = "roboticLabMap.png";

	// Init the map
	map->init(filename);

	// Use astar to calculat the path fo the robot
	PathPlanner *astar = new PathPlanner();
	std::list<Point*> path;

	// Calculate robot location on the grid
	int startLocationX = 362 / 4;
	int startLocationY = 305 / 4;
	int goalX = 169 / 4;
	int goalY = 138 / 4;

	path = astar->FindPath(startLocationX, startLocationY, goalX, goalY, map);

	// Convert waypoints from grid to map
	std::list<Point*>::iterator listIterator;
	for (listIterator = path.begin(); listIterator != path.end() ;listIterator++)
	{
		(*listIterator)->x = (*listIterator)->x * 4;
		(*listIterator)->y = (*listIterator)->y * 4;
		std::cout << " [" << (*listIterator)->x << "," << (*listIterator)->y << "] " << endl;
	}

	// Create our robot
	Robot *robot = new Robot();

	// Init our waypoint manager
	WaypointsManager::init(path, robot);

	// Launch the manager
	Manager *manager = new Manager(robot);
	manager->Run();

	return 0;
}
