#pragma once
#include "ForceGenerator.h"
#include<map>

typedef std::pair<ForceGenerator*, Particle*> FRPair;

class ParticleForceRegistry: public std::multimap<ForceGenerator*, Particle*>
{
public:
	void updateForces(double t)
	{
		for (auto it = begin(); it != end(); it++)
		{
			it->first->updateForce(it->second,t);
		}
	}
	void addRegistry(ForceGenerator* fg, Particle* p)
	{
		this->insert({ fg,p });
	}
	void deletePartReg(Particle* p) {
		for (auto it = begin(); it != end();) {
			if (it->second == p) it = erase(it);
			else ++it;
		}
	}

private:

};
