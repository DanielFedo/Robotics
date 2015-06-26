/*
 * Behaviors.h
 *
 *  Created on: Jun 12, 2015
 *      Author: colman
 */

#ifndef BEHAVIORS_H_
#define BEHAVIORS_H_

#include "Robot.h"
#include <vector> 
#include <stdlib.h>
using namespace std;

class Behaviors {
private:
    vector<Behaviors *> nextBehaviors;
protected:
    Robot *robot;
    int numNext;
    Behaviors next;
public:
    virtual bool startCond() = 0;
    virtual bool stopCond() = 0;
    virtual void action() = 0;
	Behaviors *addNext(Behaviors *beh);
	Behaviors *selectNext();
	bool isContinue();
	Behaviors();
	Behaviors(Robot *robot);
	int degToIndex(double deg);
	int indexToDeg(double index);
};

#endif /* BEHAVIORS_H_ */
