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
	Vector3 myColor;
	float damping;
	float myMass;
	float inv_myMass;
	Vector3 myGravity;
	float mySpeed;
	float lifeTime;
	float scaleValue;
	Vector3 myForce;

public:

	Particle(const PxVec3 pos, Vector3 velIni, float damp, float mass, float speed,float lifeT, float scalingValue, Vector3 color)
	{
		pose = PxTransform(pos);
		myForce = Vector3(0);
		scaleValue = scalingValue;
		//myGravity = gravity*(pow((scalingValue),2));
		lifeTime = lifeT;
		damping = damp;
		mySpeed = speed*scalingValue;
		myColor = color;
		vel = mySpeed*velIni.getNormalized();
		//masa simulada a una centesima de la velocidad
		myMass = mass* pow(1/scalingValue,2);
		inv_myMass = 1 / myMass;
		myShape = new RenderItem(CreateShape(physx::PxSphereGeometry(1)), &pose, Vector4(color.x, color.y, color.z, 1));

	}
	Particle(const PxVec3 pos, PxShape* form, Vector3 color)
	{
		pose = PxTransform(pos);
		myForce = Vector3(0);
		scaleValue = 0;
		//myGravity = gravity*(pow((scalingValue),2));
		lifeTime = 1000000;
		damping = 0;
		mySpeed = 0;
		myColor = color;
		vel = Vector3(0);
		//masa simulada a una centesima de la velocidad
		myMass = 0;
		inv_myMass = 1 / myMass;
		myShape = new RenderItem(form, &pose, Vector4(color.x, color.y, color.z, 1));
	};

	Particle(const PxVec3 pos, Vector3 velIni, float damp, float mass, float speed, float lifeT, float scalingValue, Vector3 color, PxShape* form)
	{
		pose = PxTransform(pos);
		myForce = Vector3(0);
		scaleValue = scalingValue;
		//myGravity = gravity*(pow((scalingValue),2));
		lifeTime = lifeT;
		damping = damp;
		mySpeed = speed * scalingValue;
		myColor = color;
		vel = mySpeed * velIni.getNormalized();
		//masa simulada a una centesima de la velocidad
		myMass = mass * pow(1 / scalingValue, 2);
		inv_myMass = 1 / myMass;
		myShape = new RenderItem(form, &pose, Vector4(color.x, color.y, color.z, 1));

	}

	virtual ~Particle()
	{
			myShape->release();
			myShape = nullptr;
	}
	inline double getInvMass() { return inv_myMass; }
	inline void setDuration(float dur) { lifeTime = dur; }

	Particle* Particle::clone(Vector3 newPos,Vector3 newVel, float newLifeTime) const {
		return new Particle(newPos, newVel, damping, myMass, mySpeed, newLifeTime, scaleValue, myColor);
	}
	Particle* Particle::clone( Vector3 newVel,  float newLifeTime) const {
		return new Particle(pose.p, newVel, damping, myMass, mySpeed, newLifeTime, scaleValue, myColor);
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
		Vector3 resulting_accel = myForce * inv_myMass;
		vel += resulting_accel * t;
		vel *= damping;
		pose.p += vel * t;
		lifeTime -= t;
		// Clear accum
		clearForce();
	}
	void addForce(const Vector3& force)
	{
		myForce += force;
	}
	void clearForce()
	{
		myForce *= 0;
	}

};

