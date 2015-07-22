/*
 * WaypointsManager.cpp
 *
 *  Created on: Jun 12, 2015
 *      Author: colman
 */

#include "WaypointsManager.h"

WaypointsManager::WaypointsManager(std::list<Point*> path, Robot* robot)
{
	this->robot = robot;
	std::list<Point*>::iterator listIterator;
	int i = 0;

	for (listIterator = path.begin(); listIterator != path.end() ;listIterator++)
	{
		i++;

		Point* tempPoint = (*listIterator);

		if (i % 3 == 0 || i == path.size() -1)	{
			// TODO: push back or push front?
			this->wayPoints.push_back(tempPoint);
		}
	}

    this->curPoint = *(this->wayPoints.begin());
	this->wayPoints.pop_front();
}

std::list<Point *> WaypointsManager::getWayPoints(){
	return this->wayPoints;
}

void WaypointsManager::directRobot()
{

}

