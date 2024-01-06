#pragma once
#pragma once
#include <PxPhysicsAPI.h>

#include <vector>

#include "core.hpp"
#include "RenderUtils.hpp"
#include <iostream>
using namespace physx;
class RigidBody
{
protected:
	//Parametros simulados
	PxRigidDynamic* myRigid;
	RenderItem* myRender;
	Vector3 myColor;
	float lifeTime;
	float mySize;
	float myDensity;
	bool inmortal;
	PxPhysics* myFisicas;
	PxScene* myScene;
	Vector3 myPos;

public:
	RigidBody(PxPhysics* fisicas, PxScene* scene, float boxDimens,float density, Vector3 pos, Vector3 color, int lft, bool model=false, bool inmrtl=false)
	{
		myColor = color;
		mySize = boxDimens;
		myDensity = density;
		myScene = scene;
		myFisicas = fisicas;
		myPos = pos;
		myRigid = fisicas->createRigidDynamic(PxTransform(pos));
		lifeTime = lft;
		inmortal = inmrtl;
		PxShape* shape = CreateShape(PxBoxGeometry(mySize, mySize, mySize));
		myRigid->attachShape(*shape);
		if(!model)scene->addActor(*myRigid);
		myRender = new RenderItem(shape, myRigid, Vector4(myColor,1));
		PxRigidBodyExt::updateMassAndInertia(*myRigid, myDensity);
	}

	virtual ~RigidBody()
	{
		if(myRender!=nullptr)myRender->release();
	}
	inline void setDuration(float dur) { lifeTime = dur; }

	RigidBody* clone(PxPhysics* fisicas, PxScene* scene, Vector3 color, Vector3 force) const {
		RigidBody* myBody= new RigidBody(fisicas, scene, mySize, myDensity, myPos, color, rand() % 10 + 3);
		myBody->setInitialVel(force);
		return myBody;
	}
	RigidBody* clone(PxPhysics* fisicas, PxScene* scene, Vector3 pos,Vector3 color, Vector3 force) const {
		RigidBody* myBody = new RigidBody(fisicas, scene, mySize, myDensity, pos, color, rand() % 10 + 3);
		myBody->setInitialVel(force);
		return myBody;
	}

	bool isAlive(float t)
	{
		if(!inmortal)lifeTime -= t;
		return lifeTime > 0;
	}

	PxRigidDynamic* getRigid()
	{
		return myRigid;
	}
	inline void addForce(Vector3 force)
	{
		myRigid->addForce(force);
	}
	inline void setInitialVel(Vector3 vel)
	{
		myRigid->setLinearVelocity(vel);
	}
	inline Vector3 getPosition()
	{
		return myRigid->getGlobalPose().p;
	}
	inline Vector3 getVel()
	{
		return myRigid->getLinearVelocity();
	}

	inline PxPhysics* getPhysics()
	{
		return myFisicas;
	}
	inline PxScene* getScene()
	{
		return myScene;
	}

};

