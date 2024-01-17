#include "floatRigid.h"
floatRigid::floatRigid(float V, float d, Particle* liquid_surface):
	volume(V), density(d), surface(liquid_surface)
{
}

void floatRigid::updateForce(RigidBody* p, double duration)
{
	if (fabs(p->getRigid()->getInvMass()) <= 0.0f) return;

	float h = p->getPosition().y;
	float h0 = surface->getPosition().y;
	Vector3 f(0, 0, 0);
	float immersed = 0.0;
	if (h0 - h > p->getHeight() * 0.5) immersed = 1.0;
	else if (h - h0 > p->getHeight() * 0.5) immersed = 0.0;
	else immersed = (h0 - h) / p->getHeight() + 0.5;

	f.y = density * volume * immersed * 9.8;
	p->addForce(f);
}