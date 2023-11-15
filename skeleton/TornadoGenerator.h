#pragma once
#include "WindGenerator.h"
class TornadoGenerator: public WindGenerator
{
private:
	double k;
public:
	TornadoGenerator(Vector3 wndVel, Vector3 positon, double vol, double konstant1, double konstant2, double tornStrength);
	virtual void updateForce(Particle* p);
};

