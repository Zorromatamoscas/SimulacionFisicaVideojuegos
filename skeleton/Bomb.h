#pragma once
#include "PowerUps.h"
#include "RigidSystem.h"
class Bomb:public PowerUps
{
private:
	bool activate = false;

public:
	Bomb(Vector3 pos, RigidSystem* system, bool model=false): PowerUps(pos,Vector3(0,0,0), system, model)
	{
	}
	virtual void applyPower(Car* car)
	{
		mySystem->getRegistry()->addRegistry(new ExplosionRigid(pose.p, 50, 500000, 3), car->getBody());
		lifeTime = -1;
	}
	virtual Particle* clone(Vector3 newPos, Vector3 newVel, float newLifeTime) const {
		return new Bomb(newPos,mySystem);
	}
	virtual Particle* clone(Vector3 newVel, float newLifeTime) const {
		return new Bomb(pose.p, mySystem);
	}
};
