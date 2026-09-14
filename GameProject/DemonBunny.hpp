#pragma once
#include "Enemy.hpp"
#include "Time.hpp"

class World;
class DemonBunny : public Enemy {
public:
	DemonBunny(World& gameSpace);

	void start() final;
	void firstUpdate(float deltaTime) final;
	void finalUpdate() final;
	void render(sf::RenderWindow& window) final;

	const sf::Vector2f& getPosition() const final { return rectEntity.position; }
	sf::Vector2f getCenter() final { return rectEntity.position + rectEntity.size / 2.f; }

	CollisionManager* getCollisionManager() final { return &collisionManager; }
	PhysicsManager* getPhysicsManager() final { return &physicsManager; }
private:
	bool agressive;
	bool oneShoot;
	bool jump, canJump;
	bool isAttacking;
	bool isRight;
	char direction;
	const float speed;
	float deltaTime;
	World* gameSpace;
	CollisionManager collisionManager;
	PhysicsManager physicsManager;
	TimeManager timeManager;
	sf::Vector2f desiredPosition;
	const sf::Vector2f* playerPosition;
	sf::Sprite mainSprite;

	void jumpUpdate();
	void animation();
	void collision();
};