#pragma once
#include "ForceGenerator.h"
class GravityGenerator: public ForceGenerator
{
protected:
	Vector3 myGrav;
public:
	GravityGenerator(Vector3 grav);
	virtual void updateForce(Particle* p);
	inline void setGravity(Vector3 grav) { myGrav = grav; }
};

