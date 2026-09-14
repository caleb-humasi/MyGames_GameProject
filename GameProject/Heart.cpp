#include "Heart.hpp"
#include "GameSpace.hpp"
Heart::Heart(World& gameSpace, sf::Vector2f position) :
	move(true),
	angle(sf::degrees(0.f)),
	distance(0.f),
	deltaTime(0.f),
	sprite(gameSpace.getTexture(Texture::HEART)),
	collisionManager(rectEntity, desiredPosition),
	entities(&gameSpace.getEntities()) {

	nameEntity = "Heart";
	sprite.setOrigin(sprite.getLocalBounds().size / 2.f);
	sprite.setScale({ gb::SCALE, gb::SCALE });
	rectEntity.size = { 5 * gb::SCALE, 5 * gb::SCALE };
	rectEntity.position = position;
	desiredPosition = position;
}

void Heart::start() {
	collisionManager.addRect(rectEntity);
}

void Heart::firstUpdate(float dt) {
	deltaTime = dt;
	if (!move) return;
	movement();
}
void Heart::finalUpdate() {
	collision();
	rectEntity.position = desiredPosition;
	sprite.setPosition(rectEntity.position + rectEntity.size / 2.f);
	if (collisionManager.getDidCollide()) move = false;
	
}

void Heart::render(sf::RenderWindow& window) {
	window.draw(sprite);
}

void Heart::movement(){
	distance = std::sinf(angle.asRadians()) / 2.f;
	angle += sf::degrees(6.f * deltaTime * gb::FPS);
	desiredPosition.x += distance * gb::FPS * deltaTime;
	desiredPosition.y += 0.25f * deltaTime * gb::FPS;
}

void Heart::collision() {
	for (auto& e : *entities) {
		if (e->getName() == "Player" && rectEntity.findIntersection(e->getRect())) {
			annihilateEntity = true;
			return;
		}
	}
}
