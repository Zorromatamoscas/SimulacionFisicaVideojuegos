#include "GeneradorNormal.h"
GeneradorNormal::GeneradorNormal(Vector3 origen, Vector3 var, float frec, Particle* model, bool ancla)
	: ParticleGenerator(origen, model->getVel(), var, frec), anclado(ancla) {

	// Partícula modelo
	model->setPosition(origen);
	setParticle(model);

	xVel = new std::uniform_real_distribution<float>(model->getVel().x - var.x, model->getVel().x + var.x);
	yVel = new std::uniform_real_distribution<float>(model->getVel().y - var.y, model->getVel().y + var.y);
	zVel = new std::uniform_real_distribution<float>(model->getVel().z - var.z, model->getVel().z + var.z);

	if (!anclado) {
		xPos = new std::uniform_real_distribution<float>(origen.x - var.x * 2, origen.x + var.x / 2.0f);
		yPos = new std::uniform_real_distribution<float>(origen.y - var.y * 2, origen.y + var.y / 2.0f);
		zPos = new std::uniform_real_distribution<float>(origen.z - var.z * 2, origen.z + var.z / 2.0f);
	}
}

// Destructora
GeneradorNormal::~GeneradorNormal() {
	delete xVel,yVel,zVel;
	if (!anclado) delete xPos,yPos,zPos;
}

// Genera partículas que se devuelven en la lista
std::list<Particle*> GeneradorNormal::generateParticles() {
	// Lista de partículas
	std::list<Particle*> particulas;

	// Generar según un aleatorio
	float random = (rand() % 101) / 100.0f;
	if (random < frec) {
		// Variables aleatorias
		Vector3 vel = Vector3((*xVel)(gen), (*yVel)(gen), (*zVel)(gen));
		Vector3 accl = Vector3(0);
		int lifeTime = 15;

		// Crear partícula
		if (!anclado) {
			Vector3 pos = Vector3((*xPos)(gen), (*yPos)(gen), (*zPos)(gen));
			particulas.push_back(model->clone(pos, vel, lifeTime));
		}
		else particulas.push_back(model->clone(vel, accl, lifeTime));
	}

	return particulas;
}
Vector3 GeneradorNormal::getNewVel()
{
	return Vector3((*xVel)(gen), (*yVel)(gen), (*zVel)(gen));
}