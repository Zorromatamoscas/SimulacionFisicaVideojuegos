#include "RigidSystem.h"
RigidSystem::RigidSystem(PxPhysics* fisicas, PxScene* escena, int maxRigids) {

	myMaxRigids = maxRigids;
	myFisicas = fisicas;
	myScene = escena;
	myForceRegistry = new RigidsRegistry();
	RigidBody* model = new RigidBody(fisicas, escena, 5, 0.001, Vector3(0), Vector3(255, 255, 255), 5,true);
	//RigidGenerator* ptGen = new GaussianoRigido(Vector3(0,0,0), Vector3(35),0.3,model,true);
	//partGenerator.push_back(ptGen);
	/*explGen = new ExplosionRigid(Vector3(0, 10, 0), 1000, 500000, 5);
	windGen = new WindRigid(Vector3(1000, 0, 0), Vector3(0, 0, 0), 100, 1, 0,15);*/
	player1= new Car(fisicas, escena, Vector3(-80, 10, 0), true);
	player2= new Car(fisicas, escena, Vector3(80, 10, 0), false);
	Particle* aquaSuperficie = new Particle(Vector3(0, -10, 0), CreateShape(physx::PxBoxGeometry(Vector3(200, 2, 200))), Vector3(0.2, 0.2, 1));
	fltGen = new floatRigid(100, 1, aquaSuperficie);
	myForceRegistry->addRegistry(fltGen, player1->getBumper());
	myForceRegistry->addRegistry(fltGen, player1->getBody());
	myForceRegistry->addRegistry(fltGen, player2->getBumper());
	myForceRegistry->addRegistry(fltGen, player2->getBody());
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
				/*myForceRegistry->addRegistry(explGen, *prtcls.begin());
				myForceRegistry->addRegistry(windGen, *prtcls.begin());*/
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

		//myForceRegistry->deletePartReg(p);
		particles.erase(killList.at(i));
		delete p;
	}
	killList.clear();
}