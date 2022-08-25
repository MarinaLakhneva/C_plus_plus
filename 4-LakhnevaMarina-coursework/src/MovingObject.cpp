#include "MovingObject.h"

void NArkanoid::TMovingObject::SetSpeed(const sf::Vector2f& speed) {
	this->speed = speed;
}

const sf::Vector2f& NArkanoid::TMovingObject::GetSpeed() const {
	return speed;
}

void NArkanoid::TMovingObject::RotateX() {
	speed.x = -speed.x;
}

void NArkanoid::TMovingObject::RotateY() {
	speed.y = -speed.y;
}
