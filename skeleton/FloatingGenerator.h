#pragma once
#include "ForceGenerator.h"
class FloatingGenerator: public ForceGenerator
{
private:
	float volume;
	float density;
	Particle* surface;
	float particleHeigth;
public:
	FloatingGenerator(float partHeight, float V, float d, Particle* liquid_surface);
	virtual void updateForce(Particle* p, double t);
};

