#pragma once
#include "ParticleGenerator.h"
class GeneradorNormal: public ParticleGenerator
{
private:
	std::uniform_real_distribution<float>* xVel;
	std::uniform_real_distribution<float>* yVel;
	std::uniform_real_distribution<float>* zVel;
	std::uniform_real_distribution<float>* xPos;
	std::uniform_real_distribution<float>* yPos;
	std::uniform_real_distribution<float>* zPos;
	bool anclado;

public:
	GeneradorNormal(Vector3 origen, Vector3 var, float prob, Particle* model, bool ancla);
	virtual ~GeneradorNormal();

	// Método abstracto
	virtual std::list<Particle*> generateParticles();
	Vector3 getNewVel();
};

