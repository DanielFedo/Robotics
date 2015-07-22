/*
 * TurnLeft.cpp
 *
 *  Created on: Jun 26, 2015
 *      Author: colman
 */

#include "TurnLeft.h"

TurnLeft::TurnLeft(Robot *robot) : Behaviors(robot)
{
}

bool TurnLeft::startCond()
{
	return !canGoFroward();
}

bool TurnLeft::stopCond()
{
	if (canGoFroward() == true)
	{
		robot->setSpeed(0.0,0.0);
		return true;
	}

	return false;
}

void TurnLeft::action()
{
	robot->setSpeed(0.0, -1.0);
}
