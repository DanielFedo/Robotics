#include "Particle.h"
#include <stdlib.h>
#include <vector>
using namespace std;
class LocalizationManager {
private:
    vector<Particle *> particles;
public:
    LocalizationManager();
    void update(double deltaX, double deltaY, double deltaYaw);
    void resampleParticles();
    Particle *getBestParticle();
};
