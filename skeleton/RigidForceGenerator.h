
#pragma once
#include <PxPhysicsAPI.h>

#include <vector>

#include "core.hpp"
#include "RenderUtils.hpp"
#include "RigidBody.h"
class RigidForceGenerator {
protected:
	bool activated = true;
public:
	virtual void updateForce(RigidBody* particle, double t) = 0;
	std::string _name;
	double _t = 0.0; // If starting negative --> eternal
	double _duration = -1e10;
	inline void setDuration(double t)
	{
		_duration = t;
	}
	inline bool updateTime(double t) {
		_t += t;
		return _t > _duration || _duration < 0.0;
	}
	inline void deactivate() { activated = false; }
	inline void resetTime() { _t = 0; }
	virtual ~RigidForceGenerator() {}
};



