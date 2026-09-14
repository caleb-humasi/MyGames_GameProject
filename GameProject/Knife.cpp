#include "Knife.hpp"

void Knife::start() {
	startGeneralConfiguration();
	spriteKnife.setScale({ gb::SCALE * (isRight ? 1.f : -1.f), gb::SCALE });
	nameEntity = "S_Knife";
	speed = 6.8f * (isRight ? 1.f : -1.f);
}
void Knife::firstUpdate(float dt) {
	char direction = isRight ? 1 : -1;
	rectEntity.position.x += speed * dt * gb::FPS;

	timer += dt;
	annihilateEntity = timer > 2.5f;
}

void Knife::finalUpdate() {
	spriteKnife.setPosition(rectEntity.position + rectEntity.size / 2.f);
}
void Knife::render(sf::RenderWindow& window) {
	window.draw(spriteKnife);
}

void Knife::startGeneralConfiguration() {
	spriteKnife.setOrigin(spriteKnife.getLocalBounds().size / 2.f);
	spriteKnife.setScale({ gb::SCALE, gb::SCALE });
	spriteKnife.setPosition(*playerPosition);

	rectEntity.size = spriteKnife.getGlobalBounds().size;
	rectEntity.position = *playerPosition - rectEntity.size / 2.f + sf::Vector2f(3.f * gb::SCALE / 2.f, 2.5f);
}