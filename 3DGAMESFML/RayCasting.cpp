#include <iostream>
#include "Player.h"
#include "WorldMap.h"
#include "RayCasting.h"

bool isPointInsideCircle(double x, double y, WorldMap* worldMap) {
	for (const auto& circle : worldMap->mapCircle){
		double distance = std::sqrt(std::pow(x - circle[0], 2) + std::pow(y - circle[1], 2));
		if (distance <= worldMap->SIZE_BLOCK / 2)
			return true;
	}
	return false;
}

bool isPointInsideSquare(float x, float y, WorldMap* worldMap) {
	for (const auto& square : worldMap->mapSquare)
		if (x >= square[0] && x <= square[0] + worldMap->SIZE_BLOCK &&
			y >= square[1] && y <= square[1] + worldMap->SIZE_BLOCK)
			return true;
	return false;
}

bool isPointInsideMirror(float x, float y, WorldMap* worldMap) {
	for (const auto& square : worldMap->mapMirror)
		if (x >= square[0] && x <= square[0] + worldMap->SIZE_BLOCK &&
			y >= square[1] && y <= square[1] + worldMap->SIZE_BLOCK)
			return true;
	return false;
}

Vector2f RayUpdate(float angle, int maxDepth, float x, float y, bool& isLet, bool(*isFunc)(float x, float y)) {
	float xo = 0, yo = 0;
	for (int depth = 0; depth < maxDepth; depth++) {
		float sinAngle = sin(angle);
		float cosAngle = cos(angle);
		xo = x + depth * cosAngle;
		yo = y + depth * sinAngle;
		if (isFunc(xo, yo))
			isLet = true;
			return Vector2f(xo, yo);
	}
	return Vector2f(xo, yo);
}

Vector2f RayUpdate(float angle, float& d, bool& isWall, Player* player, WorldMap* worldMap) {
	float x = 0, y = 0;
	for (int depth = 0; depth < player->MAX_DEPTH; depth++) {
		float sinAngle = sin(angle);
		float cosAngle = cos(angle);
		x = player->x + depth * cosAngle;
		y = player->y + depth * sinAngle;
		if (isPointInsideSquare(x, y, worldMap) || isPointInsideCircle(x, y, worldMap)) {
			d = depth;
			isWall = true;
			return Vector2f(x, y);
		}
		else if (isPointInsideMirror(x, y, worldMap))
			angle = -angle;
	}
	return Vector2f(x, y);
}

void RayCasting(Player* player, RenderWindow* window, WorldMap* worldMap) {
	Vector2u windowSize = window->getSize();
	float scale = windowSize.x / player->numRays;

	float curAngle = player->angle - player->FOV / 2;
	
	for (int ray = 0; ray < player->numRays; ray++) {
		float depth = 0;
		bool isWall = false;
		Vector2f pos = RayUpdate(curAngle, depth, isWall, player, worldMap);
		
		if (isWall && depth != 0) {
			//depth *= cos(player->angle - curAngle);
			float dist = player->numRays / (2 * tan(player->FOV / 2));
			float height = worldMap->SIZE_BLOCK / depth * dist;
			RectangleShape rectangle(Vector2f(scale, height));
			rectangle.setPosition(ray * scale, windowSize.y / 2 - height / 2);
			float c = (1 + depth * depth * 0.0001);
			rectangle.setFillColor(Color(17/c, 52/c, 92/c));
			window->draw(rectangle);
		}

		curAngle += player->deltaAngle;
	}
}