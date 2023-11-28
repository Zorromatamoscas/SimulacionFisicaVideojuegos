#pragma once
#include "ForceGenerator.h"
class springLockGenerator: public ForceGenerator
{
private:
	double kConstant;
	double springLength;
	Vector3 anchorPoint;
	Particle* other = nullptr;

public:
	springLockGenerator(double k, double lenght, Vector3 anchorP);
	springLockGenerator(double k, double lenght, Particle* othe);
	virtual void updateForce(Particle* p, double t);
};

