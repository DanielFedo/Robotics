/*
 * Robot.cpp
 *
 *  Created on: Jun 12, 2015
 *      Author: colman
 */

#include "Robot.h"


Robot::Robot() {
	startYaw = Utils::DegreeToRadian(Utils::configurationManager->yawStart);

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

	// Init robot yaw and odometry
	pp->SetOdometry(0,0,startYaw);
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

void Robot::setOdometry()
{
	pp->SetOdometry(0,0,startYaw);
}

double Robot::getXPos()
{
	return Utils::configurationManager->xStart + Utils::MeterToPixel(pp->GetXPos());
}

double Robot::getYPos()
{
	return Utils::configurationManager->yStart - Utils::MeterToPixel(pp->GetYPos());
}

double Robot::getYaw()
{
	int degree = Utils::RadianToDegree(pp->GetYaw());
	if (degree < 0)
		degree = 360 + degree;

	return degree;
}
