#pragma once
#include "Particle.h"
#include "GeneradorNormal.h"
class Firework: public Particle
{
private:
	int nParticles;
	int generation;
	int originalLifeTime;
public:
	Firework(int generations,int nParticlesMin,Vector3 gravity, const PxVec3 pos, Vector3 acce, Vector3 velIni, float damp, float mass, float speed, float lifeT, float scalingValue, Vector3 color) :
		Particle(gravity, pos, acce, velIni, damp, mass, speed, lifeT, scalingValue, color), nParticles(nParticles), generation(generations)
	{
		originalLifeTime = lifeTime;

	}
	Firework* Firework::clone(int gener,Vector3 newPos, Vector3 newVel, Vector3 newAce, float newLifeTime, Vector3 newColor) const
	{
		return new Firework(gener,nParticles,myGravity, newPos, newAce, newVel, damping, myMass, mySpeed, newLifeTime, scaleValue, newColor);
	}
	std::list<Particle*> explode()
	{
		if (generation != 0) {
			std::list<Particle*> confeti;
			GeneradorNormal generator = GeneradorNormal(pose.p, Vector3(20), 1, this->clone(this->generation-1,this->pose.p,this->vel,this->ace,this->originalLifeTime,Vector3(rand() % 125, rand() % 125, rand() % 125)),true);
			for (int i = 0; i < nParticles; i++)
			{
				confeti.splice(confeti.end(), generator.generateParticles());
			}
			return confeti;
		}
	}
};

