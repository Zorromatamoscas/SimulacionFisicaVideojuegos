#pragma once
#include "PowerUps.h"
class WindPowerUp: public PowerUps
{
public:
	WindPowerUp(Vector3 pos, RigidSystem* system, bool model = false) : PowerUps(pos, Vector3(0, 1, 0),system,model)
	{
	}
	virtual void applyPower(Car* car)
	{
		if (car->isPlayer1()) car = mySystem->getPlayer2();
		else car = mySystem->getPlayer1();
		mySystem->getRegistry()->addRegistry(new ExplosionRigid(pose.p, 50, 500000, 3), car->getBody());
		lifeTime = -1;
	}
	virtual Particle* clone(Vector3 newPos, Vector3 newVel, float newLifeTime) const {
		return new WindPowerUp(newPos, mySystem);
	}
	virtual Particle* clone(Vector3 newVel, float newLifeTime) const {
		return new WindPowerUp(pose.p, mySystem);
	}
};