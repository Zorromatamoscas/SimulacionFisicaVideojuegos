#pragma once
#include "GeneradorGaussiano.h"
#include "GeneradorNormal.h"
#include "Firework.h"
#include "ParticleForceRegistry.h"
#include "GravityGenerator.h"
#include "WindGenerator.h"
#include "TornadoGenerator.h"
#include "ExplosionGenerator.h"
#include "springLockGenerator.h"
#include "FloatingGenerator.h"
class ParticleSystem
{
private:
	std::list<Particle*> particles;
	std::list<ParticleGenerator*> partGenerator;
	std::vector<std::list<Particle*>::iterator> killList;
	ParticleForceRegistry* myForceRegistry;
	GravityGenerator* gravGen = nullptr;
	WindGenerator* windGen = nullptr;
	ExplosionGenerator* explGen = nullptr;
	springLockGenerator* sprgGen = nullptr;
	springLockGenerator* sprgGen1 = nullptr;
	FloatingGenerator* fltGen = nullptr;
	Particle* anchor;

public:
	ParticleSystem();
	~ParticleSystem();
	void update(double t);
	ParticleGenerator* getParticleGenerator(std::string name);
	void explosion();
	void generateFireworkSystem();
};

