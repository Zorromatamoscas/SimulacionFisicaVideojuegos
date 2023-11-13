#pragma once
#include "GeneradorGaussiano.h"
#include "GeneradorNormal.h"
#include "Firework.h"
#include "ParticleForceRegistry.h"
#include "GravityGenerator.h"
class ParticleSystem
{
private:
	std::list<Particle*> particles;
	std::list<ParticleGenerator*> partGenerator;
	std::vector<std::list<Particle*>::iterator> killList;
	ParticleForceRegistry* myForceRegistry;

public:
	ParticleSystem();
	~ParticleSystem();
	void update(double t);
	ParticleGenerator* getParticleGenerator(std::string name);
	void generateFireworkSystem();
};

