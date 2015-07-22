/*
 * PathPlanner.h
 *
 *  Created on: Jun 12, 2015
 *      Author: colman
 */

#ifndef PATHPLANNER_H_
#define PATHPLANNER_H_

#include <iostream>
#include <vector>
#include <list>
#include <map>;
#include "Point.h"
#include "../Map.h"

class PathPlanner {
public:
	PathPlanner();
	std::list<Point*> FindPath (int startX, int startY, int goalX, int goalY, Map *map);
	void isInList(Point *p, std::list<Point>& a);
};

#endif /* PATHPLANNER_H_ */
