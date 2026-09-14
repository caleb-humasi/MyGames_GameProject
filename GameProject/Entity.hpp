#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include "PhysicsManager.hpp"
#include "Collision.hpp"
#include "globals.hpp"
class Entity : public std::enable_shared_from_this<Entity>{
public:
	Entity();
	virtual ~Entity() = default;
	virtual void start() = 0;
	virtual void firstUpdate(float deltaTime) = 0;
	virtual void finalUpdate() = 0;
	virtual void render(sf::RenderWindow& window) = 0;

	template<typename T>
	std::shared_ptr<T> as() {
		return std::dynamic_pointer_cast<T>(shared_from_this());
	}
	
	void setPosition(sf::Vector2f position) { rectEntity.position = position; }
	double convertToPiDegrees(float angle) { return ((double)angle * PI) / 180.f; }
	virtual PhysicsManager* getPhysicsManager() { return nullptr; }
	virtual CollisionManager* getCollisionManager() { return nullptr; }
	virtual const sf::Vector2f& getPosition() const = 0;
	virtual sf::Vector2f getCenter() = 0;

	const sf::FloatRect& getRect() const { return rectEntity; }
	const bool& getAnnihilateEntity() const { return annihilateEntity; }
	const std::string& getName() const { return nameEntity; }
protected:
	const double PI{ 3.1415926535 };
	bool annihilateEntity;
	std::string nameEntity;
	sf::FloatRect rectEntity;
};