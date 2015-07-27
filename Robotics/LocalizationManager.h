#ifndef LOCALIZATIONMANAGER_H
#define	LOCALIZATIONMANAGER_H

#include <vector>
using namespace std;

#include "Particle.h"
#include "Map.h"

class LocalizationManager {

	Map* map;
		vector<Particle*> particles;

		float xDelta;
		float yDelta;
		float yawDelta;

		void ChildsToParticles(vector<Particle*> childs);
		void BreedParticle(Particle* particle, int dwChildCount, vector<Particle*>& childs);
		void BreedParticle(Particle* particle, int dwChildCount, float dExpansionRadius, float dYawRange, vector<Particle*>& childs);

public:
	bool CreateParticle(float xDelta, float yDelta, float yawDelta, float belief);
	bool CreateParticle(float xDelta, float yDelta, float yawDelta, float belief, float expansionRadius, float yawRange, int childsCount);

	LocalizationManager(Map* map);
	void Update(float xDelta, float yDelta, float yawDelta, LaserProxy* laserProxy);
	Particle* BestParticle();

};

#endif	/* LOCALIZATIONMANAGER_H */
