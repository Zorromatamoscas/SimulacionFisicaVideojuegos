#include "ParticleSystem.h"
ParticleSystem::ParticleSystem() {

	myForceRegistry = new ParticleForceRegistry();
	gravGen = new GravityGenerator(Vector3(0, -10, 0));

	//Muelle con ancla
	/*anchor = new Particle(Vector3(0,50,0), CreateShape(physx::PxBoxGeometry(Vector3(5))), Vector3(1, 0, 0));
	dummyParticle = new Particle(Vector3(0, 0, 0), Vector3(0), 0.99, 5, 100, 500, 1, Vector3(0, 0, 125));
	particles.push_back(dummyParticle);
	sprgGen = new springLockGenerator(5, 50, anchor->getPosition());
	myForceRegistry->addRegistry(sprgGen, particles.back());
	myForceRegistry->addRegistry(gravGen, particles.back());*/

	//Muelle entre dos particulas
	/*dummyParticle = new Particle(Vector3(0, 100, 0), Vector3(0), 0.99, 5, 100, 500, 1, Vector3(0, 0, 125));
	particles.push_back(dummyParticle);
	 particles.push_back(new Particle(Vector3(0, 0, 0), Vector3(0), 0.99, 50, 100, 500, 1, Vector3(0, 0, 125)));
	sprgGen = new springLockGenerator(5, 50, dummyParticle);
	sprgGen1 = new springLockGenerator(5, 50,particles.back() );
	myForceRegistry->addRegistry(sprgGen, particles.back());
	myForceRegistry->addRegistry(sprgGen1, dummyParticle);
	myForceRegistry->addRegistry(gravGen, particles.back());*/

	//Goma entre dos particulas
	dummyParticle = new Particle(Vector3(0, 100, 0), Vector3(0), 0.99, 5, 100, 500, 1, Vector3(0, 0, 125));
	particles.push_back(dummyParticle);
	 particles.push_back(new Particle(Vector3(0, 0, 0), Vector3(0), 0.99, 50, 100, 500, 1, Vector3(0, 0, 125)));
	sprgGen = new springLockGenerator(5, 50, dummyParticle,true);
	sprgGen1 = new springLockGenerator(5, 50,particles.back(), true);
	myForceRegistry->addRegistry(sprgGen, particles.back());
	myForceRegistry->addRegistry(sprgGen1, dummyParticle);
	myForceRegistry->addRegistry(gravGen, particles.back());
	
	//Flotacion
	/*dummyParticle= new Particle(Vector3(0), Vector3(0), 0.99, 50, 1, 100, 1, Vector3(1, 0, 0), CreateShape(physx::PxBoxGeometry(Vector3(5))));
	Particle* aquaSuperficie= new Particle(Vector3(0, -10, 0), CreateShape(physx::PxBoxGeometry(Vector3(20,2,20))), Vector3(0, 0, 1));
	 particles.push_back(dummyParticle);
	fltGen = new FloatingGenerator(5, 100, 1, aquaSuperficie);
	myForceRegistry->addRegistry(fltGen, *particles.begin());
	myForceRegistry->addRegistry(gravGen, *particles.begin());*/


	//Slinky
	/*anchor = new Particle(Vector3(0, 50, 0), CreateShape(physx::PxBoxGeometry(Vector3(5))), Vector3(1, 0, 0));
	sprgGen = new springLockGenerator(5, 5, anchor->getPosition());

	particles.push_back(new Particle(Vector3(20), Vector3(0), 0.99, 5, 1, 100, 1, Vector3(0, 0, 125)));
	myForceRegistry->addRegistry(sprgGen, particles.back());
	myForceRegistry->addRegistry(gravGen, particles.back());
	for (int i = 0; i < 20; i++)
	{
		springLockGenerator* myGen = new springLockGenerator(5, 5, particles.back());
		particles.push_back(new Particle(Vector3(0,-20*i,0), Vector3(0), 0.99, 50, 1, 100, 1, Vector3(0, 0, 125)));
		myForceRegistry->addRegistry(myGen, particles.back());
		myForceRegistry->addRegistry(gravGen, particles.back());
	}*/

	//Generador Gaussiano
	//ParticleGenerator* ptGen = new GeneradorGaussiano(Vector3(50), Vector3(35), 0.3, model,true);
	//partGenerator.push_back(ptGen);
	////Generador Uniforme
	//model = new Particle(Vector3(0, -10, 0), Vector3(0), Vector3(0), Vector3(0), 0.99, 5, 10, 0, 1, Vector3(0, 125, 0));
	//ptGen = new GeneradorNormal(Vector3(50), Vector3(35), 0.3, model, false);
	//partGenerator.push_back(ptGen);
	//particles.push_back(new Firework(3, 10, Vector3(0,0,0), Vector3(0), Vector3(0), Vector3(0,10,0), 0.99, 5, 10, 3, 1, Vector3(0, 0, 125)));
	//particles.push_back(new Particle(Vector3(0, -10, 0), Vector3(0),  Vector3(0, 1, 0), 0.99, 5, 100, 10, 1, Vector3(0, 0, 0)));

	
	//windGen = new WindGenerator(Vector3(100, 0, 0), Vector3(0, 0, 0), 100, 1, 0);
	//windGen = new TornadoGenerator(Vector3(0, 0, 0), Vector3(0, 0, 0), 100, 1, 0, 5);
	//explGen = new ExplosionGenerator(Vector3(0), 1000, 500000, 5);
	//explGen->setDuration(50);


	//myForceRegistry->addRegistry(gravGen, particles.back());*/
	/*myForceRegistry->addRegistry(windGen, *particles.begin());*/
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
			myForceRegistry->addRegistry(windGen, *prtcls.begin());
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
		myForceRegistry->deletePartReg(p);
		particles.erase(killList.at(i));
		delete p;
	}
	killList.clear();
}