#include "RigidGenerator.h"
RigidGenerator::RigidGenerator(Vector3 pos, Vector3 velocity, Vector3 var, double frequency) :origin(pos), velocity(velocity), frec(frequency),
variation(var)
{
	srand((unsigned)time);
}