#include "GaussianoRigido.h"
GaussianoRigido::GaussianoRigido(Vector3 origen, Vector3 varianza, float prob, RigidBody* model, bool ancla)
	: RigidGenerator(origen, model->getVel(), varianza, prob), anclado(ancla) {
	setRigid(model);

	// Distribuciones de velocidad
	xVel = new std::normal_distribution<float>(model->getVel().x, variation.x);
	yVel = new std::normal_distribution<float>(model->getVel().y, variation.y);
	zVel = new std::normal_distribution<float>(model->getVel().z, variation.z);

	// Distribuciones de posición
	if (!anclado) {
		xPos = new std::normal_distribution<float>(origin.x, variation.x / 2.0f);
		yPos = new std::normal_distribution<float>(origin.y, variation.y / 2.0f);
		zPos = new std::normal_distribution<float>(origin.z, variation.z / 2.0f);
	}
}

GaussianoRigido::~GaussianoRigido() {
	delete xVel, yVel, zVel;
	if (!anclado) delete xPos, yPos, zPos;
}

std::list<RigidBody*> GaussianoRigido::generateRigids() {


	// Lista de partículas
	std::list<RigidBody*> particulas;
	float rnd = (rand() % 101) / 100.0f;
	if (rnd < frec) {
		Vector3 vel = Vector3((*xVel)(gen), (*yVel)(gen), (*zVel)(gen));
		Vector3 accl = Vector3(0);
		int lifeTime = rand() % 10 + 3;

		// Si el sistema no esta anclado, le cambias la pos
		if (!anclado) {
			Vector3 pos = Vector3((*xPos)(gen), (*yPos)(gen), (*zPos)(gen));
			particulas.push_back(model->clone(model->getPhysics(),model->getScene(),pos,
				Vector3((rand() % 101) / 100.0, (rand() % 101) / 100.0, (rand() % 101) / 100.0),vel));
		}
		else particulas.push_back(model->clone(model->getPhysics(),model->getScene(),
			Vector3((rand() % 101)/100.0, (rand() % 101) / 100.0, (rand() % 101) / 100.0),vel));
	}

	return particulas;
}
