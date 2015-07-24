/*
 * TurnToWaypoint.cpp
 *
 *  Created on: Jul 24, 2015
 *      Author: colman
 */

#include "TurnToWaypoint.h"

TurnToWaypoint::TurnToWaypoint(Robot *robot) : Behaviors(robot)
{}

bool TurnToWaypoint::startCond()
{
	return !canGoFroward();
}

bool TurnToWaypoint::stopCond()
{
	if (canGoFroward() == false)
	{
		robot->setSpeed(0.0,0.0);
		return true;
	}

	return false;
}

void TurnToWaypoint::action()
{
	robot->setSpeed(0.0, 1.0);
}
