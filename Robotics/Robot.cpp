/*
 * Robot.cpp
 *
 *  Created on: Jun 12, 2015
 *      Author: colman
 */

#include "Robot.h"


Robot::Robot() {
	// Connect to the emulator
	pc = new PlayerClient("localhost",6665);

	// Init poistion proxy
	pp = new Position2dProxy(pc);

	// Init laser proxy
	lp = new LaserProxy(pc);

	pp->SetMotorEnable(true);

	for(int read=0; read<15; read++){
		pc->Read();
	}

	posX = 0.0;
	posY = 0.0;
	posYaw = 0.0;
}


void Robot::Read(){
	pc->Read();
}

void Robot::setSpeed(float speed, float angularSpeed){
	pp->SetSpeed(speed,angularSpeed);
}

float Robot::getLaserRead(int index){
	return lp->GetRange(index);
}
