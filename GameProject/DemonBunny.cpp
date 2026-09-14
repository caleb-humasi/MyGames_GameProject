#include "DemonBunny.hpp"
#include "GameSpace.hpp"

DemonBunny::DemonBunny(World& _gameSpace) :
	agressive(false),
	isAttacking(false),
	oneShoot(true),
	canJump(false),
	jump(false),
	isRight(true),
	direction(-1),
	speed(1.25f),
	deltaTime(0.f),
	gameSpace(&_gameSpace),
	playerPosition(&gameSpace->getPlayer()->getPosition()),
	physicsManager(desiredPosition, 4.f),
	collisionManager(rectEntity, desiredPosition),
	mainSprite(gameSpace->getTexture(Texture::DEMON_BUNNY)) {
	life = 12;
	rectEntity.size = sf::Vector2f{ 8.f, 10.f } * gb::SCALE;
	mainSprite.setTextureRect(sf::IntRect({ 0,0 }, { 10, 10 }));
	mainSprite.setOrigin({ mainSprite.getLocalBounds().size.x / 2.f, mainSprite.getLocalBounds().size.y / 2.f });
	mainSprite.setScale({ gb::SCALE, gb::SCALE });
	nameEntity = "E_DemonBunny";
}

void DemonBunny::start() {
	collisionManager.addRect(rectEntity);
	desiredPosition = rectEntity.position;
	timeManager.addTimer(Timer{ sf::seconds(0.15f), sf::seconds(0.f), false });
	timeManager.addTimer(Timer{ sf::seconds(0.3f), sf::seconds(0.f), false });
	timeManager.addTimer(Timer{ sf::seconds(1.25f), sf::seconds(0.f), true });
}

void DemonBunny::firstUpdate(float dt) {
	if (collisionManager.getSideIntersection(CollisionManager::Side::BOTTOM) ||
		collisionManager.getSideIntersection(CollisionManager::Side::TOP)) {
		physicsManager.setDeltaY(0.f);
	}
	if (timeManager.getTimer(0).active) { mainSprite.setColor(sf::Color::Red); }
	else { mainSprite.setColor(sf::Color(255, 255, 255)); }
	deltaTime = dt;
	canJump = collisionManager.getSideIntersection(CollisionManager::Side::BOTTOM);
	sf::Vector2f deltaDistance = *playerPosition + gb::player::size * gb::SCALE - getCenter();
	float distance = sqrtf(deltaDistance.x * deltaDistance.x + deltaDistance.y * deltaDistance.y);
	if (distance < 50.f) { agressive = true; }
	if(agressive){
		jumpUpdate();
		if (canJump) direction = (playerPosition->x + gb::player::size.x / 2.f - getCenter().x > 0) - (playerPosition->x + gb::player::size.x / 2.f - getCenter().x < 0);
	}
	animation();
	isRight = direction > 0 ? true : direction < 0 ? false : direction;
}
void DemonBunny::finalUpdate() {
	timeManager.update(deltaTime);
	collision();
	mainSprite.setPosition(getCenter());
	mainSprite.setScale({ isRight ? -gb::SCALE : gb::SCALE, gb::SCALE });
}

void DemonBunny::render(sf::RenderWindow& window) {
	window.draw(mainSprite);
}

void DemonBunny::jumpUpdate() {
	if (!timeManager.getTimer(2).active) {
		jump = true;
	}
	if (jump && canJump) {
		physicsManager.setDeltaY(-2.3f);
		timeManager.getTimer(2).active = true;
		jump = false;
	}
	if (!canJump) {
		desiredPosition.x += speed * gb::FPS * deltaTime * (float)direction;
	}
}

void DemonBunny::animation() {
	if (canJump) {
		mainSprite.setTextureRect(sf::IntRect({ 0, 0 },{ 10, 10 }));
	}
	else if (physicsManager.getDeltaDistance() < 0) {
		mainSprite.setTextureRect(sf::IntRect({ 10, 0 }, { 10, 10 }));
	}
	else {
		mainSprite.setTextureRect(sf::IntRect({ 20, 0 }, { 10, 10 }));
	}
}

void DemonBunny::collision() {
	std::vector<std::shared_ptr<Entity>>* entities = &gameSpace->getEntities();
	for (auto& e : *entities) {
		if ((e->getName()[0] == 'S' && rectEntity.findIntersection(e->getRect())
			|| e->getName() == "Player" && collisionManager.collisionEntity(*e->getCollisionManager()))
			&& !timeManager.getTimer(1).active) {
			life -= 6;
			timeManager.getTimer(0).active = true;
			timeManager.getTimer(1).active = true;

			if (life <= 0) {
				annihilateEntity = true;
				gameSpace = nullptr;
				playerPosition = nullptr;
			}
		}
	}
}