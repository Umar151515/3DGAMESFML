#pragma once

Vector2f RayUpdate(float angle, int maxDepth, float x, float y, bool& isLet, bool(*isFunc)(float x, float y));
Vector2f RayUpdate(float angle, float& d, bool& isWall, Player* player, WorldMap* worldMap);
void RayCasting(Player* player, RenderWindow* window, WorldMap* worldMap);