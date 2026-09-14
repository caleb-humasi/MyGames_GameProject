#pragma once
#include "Entity.hpp"
#include "PhysicsManager.hpp"
class Axe : public Entity {
public:
	Axe(const sf::Texture& texture, const sf::Vector2f& _playerPosition, bool _isRight) :
		spriteAxe(texture),
		playerPosition(&_playerPosition),
		physicsManager(position, 30.f),
	timer(0.f),
	isRight(_isRight),
	deltaTime(0.f){
		nameEntity = "Axe";
	}
	
	void start() final;
	void firstUpdate(float dt) final;
	void finalUpdate() final;
	void render(sf::RenderWindow& window) final;

	PhysicsManager* getPhysicsManager() final { return &physicsManager; }
	const sf::Vector2f& getPosition() const final { return position; }
	sf::Vector2f getCenter() final { return rectEntity.position + rectEntity.size / 2.f; }
private:
	bool isRight;
	float timer;
	float deltaTime;
	sf::Angle angle;
	PhysicsManager physicsManager;
	sf::Sprite spriteAxe;
	sf::Vector2f position;
	const sf::Vector2f* playerPosition;

	void startGeneralConfiguration();
};