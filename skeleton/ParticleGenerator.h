
#pragma once
#include "Particle.h"
#include <list>
#include <random>
#include <chrono>
	class ParticleGenerator
	{
	protected:
		int n_particles; 
		Particle* model = nullptr; 
		Vector3 origin, velocity, variation;
		float frec;
		std::default_random_engine gen;

		// Generador de aleatorios

	public:
		ParticleGenerator(Vector3 pos = Vector3( 0.0f, 0.0f, 0.0f), 
			Vector3 velocity = Vector3(0.0f, 0.0f, 0.0f),Vector3 var= Vector3(0.0f, 0.0f, 0.0f), double frequency = 0.1f);


		virtual std::list<Particle*> generateParticles() = 0;

		~ParticleGenerator() { delete model; }

		inline void setParticle(Particle* p) {
			model = p;
		}
		inline void setNParticles(int n_p) { n_particles = n_p; }


	

};

