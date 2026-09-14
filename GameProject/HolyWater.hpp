#pragma once
#include <SFML/Audio.hpp>
#include "Entity.hpp"
#include "PhysicsManager.hpp"
#include "Collision.hpp"
#include "Tile.hpp"
#include "EntityFactory.hpp"

class HolyWater : public Entity {
public:
	HolyWater(World& _gameSpace, const sf::Vector2f& _playerPosition, bool _isRight);

	void start() final;
	void firstUpdate(float dt) final;
	void finalUpdate() final;
	void render(sf::RenderWindow& window) final;

	PhysicsManager* getPhysicsManager() final { return &physicsManager; }
	CollisionManager* getCollisionManager() final { return &collisionManager; }
	const sf::Vector2f& getPosition() const final { return position; }
	sf::Vector2f getCenter() final { return rectEntity.position + rectEntity.size / 2.f; }
private:
	bool spawnFire;
	bool isRight;
	float velocity;
	float timer;
	float deltaTime;
	World* gameSpace;
	PhysicsManager physicsManager;
	CollisionManager collisionManager;
	std::vector<Tile>* box_tiles;
	sf::Sprite spriteHolyWater;
	sf::Vector2f position;
	sf::Vector2f desiredPosition;
	const sf::Vector2f* playerPosition;

	void startGeneralConfiguration();
};