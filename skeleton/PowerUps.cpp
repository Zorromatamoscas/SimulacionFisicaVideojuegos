#include "PowerUps.h"
PowerUps::PowerUps(Vector3 pos, Vector3 color, RigidSystem* system, bool model) : Particle(pos, Vector3(0), 0.99, 0.0f, 0.0f, 15, 0.0f, color,model)
{
	mySystem = system;
}


bool PowerUps::checkCollisions()
{
	Car* car = mySystem->getPlayer1();
	if ((getPosition() - car->getPos()).magnitude() <= (car->getColliderRadius() + this->myRadius)) {
		applyPower(car);
		return true;
	}
	car = mySystem->getPlayer2();
	if ((getPosition() - car->getPos()).magnitude() <= (car->getColliderRadius() + this->myRadius)) {
		applyPower(car);
		return true;
	}
	else return false;
}