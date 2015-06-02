/*
 * AStar.h
 *
 *  Created on: Apr 28, 2015
 *      Author: colman
 */

#ifndef ASTAR_H_
#define ASTAR_H_

#include <iostream>
#include <vector>
#include <list>
#include <map>
#include "Point.h"

class AStar {

public:
	AStar();
	void FindPath ();
	void FindPath (int startX, int startY, int goalX, int goalY);
	bool isInList(Point *p, std::list<Point>& a);

	virtual ~AStar();
};

#endif /* ASTAR_H_ */
