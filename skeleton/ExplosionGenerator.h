#pragma once
#include "ForceGenerator.h"
class ExplosionGenerator: public ForceGenerator
{
private:
	double radius;	
	float strength;
	float timeConstant;
	bool activated;
	Vector3 pos;

public:
	ExplosionGenerator(Vector3 ExpPos, double radio, float ExpStrength, float timeConstant, bool activ = false);
	virtual void updateForce(Particle* p, double t);
	inline void setActive(bool act) { 
		activated = act;
		resetTime();
	}
};

