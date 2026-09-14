#include "Stone.hpp"

void Stone::start() {
	startGeneralConfiguration();
	physicsManager.setDeltaY(0.f);
	spriteStone.setScale({ gb::SCALE, gb::SCALE });
	nameEntity = "E_Stone";
	physicsManager.setEntityOwnerName(nameEntity);
}
void Stone::firstUpdate(float dt) {
	rectEntity.position += sf::Vector2f(cosf(angle.asRadians()), sinf(angle.asRadians())) * 3.25f * dt * gb::FPS;

	if (timer < 2.5f) {
		timer += dt;
	}
	else {
		annihilateEntity = true;
		physicsManager.setAnnihilatePhysicsManager(true);
	}
	deltaTime = dt;
}

void Stone::finalUpdate() {
	rectEntity.position.y += physicsManager.getDeltaDistance() * deltaTime * gb::FPS;
	spriteStone.setPosition(rectEntity.position + rectEntity.size / 2.f);
}
void Stone::render(sf::RenderWindow& window) {
	window.draw(spriteStone);
}

void Stone::startGeneralConfiguration() {
	spriteStone.setOrigin(spriteStone.getLocalBounds().size / 2.f);
	spriteStone.setScale({ gb::SCALE, gb::SCALE });

	rectEntity.size = spriteStone.getGlobalBounds().size;
	rectEntity.position = *golemPosition + sf::Vector2f(0.f, -2* gb::SCALE) - rectEntity.size / 2.f;
	spriteStone.setPosition(getCenter());
}