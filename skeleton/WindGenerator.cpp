#include "WindGenerator.h"
WindGenerator::WindGenerator(Vector3 wndVel, Vector3 positon, double vol, double konstant1, double konstant2)
{
	windVel = wndVel;
	pos = positon;
	volume = vol;
	k1 = konstant1;
	k2 = konstant2;
}

bool WindGenerator::isInBounds(Particle* p)
{
	Vector3 Pos = p->getPosition();
	return (Pos.x > (pos.x - volume) && Pos.x < (pos.x + volume)) &&
		(Pos.y > (pos.y - volume) && Pos.y < (pos.y + volume)) &&
		(Pos.z > (pos.z - volume) && Pos.z < (pos.z + volume));
}
void WindGenerator::updateForce(Particle* p)
{
	if (fabs(p->getInvMass() < 1e-10)) return;
	if (isInBounds(p)) {

		Vector3 pVel = p->getVel();
		Vector3 diffVel = windVel - pVel;
		Vector3 force = k1 * diffVel + k2 * diffVel.magnitude() * diffVel;
		p->addForce(force);
	}
}