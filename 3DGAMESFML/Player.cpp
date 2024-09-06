#include <SFML/Graphics.hpp>
#include "Player.h"

using namespace sf;

Player::Player(RenderWindow* window) {
	this->window = window;
}

void Player::Move(float delta)
{
	float sinAngle = sin(angle);
	float cosAngle = cos(angle);
	if (w) {
		y += SPEED * delta * sinAngle;
		x += SPEED * delta * cosAngle;
	}
	else if (s) {
		y += -SPEED * delta * sinAngle;
		x += -SPEED * delta * cosAngle;
	}
	if (a) {
		//y += -SPEED * delta * sinAngle;
		//x += SPEED * delta * cosAngle;
	}
	else if (d) {
		//y += SPEED * delta * sinAngle;
		//x += -SPEED * delta * cosAngle;
	}
	if (left)
		angle -= SPEED_ANGLE * delta;
	else if (right)
		angle += SPEED_ANGLE * delta;
}

void Player::update(float delta)
{
	numRays = 150;//window->getSize().x;
	deltaAngle = FOV / numRays;
	Move(delta);
}
