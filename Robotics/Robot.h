/*
 * Robot.h
 *
 *  Created on: Jun 12, 2015
 *      Author: colman
 */

#ifndef ROBOT_H_
#define ROBOT_H_
#include <libplayerc++/playerc++.h>
#include "Utils.h"

using namespace PlayerCc;

class Robot {
	private:
		PlayerClient* pc;
		Position2dProxy* pp;
		LaserProxy* lp;
		int posX;
		int posY;
		int posYaw;
		double startYaw;
	public:
		Robot();
		void Read();
		void setSpeed(float speed, float angularSpeed);
		float getLaserRead(int index);
	    void setOdometry();
	    void setOdometry(int x, int y, int yaw);
		double getXPos();
		double getYPos();
		double getYaw();
		LaserProxy* getLaserProxy();
};

#endif /* ROBOT_H_ */
