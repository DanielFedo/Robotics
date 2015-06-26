/*
 * Particle.cpp
 *
 *  Created on: Jun 12, 2015
 *      Author: colman
 */

#include "Particle.h"

Particle::Particle() {
	// TODO Auto-generated constructor stub

}

Particle::Particle(double xPos, double yPos, double yaw){
	this->xPos = xPos;
	this->yPos = yPos;
	this->yaw = yaw;

	this->belief = 0; // ?
}

void Particle::printPosition(){
	std::cout << " " << xPos << " " << yPos << std::endl;
}

void Particle::update(double deltaX, double deltaY, double deltaYaw){
	this->xPos += deltaX;
	this->yPos += deltaY;
	this->yaw += deltaYaw;
}

double Particle::getBelief(){
	double newBelief = 0;

	this->belief = newBelief;
	return this->belief;
}
