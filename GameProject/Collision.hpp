#pragma once
#include "Tile.hpp"
class CollisionManager {
public:
	enum class Side {
		LEFT,
		RIGHT,
		TOP,
		BOTTOM
	};
	CollisionManager(sf::FloatRect& _rect, sf::Vector2f& _desiredPosition) :
		rect(&_rect),
		desiredPosition(&_desiredPosition),
		sideIntersection({ false,false,false,false }),
		didCollide(false),
		activeCollision(true),
		box_tiles(nullptr),
		respectiveIndex(0){};

	void collision();
	bool collisionEntity(const CollisionManager& collisionManager);

	void setActiveCollision(bool value) { activeCollision = value; }
	void addRect(sf::FloatRect& _rect) { rects.push_back(&_rect); }
	void setFloatRect(sf::FloatRect& _rect) { rect = &_rect; }
	void setTiles(std::vector<Tile>& _tiles) { box_tiles = &_tiles; }
	void setIndex(uint16_t index) { respectiveIndex = index; }
	void setSideIntersection(CollisionManager::Side side, bool value) { sideIntersection[(int)side] = value; }

	std::vector<std::pair<Tile*, Side>>& getCollisionTiles() { return collisionTiles; }
	const std::vector<Tile*>& getIntersectedTiles() const { return intersectedTiles; }
	const uint16_t& getIndex() const { return respectiveIndex; }
	bool getSideIntersection(Side side) const { return sideIntersection[(int)side]; }
	bool getDidCollide() { return didCollide; }
	const std::vector<sf::FloatRect*>& getRects() const { return rects; }
	const Tile& getTile(uint16_t index) const { return box_tiles->at(index); }
private:
	bool didCollide;
	bool activeCollision;
	uint16_t respectiveIndex;
	sf::FloatRect* rect;
	std::vector<sf::FloatRect*> rects;
	sf::Vector2f* desiredPosition;
	std::vector<Tile>* box_tiles;
	std::vector<Tile*> intersectedTiles;
	std::vector<std::pair<Tile*, Side>> collisionTiles;
	std::array<bool, 4> sideIntersection;
};