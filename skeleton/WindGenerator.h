#pragma once
#include "ForceGenerator.h"
class WindGenerator:public ForceGenerator
{
private:
	Vector3 windVel;
	Vector3 pos;
	double volume;
	bool isInBounds(Particle* p);
public:
	WindGenerator(Vector3 wndVel, Vector3 positon, double vol);
};

