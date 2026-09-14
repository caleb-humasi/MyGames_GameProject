#pragma once
#include "Enemy.hpp"
#include "AnimationsSelector.hpp"
#include "Time.hpp"

class World;
class StoneGolem : public Enemy {
public:
	StoneGolem(World& gameSpace);

	void start() final;
	void firstUpdate(float deltaTime) final;
	void finalUpdate() final;
	void render(sf::RenderWindow& window) final;

	const sf::Vector2f& getPosition() const final { return rectEntity.position; }
	sf::Vector2f getCenter() final { return rectEntity.position + rectEntity.size / 2.f; }

	CollisionManager* getCollisionManager() final { return &collisionManager; }
	PhysicsManager* getPhysicsManager() final { return &physicsManager; }
private:
	bool oneShoot;
	bool attack;
	bool isAttacking;
	bool isRight;
	char direction;
	float deltaTime;
	World* gameSpace;
	AnimationSelector animationSelector;
	CollisionManager collisionManager;
	PhysicsManager physicsManager;
	TimeManager timeManager;
	sf::Angle angleToShoot;
	sf::Vector2f desiredPosition;
	const sf::Vector2f* playerPosition;
	sf::Sprite mainSprite;

	void throwStone();
	void animation();
	void collision();
};