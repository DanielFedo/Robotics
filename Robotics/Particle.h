/*
 * Particle.h
 *
 *  Created on: Jun 12, 2015
 *      Author: colman
 */

#ifndef PARTICLE_H_
#define PARTICLE_H_

#include <iostream>

class Particle {
private:
	double xPos, yPos, yaw;
	double belief;
public:
	Particle();

	Particle(double xPos, double yPos, double yaw);
    double getBelief();
    void update(double deltaX, double deltaY, double deltaYaw);
    void printPosition();
};

#endif /* PARTICLE_H_ */
