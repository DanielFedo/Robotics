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
	std::vector<Point *> wayPoints;
	Robot* robot;
	Point* curPoint;
public:

	int index;
	static WaypointsManager* instance;

	static WaypointsManager* getInstance();
	static WaypointsManager* init(std::list<Point*> path, Robot* robot);

	WaypointsManager(std::list<Point*>, Robot* robot);
	std::vector<Point *> getWayPoints();
	Point getNextPoint();
	void directRobot();
	Point* getCurrWayPoint();
	bool isInWayPoint(double x,double y);
	bool isLastWayPoint();
	Point* getNextWayPoint();
};

#endif /* WAYPOINTSMANAGER_H_ */
