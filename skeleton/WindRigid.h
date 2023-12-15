#pragma once
#pragma once
#include "RigidForceGenerator.h"
class WindRigid :public RigidForceGenerator
{
protected:
	Vector3 windVel;
	Vector3 pos;
	double volume;
	bool isInBounds(RigidBody* p);
	double k1, k2;
public:
	WindRigid(Vector3 wndVel, Vector3 positon, double vol, double konstant1, double konstant2);
	virtual void updateForce(RigidBody* p, double t);
};


