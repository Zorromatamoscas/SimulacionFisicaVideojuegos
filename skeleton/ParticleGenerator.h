#pragma once
#include "Particle.h"
#include <vector>
class ParticleGenerator
{
private:
	std::vector<Particle*> myParticles;
	Vector3 singularity;
	Vector3 actSpaceSize;
public:
	ParticleGenerator(Vector3 origin, Vector3 actionSpaceSize);
	~ParticleGenerator()
	{
		if (!myParticles.empty()) for (Particle* p : myParticles) delete p;
	}
	void update(double t);
	bool isParticleOutOfBounds(Vector3 p);
};

