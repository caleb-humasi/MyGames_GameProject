#pragma once
#include "Enemy.hpp"
#include "AnimationsSelector.hpp"
#include "Time.hpp"

class World;
class Crow : public Enemy {
public:
	Crow(World& gameSpace);

	void start() final;
	void firstUpdate(float deltaTime) final;
	void finalUpdate() final;
	void render(sf::RenderWindow& window) final;

	const sf::Vector2f& getPosition() const final { return rectEntity.position; }
	sf::Vector2f getCenter() final { return rectEntity.position + rectEntity.size / 2.f; }

	CollisionManager* getCollisionManager() final { return &collisionManager; }
private:
	bool isMoving;
	float deltaTime;
	const float speed;
	World* gameSpace;
	AnimationSelector animationSelector;
	CollisionManager collisionManager;
	TimeManager timeManager;
	sf::Vector2f desiredPosition;
	const sf::Vector2f* playerPosition;
	sf::Sprite mainSprite;

	void movement();
	void animate();
	void collision();
};