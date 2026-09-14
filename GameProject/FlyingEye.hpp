#pragma once
#include "Enemy.hpp"
#include "AnimationsSelector.hpp"
#include "Time.hpp"

class World;
class FlyingEye : public Enemy {
	//raio da parte = 2 * scale!!
	struct TailPart {
		float angle{ 0.f };
		float angleTraveled{ 0.f };
		float speed{ 0.f };
		float timer{ 0.f };
		char direction{ 0 };
		sf::Sprite sprite;
		sf::Vector2f position{0.f,0.f};
		std::vector<float> angles;
	};
public:
	FlyingEye(World& gameSpace);

	void start() final;
	void firstUpdate(float deltaTime) final;
	void finalUpdate() final;
	void render(sf::RenderWindow& window) final;

	const sf::Vector2f& getPosition() const final { return rectEntity.position; }
	sf::Vector2f getCenter() final { return rectEntity.position + rectEntity.size / 2.f; }

	CollisionManager* getCollisionManager() final { return &collisionManager; }
private:
	bool isMoving;
	float passedTime;
	float deltaTime;
	float angle;
	const float radiusEye{ 2.5f };
	const float speed, speedAngle, accelerationTail, initPosTail, finalPosTail;
	World* gameSpace;
	AnimationSelector animationSelector;
	CollisionManager collisionManager;
	TimeManager timeManager;
	sf::Vector2f desiredPosition;
	const sf::Vector2f* playerPosition;
	sf::Sprite mainSprite;
	std::vector<TailPart> tailParts;

	void updateTail();
	void movement();
	void animate();
	void collision();
};