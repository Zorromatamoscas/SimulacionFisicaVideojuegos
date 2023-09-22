#pragma once
#include <PxPhysicsAPI.h>

#include <vector>

#include "core.hpp"
#include "RenderUtils.hpp"
using namespace physx;
class Particle
{
private:
	RenderItem* myShape;
	PxTransform pose;
	Vector3 vel;
public:

	Particle(Vector3 pos, Vector3 velo)
	{
		pose = PxTransform(pos);
		vel = velo;
		myShape = new RenderItem(CreateShape(physx::PxSphereGeometry(5)), &pose, Vector4(125, 0, 0, 1));
	}
	~Particle()
	{
		delete myShape;
	}
	void integrate(double t)
	{
		pose.p += vel * t;
	}

};

