#pragma once
#include "gameObject.h"
class Car: public GameObject
{
private:
	PxAggregate* myCar;
	RigidBody* myBody;
	RigidBody* myBumper;
	RigidBody* myRear;
	float colliderRadius;
	Vector3 myPos;

public:
	Car(PxPhysics* fsc, PxScene* scn, Vector3 pos, bool player1);
	virtual ~Car();

	void accelerate();
	void rotate() {};
	void checkCollision(GameObject* other);
	inline float getColliderRadius()
	{
		return colliderRadius;
	}
	inline Vector3 getPos()
	{
		return myPos;
	}
	RigidBody* Car::getBody()
	{
		return myBody;
	}
};


