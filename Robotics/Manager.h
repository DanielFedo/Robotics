/*
 * Manager.h
 *
 *  Created on: Jun 12, 2015
 *      Author: colman
 */

#ifndef MANAGER_H_
#define MANAGER_H_

#include "Robot.h"
#include "Behaviors.h"
#include <stdlib.h>

class Manager {
private:
    Robot *robot;
    Behaviors *currBehavior;
public:
    Manager();
    Manager(Robot *robot, Behaviors *startBehavior);
    void Run();
};

#endif /* MANAGER_H_ */
