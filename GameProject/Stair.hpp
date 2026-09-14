#pragma once
#include "Tile.hpp"
class Stair {
public:
	Stair(const Tile& t1, const Tile& t2, char _direction) :
	tile1(&t1),
	tile2(&t2),
	direction(_direction){}

	const Tile& getTile1() const { return *tile1; }
	const Tile& getTile2() const { return *tile2; }

	const char& getDirection() const { return direction; }
private:
	char direction;
	const Tile* tile1, *tile2;
};