#include "HolyFire.hpp"
#include "GameSpace.hpp"

HolyFire::HolyFire(World& gameSpace, sf::Vector2f respectivePosition) :
	sprite(gameSpace.getTexture(Texture::HOLY_FIRE)),
	animation(0.1f, sf::IntRect({ 0,0 }, { 10,13 }), 2),
	timer(0.f) {
	animation.setSprite(sprite);
	rectEntity = sf::FloatRect(respectivePosition, { 10 * gb::SCALE, 12 * gb::SCALE });
	nameEntity = "S_Holy_Fire";
}

void HolyFire::start() {
	sprite.setScale({ gb::SCALE,gb::SCALE });
	sprite.setPosition(rectEntity.position - sf::Vector2f(0.f, 1.f * gb::SCALE));
}
void HolyFire::firstUpdate(float dt) {
	animation.updateAnim(dt);
	timer += dt;
}
void HolyFire::finalUpdate() {
	annihilateEntity = timer > 2.f;
}
void HolyFire::render(sf::RenderWindow& window) {
	window.draw(sprite);
}
