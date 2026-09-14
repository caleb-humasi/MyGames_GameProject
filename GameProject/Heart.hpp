#pragma once
#include "Entity.hpp"

class World;
class Heart : public Entity {
public:
	Heart(World& gameSpace, sf::Vector2f position);

	void start() final;
	void firstUpdate(float dt) final;
	void finalUpdate() final;
	void render(sf::RenderWindow& window) final;

	CollisionManager* getCollisionManager() final { return &collisionManager; }
	const sf::Vector2f& getPosition() const final { return rectEntity.position; }
	sf::Vector2f getCenter() final { return rectEntity.position + rectEntity.size / 2.f;  }
private:
	bool move;
	float distance, deltaTime;
	sf::Angle angle;
	sf::Sprite sprite;
	sf::Vector2f desiredPosition;
	std::vector<std::shared_ptr<Entity>>* entities;
	CollisionManager collisionManager;

	void movement();
	void collision();
};