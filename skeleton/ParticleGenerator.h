
#pragma once
#include "Particle.h"
#include <list>
#include <random>
	class ParticleSystem;
	class ParticleGenerator
	{
	protected:
		int _n_particles; // Number of particles for each generateParticles call(TODO: add randomness ? ? )
		Particle* _model = nullptr; // Has the attributes of the particle that will be generated!(damping, lifetime, etc.)
		Vector3 _origin, _velocity, _grav;
		float _frec;
	public:
		ParticleGenerator(ParticleSystem* system, int n_particles, Vector3 pos = Vector3( 0.0f, 0.0f, 0.0f), Vector3 velocity = Vector3(0.0f, 0.0f, 0.0f), double frequency = 0.1f, Vector3 gravity = Vector3(0.0f, -10.0f, 0.0f));


		virtual std::list<Particle*> generateParticles() = 0;


		inline void setOrigin(const Vector3& p) { _origin = p; }
		inline void setFrequency(double f) { _frec = f; }

		inline void setVelocity(const Vector3& v) {
			_velocity = v;
		}
		inline Vector3 getVelocity() const {
			return _velocity;
		}
		inline void setDuration(double dur) {
			_model->setDuration(dur);
		}

		inline void setParticle(Particle* p) {
			delete _model;
			_model = p;
		}
		inline void setNParticles(int n_p) { _n_particles = n_p; }


	

};

