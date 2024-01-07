#pragma once
#include "PowerUps.h"
#include "RigidSystem.h"
class Bomb:public PowerUps
{
private:
	bool activate = false;
public:
	Bomb(Vector3 pos): PowerUps(pos,Vector3(0,0,0))
	{
	}
	virtual void applyPower(Car* car, RigidsRegistry* registry)
	{
		registry->addRegistry(new ExplosionRigid(pose.p, 50, 500000, 3), car->getBody());
	}
	virtual void integrate(double t)
	{
		PowerUps::integrate(t);
		if (activate)
		{

		}
	}
};
