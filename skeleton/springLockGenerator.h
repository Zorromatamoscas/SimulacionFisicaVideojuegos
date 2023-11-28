#pragma once
#include "ForceGenerator.h"
class springLockGenerator: public ForceGenerator
{
private:
	double kConstant;
	double springLength;
	Vector3 anchorPoint;

public:
	springLockGenerator(double k, double lenght, Vector3 anchorP);
	virtual void updateForce(Particle* p, double t);
};

