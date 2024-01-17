#include "Car.h"
Car::Car(PxPhysics* fsc, PxScene* scn, Vector3 pos, bool player1) : GameObject(fsc, scn)
{
	myCar = fisicas->createAggregate(3, false);
	myBody = new RigidBody(fisicas, escena, 5, 0.05, pos, player1 ? Vector3(1, 0, 0) : Vector3(0, 0, 1), 100,false,true,true);
	myCar->addActor(*myBody->getRigid());
	myBumper = new RigidBody(fisicas, escena, 3, 0.01, Vector3(pos.x + player1 ? 8 : -8, pos.y, pos.z), Vector3(0.2, 0.2, 0.2), 100, false, true,true);
	myBumper->bumperIt();
	myCar->addActor(*myBumper->getRigid());
	myRear = new RigidBody(fisicas, escena, 3, 0.02, Vector3(pos.x + player1 ? -8 : 8, pos.y, pos.z), player1 ? Vector3(1, 0, 0) : Vector3(0, 0, 1), 100, false, true, true);
	myCar->addActor(*myRear->getRigid());
	PxFixedJointCreate(*fisicas, myBody->getRigid(), PxTransform(Vector3(0, 0, 0)), myBumper->getRigid(), PxTransform(Vector3(player1 ? -8 : 8, 0, 0)));
	PxFixedJointCreate(*fisicas, myBody->getRigid(), PxTransform(Vector3(0, 0, 0)), myRear->getRigid(), PxTransform(Vector3(player1 ? 8 : -8, 0, 0)));
	escena->addAggregate(*myCar);
	colliderRadius = 7;
	myPos = pos;
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
	Vector3 forceDirection = Vector3(1,0,0);
	if (myBody->getVel().magnitude() <= 100) {
		forceDirection=myBody->getRigid()->getGlobalPose().q.rotate(forceDirection);
		myBody->addForce((player1? 1 : -1) * 10000*forceDirection);
	}
}
void Car::deccelerate()
{
	Vector3 forceDirection = Vector3(1, 0, 0);
	if (myBody->getVel().magnitude() >= -100) {
		forceDirection = myBody->getRigid()->getGlobalPose().q.rotate(forceDirection);
		myBody->addForce((player1 ? -1 : 1)*10000 * forceDirection);
	}
}
void Car::rotate(bool drcha) 
{
	float rotationAngle = 5;
	float quat_angle = rotationAngle * (PI / 180);
	if (drcha)
	{
		PxTransform oldTr = myBody->getRigid()->getGlobalPose();
		myBody->getRigid()->setGlobalPose
		(PxTransform(oldTr.p, PxQuat(0, sin(quat_angle /2), 0, cos(quat_angle/2))*oldTr.q));
	}
	else
	{
		PxTransform oldTr = myBody->getRigid()->getGlobalPose();
		myBody->getRigid()->setGlobalPose(PxTransform(oldTr.p, PxQuat(0, sin(-quat_angle /2), 0, cos(-quat_angle /2))*oldTr.q));
	}

}
