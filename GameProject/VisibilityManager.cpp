#include "VisibilityManager.hpp"

std::vector<Tile*> VisibilityManager::getCuttedTiles(std::vector<std::array<Tile*, 3>>& tiles) {
	std::vector<Tile*> tilesToRender;
	int initX = std::floor((float)topLeftCorner->x / 8.f), initY = std::floor((float)topLeftCorner->y / 8.f);
	int index = initX + initY * total_collumns;
	for (int y = 0; y < 152 / 8; ++y) {
		for (int x = 0; x < 208 / 8; ++x) {
			for (int i = 0; i < 3; ++i) {
				if (initX + x >= total_collumns) {
					break;
				}
				if (tiles[initX + x + (initY + y) * total_collumns][2 - i] != nullptr) {
					tilesToRender.push_back(tiles[initX + x + (initY + y) * total_collumns][2 - i]);
				}
			}
		}
	}
	return tilesToRender;
}