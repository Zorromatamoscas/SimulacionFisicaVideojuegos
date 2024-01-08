#include "WindRigid.h"
WindRigid::WindRigid(Vector3 wndVel, Vector3 positon, double vol, double konstant1, double konstant2, double duration)
{
	windVel = wndVel;
	pos = positon;
	volume = vol;
	k1 = konstant1;
	k2 = konstant2;
	setDuration(duration);
}

bool WindRigid::isInBounds(RigidBody* p)
{
	Vector3 Pos = p->getPosition();
	return (Pos.x > (pos.x - volume) && Pos.x < (pos.x + volume)) &&
		(Pos.y > (pos.y - volume) && Pos.y < (pos.y + volume)) &&
		(Pos.z > (pos.z - volume) && Pos.z < (pos.z + volume));
}
void WindRigid::updateForce(RigidBody* p, double t)
{
	if (isInBounds(p)) {

		Vector3 pVel = p->getVel();
		Vector3 diffVel = windVel - pVel;
		Vector3 force = k1 * diffVel + k2 * diffVel.magnitude() * diffVel;
		p->addForce(force);
	}
}
