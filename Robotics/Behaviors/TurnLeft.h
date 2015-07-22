/*
 * TurnLeft.h
 *
 *  Created on: Jun 26, 2015
 *      Author: colman
 */

#ifndef TURNLEFT_H_
#define TURNLEFT_H_

#include "Behaviors.h"

class TurnLeft: public Behaviors {
public:
	TurnLeft(Robot *robot);

	bool startCond();
	bool stopCond();
	void action();
};

#endif /* TURNLEFT_H_ */
