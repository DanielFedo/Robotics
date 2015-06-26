/*
 * Robot.cpp
 *
 *  Created on: Jun 12, 2015
 *      Author: colman
 */

#include "Robot.h"

#include <libplayerc++/playerc++.h>

using namespace PlayerCc;

Robot::Robot() {
	pc("localhost", 6665);

	pp = new Position2dProxy(pc);
	lp = new LaserProxy(pc);

	for(int read=0; read<15; read++){
		pc.Read();
	}
	pp.SetMotorEnable(true);

	posX = 0.0;
	posY = 0.0;
	posYaw = 0.0;
}

Robot::Read(){
	pc.Read();
}

void Robot::setSpeed(float speed, float angularSpee){
	pp.SetSpeed(speed,angularSpee);
}
