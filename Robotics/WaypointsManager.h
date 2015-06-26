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
#include "Point.h"

class WaypointsManager {
private:
	std::list<Point *> wayPoints;
public:
	WaypointsManager();
	WaypointsManager(std::list<Point*>);
	std::list<Point *> getWayPoints();
};

#endif /* WAYPOINTSMANAGER_H_ */
