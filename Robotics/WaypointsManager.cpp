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

// Init the waypoint manager
WaypointsManager::WaypointsManager(std::list<Point*> path, Robot* robot)
{
	this->index = 0;
	this->robot = robot;
	std::list<Point*>::iterator listIterator;
	int i = 0;

	// Insert the path into a list of way points.
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

// Return the path of the waypoints
std::vector<Point *> WaypointsManager::getWayPoints(){
	return this->wayPoints;
}


// Returns the current waypoint
// (The waypoint to which the robot is supposed to go now)
Point* WaypointsManager::getCurrWayPoint() {
	if (index >= wayPoints.size()){
		return NULL;
	}

	return wayPoints[index];
}

// Return if the current waypoint is the last one
bool WaypointsManager::isLastWayPoint() {
	return (index == wayPoints.size() - 1);
}

// Checks if the robot arrived to the current waypoint.
// Has a distance tolerance
bool WaypointsManager::isInWayPoint(double x,double y)
{
	double dx = getCurrWayPoint()->x - x;
	double dy = getCurrWayPoint()->y - y;
	double distance = sqrt(pow(dx, 2) + pow(dy, 2));
	int distanceTolerance = Utils::DISTANCE_TOLERANCE;

	std::cout << "distance: " << distance << std::endl;

	// Less distance toleration for last waypoint
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

// Return the next waypoint (the waypoint after the current one)
Point* WaypointsManager::getNextWayPoint() {
	Point* nextWaypoint = NULL;

	if (index < wayPoints.size())
	{
		index++;
		nextWaypoint = wayPoints[index];
	}

	return nextWaypoint;
}
