#pragma once
#pragma once
#include "RigidForceGenerator.h"
class ExplosionRigid : public RigidForceGenerator
{
private:
	double radius;
	float strength;
	float timeConstant;
	bool activated;
	Vector3 pos;

public:
	ExplosionRigid(Vector3 ExpPos, double radio, float ExpStrength, float timeConstant, bool activ = false);
	virtual void updateForce(RigidBody* p, double t);
	inline void setActive(bool act) {
		activated = act;
		resetTime();
	}
};

