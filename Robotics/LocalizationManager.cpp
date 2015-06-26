/*
 * LocalizationManager.cpp
 *
 *  Created on: Jun 12, 2015
 *      Author: colman
 */

#include "LocalizationManager.h"

LocalizationManager::LocalizationManager() {
	int numToGenerate = 500;
	int posX;
	int posY;
	int yaw;

	for (int i = 0; i < numToGenerate; i++)
	{
		posX = (rand() % 550);
		posY = (rand() % 380);
		yaw = (rand() % 240);

		Particle *p = new Particle(posX, posY, yaw);
		this->particles[i] = p;
	}
}
