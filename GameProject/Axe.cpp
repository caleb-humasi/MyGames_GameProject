#include "Axe.hpp"

void Axe::start() {
	startGeneralConfiguration();
	physicsManager.setDeltaY(-3.25f);
	spriteAxe.setScale({ gb::SCALE * (isRight ? 1.f : -1.f), gb::SCALE });
	nameEntity = "S_Axe";
	physicsManager.setEntityOwnerName(nameEntity);
}
void Axe::firstUpdate(float dt) {
	char direction = isRight ? 1.f : -1.f;
	angle += sf::degrees(30.f * dt * gb::FPS) * (float)direction;
	rectEntity.position.x += 1.5f * dt * gb::FPS * (float)direction;

	if (timer < 2.5f) {
		timer += dt;
	}
	else {
		annihilateEntity = true;
		physicsManager.setAnnihilatePhysicsManager(true);
	}
	deltaTime = dt;
}

void Axe::finalUpdate() {
	rectEntity.position.y += physicsManager.getDeltaDistance() * deltaTime * gb::FPS;
	spriteAxe.setPosition(rectEntity.position + rectEntity.size / 2.f);
	spriteAxe.setRotation(angle);
}
void Axe::render(sf::RenderWindow& window) {
	window.draw(spriteAxe);
}

void Axe::startGeneralConfiguration() {
	spriteAxe.setOrigin(spriteAxe.getLocalBounds().size / 2.f);
	spriteAxe.setScale({ gb::SCALE, gb::SCALE });
	spriteAxe.setPosition(*playerPosition);

	rectEntity.size = spriteAxe.getGlobalBounds().size;
	rectEntity.position = *playerPosition - rectEntity.size / 2.f + sf::Vector2f(3 * gb::SCALE / 2.f, 0);
}