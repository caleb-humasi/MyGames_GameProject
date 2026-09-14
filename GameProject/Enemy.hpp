#pragma once
#include "Entity.hpp"

class Enemy : public Entity {
public:
	virtual void start() = 0;
	virtual void firstUpdate(float deltaTime) = 0;
	virtual void finalUpdate() = 0;
	virtual void render(sf::RenderWindow& window) = 0;

	const uint8_t& getDamage() const { return damage; }
	virtual const sf::Vector2f& getPosition() const = 0;
	virtual sf::Vector2f getCenter() = 0;
protected:
	int8_t life;
	uint8_t damage;
};