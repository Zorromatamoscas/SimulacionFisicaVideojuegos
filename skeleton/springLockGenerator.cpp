#include "springLockGenerator.h"
springLockGenerator::springLockGenerator(double k, double lenght, Vector3 anchorP): ForceGenerator(), kConstant(k), springLength(lenght), anchorPoint(anchorP)
{

}
springLockGenerator::springLockGenerator(double k, double lenght, Particle* othe) : ForceGenerator(), kConstant(k), springLength(lenght), anchorPoint(0), other(othe)
{

}

void springLockGenerator::updateForce(Particle* p, double t)
{
	Vector3 force;
	Vector3 springVector;
	double totalLenght;
	Vector3 springDirection;
	if (fabs(p->getInvMass() < 1e-10)) return;
	springVector = p->getPosition() - (other==nullptr?anchorPoint: other->getPosition());
	totalLenght = springVector.magnitude();
	springDirection = springVector.getNormalized();
	force = -kConstant * (totalLenght - springLength) * springDirection;
	p->addForce(force);
}