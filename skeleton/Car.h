#pragma once
#include "gameObject.h"
class Car: public GameObject
{
private:
	PxAggregate* myCar;
	RigidBody* myBody;
	RigidBody* myBumper;
	RigidBody* myRear;

public:
	Car(PxPhysics* fsc, PxScene* scn, Vector3 pos, bool player1);
	virtual ~Car();

	void accelerate();
	void rotate() {};
	void checkCollision(GameObject* other);
};


