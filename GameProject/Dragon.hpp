#pragma once
#include "Enemy.hpp"
#include "AnimationManager.hpp"
#include "Time.hpp"
#include <random>
#include "Enum.hpp"

class World;
class Dragon : public Enemy {
public:
	Dragon(World& gameSpace);

	void start() final;
	void firstUpdate(float deltaTime) final;
	void finalUpdate() final;
	void render(sf::RenderWindow& window) final;

	const sf::Vector2f& getPosition() const final { return rectEntity.position; }
	sf::Vector2f getCenter() final { return rectEntity.position + rectEntity.size / 2.f; }

	CollisionManager* getCollisionManager() final { return &collisionManager; }
private:
	bool isChasing, enraged, onRight, isDashing;
	float deltaTime;
	int moves[7] = { 0,1,3,1,0,-1,-1 };
	const float speed, dashSpeed;
	dragon::EntityState state;
	AnimationManager animManager;
	World* gameSpace;
	CollisionManager collisionManager;
	TimeManager timeManager;
	sf::Vector2f desiredPosition;
	const sf::Vector2f* playerPosition;
	sf::Sprite mainSprite, headSprite, dragon_fire;

	void movement();
	void dashing();
	void animate();
	void collision();
};