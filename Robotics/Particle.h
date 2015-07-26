/*
 * Particle.h
 *
 *  Created on: Jun 12, 2015
 *      Author: colman
 */

#ifndef PARTICLE_H_
#define PARTICLE_H_

#include <iostream>
#include <vector>
#include "Robot.h"
#include "Utils.h"
#include <math.h>
#include <cmath>
#include <cstdlib>
#include "Map.h"

class Particle {

public:
	double belief;
	double xPos, yPos, yaw;
	Particle();

	Particle(double xPos, double yPos, double yaw, double belif);
    double update(int deltaX, int deltaY, int deltaYaw, Robot* robot);
    double probByMove(int deltaX, int deltaY, int deltaYaw);
    double probByMeasure(Robot* robot);
    Particle* createParticle();
    double convertLaserIndexToLaserAngle(int index);
    void printPosition();
};

#endif /* PARTICLE_H_ */
