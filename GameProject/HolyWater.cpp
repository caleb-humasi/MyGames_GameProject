#include "HolyWater.hpp"
#include "GameSpace.hpp"
HolyWater::HolyWater(World& _gameSpace, const sf::Vector2f& _playerPosition, bool _isRight) :
	spawnFire(true),
	spriteHolyWater(_gameSpace.getTexture(Texture::HOLY_WATER)),
	playerPosition(&_playerPosition),
	gameSpace(&_gameSpace),
	physicsManager(desiredPosition, 30.f),
	collisionManager(rectEntity, desiredPosition),
	timer(0.f),
	isRight(_isRight),
	deltaTime(0.f),
	velocity(1.5f),
	box_tiles(&_gameSpace.getTiles()){
	collisionManager.setTiles(*box_tiles);
	nameEntity = "Holy_Water";
}
void HolyWater::start() {
	startGeneralConfiguration();
	physicsManager.setDeltaY(-1.f);
	spriteHolyWater.setScale({ gb::SCALE * (isRight ? 1.f : -1.f), gb::SCALE });
	physicsManager.setEntityOwnerName(nameEntity);
}

void HolyWater::firstUpdate(float dt) {
	char direction = isRight ? 1.f : -1.f;
	desiredPosition.x += velocity * dt * gb::FPS * (float)direction;

	timer += dt;
	annihilateEntity = timer > 2.5f;
	deltaTime = dt;	
}

void HolyWater::finalUpdate() {
	if(collisionManager.getSideIntersection(CollisionManager::Side::LEFT) ||
		collisionManager.getSideIntersection(CollisionManager::Side::RIGHT)) { velocity = 0.f; }

	if (collisionManager.getSideIntersection(CollisionManager::Side::BOTTOM)) {
		gameSpace->playBreakGlass();
		EntityFactory::invokeFire(*gameSpace, rectEntity.position + 
		sf::Vector2f(rectEntity.size.x / 2.f - 10.f * gb::SCALE / 2.f, rectEntity.size.y - 12.f * gb::SCALE));
		annihilateEntity = true;
		timer = 2.5f;
	}
	rectEntity.position.y = desiredPosition.y;
	spriteHolyWater.setPosition(rectEntity.position + rectEntity.size / 2.f);
}
void HolyWater::render(sf::RenderWindow& window) {
	window.draw(spriteHolyWater);
}

void HolyWater::startGeneralConfiguration() {
	spriteHolyWater.setOrigin(spriteHolyWater.getLocalBounds().size / 2.f);
	spriteHolyWater.setScale({ gb::SCALE, gb::SCALE });
	spriteHolyWater.setPosition(*playerPosition);

	rectEntity.size = spriteHolyWater.getGlobalBounds().size;
	rectEntity.position = *playerPosition - rectEntity.size / 2.f + sf::Vector2f(3 * gb::SCALE, 7 * gb::SCALE) / 2.f;
	desiredPosition = rectEntity.position;
}