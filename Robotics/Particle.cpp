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

	this->age = 1;
}

Particle* Particle::CreateChild(float expansionRadius, float yawRange)
{
    float newX = this->xDelta + Random(-expansionRadius, expansionRadius);
    float newY = this->yDelta + Random(-expansionRadius, expansionRadius);
    float newYaw = this->yawDelta + Random(-yawRange, yawRange);
    return new Particle(newX, newY, newYaw, -1);
}

void Particle::Update(float xDelta, float yDelta, float yawDelta, Map* map, LaserProxy* laserProxy)
{
	this->xDelta += xDelta;
    this->yDelta += yDelta;
    this->yawDelta += yawDelta;

    //float predictionBelif = ProbabilityByMovement(xDelta, yDelta, yawDelta) * this->belief;
    float probabilityByScan = ProbabilityByLaserScan(this->xDelta, this->yDelta, this->yawDelta, map, laserProxy);
    this->belief = probabilityByScan ;//* predictionBelif; //* BELIEF_MAGIC_NUMBER;

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

	if (distance < 1)
		return 1;

	if (distance < 3)
		return 0.9;

	if (distance < 5)
		return 0.7;

	if (distance < 7)
		return 0.5;

	if (distance < 9)
		return 0.3;

	return 0.1;
}

float Particle::ProbabilityByLaserScan(float xDelta, float yDelta, float yawDelta, Map* map, LaserProxy* laserProxy)
{
	//cout << "X: " << xDelta << "Y: " << yDelta << " YAW: " << yawDelta << endl;

	float mapWidth = map->width;
	float mapHeight = map->height;

	float x = xDelta;
	float y = yDelta;

	int xCoord = floor(x);
	int yCoord = floor(y);

	if (x < 0 || x >= mapWidth ||
	    y < 0 || y >= mapHeight)
	{
		//printf("Oops! out of bound! (%f, %f)\n", x, y);
		return 0;
	}

	vector< vector<Utils::CELL_STATUS> > grid = map->originalMap;

	if (grid[yCoord][xCoord] == 1)
	{
		printf("!!obstacle ahead! at (%u, %u) with value:%u\n", yCoord, xCoord, grid[yCoord][xCoord]);
		return 0;
	}

	int scans = laserProxy->GetCount();
	float maxRange = laserProxy->GetMaxRange();

	float totalHits = 0;
	float correctHits = 0;
	int boundaryMisses = 0;

	for(int i=0; i < scans; i++)
	{
		float range = laserProxy->GetRange(i);

		if (range < maxRange)
		{
			totalHits++;

			float bearing = laserProxy->GetBearing(i);
					//Utils::IndexToRadians(i);

			float rangeInPixels = Utils::MeterToPixel(range);
			float yawInRadians = Utils::DegreeToRadian(yawDelta);

			float obstacleX = xDelta + rangeInPixels * cos(yawInRadians + bearing);
			float obstacleY = yDelta - rangeInPixels * sin(yawInRadians + bearing);

			//cout << "obstacle in range: " << rangeInPixels << " yaw: " << Utils::RadianToDegree(yawInRadians + bearing) << endl;

			if ((obstacleX) < 0 || (obstacleX) >= mapWidth -10 ||
					obstacleY < 0 || (obstacleY) >= mapHeight -10)
			{
				boundaryMisses++;

				continue;
			}

			if (grid[floor(obstacleY)][floor(obstacleX)] == 1)
			{

				correctHits++;
				//cout << "correct hit on: [" << obstacleX << ", " << obstacleY << "]   ";
			}
			else
			{
				//cout << "!missed hit on: [" << obstacleX << ", " << obstacleY << "]   ";
			}
		}
	}

	float accuracy = correctHits / totalHits;
	//cout << "--Particle accuracy: " << accuracy << " Yaw " << yawDelta << " correct hits: " << correctHits  << " total hits: " << totalHits << endl;

	return accuracy;
}

Particle* Particle::CreateChild()
{
    return CreateChild(EXPANSION_RADIUS, YAW_RANGE);
}

float Particle::GetX()
{
    return xDelta;
}

float Particle::GetY()
{
    return yDelta;
}

float Particle::GetYaw()
{
    return yawDelta;
}


