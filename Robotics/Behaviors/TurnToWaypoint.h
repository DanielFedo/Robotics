/*
 * TurnToWaypoint.h
 *
 *  Created on: Jul 24, 2015
 *      Author: colman
 */

#ifndef TURNTOWAYPOINT_H_
#define TURNTOWAYPOINT_H_

#include "Behaviors.h"

class TurnToWaypoint: public Behaviors {
public:
	TurnToWaypoint(Robot *robot);

	bool startCond();
	bool stopCond();
	void action();
};

#endif /* TURNTOWAYPOINT_H_ */
