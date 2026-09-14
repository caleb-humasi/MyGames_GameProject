#pragma once
#include "Enemy.hpp"
#include "PhysicsManager.hpp"
#include "AnimationsSelector.hpp"
#include "Collision.hpp"
#include "AnimationFactory.hpp"
#include "Time.hpp"
class World;
class Robot : public Enemy {
public:
	Robot(World& gameSpace);

	void start() final;
	void firstUpdate(float deltaTime) final;
	void finalUpdate() final;
	void render(sf::RenderWindow& window) final;

	PhysicsManager* getPhysicsManager() final { return &physicsManager; }
	CollisionManager* getCollisionManager() final { return &collisionManager; }

	const sf::Vector2f& getPosition() const final { return rectEntity.position; }
	sf::Vector2f getCenter() final { return rectEntity.position + rectEntity.size / 2.f; }
private:
	bool jump;
	bool canJump;
	bool isWalking;
	const float speed{0.4f};
	float deltaTime;
	PhysicsManager physicsManager;
	CollisionManager collisionManager;
	TimeManager timeManager;
	World* gameSpace;
	AnimationSelector animationSelector;
	sf::Sprite robotSprite;
	sf::Vector2f desiredPosition;
	const sf::Vector2f* playerPosition;

	void startSpriteConfiguration();

	void jumpAbove();
	void movement(float dt);
	void animate();
	void collision();
};