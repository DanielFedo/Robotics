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
private:
	double xPos, yPos, yaw;
	double belief;
public:
	Particle();

	Particle(double xPos, double yPos, double yaw, double belif);
    double getBelief();
    void update(double deltaX, double deltaY, double deltaYaw);
    Particle* createParticle();
    void printPosition();
};

#endif /* PARTICLE_H_ */
