#include "ParticleGenerator.h"
//#include "ParticleSystem.h"
ParticleGenerator::ParticleGenerator(ParticleSystem* system, int n_particles, Vector3 pos, Vector3 velocity, double frequency, Vector3 gravity) :
	_system(system), _n_particles(n_particles),
	_origin(pos), _velocity(velocity), _frec(frequency), _grav(gravity)
{

}

//void ParticleGenerator::update(double t)
//{
//
//
//	if (!myParticles.empty())
//	{
//		for (Particle* p : myParticles)
//		{
//			p->integrate(t);
//			if (!p->isAlive()||isParticleOutOfBounds(p->getPosition())) delete p;
//			
//		}
//	}
//	if (myParticles.size() < 1000)
//	{
//		myParticles.push_back(new Particle(Vector3(0, -10, 0), singularity, Vector3(0, 0, 0), Vector3(rand() % 2 ? rand() % 10 : -rand() % 10,
//			100 + (rand() % 2 ? rand() % 10 : -rand() % 10), rand() % 2 ? rand() % 10 : -rand() % 10), 0.99, 1, 1, 10, 1));
//	}
//}
//bool ParticleGenerator::isParticleOutOfBounds(Vector3 p)
//{
//	return p.x > (singularity.x + actSpaceSize.x) || p.x < (singularity.x - actSpaceSize.x) || p.y >(singularity.y + actSpaceSize.y)
//		|| p.y < (singularity.y - actSpaceSize.y) || p.z >(singularity.z + actSpaceSize.z) || p.z < (singularity.z - actSpaceSize.z);
//}