#include "TornadoGenerator.h"
TornadoGenerator::TornadoGenerator(Vector3 wndVel, Vector3 positon, double vol, double konstant1, double konstant2, double tornStrength)
	: WindGenerator(wndVel, positon, vol, konstant1, konstant2), k(tornStrength) {}


void TornadoGenerator::updateForce(Particle* p, double t)
{
	if (fabs(p->getInvMass() < 1e-10)) return;
	if (isInBounds(p)) {

		if (fabs(p->getInvMass()) < 1e-10) return;

		Vector3 p_pos = p->getPosition();

		windVel = k * Vector3(-(p_pos.z - pos.z), 50 - (p_pos.y - pos.y), p_pos.x - pos.x);

		WindGenerator::updateForce(p,t);
	}
}
