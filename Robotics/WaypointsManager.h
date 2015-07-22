/*
 * WaypointsManager.h
 *
 *  Created on: Jun 12, 2015
 *      Author: colman
 */

#ifndef WAYPOINTSMANAGER_H_
#define WAYPOINTSMANAGER_H_

#include <iostream>
#include <vector>
#include <list>
#include "AStar/Point.h"
#include "Robot.h"

class WaypointsManager {
private:
	std::list<Point *> wayPoints;
	Robot* robot;
	Point* curPoint;
public:
	WaypointsManager(std::list<Point*>, Robot* robot);
	std::list<Point *> getWayPoints();
	Point getNextPoint();
	void directRobot();
};

#endif /* WAYPOINTSMANAGER_H_ */
