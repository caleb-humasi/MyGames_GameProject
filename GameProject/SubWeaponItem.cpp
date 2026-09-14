#include "SubWeaponItem.hpp"
#include "GameSpace.hpp"
SubWeaponItem::SubWeaponItem(World& gameSpace, sf::Vector2f position, Texture texture) :
	subWeaponItemTexture(texture),
	deltaTime(0.f),
	sprite(gameSpace.getTexture(texture)),
	collisionManager(rectEntity, desiredPosition),
	entities(&gameSpace.getEntities()) {

	nameEntity = "SubWeaponItem";
	sprite.setOrigin(sprite.getLocalBounds().size / 2.f);
	sprite.setScale({ gb::SCALE, gb::SCALE });
	rectEntity.size = { 5 * gb::SCALE, 5 * gb::SCALE };
	rectEntity.position = position;
	desiredPosition = position;

}

void SubWeaponItem::start() {
	collisionManager.addRect(rectEntity);
}

void SubWeaponItem::firstUpdate(float dt) {
	deltaTime = dt;
	movement();
}
void SubWeaponItem::finalUpdate() {
	collision();
	rectEntity.position = desiredPosition;
	sprite.setPosition(rectEntity.position + rectEntity.size / 2.f);
}

void SubWeaponItem::render(sf::RenderWindow& window) {
	window.draw(sprite);
}

void SubWeaponItem::movement() {
	desiredPosition.y += 0.25f * deltaTime * gb::FPS;
}

void SubWeaponItem::collision() {
	for (auto& e : *entities) {
		if (e->getName() == "Player" && rectEntity.findIntersection(e->getRect())) {
			annihilateEntity = true;
			return;
		}
	}
}
