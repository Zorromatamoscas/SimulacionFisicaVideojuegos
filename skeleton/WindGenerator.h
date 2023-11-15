#pragma once
#include "ForceGenerator.h"
class WindGenerator:public ForceGenerator
{
protected:
	Vector3 windVel;
	Vector3 pos;
	double volume;
	bool isInBounds(Particle* p);
	double k1, k2;
public:
	WindGenerator(Vector3 wndVel, Vector3 positon, double vol, double konstant1, double konstant2);
	virtual void updateForce(Particle* p);
};

