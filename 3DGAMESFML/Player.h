#pragma once

#include <SFML/Graphics.hpp>

using namespace sf;

class Player
{
public:
	RenderWindow* window;
	const int SPEED = 250;
	const int SPEED_ANGLE = 2;
	const int MAX_DEPTH = 600;
	const float FOV = 3.141592654f / 6;
	float x = 0, y = 0, angle = 0, numRays = 0, deltaAngle = 0;
	bool w = false, a = false, s = false, d = false, right = false, left = false;

	Player(RenderWindow* window);
	void Move(float delta);
	void update(float delta);
};