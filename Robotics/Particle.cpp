/*
 * Particle.cpp
 *
 *  Created on: Jun 12, 2015
 *      Author: colman
 */

#include "Particle.h"


Particle::Particle(float xDelta, float yDelta, float yawDelta, float belief)
{
	this->xDelta = xDelta;
	this->yDelta = yDelta;
	this->yawDelta = yawDelta;
	this->belief = belief;

	this->lifes = PARTICLE_LIFES_NUM;
	this->age = 1;
}

Particle* Particle::CreateChild(float expansionRadius, float yawRange)
{
    float newX = this->xDelta + Random(-expansionRadius, expansionRadius);
    float newY = this->yDelta + Random(-expansionRadius, expansionRadius);
    float newYaw = this->yawDelta + Random(-yawRange, yawRange);
    return new Particle(newX, newY, newYaw, 1);
}

void Particle::Update(float xDelta, float yDelta, float yawDelta, Map* map, LaserProxy* laserProxy)
{
	this->xDelta += xDelta;
    this->yDelta += yDelta;
    this->yawDelta += yawDelta;

    float predictionBelif = ProbabilityByMovement(this->xDelta, this->yDelta, this->yawDelta) * this->belief;
    float probabilityByScan = ProbabilityByLaserScan(this->xDelta, this->yDelta, this->yawDelta, map, laserProxy);
    this->belief = probabilityByScan * predictionBelif * BELIEF_MAGIC_NUMBER;

    if (this->belief > 1)
    	this->belief = 1;
}

float Particle::Random(float min, float max)
{
    float num = (float)rand() / RAND_MAX;
    return min + num * (max - min);
}

float Particle::ProbabilityByMovement(float xDelta, float yDelta, float yawDelta)
{

	float distance = sqrt(pow(xDelta,2) + pow(yDelta,2));

	if (distance < 0.1)
		return 1;

	if (distance < 0.2)
		return 0.9;

	if (distance < 0.4)
		return 0.7;

	if (distance < 0.5)
		return 0.5;

	if (distance < 0.7)
		return 0.3;

	return 0.1;
}

float Particle::ProbabilityByLaserScan(float xDelta, float yDelta, float yawDelta, Map* map, LaserProxy* laserProxy)
{
	// should be pixels.
	float resolution = (Utils::configurationManager->mapResolution) / 100;
	float mapWidth = map->width;
	float mapHeight = map->height;

	float x = Utils::RobotToPixelX(xDelta, resolution, mapWidth);
	float y = Utils::RobotToPixelY(yDelta, resolution, mapHeight);

	double cmInCell = Utils::configurationManager->cmInCell();

        int xCoord = floor(x / cmInCell);
        int yCoord = floor(y / cmInCell);

	if (x < 0 || (x) >= mapWidth ||
	    y < 0 || (y) >= mapHeight)
        {
            //printf("Oops! out of bound! (%f, %f)\n", x, y);
            return 0;
	}

	int** grid = map->grid;

        if (grid[yCoord][xCoord] == 1)
        {
            //printf("obstacle ahead! at (%u, %u) with value:%u\n", yCoord, xCoord, grid[yCoord][xCoord]);
            return 0;
        }

	int scans = laserProxy->GetCount();
	float maxRange = laserProxy->GetMaxRange();

	float totalHits = 0;
	float correctHits = 0;
	int boundaryMisses = 0;

	for(int i=0; i<scans; i++)
        {
            float range = laserProxy->GetRange(i);

            if (range < maxRange)
            {
                totalHits++;

                float bearing = laserProxy->GetBearing(i);
                float obstacleX = xDelta + range * cos(yawDelta + bearing);
                float obstacleY = yDelta + range * sin(yawDelta + bearing);

                obstacleX = Utils::RobotToPixelX(obstacleX, resolution, mapWidth);
                obstacleY = Utils::RobotToPixelY(obstacleY, resolution, mapHeight);

                if ((obstacleX) < 0 || (obstacleX) >= mapWidth ||
                		obstacleY < 0 || (obstacleY) >= mapHeight)
                {
                    boundaryMisses++;
                    continue;
                }

                xCoord = floor(obstacleX / cmInCell);
                yCoord = floor(obstacleY / cmInCell);

                if (grid[yCoord][xCoord] == 1)
                {

                    correctHits++;
//                            printf("%f\n", correctHits);
                }
                else
                {
//                            printf("Oh noes, no hit at (%u, %u)\n", xCoord, yCoord);
                }
            }
	}

	float accuracy = correctHits / totalHits;
//	printf("Particle accuracy: %f\n", accuracy);
	return accuracy;
}


bool Particle::IsDead()
{
    return lifes <= 0;
}


