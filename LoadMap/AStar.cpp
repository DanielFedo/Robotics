/*
 * AStar.cpp
 *
 *  Created on: Apr 28, 2015
 *      Author: colman
 */

#include "AStar.h"


AStar::AStar() {
	// TODO Auto-generated constructor stub

}

std::list<Point*> AStar::FindPath (int startX, int startY, int goalX, int goalY, Map *map)
{
	std::list<Point*> openList;
	std::list<Point*> closedList;
	std::list<Point*> finalPath;
	std::list<Point*>::iterator listIterator;
	std::map<Point*, Point*> cameFrom;

	Point *startPoint = new Point(startX, startY);
	Point *endPoint = new Point(goalX, goalY);
	Point *currentPoint = new Point(-1, -1);

	openList.push_back(startPoint);

	while (!currentPoint->isEqual(endPoint))
	{
		// Search for point with the smallest F score in the open list
		// and put it as the currentPoint
		for (listIterator = openList.begin(); listIterator != openList.end() ;listIterator++)
		{
			if ((listIterator == openList.begin()) ||
				(*listIterator)->getFScore() <= currentPoint->getFScore())
			{
				currentPoint = *listIterator;
			}
		}

		// Stop if we reached the end
		if (currentPoint->isEqual(endPoint))
		{
			break;
		}

		// Remove the current point from the open list
		openList.remove(currentPoint);

		// Add the current point to the closed list
		closedList.push_back(currentPoint);

		// Scan all the adjacent points of the current point
		for (int i = -1; i < 2; i++)
		{
			for (int j = -1; j < 2; j++)
			{
				// If its the current point - then pass
				if (i == 0 && j == 0)
					continue;

				// If we are in a corner - then pass (we don't move in diagonal)
				if (i != 0 && j != 0)
					continue;

				// calculate x & adjacentY of adjacent point
				int adjacentX = currentPoint->x + i;
				int adjacentY = currentPoint->y + j;

				// Check if this point is in the closed list
				bool isPointInClosedList = false;
				for (listIterator = closedList.begin(); listIterator != closedList.end(); listIterator++)
				{
					if ((*listIterator)->x == adjacentX && (*listIterator)->y == adjacentY)
					{
						isPointInClosedList = true;
						break;
					}
				}

				// If this point is in the closed list - continue
				if (isPointInClosedList)
					continue;

				// Check if this point is in the open list
				bool isPointInOpenedList = false;
				for (listIterator = openList.begin(); listIterator != openList.end(); listIterator++)
				{
					if ((*listIterator)->x == adjacentX && (*listIterator)->y == adjacentY)
					{
						isPointInOpenedList = true;
						break;
					}
				}

				// If this point is in the open list - continue
				if (isPointInOpenedList)
					continue;

				// Check if cell is freed for the robot
				if (!map->isCellFree(i, j))
					continue;

				Point *thisPoint = new Point(adjacentX, adjacentY);
				thisPoint->calculateScores(endPoint);
				openList.push_front(thisPoint);

				cameFrom[thisPoint] = currentPoint;
			}
		}
	}

	Point *pathCurrent = currentPoint;
	finalPath.push_back(currentPoint);

	while (pathCurrent->isEqual(startPoint))
	{
		pathCurrent = cameFrom[pathCurrent];
		finalPath.push_back(pathCurrent);
	}

	return finalPath;
}

AStar::~AStar() {
	// TODO Auto-generated destructor stub
}

