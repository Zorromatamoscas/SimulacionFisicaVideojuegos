#pragma once
#include "ForceGenerator.h"
// TENGO QUE HACER QUE SE ELIMINE A SI MISMO TRAS SER USADO (PROBABLEMENTE INCLUYENDO EL REGISTRY O CON ALGUNA FLAG)
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

