/*
 * TurnRight.h
 *
 *  Created on: Jun 26, 2015
 *      Author: colman
 */

#ifndef TURNRIGHT_H_
#define TURNRIGHT_H_

#include "Behaviors.h"

class TurnRight: public Behaviors {
public:
	TurnRight();

	bool startCond();
	bool stopCond();
	void action();
};

#endif /* TURNRIGHT_H_ */
