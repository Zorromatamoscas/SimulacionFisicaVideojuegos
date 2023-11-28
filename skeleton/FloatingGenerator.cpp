#include "FloatingGenerator.h"
FloatingGenerator::FloatingGenerator(float partHeight, float V, float d, Particle* liquid_surface) : ForceGenerator(),
volume(V), density(d), surface(liquid_surface), particleHeigth(partHeight);
{
}

void FloatingGenerator::updateForce(Particle* p, double duration)
{
	if (fabs(p->getInvMass()) <= 0.0f) return;

	float h = p->getPosition().y;
	float h0 = surface->getPosition().y;

	Vector3 f(0, 0, 0);
	float immersed = 0.0;
	if (h0 - h > particleHeigth * 0.5) immersed = 1.0;
	else if (h - h0 > particleHeigth * 0.5) immersed = 0.0;
	else immersed = (h0 - h) / particleHeigth + 0.5;

	f.y = density * volume * immersed * 9.8;
	p->addForce(f);
}