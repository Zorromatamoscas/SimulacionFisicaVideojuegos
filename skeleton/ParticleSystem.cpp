#include "ParticleSystem.h"
ParticleSystem::ParticleSystem() {

	//Generador Gaussiano
	Particle* model = new Particle(Vector3(0,-10,0),Vector3(0), Vector3(0), Vector3(0), 0.99, 5, 10, 0, 1, Vector3(0,0,125));
	ParticleGenerator* ptGen = new GeneradorGaussiano(Vector3(0), Vector3(35), 0.3, model,false);
	partGenerator.push_back(ptGen);
	//Generador Uniforme
	model = new Particle(Vector3(0, -10, 0), Vector3(0), Vector3(0), Vector3(0), 0.99, 5, 10, 0, 1, Vector3(0, 125, 0));
	ptGen = new GeneradorNormal(Vector3(100, 0, 0), Vector3(35), 0.3, model, false);
	partGenerator.push_back(ptGen);
}

ParticleSystem::~ParticleSystem() {
	// Eliminas todos los generadores
	for (ParticleGenerator* p :partGenerator) delete p;
	partGenerator.clear();

	// Eliminas todas las particulas
	for (Particle* p : particles) delete p;
	particles.clear();
}

void ParticleSystem::update(double t) {
	// Generas nuevas particulas si es necesario
	for (ParticleGenerator* p : partGenerator) {
		std::list<Particle*> prtcls = p->generateParticles();
		if (!prtcls.empty()) particles.splice(particles.end(), prtcls);
	}

	// Actualizas las particulas y las marcas para borrar si se ha acabado su tiempo
	for (auto it = particles.begin(); it != particles.end(); it++) {
		(*it)->integrate(t);
		if (!(*it)->isAlive()) killList.push_back(it);
	}

	// Borras las particulas muertas
	for (int i = 0; i < killList.size(); i++) {
		Particle* p = *killList[i];
		particles.erase(killList[i]);
		delete p;
	}
	killList.clear();
}