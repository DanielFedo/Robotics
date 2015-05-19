/*
 * main.cpp
 *
 *  Created on: Jan 10, 2015
 *      Author: colman
 */

#include <libplayerc++/playerc++.h>

using namespace PlayerCc;

#define LASER_SAMPLES 666

int main() {

	PlayerClient pc("localhost", 6665);
	SonarProxy lp(&pc);
	Position2dProxy pp(&pc);
	LaserProxy laser (&pc);
	bool isClear = true;
	int nRight;
	int nLeft;

	pp.SetMotorEnable(true);
	while (true) {
		pc.Read();

		nRight = 0;
		nLeft = 0;

		for (int i = LASER_SAMPLES/3; i < LASER_SAMPLES * 2 / 3; ++i) {
			if (laser [i] < 0.8 && i <= LASER_SAMPLES/2) {
				isClear = false;
				nRight +=1;
			}

			else if (laser [i] < 0.8 && i > LASER_SAMPLES/2) {
				isClear = false;
				nLeft +=1;
			}
		}

		if (!isClear) {
			if (nLeft > nRight)
				pp.SetSpeed(0.0, 0.3);
			else
				pp.SetSpeed(0.0, -0.3);

			isClear = true;
		}

		else
			pp.SetSpeed(0.8, 0.0);
	}
	return 0;

}
