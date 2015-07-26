/*
 * Manager.h
 *
 *  Created on: Jun 12, 2015
 *      Author: colman
 */

#ifndef MANAGER_H_
#define MANAGER_H_

#include "Robot.h"
#include "Behaviors/Behaviors.h"
#include "Behaviors/GoForward.h"
#include "Behaviors/TurnLeft.h"
#include "Behaviors/TurnRight.h"
#include "Behaviors/TurnToWaypoint.h"
#include "WaypointsManager.h"
#include "LocalizationManager.h"

#include <stdlib.h>

class Manager {
private:
    Robot *robot;
    Behaviors *currBehavior;
public:
    Manager(Robot *robot);
    void Run();
};

#endif /* MANAGER_H_ */
