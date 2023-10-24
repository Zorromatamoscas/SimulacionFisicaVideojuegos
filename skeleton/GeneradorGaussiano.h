#pragma once
#include "ParticleGenerator.h"
class GeneradorGaussiano: public ParticleGenerator
{
private:
	std::normal_distribution<float>* xVel;
	std::normal_distribution<float>* yVel;
	std::normal_distribution<float>* zVel;
	std::normal_distribution<float>* xPos;
	std::normal_distribution<float>* yPos;
	std::normal_distribution<float>* zPos;
	bool anclado;
public:
	GeneradorGaussiano(Vector3 origen, Vector3 varianza, float prob, Particle* model, bool ancla);
	virtual GeneradorGaussiano::~GeneradorGaussiano();

	virtual std::list<Particle*> generateParticles();
};

