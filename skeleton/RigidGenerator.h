#pragma once
#include <list>
#include <random>
#include <chrono>
#include "RigidBody.h"
class RigidGenerator
{
protected:
	int n_particles;
	RigidBody* model = nullptr;
	Vector3 origin, velocity, variation;
	float frec;
	std::default_random_engine gen;

	// Generador de aleatorios

public:
	RigidGenerator(Vector3 pos = Vector3(0.0f, 0.0f, 0.0f),
		Vector3 velocity = Vector3(0.0f, 0.0f, 0.0f), Vector3 var = Vector3(0.0f, 0.0f, 0.0f), double frequency = 0.1f);


	virtual std::list<RigidBody*> generateRigids() = 0;

	~RigidGenerator() { delete model; }

	inline void setRigid(RigidBody* p) {
		model = p;
	}
	inline void setNParticles(int n_p) { n_particles = n_p; }




};

