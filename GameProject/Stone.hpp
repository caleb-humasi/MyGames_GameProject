#pragma once
#include "Entity.hpp"
#include "PhysicsManager.hpp"
class Stone : public Entity {
public:
	Stone(const sf::Texture& texture, const sf::Vector2f& _golemPosition, sf::Angle _angle) :
		spriteStone(texture),
		golemPosition(&_golemPosition),
		physicsManager(position, 30.f),
		timer(0.f),
		angle(_angle),
		deltaTime(0.f) {
	}

	void start() final;
	void firstUpdate(float dt) final;
	void finalUpdate() final;
	void render(sf::RenderWindow& window) final;

	PhysicsManager* getPhysicsManager() final { return &physicsManager; }
	const sf::Vector2f& getPosition() const final { return position; }
	sf::Vector2f getCenter() final { return rectEntity.position + rectEntity.size / 2.f; }
private:
	float timer;
	float deltaTime;
	sf::Angle angle;
	PhysicsManager physicsManager;
	sf::Sprite spriteStone;
	sf::Vector2f position;
	const sf::Vector2f* golemPosition;

	void startGeneralConfiguration();
};