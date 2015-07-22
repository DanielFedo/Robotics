/*
 * Manager.cpp
 *
 *  Created on: Jun 12, 2015
 *      Author: colman
 */

#include "Manager.h"

Manager::Manager(Robot *robot){
	this->robot = robot;
}

void Manager::Run(){
    this->robot->Read();

    // Creating behaviors
    Behaviors ** behaviors = new Behaviors*[4];
    behaviors[0] = new GoForward(robot);
    behaviors[1] = new TurnLeft(robot);
    behaviors[2] = new TurnRight(robot);

    // Connectiong behaviors
    behaviors[0]->addNext(behaviors[1]);
    behaviors[0]->addNext(behaviors[2]);
    behaviors[1]->addNext(behaviors[0]);
    behaviors[2]->addNext(behaviors[0]);

    this->currBehavior = behaviors[0];

    if (!currBehavior->startCond()) {
        std::cout << "Cannot start the first behavior" << std::endl;
        return;
    }

    while (currBehavior != NULL) {
        currBehavior->action();
        robot->Read();
        // Update particles...

        if (currBehavior->stopCond()) {
            currBehavior = currBehavior->selectNext();
        }
    }
    std::cout << "Manager stopped" << std::endl;
}
