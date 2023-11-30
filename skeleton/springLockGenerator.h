#pragma once
#include "ForceGenerator.h"
class springLockGenerator: public ForceGenerator
{
private:
	double kConstant;
	double springLength;
	Vector3 anchorPoint;
	Particle* other = nullptr;
	bool myGoma;

public:
	springLockGenerator(double k, double lenght, Vector3 anchorP, bool goma=false);
	springLockGenerator(double k, double lenght, Particle* othe, bool goma=false);
	virtual void updateForce(Particle* p, double t);
};

