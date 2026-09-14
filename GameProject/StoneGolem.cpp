#include "StoneGolem.hpp"
#include "GameSpace.hpp"

StoneGolem::StoneGolem(World& _gameSpace) :
	isAttacking(false),
	oneShoot(true),
	attack(false),
	isRight(true),
	direction(-1),
	deltaTime(0.f),
	gameSpace(&_gameSpace),
	playerPosition(&gameSpace->getPlayer()->getPosition()),
	physicsManager(desiredPosition, 3.75f),
	collisionManager(rectEntity, desiredPosition),
	animationSelector(mainSprite),
	mainSprite(gameSpace->getTexture(Texture::STONE_GOLEM)) {
	life = 24;
	rectEntity.size = gb::stone_golem::size * gb::SCALE;
	AnimationFactory::setStoneGolem(animationSelector);
	mainSprite.setTextureRect(sf::IntRect({ 0,0 }, { 16, 16 }));
	mainSprite.setOrigin({ mainSprite.getLocalBounds().size.x / 2.f, mainSprite.getLocalBounds().size.y / 2.f });
	mainSprite.setScale({ gb::SCALE, gb::SCALE });
	nameEntity = "E_StoneGolem";
}

void StoneGolem::start() {
	angleToShoot = sf::degrees(135.f);
	collisionManager.addRect(rectEntity);
	desiredPosition = rectEntity.position;
	timeManager.addTimer(Timer{ sf::seconds(0.15f), sf::seconds(0.f), false });
	timeManager.addTimer(Timer{ sf::seconds(0.3f), sf::seconds(0.f), false });
	timeManager.addTimer(Timer{ sf::seconds(2.f), sf::seconds(0.f), true });
}

void StoneGolem::firstUpdate(float dt) {
	if (timeManager.getTimer(0).active) { mainSprite.setColor(sf::Color::Red); }
	else { mainSprite.setColor(sf::Color(255, 255, 255)); }
	deltaTime = dt;
	animation();
	animationSelector.update(dt);
	throwStone();
	direction = (playerPosition->x + gb::player::size.x - getCenter().x > 0) - (playerPosition->x + gb::player::size.x - getCenter().x < 0);
	isRight = direction > 0 ? true : direction < 0 ? false : direction;
	angleToShoot = sf::degrees(isRight? -60.f : -120.f);
}
void StoneGolem::finalUpdate() {
	if (collisionManager.getSideIntersection(CollisionManager::Side::BOTTOM)) { physicsManager.setDeltaY(0.f); }
	timeManager.update(deltaTime);
	collision();
	mainSprite.setPosition(getCenter());
	mainSprite.setScale({ isRight? -gb::SCALE : gb::SCALE, gb::SCALE});
}

void StoneGolem::render(sf::RenderWindow& window) {
	window.draw(mainSprite);
}

void StoneGolem::throwStone(){
	if (oneShoot && attack) {
		EntityFactory::invokeStone(*gameSpace, getCenter(), angleToShoot);
		oneShoot = false;
	}
}

void StoneGolem::animation(){
	if (!isAttacking && !timeManager.getTimer(2).active) {
		isAttacking = true;
		timeManager.getTimer(2).active = true;
	}
	else if (isAttacking && !animationSelector.getInAction()) {
		isAttacking = false;
	}
	if (!isAttacking) {
		animationSelector.setAnimationID(0);
		attack = false;
		oneShoot = true;
	}
	else {
		animationSelector.setAnimationID(1);
	}
	if (isAttacking && animationSelector.getAnimation().getFrame() == 2) {
		attack = true;
	}
}

void StoneGolem::collision() {
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