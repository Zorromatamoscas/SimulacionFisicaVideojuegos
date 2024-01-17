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
#include "Bomb.h"
#include "WindPowerUp.h"
class ParticleSystem
{
private:
	std::list<Particle*> particles;
	std::list<Particle*> particlesFire;
	std::list<ParticleGenerator*> partGenerator;
	std::vector<std::list<Particle*>::iterator> killList;
	std::vector<std::list<Particle*>::iterator> killListFire;
	ParticleForceRegistry* myForceRegistry;
	GravityGenerator* gravGen = nullptr;
	WindGenerator* windGen = nullptr;
	ExplosionGenerator* explGen = nullptr;
	springLockGenerator* sprgGen = nullptr;
	springLockGenerator* sprgGen1 = nullptr;
	FloatingGenerator* fltGen = nullptr;
	Particle* anchor = nullptr;
	Particle* dummyParticle = nullptr;
	float myCooldown;
	float elapsedCoolDown;

public:
	ParticleSystem(RigidSystem* system,float coolDown=0);
	~ParticleSystem();
	void update(double t);
	ParticleGenerator* getParticleGenerator(std::string name);
	void explosion();
	void celebrate();
	void generateFireworkSystem();
	inline void Engorda()
	{
		if (dummyParticle != nullptr) dummyParticle->Engorda();
	}
	inline void Adelgaza()
	{
		if (dummyParticle != nullptr) dummyParticle->Adelgaza();
	}
};

