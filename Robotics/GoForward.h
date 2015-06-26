/*
 * GoForward.h
 *
 *  Created on: Jun 26, 2015
 *      Author: colman
 */

#ifndef GOFORWARD_H_
#define GOFORWARD_H_

#include "Robot.h"
#include "Behaviors.h"

class GoForward: public Behaviors {
public:
	GoForward(Robot* robot);

	bool startCond();
	bool stopCond();
	void action();

	virtual ~GoForward();
};

#endif /* GOFORWARD_H_ */
