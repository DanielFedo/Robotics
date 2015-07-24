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
	for (int i = 0; i < 15; i++) {
		robot->setOdometry();
		robot->Read();
	}
	Behaviors *turnToWayPoint;
	turnToWayPoint = new TurnToWaypoint(robot);
    // Creating behaviors

    Behaviors ** behaviors = new Behaviors*[4];
    behaviors[0] = new GoForward(robot);
    behaviors[1] = new TurnLeft(robot);
    behaviors[2] = new TurnRight(robot);

    // Connecting behaviors
    behaviors[0]->addNext(behaviors[1]);
    behaviors[0]->addNext(behaviors[2]);
    behaviors[1]->addNext(behaviors[0]);
    behaviors[2]->addNext(behaviors[0]);

    this->currBehavior = behaviors[0];

    if (!currBehavior->startCond()) {
        std::cout << "Cannot start the first behavior" << std::endl;
        return;
    }

	double prevX = Utils::configurationManager->xStart;
	double prevY = Utils::configurationManager->yStart;
	double prevYaw = Utils::configurationManager->yawStart;
    double newX, newY, newYaw;

    while (currBehavior != NULL) {
        currBehavior->action();
        robot->Read();
        robot->Read();

        // Get new robot location
		newX = robot->getXPos();
		newY = robot->getYPos();
		newYaw = robot->getYaw();

		if (WaypointsManager::getInstance()->isInWayPoint(newX, newY))
		{
			turnToWayPoint->action();
		}

		// Check if the robot moved
		double deltaX = newX - prevX;
		double deltaY = newY - prevY;
		double deltaYaw = newYaw - prevYaw;
		if (deltaX == 0 &&  deltaY == 0 && deltaYaw == 0)
			continue;

        // Update particles...
		//LocalizationManager.updateParticles(_robot, deltaX, deltaY, deltaYaw);
		//Particle* best = _localizationManager.getBestParticle();
		//LocalizationManager.createParticles();

		cout << "Robot's position: " << newX << ", " << newY << endl;

        if (currBehavior->stopCond()) {
            currBehavior = currBehavior->selectNext();
        }
    }
    std::cout << "Manager stopped" << std::endl;
}

