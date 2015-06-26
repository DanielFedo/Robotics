/*
 * TurnLeft.cpp
 *
 *  Created on: Jun 26, 2015
 *      Author: colman
 */

#include "TurnLeft.h"

TurnLeft::TurnLeft() {
	// TODO Auto-generated constructor stub

}

bool TurnRight::startCond(){
	return isContinue();
}

bool TurnRight::stopCond(){
	if (isContinue() == false)	{
		robot->setSpeed(0.0,0.0);
		return true;
	}
	return false;
}

void TurnRight::action() {
	robot->setSpeed(0.0, -1.0);
}
