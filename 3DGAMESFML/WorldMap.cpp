#include <string>
#include <vector>
#include "WorldMap.h"
#include "Player.h"

WorldMap::WorldMap(Player* player) {
	for (int y = 0; y < MAP_HEIGHT; y++)
		for (int x = 0; x < MAP_WIDTH; x++) {
			if (textMap[y][x] == '#')
				mapSquare.push_back({ x * SIZE_BLOCK, y * SIZE_BLOCK });
			if (textMap[y][x] == '|')
				mapMirror.push_back({ x * SIZE_BLOCK, y * SIZE_BLOCK });
			if (textMap[y][x] == 'c')
				mapCircle.push_back({ x * SIZE_BLOCK + SIZE_BLOCK / 2, y * SIZE_BLOCK + SIZE_BLOCK / 2 });
			else if (textMap[y][x] == 'p') {
				player->x = x * SIZE_BLOCK;
				player->y = y * SIZE_BLOCK;
			}
		}
}