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

Particle::Particle(double xPos, double yPos, double yaw, double belief){
	this->xPos = xPos;
	this->yPos = yPos;
	this->yaw = yaw;
	this->belief = belief;
}

void Particle::printPosition(){
	std::cout << " " << xPos << " " << yPos << std::endl;
}

void Particle::update(double deltaX, double deltaY, double deltaYaw){
	this->xPos += deltaX;
	this->yPos += deltaY;
	this->yaw += deltaYaw;
}

Particle* Particle::createParticle() {
	int xPos = this->xPos += pow(-1, rand());
	int yPos = this->yPos += pow(-1, rand());
	int yaw = this->yaw += (rand() % 30 - 15);

	return new Particle(xPos,yPos, yaw this->belief-0.01);

double Particle::getBelief(){
	double newBelief = 0;

	this->belief = newBelief;
	return this->belief;
}
