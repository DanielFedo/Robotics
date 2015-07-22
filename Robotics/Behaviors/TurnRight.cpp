/*
 * TurnRight.cpp
 *
 *  Created on: Jun 26, 2015
 *      Author: colman
 */

#include "TurnRight.h"

TurnRight::TurnRight(Robot *robot) : Behaviors(robot)
{
}

bool TurnRight::startCond()
{
	return !canGoFroward();
}

bool TurnRight::stopCond()
{
	if (canGoFroward() == false)
	{
		robot->setSpeed(0.0,0.0);
		return true;
	}

	return false;
}

void TurnRight::action()
{
	robot->setSpeed(0.0, 1.0);
}
