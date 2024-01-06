#pragma once
#include "gameObject.h"
class PowerUps: public GameObject
{
public:
	PowerUps(PxPhysics* fsc, PxScene* scn, Vector3 pos);
	virtual ~PowerUps();

private:

};
	
PowerUps::PowerUps(PxPhysics* fsc, PxScene* scn, Vector3 pos):GameObject(fsc, scn)
{
}

PowerUps::~PowerUps()
{
};

