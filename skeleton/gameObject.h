#pragma once
#include "RigidBody.h"
class GameObject
{
public:
	GameObject(PxPhysics* fsc, PxScene* scn) : fisicas(fsc), escena(scn) {};
	virtual ~GameObject() {};

protected:
	PxPhysics* fisicas;
	PxScene* escena;
};

