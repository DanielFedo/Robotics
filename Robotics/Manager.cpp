/*
 * Manager.cpp
 *
 *  Created on: Jun 12, 2015
 *      Author: colman
 */

#include "Manager.h"

Manager::Manager() {
	// TODO Auto-generated constructor stub

}

Manager::Manager(Robot *robot, Behaviors *startBehavior){
	this->robot = robot;
	this->currBehavior = startBehavior;
}

void Manager::Run(){
    this->robot->Read();

    if (!currBehavior->startCond()) {
        cout << "Cannot start the first behavior" << endl;
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
    cout << "Manager stopped" << endl;
}
