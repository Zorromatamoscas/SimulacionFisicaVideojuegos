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
	Firework(int generations,int nParticlesMin, const PxVec3 pos, Vector3 velIni, float damp, float mass, float speed, float lifeT, float scalingValue, Vector3 color) :
		Particle( pos, velIni, damp, mass, speed, lifeT, scalingValue, color), nParticles(nParticles), generation(generations)
	{
		originalLifeTime = lifeTime;
		 nParticles= nParticlesMin;
		 generation= generations;

	}
	Firework* Firework::clone(int gener,Vector3 newPos, Vector3 newVel, float newLifeTime, Vector3 newColor) const
	{
		return new Firework(gener,nParticles, newPos, newVel, damping, myMass, mySpeed, newLifeTime, scaleValue, newColor);
	}
	std::list<Particle*> explode(std::list<Particle*>& myList)
	{
		std::list<Particle*> confeti;
		GeneradorNormal generator = GeneradorNormal(pose.p, Vector3(20), 1, this->clone(this->generation - 1, this->pose.p, this->vel,this->originalLifeTime, Vector3(rand() % 125, rand() % 125, rand() % 125)), true);
		if (generation > 1) {
			
			
			for (int i = 0; i < nParticles; i++)
			{
				myList.push_back(this->clone(this->generation - 1, this->pose.p, generator.getNewVel(), this->originalLifeTime, Vector3(120,80,100)));
			}
			
		}
		else if (generation == 1)
		{
			for (int i = 0; i < nParticles; i++)
			{
				confeti.splice(confeti.end(), generator.generateParticles());
			}
		}
		return confeti;
	}
	inline int getGenerations()
	{
		return generation;
	}
};

