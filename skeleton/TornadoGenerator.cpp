#include "TornadoGenerator.h"
TornadoGenerator::TornadoGenerator(Vector3 wndVel, Vector3 positon, double vol, double konstant1, double konstant2, double tornStrength)
	: WindGenerator(wndVel, positon, vol, konstant1, konstant2), k(tornStrength) {}


void TornadoGenerator::updateForce(Particle* p)
{
	if (fabs(p->getInvMass() < 1e-10)) return;
	if (isInBounds(p)) {

		double zTorn = -(p->getPosition().z - pos.z);
		double yTorn = 50 - (p->getPosition().y - pos.y);
		double xTorn = p->getPosition().x - pos.x;
		Vector3 velTor = k * Vector3(xTorn, yTorn, zTorn);
		Vector3 force = k1 * velTor + k2 * velTor.magnitude() * velTor;
		p->addForce(force);
	}
}
