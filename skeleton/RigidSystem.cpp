#include "RigidSystem.h"
RigidSystem::RigidSystem(PxPhysics* fisicas, PxScene* escena, int maxRigids) {

	myMaxRigids = maxRigids;
	myFisicas = fisicas;
	myScene = escena;
	myForceRegistry = new RigidsRegistry();
	RigidBody* model = new RigidBody(fisicas, escena, 5, 0.001, Vector3(0), Vector3(255, 255, 255), 5,true);
	model2 = new RigidBody(fisicas, escena, 5, 0.001, Vector3(50,50,0), Vector3(250, 0, 0), 5);
	//RigidGenerator* ptGen = new GaussianoRigido(Vector3(0,0,0), Vector3(35),0.3,model,true);
	//partGenerator.push_back(ptGen);
	explGen = new ExplosionRigid(Vector3(0, 10, 0), 1000, 500000, 5);
	windGen = new WindRigid(Vector3(1000, 0, 0), Vector3(0, 0, 0), 100, 1, 0);
	Car* myCar = new Car(fisicas, escena, Vector3(0, 10, 0), true);
}

RigidSystem::~RigidSystem() {
	// Eliminas todos los generadores
	for (RigidGenerator* p : partGenerator) delete p;
	partGenerator.clear();

	// Eliminas todas las particulas
	for (RigidBody* p : particles) delete p;
	particles.clear();
}
void RigidSystem::explosion()
{
	if (explGen != nullptr) explGen->setActive(true);
}

void RigidSystem::update(double t) {
	// Generas nuevas particulas si es necesario
	if (particles.size() < myMaxRigids) {
		for (RigidGenerator* p : partGenerator) {
			std::list<RigidBody*> prtcls = p->generateRigids();

			if (!prtcls.empty()) {
				//myForceRegistry->addRegistry(gravGen, *prtcls.begin());
				myForceRegistry->addRegistry(explGen, *prtcls.begin());
				myForceRegistry->addRegistry(windGen, *prtcls.begin());
				particles.splice(particles.end(), prtcls);
			}
		}
	}
	myForceRegistry->updateForces(t);

	for (auto it = particles.begin(); it != particles.end(); it++) {
		if (!(*it)->isAlive(t)) killList.push_back(it);
	}

	// Borras las particulas muertas
	int initialSize = killList.size();
	for (int i = 0; i < initialSize; i++) {
		RigidBody* p = *killList.at(i);

		myForceRegistry->deletePartReg(p);
		particles.erase(killList.at(i));
		delete p;
	}
	killList.clear();
}