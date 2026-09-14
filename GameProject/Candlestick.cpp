#include "Candlestick.hpp"
#include "GameSpace.hpp"
#include "EntityFactory.hpp"

Candlestick::Candlestick(World& _gameSpace):
	subWeaponTexture(Texture::NULL_TEXTURE),
	isHeart(true),
	candle_animation(0.15f, sf::IntRect({ 0,0 }, { 8, 14 }), 2),
	mainSprite(_gameSpace.getTexture(Texture::CANDLESTICK)),
	entities(&_gameSpace.getEntities()),
	gameSpace(&_gameSpace){
	rectEntity = sf::FloatRect({ 0,0 }, { 8.f * gb::SCALE, 14.f * gb::SCALE });
	mainSprite.setScale({ gb::SCALE, gb::SCALE });
}

void Candlestick::start() {
	mainSprite.setPosition(rectEntity.position);
	candle_animation.setSprite(mainSprite);
}

void Candlestick::firstUpdate(float dt){
	candle_animation.updateAnim(dt);
}
void Candlestick::finalUpdate() {
	collision();
}
void Candlestick::render(sf::RenderWindow& window) {
	window.draw(mainSprite);
}

void Candlestick::collision() {
	for (auto& e : *entities) {
		if (e->getName() == "Player" && rectEntity.findIntersection(*e->getCollisionManager()->getRects()[0])) {
			annihilateEntity = true;
			if(isHeart)
				EntityFactory::invokeHeart(*gameSpace, getCenter() - gb::candlestick::size / 2.f * gb::SCALE);
			else
				EntityFactory::invokeSubWeaponItem(*gameSpace, getCenter() - gb::candlestick::size / 2.f * gb::SCALE, subWeaponTexture);
			gameSpace->playBreakSound();
			return;
		}
	}
}