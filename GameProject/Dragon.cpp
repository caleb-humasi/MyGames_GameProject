#include "Dragon.hpp"
#include "GameSpace.hpp"

Dragon::Dragon(World& _gameSpace) :
	deltaTime(0.f),
	speed(0.55f),
	isMoving(false),
	gameSpace(&_gameSpace),
	playerPosition(&gameSpace->getPlayer()->getPosition()),
	collisionManager(rectEntity, desiredPosition),
	animationSelector(mainSprite),
	mainSprite(gameSpace->getTexture(Texture::CROW)) {

	rectEntity.size = sf::Vector2f{ 5.f, 7.f } *gb::SCALE;
	AnimationFactory::setCrow(animationSelector);
	mainSprite.setTextureRect(sf::IntRect({ 0,11 }, { 10, 9 }));
	mainSprite.setOrigin({ mainSprite.getLocalBounds().size.x / 2.f, mainSprite.getLocalBounds().size.y / 2.f });
	mainSprite.setScale({ gb::SCALE, gb::SCALE });
	nameEntity = "B_Dragon";
}

void Dragon::start() {
	collisionManager.addRect(rectEntity);
	desiredPosition = rectEntity.position;
	timeManager.addTimer(Timer{ sf::seconds(0.15f), sf::seconds(0.f), false });
	timeManager.addTimer(Timer{ sf::seconds(0.3f), sf::seconds(0.f), false });
}

void Dragon::firstUpdate(float dt) {
	if (timeManager.getTimer(0).active) { mainSprite.setColor(sf::Color::Red); }
	else { mainSprite.setColor(sf::Color(255, 255, 255)); }
	deltaTime = dt;
	movement();
	animate();
	animationSelector.update(dt);
}
void Dragon::finalUpdate() {
	timeManager.update(deltaTime);
	collision();
	mainSprite.setPosition(rectEntity.position + sf::Vector2f({ 5.f, 7.f }) / 2.f);
}

void Dragon::render(sf::RenderWindow& window) {
	window.draw(mainSprite);
}

void Dragon::movement() {
	sf::Vector2f deltaDistance = *playerPosition + gb::player::size * gb::SCALE - getCenter();
	float distance = sqrtf(deltaDistance.x * deltaDistance.x + deltaDistance.y * deltaDistance.y);
	if (distance < 40.f) isMoving = true;
	if (!isMoving) return;
	float cosX = deltaDistance.x / distance, sinX = deltaDistance.y / distance;

	desiredPosition = rectEntity.position + sf::Vector2f(cosX, sinX) * speed * deltaTime * gb::FPS;
	if (deltaDistance.x > 0) { mainSprite.setScale({ -gb::SCALE, gb::SCALE }); }
	else if (deltaDistance.x < 0) { mainSprite.setScale({ gb::SCALE, gb::SCALE }); }
}
void Dragon::animate() {
	if (isMoving) {
		animationSelector.setAnimationID(0);
	}
	else {
		animationSelector.setAnimationID(1);
	}
}
void Dragon::collision() {
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