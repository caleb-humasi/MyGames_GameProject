#pragma once
#include "Enemy.hpp"
#include "AnimationsSelector.hpp"
#include "Time.hpp"
#include <random>

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
	enum class State {
		FLYING,
		ATTACKING,
		DASHING,
		DAMAGED
	};
	bool isChasing, enraged, onRight, isDashing;
	float deltaTime;
	int moves[7] = { 0,1,3,1,0,-1,-1 };
	const float speed, dashSpeed;
	State state;
	World* gameSpace;
	AnimationSelector animationSelector;
	CollisionManager collisionManager;
	TimeManager timeManager;
	sf::Vector2f desiredPosition;
	const sf::Vector2f* playerPosition;
	sf::Sprite mainSprite, headSprite;

	void movement();
	void dashing();
	void animate();
	void collision();
};