/*
 * Particle.h
 *
 *  Created on: Jun 12, 2015
 *      Author: colman
 */

#ifndef PARTICLE_H_
#define PARTICLE_H_

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
using namespace std;

#include "Map.h"
#include <libplayerc++/playerc++.h>
using namespace PlayerCc;

#define NORMAL_BREED 5
#define HIGH_BREED 20
#define MAX_PARTICLES_COUNT 200
#define EXPANSION_RADIUS 1
#define YAW_RANGE 10
#define LOW_BELIEF_MIN 0.2
#define HIGH_BELIEF_MIN 0.7
#define BELIEF_MAGIC_NUMBER 2
#define PARTICLE_LIFES_NUM 5
#define EMERGENCY_EXPANSION_RADIUS EXPANSION_RADIUS * 2
#define EMERGENCY_YAW_RANGE YAW_RANGE * 2
#define PARTICLE_EMERGENCY_BREED MAX_PARTICLES_COUNT - 2
#define DEFAULT_WAYPOINT_RESOLUTION 6
#define DEFAULT_WAYPOINT_ACCURACY (0.1F)
#define WAYPOINT_RADIUS 4
#define DETECT_EVASION_RADIUS 0.6

class Particle {
public:
	float xDelta;
	float yDelta;
	float yawDelta;
	float belief;

	int lifes;
	int age;

	float Random(float min, float max);
	float ProbabilityByMovement(float xDelta, float yDelta, float yawDelta);
	float ProbabilityByLaserScan(float xDelta, float yDelta, float yawDelta, Map* map, LaserProxy* laserProxy);

	Particle(float xDelta, float yDelta, float yawDelta, float belief);
	Particle* CreateChild();
	Particle* CreateChild(float expansionRadius, float yawRange);
	void Update(float X_delta, float Y_delta, float Yaw_delta, Map* map, LaserProxy* lp);
	bool IsDead();

	float GetX();
	float GetY();
	float GetYaw();
};

#endif /* PARTICLE_H_ */
