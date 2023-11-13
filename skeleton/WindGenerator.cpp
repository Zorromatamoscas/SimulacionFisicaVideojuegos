#include "WindGenerator.h"
WindGenerator::WindGenerator(Vector3 wndVel, Vector3 positon, double vol)
{
	windVel = wndVel;
	pos = positon;
	volume = vol;
}

bool WindGenerator::isInBounds(Particle* p)
{
	Vector3 Pos = p->getPosition();
	return (Pos.x > pos.x - volume && Pos.x > pos.x + volume) &&
		(Pos.y > pos.y - volume && Pos.y > pos.y + volume) &&
		(Pos.z > pos.z - volume && Pos.z > pos.z + volume);
}
void WindGenerator::updateForce(Particle* p)
{
	if (fabs(p->getInvMass() < 1e-10)) return;
	if (isInBounds(p)) {

		Vector3 pVel = p->getVel();
		Vector3 diffVel = windVel - pVel;
		Vector3 force = _k1 * diffVel + _k2 * diffVel.magnitude() * diffVel;
		p->addForce(force);
	}
}