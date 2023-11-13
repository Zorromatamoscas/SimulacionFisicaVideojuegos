#include "GravityGenerator.h"
void GravityGenerator::updateForce(Particle* p, double t)
{
	if (fabs(p->getInvMass() < 1e-10)) return;
}