#pragma once
#pragma once
#include "GaussianoRigido.h"
#include "Firework.h"
#include "RigidsRegistry.h"
#include "ExplosionRigid.h"
#include "WindRigid.h"
class RigidSystem
{
private:
	int myMaxRigids;
	std::list<RigidBody*> particles;
	std::list<RigidGenerator*> partGenerator;
	std::vector<std::list<RigidBody*>::iterator> killList;
	RigidsRegistry* myForceRegistry;
	PxPhysics* myFisicas=nullptr;
	PxScene* myScene = nullptr;
	ExplosionRigid* explGen = nullptr;
	WindRigid* windGen = nullptr;
	RigidBody* model2 = nullptr;
public:
	RigidSystem(PxPhysics* fisicas, PxScene* escena, int maxRigids);
	~RigidSystem();
	void update(double t);
	void explosion();
};


