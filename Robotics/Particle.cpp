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

double Particle::update(int deltaX, int deltaY, int deltaYaw,
		Robot* robot) {

	this->xPos =  deltaX;
	this->yPos += deltaY;
	this->yaw += deltaYaw;

	double probByMovement = this->probByMove(deltaX, deltaY, deltaYaw);
	double probByMeasure = this->probByMeasure(robot);
	double newBelief = belief * 2.5 * probByMeasure * probByMovement;

	//cout << " x: " << loc->x << " y: " << loc->y << "before: " << belief << " after: " << newBelief <<
		//	" measure: "<< probByMeasure << " movement: " << probByMovement << endl;

	belief = newBelief;

	if (belief > 1){
		belief = 1;
	}

	return belief;
}

Particle* Particle::createParticle() {
	int xPos = this->xPos += pow(-1, rand());
	int yPos = this->yPos += pow(-1, rand());
	int yaw = this->yaw += (rand() % 30 - 15);

	return new Particle(xPos,yPos, yaw, this->belief-0.01);
}

double Particle::probByMove(int deltaX, int deltaY, int deltaYaw) {
	double prob;
	double deltaDistance = sqrt(pow(deltaX, 2) + pow(deltaY, 2));

	double realDeltaYaw = 0;
	int absDeltaYaw = fabs(deltaYaw);

	// Fix the angle reading
	if (absDeltaYaw > 180) {
		realDeltaYaw = 360 - absDeltaYaw;
	} else {
		realDeltaYaw = absDeltaYaw;
	}

	// Check the probability of the robot real location
	if ((deltaDistance < 0.2) && (realDeltaYaw < 0.01)) {
		prob = Utils::PERFECT_PROB;
	} else if ((deltaDistance < 0.2) && (realDeltaYaw < 20)) {
		prob = Utils::HIGH_PROB;
	} else if ((deltaDistance > 0.2) && (realDeltaYaw > 20)) {
		prob = Utils::LOW_PROB;
	} else {
		prob = Utils::MEDIUM_PROB;
	}

	return prob;
}

double Particle::probByMeasure(Robot* robot) {
	double missesCount = 0;
	double hitsCount = 0;

	double currentYaw = Utils::DegreeToRadian(this->yaw);
	vector< vector<Utils::CELL_STATUS> > map = Map::getInstance()->newMatrix;

	for (int i = 0; i <= Utils::MAX_LASER_INDEX; i += 20) {
		double laserAngle = convertLaserIndexToLaserAngle(i);
		double disFromObstacle = robot->getLaserRead(i);
		double measuredDistance = Utils::MeterToPixel(disFromObstacle);

		bool isObstacleHit = false;

		// check the distance
		if (disFromObstacle < 4.0 && disFromObstacle > 0.2) {
			double cosinus = cos(currentYaw + laserAngle);
			double sinus = sin(currentYaw + laserAngle);

			// check if the obstacle is in the right place
			for (int j=0; j<measuredDistance; j++){

				int xToCheck= this->xPos +  (j * cosinus);
				int yToCheck = this->yPos - (j * sinus);

				if (xToCheck > Map::getInstance()->gridHeight || yToCheck > Map::getInstance()->gridWidth) {
					isObstacleHit = true;
					break;
				}

				if (Map::getInstance()->isCellFree(1, 0)) {
					double realDistanceFromObstacle = sqrt(pow(yToCheck - this->yPos,2) + pow(xToCheck - this->xPos,2));
					double disAbs = fabs(
							realDistanceFromObstacle - measuredDistance);

					if (disAbs < 1)
					{
						isObstacleHit = true;
					}
					break;
				}
			}

			if (!isObstacleHit) {
				missesCount++;
			}
			else {
				hitsCount++;
			}
		}
	}

	if (hitsCount + missesCount == 0){
		return 1;
	}

	return (hitsCount / (hitsCount + missesCount));
}

double Particle::convertLaserIndexToLaserAngle(int index)
{
	return ((index * Utils::ANGULAR_RESULUTION - 120.0) / 180.0) * PI;
}
