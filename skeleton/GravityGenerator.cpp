#include "GravityGenerator.h"
GravityGenerator::GravityGenerator(Vector3 grav) : ForceGenerator()
{
	myGrav = grav;
}
void GravityGenerator::updateForce(Particle* p, double t)
{
	if (fabs(p->getInvMass() < 1e-10)) return;
	p->addForce(myGrav/p->getInvMass());
}