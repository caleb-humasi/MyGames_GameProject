#pragma once
#include "Stair.hpp"

class StairManager {
public:
	StairManager(const std::vector<Stair>& _stairs, sf::FloatRect& _rectEntity):
	stairs(&_stairs),
	rectEntity(&_rectEntity),
	isAuthorized(false),
	stair(nullptr),
	intersectedTiles(nullptr){}

	bool update();

	void setIntersectedTiles(const std::vector<Tile*>& _intersectedTiles) {
		intersectedTiles = &_intersectedTiles;
	}
	void authorizeManager(bool authorize) { isAuthorized = authorize; }
private:
	const int total_colunas{ 51 };
	bool isAuthorized;
	sf::FloatRect* rectEntity;
	const Stair* stair;
	const std::vector<Stair>* stairs;
	const std::vector<Tile*>* intersectedTiles;
};