#include "Cross.hpp"

void Cross::start() {
	startGeneralConfiguration();
	spriteCross.setScale({ gb::SCALE * (isRight ? 1.f : -1.f), gb::SCALE });
	nameEntity = "S_Cross";
	speed = 3.25f * (isRight? 1.f : -1.f);
}
void Cross::firstUpdate(float dt) {
	char direction = isRight ? 1.f : -1.f;
	speed -= 0.1f * dt * gb::FPS * (float)direction;
	angle += sf::degrees(20.f * dt * gb::FPS) * (float)direction;
	rectEntity.position.x += speed * dt * gb::FPS;

	if (timer < 2.5f) {
		timer += dt;
	}
	else {
		annihilateEntity = true;
	}
}

void Cross::finalUpdate() {
	spriteCross.setPosition(rectEntity.position + rectEntity.size / 2.f);
	spriteCross.setRotation(angle);
}
void Cross::render(sf::RenderWindow& window) {
	window.draw(spriteCross);
}

void Cross::startGeneralConfiguration() {
	spriteCross.setOrigin(spriteCross.getLocalBounds().size / 2.f);
	spriteCross.setScale({ gb::SCALE, gb::SCALE });
	spriteCross.setPosition(*playerPosition);

	rectEntity.size = spriteCross.getGlobalBounds().size;
	rectEntity.position = *playerPosition - rectEntity.size / 2.f + sf::Vector2f(3.f * gb::SCALE / 2.f , 5.f);
}