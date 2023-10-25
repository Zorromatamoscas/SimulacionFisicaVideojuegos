#pragma once
#include <PxPhysicsAPI.h>

#include <vector>

#include "core.hpp"
#include "RenderUtils.hpp"
#include <iostream>
using namespace physx;
class Particle
{
protected:
	//Parametros simulados
	RenderItem* myShape;
	PxTransform pose;
	Vector3 vel;
	Vector3 ace;
	Vector3 myColor;
	float damping;
	float myMass;
	Vector3 myGravity;
	float mySpeed;
	float lifeTime;
	float scaleValue;

public:

	Particle(Vector3 gravity, const PxVec3 pos, Vector3 acce, Vector3 velIni, float damp, float mass, float speed,float lifeT, float scalingValue, Vector3 color)
	{
		pose = PxTransform(pos);
		scaleValue = scalingValue;
		myGravity = gravity*(pow((scalingValue),2));
		lifeTime = lifeT;
		ace = acce;
		damping = damp;
		mySpeed = speed*scalingValue;
		myColor = color;
		vel = mySpeed*velIni.getNormalized();
		//masa simulada a una centesima de la velocidad
		myMass = mass* pow(1/scalingValue,2);
		myShape = new RenderItem(CreateShape(physx::PxSphereGeometry(1)), &pose, Vector4(color.x, color.y, color.z, 1));

	}
	virtual ~Particle()
	{
		if (myShape != nullptr)
		{
			myShape->release();

		}
	}
	inline void setDuration(float dur) { lifeTime = dur; }

	Particle* Particle::clone(Vector3 newPos,Vector3 newVel, Vector3 newAce, float newLifeTime) const {
		return new Particle(myGravity, newPos, newAce, newVel, damping, myMass, mySpeed, newLifeTime, scaleValue, myColor  );
	}
	Particle* Particle::clone( Vector3 newVel, Vector3 newAce, float newLifeTime) const {
		return new Particle(myGravity, pose.p, newAce, newVel, damping, myMass, mySpeed, newLifeTime, scaleValue, myColor);
	}

	bool isAlive()
	{
		return lifeTime > 0;
	}
	inline Vector3 getPosition()
	{
		return pose.p;
	}
	inline void setPosition(Vector3 newPos)
	{
		pose.p= newPos;
	}
	inline Vector3 getVel()
	{
		return vel;
	}
	void integrate(double t)
	{
		lifeTime -= t;
		vel += ace * t;
		vel.x *= powf(damping, t);
		vel.z *= powf(damping, t);
		vel += myGravity * t;
		pose.p += vel * t;
	}

};

