#include "ParticleSystem.h"
ParticleSystem::ParticleSystem(RigidSystem* system, float coolDown) {

	//Generador Uniforme
	Particle* modelBomb = new Bomb(Vector3(0, 5, 0), system,true);
	Particle* modelWindPower = new WindPowerUp(Vector3(0, 5, 0), system, true);
	ParticleGenerator* ptGen = new GeneradorGaussiano(Vector3(0,0,0), Vector3(100), 1, modelBomb, false);
	partGenerator.push_back(ptGen);
	ptGen = new GeneradorNormal(Vector3(0), Vector3(100), 0.5, modelWindPower, false);
	partGenerator.push_back(ptGen);
	//particles.push_back(new Particle(Vector3(0, -10, 0), Vector3(0),  Vector3(0, 1, 0), 0.99, 5, 100, 10, 1, Vector3(0, 0, 0)));*/
	myCooldown = coolDown;
	elapsedCoolDown = 0;
}


ParticleSystem::~ParticleSystem() {
	// Eliminas todos los generadores
	for (ParticleGenerator* p :partGenerator) delete p;
	partGenerator.clear();

	// Eliminas todas las particulas
	for (Particle* p : particles) delete p;
	particles.clear();
}
void ParticleSystem::celebrate()
{
	GeneradorNormal* ptGen = new GeneradorNormal(Vector3(0), Vector3(100), 1, 
		new Firework(3, 10, Vector3(0, 0, 0), Vector3(0, 10, 0), 0.99, 5, 40, 3, 1, Vector3(0, 1, 0),true), false);
	for (int i = 0; i < 5; i++) {
		ptGen->generateParticles();

		particlesFire.push_back(new Firework(3, 10, Vector3(0, 0, 0), ptGen->getNewVel(), 0.99, 5, 40, 3, 1, Vector3(0, 1, 0)));
	}
	delete ptGen;
}
void ParticleSystem::explosion()
{
	if (explGen != nullptr) explGen->setActive(true);
}

void ParticleSystem::update(double t) {
	// Generas nuevas particulas si es necesario
	elapsedCoolDown += t;
	if (elapsedCoolDown >= myCooldown) {
		for (ParticleGenerator* p : partGenerator) {
			std::list<Particle*> prtcls = p->generateParticles();

			if (!prtcls.empty()) {
				particles.splice(particles.end(), prtcls);
			}
		}
		elapsedCoolDown = 0;
	}

	//myForceRegistry->updateForces(t);

	for (auto it = particles.begin(); it != particles.end(); it++) {
		(*it)->integrate(t);
		try
		{
			static_cast<PowerUps*>(*it)->checkCollisions();
		}
		catch(...){}
		if (!(*it)->isAlive()) killList.push_back(it);
	}
	for (auto it = particlesFire.begin(); it != particlesFire.end(); it++) {
		(*it)->integrate(t);
		if (!(*it)->isAlive()) killListFire.push_back(it);
	}

	// Borras las particulas muertas
	int initialSize = killList.size();
	for (int i = 0; i <initialSize; i++) {
		Particle* p = *killList.at(i);

		//myForceRegistry->deletePartReg(p);
		particles.erase(killList.at(i));
		delete p;
	}
	killList.clear();
	initialSize = killListFire.size();
	for (int i = 0; i < initialSize; i++) {
		Particle* p = *killListFire.at(i);
		if (typeid(static_cast<Firework*>(*killListFire[i])) == typeid(Firework*))
		{
			Firework* fire = static_cast<Firework*>(*killListFire[i]);
			particlesFire.splice(particlesFire.end(), fire->explode(particlesFire));
		}
		//myForceRegistry->deletePartReg(p);
		particlesFire.erase(killListFire.at(i));
		delete p;
	}
	
	killListFire.clear();
}