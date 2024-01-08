#pragma once
#include "gameObject.h"
#include "Car.h"
#include "Particle.h"
#include "RigidSystem.h"
class PowerUps: public Particle
{
protected:
	RigidSystem* mySystem;
public:
	PowerUps(Vector3 pos, Vector3 color, RigidSystem* system, bool model=false);
	bool checkCollisions();
	virtual void integrate(double t)
	{
		lifeTime -= t;
	}
	virtual void applyPower(Car* car) = 0;
};
	


