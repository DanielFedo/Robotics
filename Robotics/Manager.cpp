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
    behaviors[0] = new TurnToWaypoint(robot);
    behaviors[1] = new GoForward(robot);
    behaviors[2] = new TurnLeft(robot);
    behaviors[3] = new TurnRight(robot);

    // Connecting behaviors
    behaviors[0]->addNext(behaviors[1]);
    behaviors[1]->addNext(behaviors[2]);
    behaviors[2]->addNext(behaviors[0]);
    behaviors[2]->addNext(behaviors[0]);

    this->currBehavior = behaviors[0];

    robot->Read();

    if (!currBehavior->startCond()) {
        std::cout << "Cannot start the first behavior" << std::endl;
        return;
    }

	double prevX = Utils::configurationManager->xStart;
	double prevY = Utils::configurationManager->yStart;
	double prevYaw = Utils::configurationManager->yawStart;
    double newX, newY, newYaw;

    while (currBehavior != NULL) {
    	robot->Read();
		robot->Read();

		if (!currBehavior->stopCond())
			currBehavior->action();

    	robot->Read();
        robot->Read();


        // Get new robot location
		newX = robot->getXPos();
		newY = robot->getYPos();
		newYaw = robot->getYaw();

		// Check if the robot moved
		double deltaX = newX - prevX;
		double deltaY = newY - prevY;
		double deltaYaw = newYaw - prevYaw;
		if (deltaX == 0 &&  deltaY == 0 && deltaYaw == 0)
			continue;

        // Update particles...
		LocalizationManager* localizationManager = LocalizationManager::getInstance();
		localizationManager->updateParticles(robot, deltaX, deltaY, deltaYaw);
		localizationManager->createParticles();
		Particle* best = localizationManager->getBestParticle();

		cout << "Best Particle: X" << best->xPos << ", Y" << best->yPos << " Yaw:" << best->yaw << endl;
		cout << "Robot's position: X" << newX << ", Y" << newY << " Yaw: "<< robot->getYaw() << endl;
		cout << "Waypoint's position: "<< WaypointsManager::getInstance()->getCurrWayPoint()->x << " , "  << WaypointsManager::getInstance()->getCurrWayPoint()->y;
		cout << " index: " << WaypointsManager::getInstance()->index << endl;

		robot->setOdometry(best->xPos, best->yPos, best->yaw);


        if (currBehavior->stopCond()) {
        	cout << "stop condition!" << endl;
            currBehavior = currBehavior->selectNext();
        } else if (WaypointsManager::getInstance()->isInWayPoint(newX, newY)){
        	cout << "Reached to the way point!" << endl;
        	currBehavior = behaviors[0];
        	currBehavior->startCond();
        }

        prevX = newX;
        prevY = newY;
    }
    std::cout << "Manager stopped" << std::endl;
}

