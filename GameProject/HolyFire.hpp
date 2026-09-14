#pragma once
#include "Entity.hpp"
#include "Animation.hpp"

class World;
class HolyFire : public Entity {
public:
	HolyFire(World& _gameSpace, sf::Vector2f respectivePosition);

	void start() final;
	void firstUpdate(float dt) final;
	void finalUpdate() final;
	void render(sf::RenderWindow& window) final;

	const sf::Vector2f& getPosition() const final { return rectEntity.position; }
	sf::Vector2f getCenter() final { return rectEntity.position + rectEntity.size / 2.f; }
private:
	float timer;
	Animation animation;
	sf::Sprite sprite;
};