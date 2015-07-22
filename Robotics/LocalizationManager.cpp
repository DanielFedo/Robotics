/*
 * LocalizationManager.cpp
 *
 *  Created on: Jun 12, 2015
 *      Author: colman
 */

#include "LocalizationManager.h"

LocalizationManager::LocalizationManager()
{
	int xStartLocation = Utils::configurationManager->xStart;
	int yStartLocation = Utils::configurationManager->yStart;
	int yawStartLocation = Utils::configurationManager->yawStart;

	// Create the first particle
	Particle* firstParticle = new Particle(xStartLocation, yStartLocation, yawStartLocation, 1);
	particles.push_back(firstParticle);

	// Create all particles
	for(int i = 1; i < Utils::PARTICLES_NUMBER; i++)
	{
		Particle* currentParticle = firstParticle->createParticle();
		particles.push_back(currentParticle);
	}
}
