#pragma once
#include "gameObject.h"
#include "Car.h"
#include "Particle.h"
class PowerUps: public Particle
{
protected:
public:
	PowerUps(Vector3 pos, Vector3 color);
	bool checkCollisions(Car* car);
	virtual void integrate(double t)
	{
		lifeTime -= t;
	}
	virtual void applyPower(Car* car) = 0;
};
	


