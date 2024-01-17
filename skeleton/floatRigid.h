#pragma once
#include "RigidForceGenerator.h"
#include "Particle.h"
class floatRigid: public RigidForceGenerator
{
private:
	float volume;
	float density;
	Particle* surface;
public:
	floatRigid(float V, float d, Particle* liquid_surface);
	virtual void updateForce(RigidBody* p, double t);
};

