#include "Particle.h"
#include <stdlib.h>
#include <vector>
#include "Utils.h"
#include "ConfigurationManager.h"

using namespace std;
class LocalizationManager {

public:
    LocalizationManager();

    vector<Particle *> particles;
    void update(double deltaX, double deltaY, double deltaYaw);
    Particle *getBestParticle();
	void createParticles();
};
