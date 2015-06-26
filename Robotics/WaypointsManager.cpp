/*
 * WaypointsManager.cpp
 *
 *  Created on: Jun 12, 2015
 *      Author: colman
 */

#include "WaypointsManager.h"

WaypointsManager::WaypointsManager() {
	// TODO Auto-generated constructor stub

}

WaypointsManager::WaypointsManager(std::list<Point*> path){
	for (int i = 0; i < path.size(); i++)
	{
		Point* curPoint = path[i];

		if (i % 3 == 0 || i == path.size() -1)	{
			// TODO: push back or push front?
			this->wayPoints.push_back(curPoint);
		}
	}
}

std::list<Point *> WaypointsManager::getWayPoints(){
	return this->wayPoints;
}

