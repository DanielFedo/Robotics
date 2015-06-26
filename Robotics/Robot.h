/*
 * Robot.h
 *
 *  Created on: Jun 12, 2015
 *      Author: colman
 */

#ifndef ROBOT_H_
#define ROBOT_H_
#include <libplayerc++/playerc++.h>

using namespace PlayerCc;

class Robot {
	private:
		PlayerClient pc;
		Position2dProxy pp;
		LaserProxy lp;
		int posX;
		int posY;
		int posYaw;
	public:
		Robot();
		void Read();
		void setSpeed(float speed, float angularSpeed);
};

#endif /* ROBOT_H_ */
