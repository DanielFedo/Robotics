#include <iostream>
#include <libplayerc++/playerc++.h>

using namespace std;
using namespace PlayerCc;

#define LASER_SAMPLES 666
#define MIN_ANGLE_FOR_AVOIDANCE -45
#define MAX_ANGLE_FOR_AVOIDANCE 45
#define MAX_DIST_TO_OBSTACLE 0.5


int deg_to_index(double deg)
{
	return (deg + 120) / 0.36;
}

int indexToDeg(double index)
{
	return ((index * 0.36) - 120);
}

void move()
{
	// Connect to the emulator
	PlayerClient pc("localhost",6665);

	// Init poistion proxy
	Position2dProxy pp(&pc,0);

	// Init laser proxy
	LaserProxy lp(&pc, 0);

	pc.Read();


	pp.SetSpeed(1, 0);

	pp.SetSpeed(0, 0);
}

void move2()
{
	PlayerClient pc("localhost",6665);
    Position2dProxy pp(&pc);
    pp.SetMotorEnable(true);

    // Move the robot forward for 2 seconds
    for (int i = 1; i < 20; i++) {
        // Read from the proxies
        pc.Read();

        // Command the motors
        pp.SetSpeed(0.2, 0);
    }
}

void printPosition()
{
	PlayerClient pc("localhost",6665);
    Position2dProxy pp(&pc);


    pc.Read();
    pp.ResetOdometry();
    pc.Read();
    double x_rob = pp.GetXPos();
    double y_rob = pp.GetYPos();
    double yaw = pp.GetYaw();

    cout << "robot's pose is: (" << x_rob << "," << y_rob << "," << yaw << ")" << endl;
}

int main(int argc, char** argv)
{
	//move();

	//move2();

	//printPosition();

	// Connect to the emulator
	PlayerClient pc("localhost",6665);

	// Init poistion proxy
	Position2dProxy pp(&pc,0);

	// Init laser proxy
	LaserProxy lp(&pc, 0);

	while (true)
	{
		pc.Read();
		bool isObstacleInFront = false;
		int minIndex = deg_to_index(MIN_ANGLE_FOR_AVOIDANCE);
		int maxIndex = deg_to_index(MAX_ANGLE_FOR_AVOIDANCE);

		for (int i = minIndex; i <= maxIndex; i++)
		{
			if (lp[i] < MAX_DIST_TO_OBSTACLE)
			{
				isObstacleInFront = true;

				double d = lp[i];
				double alpha = pp.GetYaw();
				double beta = indexToDeg(i);
				double robotX = pp.GetXPos();
				double robotY = pp.GetYPos();

				double obstacleX = robotX + d * cos(alpha + beta);
				double obstacleY = robotY + d * sin(alpha + beta);

				cout << "obstacle's pose is: (" << obstacleX << "," << obstacleY << endl;

				break;
			}
		}

		if (isObstacleInFront)
			pp.SetSpeed(0, 0.5);
		else
			pp.SetSpeed(0.5, 0);
	}

	return 0;
}



