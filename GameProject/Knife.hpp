#pragma once
#include "Entity.hpp"
class Knife : public Entity {
public:
	Knife(const sf::Texture& texture, const sf::Vector2f& _playerPosition, bool _isRight) :
		spriteKnife(texture),
		playerPosition(&_playerPosition),
		timer(0.f),
		speed(0.f),
		isRight(_isRight) {
		nameEntity = "Cross";
	}

	void start() final;
	void firstUpdate(float dt) final;
	void finalUpdate() final;
	void render(sf::RenderWindow& window) final;

	const sf::Vector2f& getPosition() const final { return position; }
	sf::Vector2f getCenter() final { return rectEntity.position + rectEntity.size / 2.f; }
private:
	bool isRight;
	float timer;
	float speed;
	sf::Sprite spriteKnife;
	sf::Vector2f position;
	const sf::Vector2f* playerPosition;

	void startGeneralConfiguration();
};