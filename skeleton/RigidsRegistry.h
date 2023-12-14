#pragma once
#pragma once
#include "RigidForceGenerator.h"
#include<map>

typedef std::pair<RigidForceGenerator*, RigidBody*> FRPair2;

class RigidsRegistry : public std::multimap<RigidForceGenerator*, RigidBody*>
{
public:
	void updateForces(double t)
	{
		for (auto it = begin(); it != end(); it++)
		{
			it->first->updateForce(it->second, t);
		}
	}
	void addRegistry(RigidForceGenerator* fg, RigidBody* p)
	{
		this->insert({ fg,p });
	}
	void deletePartReg(RigidBody* p) {
		for (auto it = begin(); it != end();) {
			if (it->second == p) it = erase(it);
			else ++it;
		}
	}

private:

};


