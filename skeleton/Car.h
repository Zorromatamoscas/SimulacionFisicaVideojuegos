#pragma once
#include "gameObject.h"
#include <cmath>
#define PI 3.14159265358979323846
class Car: public GameObject
{
private:
	PxAggregate* myCar;
	RigidBody* myBody;
	RigidBody* myBumper;
	RigidBody* myRear;
	float colliderRadius;
	Vector3 myPos;
	bool player1;

public:
	Car(PxPhysics* fsc, PxScene* scn, Vector3 pos, bool player1);
	virtual ~Car();

	void accelerate();
	void deccelerate();
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
	inline bool isPlayer1()
	{
		return player1;
	}
};


