#pragma once
#include <PxPhysicsAPI.h>

#include <vector>

#include "core.hpp"
#include "RenderUtils.hpp"
using namespace physx;
class Particle
{
private:
	//Parametros simulados
	RenderItem* myShape;
	PxTransform pose;
	Vector3 vel;
	Vector3 ace;
	float damping;
	float myMass;
	Vector3 myGravity;
	float mySpeed;

public:

	Particle(PxSceneDesc myScene, const PxVec3 pos, Vector3 acce,Vector3 velIni, float damp, float mass, float speed, float scalingValue)
	{
		pose = PxTransform(pos);
		myGravity = myScene.gravity*(pow((scalingValue),2));
		ace = acce;
		damping = damp;
		mySpeed = speed*scalingValue;
		vel = mySpeed*velIni.getNormalized();
		//masa simulada a una centesima de la velocidad
		myMass = mass* pow(1/scalingValue,2);
		myShape = new RenderItem(CreateShape(physx::PxSphereGeometry(1)), &pose, Vector4(125, 0, 0, 1));

	}
	~Particle()
	{
		myShape->release();
		delete myShape;
	}
	void integrate(double t)
	{
		vel += ace * t;
		vel += myGravity* t;
		vel *= powf(damping, t);
		pose.p += vel * t;
	}

};

