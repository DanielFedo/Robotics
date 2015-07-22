/*
 * Behaviors.cpp
 *
 *  Created on: Jun 12, 2015
 *      Author: colman
 */

#include "Behaviors.h"

int Behaviors::degToIndex(double deg)
{
	return (deg + 120) / 0.36;
}

int Behaviors::indexToDeg(double index)
{
	return (index * 0.36) - 120;
}


Behaviors::Behaviors(Robot *robot) {
    this->robot = robot;
    this->numNext = 0;
}


Behaviors *Behaviors::addNext(Behaviors *beh) {
    nextBehaviors.push_back(beh);
    return this;
}

Behaviors *Behaviors::selectNext() {
    for (int i = 0; i < nextBehaviors.size(); i++)
    {
        if (nextBehaviors[i]->startCond())
            return nextBehaviors[i];
    }
    return NULL;
}

bool Behaviors::stopCond()
{
	return true;
}

void Behaviors::action()
{

}

bool Behaviors::startCond()
{
	return true;
}

// Check if the robot can continue going
bool Behaviors::canGoFroward(){
	int freeEdges;

	// making sure we can go forward
	int startIndex = Utils::DegreesToIndex(-45);
	int endIndex = Utils::DegreesToIndex(45);

	for (int i= startIndex  ; i < endIndex; i++)
	{
		if(robot->getLaserRead(i) <= Utils::UNSAFE_DIST)
		{
			return false;
		}
	}

	return true;
}
