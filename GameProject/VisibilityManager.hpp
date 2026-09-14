#pragma once
#include "Tile.hpp"

class VisibilityManager {
public:
	VisibilityManager():
	topLeftCorner(nullptr),
	levelWidth(0),
	levelHeight(0),
	total_collumns(0),
	total_lines(0){
	}

	void setWidthAndHeight(int width, int height) {
		levelWidth = width;
		levelHeight = height;
		total_collumns = width / 8;
		total_lines = height / 8;
	}
	void setTopLeftCorner(const sf::Vector2f& _topLeftCorner) {
		topLeftCorner = &_topLeftCorner;
	}
	void setCameraSize(sf::Vector2f _cameraSize) {
		cameraSize = _cameraSize;
	}
	std::vector<Tile*> getCuttedTiles(std::vector<std::array<Tile*, 3>>& tiles);
private:
	const sf::Vector2f* topLeftCorner;
	sf::Vector2f cameraSize;
	int levelWidth, levelHeight;
	int total_collumns, total_lines;
};