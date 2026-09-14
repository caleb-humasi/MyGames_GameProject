#include "Robot.hpp"
#include "GameSpace.hpp"

Robot::Robot(World& _gameSpace) :
	deltaTime(0.f),
	gameSpace(&_gameSpace),
	robotSprite(_gameSpace.getTexture(Texture::ROBOT)),
	playerPosition(&_gameSpace.getPlayer()->getPosition()),
	desiredPosition({ 0.f,0.f }),
	physicsManager(desiredPosition, 15.f),
	collisionManager(rectEntity, desiredPosition),
	canJump(true),
	isWalking(false),
	jump(false),
animationSelector(robotSprite){
	nameEntity = "E_Robot";
	life = 12;
	rectEntity.size = { 7.f * gb::SCALE, 13 * gb::SCALE };
}

void Robot::start() {
	startSpriteConfiguration();
	AnimationFactory::setRobot(animationSelector);
	collisionManager.addRect(rectEntity);
	timeManager.addTimer(Timer{ sf::seconds(0.15f), sf::seconds(0.f), false });
	timeManager.addTimer(Timer{ sf::seconds(0.3f), sf::seconds(0.f), false });
	desiredPosition = rectEntity.position;
}
void Robot::firstUpdate(float dt) {
	if (timeManager.getTimer(0).active) { robotSprite.setColor(sf::Color::Red); }
	else { robotSprite.setColor(sf::Color(255, 255, 255)); }
	deltaTime = dt;
	animationSelector.update(dt);
	movement(dt);
	jumpAbove();
	if (jump && canJump) { physicsManager.setDeltaY(-2.2f); }
	animate();
}
void Robot::finalUpdate() {
	timeManager.update(deltaTime);
	collision();
	if (collisionManager.getSideIntersection(CollisionManager::Side::BOTTOM) ||
		collisionManager.getSideIntersection(CollisionManager::Side::TOP)) {
		physicsManager.setDeltaY(0.f);
	}
	robotSprite.setPosition(rectEntity.position + rectEntity.size / 2.f);
}
void Robot::render(sf::RenderWindow& window) {
	window.draw(robotSprite);
}
void Robot::startSpriteConfiguration(){
	robotSprite.setTextureRect(sf::IntRect({0,0}, { 11, 13 }));
	robotSprite.setOrigin( robotSprite.getGlobalBounds().size / 2.f);
	robotSprite.setScale({ gb::SCALE, gb::SCALE });
}
void Robot::jumpAbove(){
	uint16_t i(0);
	std::vector<std::pair<Tile*, CollisionManager::Side>>& collisionTiles = collisionManager.getCollisionTiles();
	for (auto& e : collisionTiles){
		if (e.second == CollisionManager::Side::BOTTOM) {
			if (getCenter().x < e.first->getCenter().x && collisionManager.getTile(e.first->getIndex() - 1).isNullTile() &&
				getPosition().x < e.first->getRect().position.x && desiredPosition.x - rectEntity.position.x < 0) {
				jump = true;
				break;
			}
			else if (getCenter().x > e.first->getCenter().x && collisionManager.getTile(e.first->getIndex() + 1).isNullTile() &&
				getPosition().x + rectEntity.size.x < e.first->getRect().position.x + e.first->getRect().size.x && 
				desiredPosition.x - rectEntity.position.x > 0) {
				jump = true;
				break;
			}
			
		}
	}
}
void Robot::movement(float dt){
	jump = collisionManager.getSideIntersection(CollisionManager::Side::LEFT) 
		|| collisionManager.getSideIntersection(CollisionManager::Side::RIGHT);

	canJump = collisionManager.getSideIntersection(CollisionManager::Side::BOTTOM);

	sf::Vector2f deltaDistance = 
		*playerPosition + (sf::Vector2f)gb::player::size / 2.f - (rectEntity.position + rectEntity.size / 2.f);
	isWalking = std::abs(deltaDistance.x) < 50.f * gb::SCALE && std::abs(deltaDistance.y) < 40.f;

	char direction = deltaDistance.x > 0 ? 1 : -1;
	robotSprite.setScale({ gb::SCALE * direction, robotSprite.getScale().y });
	desiredPosition.x = isWalking? rectEntity.position.x + speed * direction * dt * gb::FPS : rectEntity.position.x;
}

void Robot::animate(){
	if (!canJump) { animationSelector.setAnimationID((int)robot::EntityState::JUMP); }
	else if(isWalking) { 
		animationSelector.setAnimationID((int)robot::EntityState::WALKING); 
	}
	else {
		animationSelector.setAnimationID((int)robot::EntityState::IDDLE);
	}
}

void Robot::collision() {
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
