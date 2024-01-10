#include "Car.h"
Car::Car(PxPhysics* fsc, PxScene* scn, Vector3 pos, bool player1) : GameObject(fsc, scn)
{
	myCar = fisicas->createAggregate(3, false);
	myBody = new RigidBody(fisicas, escena, 5, 0.05, pos, player1 ? Vector3(1, 0, 0) : Vector3(0, 0, 1), 100,false,true,true);
	myCar->addActor(*myBody->getRigid());
	myBumper = new RigidBody(fisicas, escena, 3, 0.02, Vector3(pos.x + 8 , pos.y, pos.z), Vector3(0.2, 0.2, 0.2), 100, false, true,true);
	myBumper->bumperIt();
	myCar->addActor(*myBumper->getRigid());
	myRear = new RigidBody(fisicas, escena, 3, 0.02, Vector3(pos.x -8, pos.y, pos.z), player1 ? Vector3(1, 0, 0) : Vector3(0, 0, 1), 100, false, true, true);
	myCar->addActor(*myRear->getRigid());
	PxFixedJointCreate(*fisicas, myBody->getRigid(), PxTransform(Vector3(0, 0, 0)), myBumper->getRigid(), PxTransform(Vector3(-8, 0, 0)));
	PxFixedJointCreate(*fisicas, myBody->getRigid(), PxTransform(Vector3(0, 0, 0)), myRear->getRigid(), PxTransform(Vector3(8, 0, 0)));
	escena->addAggregate(*myCar);
	colliderRadius = 7;
	myPos = pos;
	PxTransform oldTr = myBody->getRigid()->getGlobalPose();
	if (!player1) myBody->getRigid()->setGlobalPose(PxTransform(oldTr.p, PxQuat(0,sin(PI/2),0,cos(PI/2))));
}

Car::~Car()
{
	escena->removeAggregate(*myCar);
	delete myBody;
	delete myBumper;
	delete myRear;
}
void Car::accelerate()
{
	if (myBody->getVel().x <= 100) myBody->addForce(Vector3(30000, 0, 0));
}
void Car::deccelerate()
{
	if (myBody->getVel().x <= -100) myBody->addForce(Vector3(-30000, 0, 0));
}
