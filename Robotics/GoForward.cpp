#include "GoForward.h"

GoForward::GoForward(Robot* robot):Behaviors(robot) {}

bool GoForward::startCond(){
	return isContinue();
}

bool GoForward::stopCond(){
	if (isContinue() == false)	{
		robot->setSpeed(0.0,0.0);
		return true;
	}
	return false;
}

void GoForward::action() {
	robot->setSpeed(0.1,0.0);
}

GoForward::~GoForward() {

}
