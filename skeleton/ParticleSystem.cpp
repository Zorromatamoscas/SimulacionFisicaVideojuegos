#include "ParticleSystem.h"
ParticleSystem::ParticleSystem() {

	//Generador Gaussiano
	//particles.push_back(new Particle(Vector3(0), Vector3(0), 0.9999, 5, 1, 100, 1, Vector3(0, 0, 125)));
	Particle* model = new Particle(Vector3(0), Vector3(0), 0.99, 5, 100, 0, 1, Vector3(0, 0, 125));
	ParticleGenerator* ptGen = new GeneradorGaussiano(Vector3(50), Vector3(35), 0.3, model,true);
	partGenerator.push_back(ptGen);
	////Generador Uniforme
	//model = new Particle(Vector3(0, -10, 0), Vector3(0), Vector3(0), Vector3(0), 0.99, 5, 10, 0, 1, Vector3(0, 125, 0));
	//ptGen = new GeneradorNormal(Vector3(50), Vector3(35), 0.3, model, false);
	//partGenerator.push_back(ptGen);
	//particles.push_back(new Firework(3, 10, Vector3(0,0,0), Vector3(0), Vector3(0), Vector3(0,10,0), 0.99, 5, 10, 3, 1, Vector3(0, 0, 125)));
	//particles.push_back(new Particle(Vector3(0, -10, 0), Vector3(0),  Vector3(0, 1, 0), 0.99, 5, 100, 10, 1, Vector3(0, 0, 0)));
	myForceRegistry = new ParticleForceRegistry();
	gravGen = new GravityGenerator(Vector3(0, -10, 0));
	//windGen = new WindGenerator(Vector3(100, 0, 0), Vector3(0, 0, 0), 100, 1, 0);
	//windGen = new TornadoGenerator(Vector3(0, 0, 0), Vector3(0, 0, 0), 100, 1, 0, 5);
	explGen = new ExplosionGenerator(Vector3(0), 1000, 500000, 5);
	explGen->setDuration(50);
	/*myForceRegistry->addRegistry(gravGen, *particles.begin());
	myForceRegistry->addRegistry(windGen, *particles.begin());*/
}

ParticleSystem::~ParticleSystem() {
	// Eliminas todos los generadores
	for (ParticleGenerator* p :partGenerator) delete p;
	partGenerator.clear();

	// Eliminas todas las particulas
	for (Particle* p : particles) delete p;
	particles.clear();
}
void ParticleSystem::explosion()
{
	if (explGen != nullptr) explGen->setActive(true);
}

void ParticleSystem::update(double t) {
	// Generas nuevas particulas si es necesario
	for (ParticleGenerator* p : partGenerator) {
		std::list<Particle*> prtcls = p->generateParticles();
		
		if (!prtcls.empty()) {
			myForceRegistry->addRegistry(gravGen, *prtcls.begin());
			myForceRegistry->addRegistry(explGen, *prtcls.begin());
			//myForceRegistry->addRegistry(windGen, *prtcls.begin());
			particles.splice(particles.end(), prtcls);
		}
	}

	myForceRegistry->updateForces(t);

	for (auto it = particles.begin(); it != particles.end(); it++) {
		(*it)->integrate(t);
		if (!(*it)->isAlive()) killList.push_back(it);
	}

	// Borras las particulas muertas
	int initialSize = killList.size();
	for (int i = 0; i <initialSize; i++) {
		Particle* p = *killList.at(i);
		
		if (typeid(static_cast<Firework*>(*killList[i])) == typeid(Firework*))
		{
			Firework* fire = static_cast<Firework*>(*killList[i]);
			particles.splice(particles.end(),fire->explode(particles));
		}
		particles.erase(killList.at(i));
		delete p;
	}
	killList.clear();
}