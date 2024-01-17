#pragma once
#pragma once
#include "GaussianoRigido.h"
#include "Firework.h"
#include "RigidsRegistry.h"
#include "ExplosionRigid.h"
#include "WindRigid.h"
#include "floatRigid.h"
#include "Car.h"
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
	Car* player1;
	Car* player2;
	floatRigid* fltGen = nullptr;
public:
	RigidSystem(PxPhysics* fisicas, PxScene* escena, int maxRigids);
	~RigidSystem();
	void update(double t);
	void explosion();
	inline RigidsRegistry* getRegistry()
	{
		return myForceRegistry;
	}
	inline std::list<RigidBody*> getItems()
	{
		return particles;
	}
	inline Car* getPlayer1()
	{
		return player1;
	}
	inline Car* getPlayer2()
	{
		return player2;
	}
};


