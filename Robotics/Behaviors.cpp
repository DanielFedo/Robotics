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
    this->next = NULL;
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

bool Behaviors::isContinue(){
	int freeToGo = 0;
	int freeEdges;

	// making sure we can go forward
	for (int i= -60 ; i< 60 ; i = i+9){
		if(_robot->getLaserRead(FORWARD_INDEX + i) >= UNSAFE_DIST)
			freeToGo++;
	}

	if (freeToGo != 14)
		return false;

	// making sure that while going forward the edges can go threw the obstacles
	freeEdges = 0;
	for (int i= -30 ; i< 30 ; i = i+9){
		if (_robot->getLaserRead(WALL_INDEX_LEFT_TOP + i) >= UNSAFE_DIST &&
			_robot->getLaserRead(WALL_INDEX_RIGHT_TOP + i) >= UNSAFE_DIST)

			freeEdges++;
	}

	if (freeEdges == 7)
		return true;
	return false;
}
