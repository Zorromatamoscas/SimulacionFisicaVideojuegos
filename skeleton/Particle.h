#pragma once
#include <PxPhysicsAPI.h>

#include <vector>

#include "core.hpp"
#include "RenderUtils.hpp"
#include <iostream>
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
	float lifeTime;

public:

	Particle(Vector3 gravity, const PxVec3 pos, Vector3 acce, Vector3 velIni, float damp, float mass, float speed,float lifeT, float scalingValue)
	{
		pose = PxTransform(pos);
		myGravity = gravity*(pow((scalingValue),2));
		lifeTime = lifeT;
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
		if (myShape != nullptr)
		{
			DeregisterRenderItem(myShape);
			myShape->release();
			myShape = nullptr;

		}
	}
	inline void setDuration(float dur) { lifeTime = dur; }

	bool isAlive()
	{
		return lifeTime > 0;
	}
	inline Vector3 getPosition()
	{
		return pose.p;
	}
	void integrate(double t)
	{
		lifeTime -= t;
		vel += ace * t;
		vel.x *= powf(damping, t);
		vel.z *= powf(damping, t);
		vel += myGravity * t;
		pose.p += vel * t;
		std::cout << vel.y << std::endl;
	}

};

