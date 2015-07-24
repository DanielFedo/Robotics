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

Point* WaypointsManager::getCurrWayPoint() {
	if (index >= wayPoints.size()){
		return NULL;
	}

	return wayPoints[index];
}

bool WaypointsManager::isLastWayPoint() {
	return (index == wayPoints.size() - 1);
}

bool WaypointsManager::isInWayPoint(double x,double y)
{
	double dx = getCurrWayPoint()->x - x;
	double dy = getCurrWayPoint()->y - y;
	double distance = sqrt(pow(dx, 2) + pow(dy, 2));

	//std::cout << "way point x"<< " " << currWP->getX() << " " << "x" << " " << x << std::endl;
	//std::cout << "way point y" << " " << currWP->getY() << " " << "y" << " "  << y << std::endl;
	//std::cout << "distance: " << distance << std::endl;

	int distanceTolerance;

	if (this->isLastWayPoint())
		int distanceTolerance = 3;
	else
		int distanceTolerance = 10;

	if (distance <= distanceTolerance)
	{
		this->getNextWayPoint();
		return true;
	}
	return false;
}

Point* WaypointsManager::getNextWayPoint() {
	Point* nextWaypoint = NULL;

	if (index < wayPoints.size())
	{
		index++;
		nextWaypoint = wayPoints[index];
	}

	return nextWaypoint;
}
