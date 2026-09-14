#pragma once
#include "Entity.hpp"
#include "Textures.hpp"
class World;
class SubWeaponItem : public Entity{
public:
	SubWeaponItem(World& gameSpace, sf::Vector2f position, Texture texture);

	void start() final;
	void firstUpdate(float dt) final;
	void finalUpdate() final;
	void render(sf::RenderWindow& window) final;

	CollisionManager* getCollisionManager() final { return &collisionManager; }
	const sf::Vector2f& getPosition() const final { return rectEntity.position; }
	sf::Vector2f getCenter() final { return rectEntity.position + rectEntity.size / 2.f; }
	Texture getTexture() { return subWeaponItemTexture; }
private:
	float deltaTime;
	sf::Sprite sprite;
	sf::Vector2f desiredPosition;
	std::vector<std::shared_ptr<Entity>>* entities;
	CollisionManager collisionManager;
	Texture subWeaponItemTexture;

	void movement();
	void collision();
};