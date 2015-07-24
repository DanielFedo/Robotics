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
	// Turn to waypoint if we have eye contact to it
		Point* currWayPoint = WaypointsManager::getInstance()->getCurrWayPoint();

		// Check if it's the last waypoint
		if (currWayPoint == NULL){
			return false;
		}

		if (currWayPoint->x - robot->getXPos() == 0){
			nextWaypointYaw = robot->getYPos() - currWayPoint->y ? 180 : 0;
		}
		else{
			double arctan = atan((currWayPoint->y - robot->getYPos()) / (currWayPoint->x - robot->getXPos()));
			nextWaypointYaw = 180 -
				Utils::RadianToDegree(arctan);
		}

		isLeftTurn = robot->getYaw() - nextWaypointYaw < 0 ? 1 : -1;

		return true;
}

bool TurnToWaypoint::stopCond()
{
	// stop if we reached way point yaw
	return fabs(nextWaypointYaw - robot->getYaw()) < 2;
}

void TurnToWaypoint::action()
{
	robot->setSpeed(0.0, isLeftTurn*0.2);
}

double TurnToWaypoint::getPriority()
{
	return 99999.0;
}
