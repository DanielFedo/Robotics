/*
 * TurnToWaypoint.h
 *
 *  Created on: Jul 24, 2015
 *      Author: colman
 */

#ifndef TURNTOWAYPOINT_H_
#define TURNTOWAYPOINT_H_

#include "Behaviors.h"
#include "WaypointsManager.h"
#include "AStar/Point.h"
#include "Robot.h"
#include <cmath>

class TurnToWaypoint: public Behaviors {
	double nextWaypointYaw;
	int isLeftTurn;
public:
	TurnToWaypoint(Robot *robot);

	bool startCond();
	bool stopCond();
	void action();
	double getPriority();

};

#endif /* TURNTOWAYPOINT_H_ */
