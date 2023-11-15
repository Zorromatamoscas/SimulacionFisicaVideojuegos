#include "ExplosionGenerator.h"
ExplosionGenerator::ExplosionGenerator(Vector3 ExpPos, double radio, float ExpStrength, float timeconstant, bool activ = false)
	: pos(ExpPos), strength(ExpStrength), radius(radio), timeConstant(timeconstant), activated(activ){}

