/*
 * WaypointsManager.cpp
 *
 *  Created on: Jun 12, 2015
 *      Author: colman
 */

#include "WaypointsManager.h"

WaypointsManager* WaypointsManager::instance = NULL;

WaypointsManager* WaypointsManager::getInstance()
{
	return WaypointsManager::instance;
}

WaypointsManager* WaypointsManager::init(std::list<Point*> path, Robot* robot)
{
	WaypointsManager::instance = new WaypointsManager(path, robot);
}

WaypointsManager::WaypointsManager(std::list<Point*> path, Robot* robot)
{
	this->index = 0;
	this->robot = robot;
	std::list<Point*>::iterator listIterator;
	int i = 0;

	for (listIterator = path.begin(); listIterator != path.end() ;listIterator++)
	{
		i++;

		Point* tempPoint = (*listIterator);

		if (i % 2 == 0 || i == path.size() -1 || i == path.size())	{
			this->wayPoints.push_back(tempPoint);
		}
	}

    this->curPoint = *(this->wayPoints.begin());
	this->wayPoints.pop_back();
}

std::vector<Point *> WaypointsManager::getWayPoints(){
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
	int distanceTolerance = Utils::DISTANCE_TOLERANCE;

	std::cout << "distance: " << distance << std::endl;

	if (this->isLastWayPoint())
		distanceTolerance = 3;

	if (distance <= distanceTolerance)
	{
		this->getNextWayPoint();
		robot->setSpeed(0 ,0);
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
