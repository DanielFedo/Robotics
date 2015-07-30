#include "LocalizationManager.h"
#include <ctime>

LocalizationManager::LocalizationManager(Map* map) {
	this->map = map;

	xDelta = yDelta = yawDelta = 0;
}

bool LocalizationManager::CreateParticle(float xDelta, float yDelta, float yawDelta, float belief)
{
	CreateParticle(xDelta, yDelta, yawDelta, belief, EXPANSION_RADIUS, YAW_RANGE, HIGH_BREED);
}

bool LocalizationManager::CreateParticle(float xDelta, float yDelta, float yawDelta, float belief, float expansionRadius, float yawRange, int childsCount)
{
	if (particles.size() + childsCount < MAX_PARTICLES_COUNT)
	{
		Particle* particle = new Particle(xDelta, yDelta, yawDelta, belief);
		particles.push_back(particle);
		vector<Particle*> childs;
		BreedParticle(particle, childsCount, expansionRadius, yawRange, childs);
		ChildsToParticles(childs);
		return true;
	}

	return false;
}

void LocalizationManager::Update(float deltaX, float deltaY, float deltaYaw, LaserProxy* laserProxy) {
	vector<Particle*> childsToAdd;
	vector<int> childsToRemove;
	int particlesSize = particles.size();

	// Update all the particles
	for (int i = 0; i < particlesSize; i++)
	{
		Particle* particle = particles[i];
		particle->Update(deltaX, deltaY, deltaYaw, map, laserProxy);

		float belif = particle->belief;

		// If belief is too low - remove the particle
		if (belif <= LOW_BELIEF_MIN)
		{
			childsToRemove.push_back(i);
		}
		// If belief is high - high breed
		else if (belif >= HIGH_BELIEF_MIN &&
				 ((particlesSize + HIGH_BREED + childsToAdd.size()) < MAX_PARTICLES_COUNT))
		{
			particle->age++;
			BreedParticle(particle, HIGH_BREED, childsToAdd);
		}
		// If belief is normal - normal breed
		else if ((particlesSize + NORMAL_BREED + childsToAdd.size()) < MAX_PARTICLES_COUNT)
		{
			particle->age++;
			BreedParticle(particle, NORMAL_BREED, childsToAdd);
		}
	}

	if (childsToRemove.size() > 0)
	{
		for(int i = childsToRemove.size() - 1; i >=0 ; i--)
		{
			int indexToRemove = childsToRemove[i];
			particles.erase(particles.begin() + indexToRemove);
		}
	}

	if (childsToAdd.size() > 0)
	{
		ChildsToParticles(childsToAdd);
	}
}

void LocalizationManager::BreedParticle(Particle* particle, int childCount, vector<Particle*>& childs)
{
	if (particles.size() + childCount < MAX_PARTICLES_COUNT)
	{
		for (int i = 0; i < childCount; i++)
		{
			Particle* child = particle->CreateChild();
			childs.push_back(child);
		}
	}
}

void LocalizationManager::BreedParticle(Particle* particle, int childCount, float expansionRadius, float yawRange, vector<Particle*>& childs)
{
	if (particles.size() + childCount < MAX_PARTICLES_COUNT)
	{
		for (int i = 0; i < childCount; i++)
		{
				Particle* child = particle->CreateChild(expansionRadius, yawRange);
				childs.push_back(child);
		}
	}
}

// This method return the particle with highest belief
Particle* LocalizationManager::BestParticle()
{
	// If there are no particles - we need to generate new ones
	if (particles.empty())
	{
		printf("!!Out of particles! Making new ones!\n");
		CreateParticle(xDelta, yDelta, yawDelta, 1, EMERGENCY_EXPANSION_RADIUS, EMERGENCY_YAW_RANGE,  PARTICLE_EMERGENCY_BREED);

		Particle* randomParticle = particles[rand() % particles.size()];

		xDelta = randomParticle->xDelta;
		yDelta = randomParticle->yDelta;
		yawDelta = randomParticle->yawDelta;

		return randomParticle;
	}

	Particle* bestParticle = particles[0];

	cout << "** Choosing best particle **" << endl;

	// Search for the best particale
	for (int i = 1; i < particles.size(); i++)
	{
		cout << "[" << particles[i]->xDelta << "," << particles[i]->yDelta << "] Yaw: " << particles[i]->yawDelta << " b: " << particles[i]->belief << endl;

		if (particles[i]->belief > bestParticle->belief)
				//&& particles[i]->age < bestParticle->age)
		{
			bestParticle = particles[i];
		}
	}

	xDelta = bestParticle->xDelta;
	yDelta = bestParticle->yDelta;
	yawDelta = bestParticle->yawDelta;

	return bestParticle;
}

void LocalizationManager::ChildsToParticles(vector<Particle*> childs)
{
	for (int i = 0; i < childs.size(); i++)
	{
		particles.push_back(childs[i]);
	}
}
