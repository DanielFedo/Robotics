/*
 * Behaviors.h
 *
 *  Created on: Jun 12, 2015
 *      Author: colman
 */

#ifndef BEHAVIORS_H_
#define BEHAVIORS_H_

#include "../Robot.h"
#include <vector> 
#include <stdlib.h>
#include "../Utils.h"
using namespace std;

class Behaviors {

private:
    vector<Behaviors *> nextBehaviors;
protected:

    Robot *robot;
    int numNext;

public:
    Behaviors(Robot *robot);

    virtual bool startCond();
    virtual void action();
    virtual bool stopCond();

	Behaviors *addNext(Behaviors *beh);
	Behaviors *selectNext();

	bool canGoFroward();
	int degToIndex(double deg);
	int indexToDeg(double index);
};

#endif /* BEHAVIORS_H_ */
