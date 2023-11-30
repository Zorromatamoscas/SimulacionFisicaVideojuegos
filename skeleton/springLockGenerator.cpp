#include "springLockGenerator.h"
springLockGenerator::springLockGenerator(double k, double lenght, Vector3 anchorP, bool goma ): ForceGenerator(), kConstant(k), springLength(lenght), anchorPoint(anchorP), myGoma(goma)
{

}
springLockGenerator::springLockGenerator(double k, double lenght, Particle* othe, bool goma) : ForceGenerator(), kConstant(k), springLength(lenght), anchorPoint(0), other(othe), myGoma(goma)
{

}

void springLockGenerator::updateForce(Particle* p, double t)
{
	Vector3 force;
	Vector3 springVector;
	double totalLenght;
	Vector3 springDirection;
	if (fabs(p->getInvMass() < 1e-10)) return;
	springVector = p->getPosition() - (other == nullptr ? anchorPoint : other->getPosition());
	if (myGoma && (springVector.magnitude() <= springLength)) {
		std::cout << "hola" << std::endl;
		return;
	}
	else {
		totalLenght = springVector.magnitude();
		springDirection = springVector.getNormalized();
		force = -kConstant * (totalLenght - springLength) * springDirection;
		p->addForce(force);
	}
}