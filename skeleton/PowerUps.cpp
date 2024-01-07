#include "PowerUps.h"
PowerUps::PowerUps(Vector3 pos, Vector3 color) : Particle(pos, Vector3(0), 0.99, 0.0f, 0.0f, 15, 0.0f, color)
{

}


bool PowerUps::checkCollisions(Car* car)
{
	if ((getPosition() - car->getPos()).magnitude() <= (car->getColliderRadius() + this->myRadius)) return true;
	else return false;
}