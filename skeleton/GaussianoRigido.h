#pragma once
#include "RigidGenerator.h"
class GaussianoRigido : public RigidGenerator
{
private:
	std::normal_distribution<float>* xVel;
	std::normal_distribution<float>* yVel;
	std::normal_distribution<float>* zVel;
	std::normal_distribution<float>* xPos;
	std::normal_distribution<float>* yPos;
	std::normal_distribution<float>* zPos;
	bool anclado;
public:
	GaussianoRigido(Vector3 origen, Vector3 varianza, float prob, RigidBody* model, bool ancla);
	virtual ~GaussianoRigido();

	virtual std::list<RigidBody*> generateRigids();
};

