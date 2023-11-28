#include "springLockGenerator.h"
springLockGenerator::springLockGenerator(double k, double lenght, Vector3 anchorP): ForceGenerator(), kConstant(k), springLength(lenght), anchorPoint(anchorP)
{

}

void springLockGenerator::updateForce(Particle* p, double t)
{
	if (fabs(p->getInvMass() < 1e-10)) return;

	Vector3 force;
	Vector3 springVector = p->getPosition() - anchorPoint;
	double totalLenght = springVector.magnitude();
	Vector3 springDirection = springVector.getNormalized();
	force = -kConstant*(totalLenght - springLength) * springDirection;
	p->addForce(force);
}