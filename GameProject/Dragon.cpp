#include "Dragon.hpp"
#include "GameSpace.hpp"

Dragon::Dragon(World& _gameSpace) :
	deltaTime(0.f),
	speed(0.55f),
	isMoving(true),
	gameSpace(&_gameSpace),
	playerPosition(&gameSpace->getPlayer()->getPosition()),
	collisionManager(rectEntity, desiredPosition),
	animationSelector(mainSprite),
	mainSprite(gameSpace->getTexture(Texture::BLUE_DRAGON)),
	headSprite(gameSpace->getTexture(Texture::HEAD_DRAGON)){

	rectEntity.size = sf::Vector2f{ 72.f, 10.f };
	AnimationFactory::setDragon(animationSelector);
	mainSprite.setTextureRect(sf::IntRect({ 0,0 }, { 134, 46 }));
	mainSprite.setOrigin({ mainSprite.getGlobalBounds().size.x / 2.f, mainSprite.getGlobalBounds().size.y / 2.f });
	mainSprite.setScale({ gb::SCALE, gb::SCALE });
	headSprite.setTextureRect(sf::IntRect({ 0,0 }, {32, 11}));
	headSprite.setOrigin({ headSprite.getGlobalBounds().size.x / 2.f, headSprite.getGlobalBounds().size.y / 2.f });
	nameEntity = "B_Dragon";
}

void Dragon::start() {
	life = 48;
	collisionManager.addRect(rectEntity);
	desiredPosition = rectEntity.position;
	timeManager.addTimer(Timer{ sf::seconds(0.15f), sf::seconds(0.f), false });
	timeManager.addTimer(Timer{ sf::seconds(0.3f), sf::seconds(0.f), false });
	collisionManager.setActiveCollision(false);
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
	mainSprite.setPosition(rectEntity.position + gb::dragon::size / 2.f + sf::Vector2f{ 0, (float)moves[animationSelector.getAnimation().getFrame() - 1] });
	headSprite.setPosition(mainSprite.getPosition() + sf::Vector2f(-27.f * mainSprite.getScale().x, -3.5f));
	headSprite.setScale(mainSprite.getScale());
}

void Dragon::render(sf::RenderWindow& window) {
	window.draw(mainSprite);
	window.draw(headSprite);
}

void Dragon::movement() {
	sf::Vector2f deltaDistance = *playerPosition + gb::player::size * gb::SCALE / 2.f - getCenter();
	float distance = sqrtf(deltaDistance.x * deltaDistance.x + deltaDistance.y * deltaDistance.y);
	if (distance < 200.f) isMoving = true;
	if (!isMoving) return;
	float cosX = deltaDistance.x / distance, sinX = deltaDistance.y / distance;

	desiredPosition = rectEntity.position + sf::Vector2f(cosX, sinX) * speed * deltaTime * gb::FPS;
	if (deltaDistance.x > 0) { mainSprite.setScale({ -gb::SCALE, gb::SCALE }); }
	else if (deltaDistance.x < 0) { mainSprite.setScale({ gb::SCALE, gb::SCALE }); }
}
void Dragon::animate() {
	animationSelector.setAnimationID(0);
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