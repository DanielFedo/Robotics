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
		double arctan;

		// Check if it's the last waypoint
		if (currWayPoint == NULL){
			return false;
		}

		if (currWayPoint->x - robot->getXPos() == 0){
			if (robot->getYPos() - currWayPoint->y == 0)
				nextWaypointYaw = 0;
			else
				nextWaypointYaw = 180;
			//nextWaypointYaw = robot->getYPos() - currWayPoint->y ? 180 : 0;
		}
		else{
			arctan = atan(((double)currWayPoint->y - robot->getYPos()) / ((double)currWayPoint->x - robot->getXPos()));

			if (arctan < 0)
				nextWaypointYaw = 180 +
									Utils::RadianToDegree(arctan);
			else
				nextWaypointYaw = 180 -
					Utils::RadianToDegree(arctan);


		}

		if (robot->getYaw() - nextWaypointYaw < 0)
			isLeftTurn = 1;
		else if (stopCond())
			isLeftTurn = 0;
		else
			isLeftTurn =-1;


		//isLeftTurn = robot->getYaw() - nextWaypointYaw < 0 ? 1 : -1;

		return true;
}

bool TurnToWaypoint::stopCond()
{
	// stop if we reached way point yaw
	cout << "way point yaw: " << nextWaypointYaw << endl;

	bool isStop = fabs(nextWaypointYaw - robot->getYaw()) <= 1;

	if (isStop)
	{
		robot->setSpeed(0.0, 0);
		cout << "Facing Waypoint!! deviation: " << nextWaypointYaw - robot->getYaw() << endl;
	}

	return isStop;
}

void TurnToWaypoint::action()
{
	robot->setSpeed(0.0, isLeftTurn * 0.1);
}

double TurnToWaypoint::getPriority()
{
	return 99999.0;
}
