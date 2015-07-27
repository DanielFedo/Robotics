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
	pc = new PlayerClient("10.10.245.65",6665);

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

void Robot::setOdometry(int x, int y, int yaw)
{
	int newX = Utils::PixelToMeter(x - Utils::configurationManager->xStart);
	int newY = Utils::PixelToMeter(y - Utils::configurationManager->yStart);


	int radianYaw = Utils::DegreeToRadian(yaw);

	pp->SetOdometry(newX, newY,radianYaw);
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
