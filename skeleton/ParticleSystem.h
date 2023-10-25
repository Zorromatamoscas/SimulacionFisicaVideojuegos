#pragma once
#include "GeneradorGaussiano.h"
#include "GeneradorNormal.h"
#include "Firework.h"
class ParticleSystem
{
private:
	std::list<Particle*> particles;
	std::list<ParticleGenerator*> partGenerator;
	std::vector<std::list<Particle*>::iterator> killList;

public:
	ParticleSystem();
	~ParticleSystem();
	void update(double t);
	ParticleGenerator* getParticleGenerator(std::string name);
	void generateFireworkSystem();
};

