#include "ExplosionRigid.h"
ExplosionRigid::ExplosionRigid(Vector3 ExpPos, double radio, float ExpStrength, float timeconstant, bool activ)
	: pos(ExpPos), strength(ExpStrength), radius(radio), timeConstant(timeconstant), activated(activ) {
	setDuration(3);
}

void ExplosionRigid::updateForce(RigidBody* p, double t)
{
	Vector3 f = Vector3(0.0f, 0.0f, 0.0f);
	Vector3 P_pos = p->getPosition();
	Vector3 diff = P_pos - pos;
	double r = diff.magnitude(); // distacia a la explosión

	if (r < radius && activated) {
		f = (strength / pow(r, 2)) * diff * exp(-t / timeConstant);
		p->addForce(f);
	}
}
