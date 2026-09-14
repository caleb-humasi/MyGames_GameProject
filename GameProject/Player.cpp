#include "Player.hpp"
#include "SubWeapon_Manager.hpp"
#include "GameSpace.hpp"

Player::Player(World& _gameSpace, sf::View& _view):
	rightKnockback(false),
	isAttacking(false),
	isThrowingSubWeapon(false),
	isInvencible(false),
	isSquat(false),
	p_deltaTime(0.f),
	life(maxLife),
	accelerationY(0),
	camera(_view),
	gameSpace(&_gameSpace),
	view(&_view),
	mainSprite(_gameSpace.getTexture(Texture::PLAYER)),
	whipSprite(_gameSpace.getTexture(Texture::WHIP)),
	bar(_gameSpace.getTexture(Texture::BAR)),
	life_bar(_gameSpace.getTexture(Texture::LIFE_BAR)),
	whip(gameSpace->getSoundBuffer(Sound::PLAYER_ATTACK)),
	damaged(gameSpace->getSoundBuffer(Sound::PLAYER_DAMAGED)),
	subWeapon_Manager(rectEntity, mainSprite, _gameSpace),
	keyManager({
		ButtonManager<(int)Button::SIZE>::Button{sf::Keyboard::Key::L,     false},
		ButtonManager<(int)Button::SIZE>::Button{sf::Keyboard::Key::Space, false},
		ButtonManager<(int)Button::SIZE>::Button{sf::Keyboard::Key::K,     false}
	}),
	collisionManager(rectEntity, desiredPosition),
	physicsManager(desiredPosition, 5.f),
	stairManager(gameSpace->getStairs(), rectEntity){
	nameEntity = "Player";
	physicsManager.setEntityOwnerName(nameEntity);
	startSpriteConfiguration();
	AnimationFactory::setPlayer(animationManager, mainSprite, whipSprite);
	whip_rect = sf::FloatRect({ 0.f, 0.f }, { 17.f * gb::SCALE, 3.f * gb::SCALE });
}

void Player::start() {
	camera.setCameraLimit({0.f,0.f},{10000.f,152.f});
	camera.setCameraMode(Camera::HORIZONTAL);
	timeManager.addTimer(Timer{ sf::seconds(0.5f), sf::seconds(0.f), false });
	timeManager.addTimer(Timer{ sf::seconds(0.1f), sf::seconds(0.f), false });
	collisionManager.addRect(whip_rect);
	stairManager.setIntersectedTiles(collisionManager.getIntersectedTiles());
}

void Player::firstUpdate(float deltaTime) {
	p_deltaTime = deltaTime;
	damagedState();
	squat();
	movement(deltaTime);
	attack();
	upStairs();
	animationManager.update(deltaTime);
	updateTimers(deltaTime);
}
void Player::finalUpdate(){
	updatePlayerState();
	collisionWithEntities();

	float y1 = isSquat ? -6.f * gb::SCALE : 0.f;
	float y2 = isSquat ? 2.f * gb::SCALE : 0.f;

	mainSprite.setPosition(rectEntity.position + sf::Vector2f(3.f * gb::SCALE, 14.f * gb::SCALE) / 2.f + sf::Vector2f(0.f, y1));
	whipSprite.setPosition(mainSprite.getPosition() + sf::Vector2f(0,y2));
	whipSprite.setScale(mainSprite.getScale());
	life_bar.setScale({gb::SCALE, -gb::SCALE * (static_cast<float>(life) / static_cast<float>(maxLife))});
	timeManager.update(p_deltaTime);
	updateWhipRect();

	if (rectEntity.position.y > camera.getBottomRight().y) life = 0;
	if (life <= 0) {
		annihilateEntity = true;
	}
	camera.update(getCenter() + sf::Vector2f(0, y1) / 2.f);
	life_bar.setPosition(life_barPosition + view->getCenter() - view->getSize() / 2.f);
	bar.setPosition(barPosition + view->getCenter() - view->getSize() / 2.f);
}
void Player::render(sf::RenderWindow& window) {
	window.draw(mainSprite);
	if(isAttacking && !isInvencible) window.draw(whipSprite);
	window.draw(bar);
	window.draw(life_bar);
}

void Player::startSpriteConfiguration(){
	sf::IntRect rect = sf::IntRect({ 0, 0 }, { 19, 14 });
	mainSprite.setTextureRect(rect);
	mainSprite.setOrigin({ mainSprite.getLocalBounds().size.x / 2.f, mainSprite.getLocalBounds().size.y / 2.f });
	mainSprite.setScale({ gb::SCALE, gb::SCALE });

	sf::IntRect rect1 = sf::IntRect({ 0,0 }, {43,14});
	whipSprite.setTextureRect(rect1);
	whipSprite.setOrigin({ whipSprite.getLocalBounds().size.x / 2.f, whipSprite.getLocalBounds().size.y / 2.f });
	whipSprite.setScale({ gb::SCALE, gb::SCALE });
	whipSprite.setPosition({ 15.f, 40.f });

	rectEntity = sf::FloatRect({20.f, 50.f}, {3.f * gb::SCALE, 14.f * gb::SCALE});

	bar.setScale({ gb::SCALE,gb::SCALE });
	bar.setPosition({ 5.f, 15.f });
	barPosition = bar.getPosition();
	life_bar.setScale({ 1, -1 });
	life_bar.setPosition({ 
		bar.getPosition().x + bar.getGlobalBounds().size.x / 2.f - life_bar.getGlobalBounds().size.x / 2.f,
	bar.getPosition().y + bar.getGlobalBounds().size.y - 3.f * gb::SCALE});
	life_barPosition = life_bar.getPosition();
}

void Player::squat() {
	if (isAttacking || isThrowingSubWeapon || isInvencible) return;
	if (collisionManager.getSideIntersection(CollisionManager::Side::BOTTOM) && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
		if (!isSquat) {
			rectEntity.position.y += 6.f;
		}
		animationManager.setState((int)player::EntityState::SQUAT);
		rectEntity.size.y = 8.f;
		isSquat = true;
	}
	else {
		if (isSquat) {
			rectEntity.position.y -= 6.f;
		}
		isSquat = false;
		rectEntity.size.y = 14.f;
	}
}

void Player::movement(float deltaTime){
	if (isInvencible) { return; }
	sf::Vector2f nextPos = rectEntity.position;
	const float deltaX = 0.95f * deltaTime * gb::FPS;
	char direction = 0;
	bool isGrounded = collisionManager.getSideIntersection(CollisionManager::Side::BOTTOM);

	if (!isSquat && isGrounded && keyManager.isButtonDown((int)Button::JUMP)) {
		physicsManager.setDeltaY(-2.75f); 
		stairManager.authorizeManager(false);
	}
	
	if (!isAttacking && !isThrowingSubWeapon && !isSquat || !isGrounded) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) { ++direction; }
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) { --direction; }
		nextPos.x += deltaX * direction;
	}
	desiredPosition = nextPos;
	if (isAttacking || isThrowingSubWeapon || isSquat) return;
	updatePlayerView(direction, isGrounded);
}

void Player::updatePlayerView(char direction, bool isGrounded){
	mainSprite.setScale({ (direction != 0 ? gb::SCALE * direction : mainSprite.getScale().x), gb::SCALE });

	if (!isGrounded) {
		animationManager.setState((int)player::EntityState::JUMPING);
		return;
	}
	direction != 0 ? animationManager.setState((int)player::EntityState::WALKING) :
		animationManager.setState((int)player::EntityState::IDDLE);
}

void Player::attack(){
	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num1)) subWeapon_Manager.setSubWeapon(SubWeapon_Manager::Weapon::KNIFE);
	//else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num2)) subWeapon_Manager.setSubWeapon(SubWeapon_Manager::Weapon::AXE);
	//else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num3)) subWeapon_Manager.setSubWeapon(SubWeapon_Manager::Weapon::CROSS);
	//else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num4)) subWeapon_Manager.setSubWeapon(SubWeapon_Manager::Weapon::HOLY_WATER);
	
	if (isInvencible) return;
	if ((isAttacking || isThrowingSubWeapon) && !animationManager.getAnimSelector((int)player::AnimLayer::BODY).getInAction()) {
		animationManager.setState((int)player::EntityState::WALKING);
		isAttacking = false;
		isThrowingSubWeapon = false;
		return;
	}
	if (isThrowingSubWeapon) return;
	if (keyManager.isButtonDown((int)Button::ATTACK)) {
		if (!isAttacking && !isSquat) {
			whip.play();
			animationManager.setState((int)player::EntityState::ATTACKING);
			isAttacking = true;
		}
		else if (!isAttacking && isSquat) {
			whip.play();
			animationManager.setState((int)player::EntityState::SQUAT_ATTACK);
			isAttacking = true;
		}
		
	}
	if (isAttacking) return;
	if (subWeapon_Manager.subWeapon == SubWeapon_Manager::Weapon::NOTHING) return;

	if (keyManager.isButtonDown((int)Button::THROW_SUBWEAPON)) {
		if (!isThrowingSubWeapon && !isSquat && subWeapon_Manager.throwSubWeapon()) {
			animationManager.setState((int)player::EntityState::THROWING_SUBWEAPON);
			isThrowingSubWeapon = true;
		}
		else if (!isThrowingSubWeapon && isSquat && subWeapon_Manager.throwSubWeapon()) {
			animationManager.setState((int)player::EntityState::SQUAT_THROWING_SUBWEAPON);
			isThrowingSubWeapon = true;
		}
	}
}

void Player::upStairs(){
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) && !isInvencible) {
		stairManager.authorizeManager(true);
	}
}

void Player::updatePlayerState(){
	if (stairManager.update()) {
		physicsManager.setActivePhysics(false);
		collisionManager.setActiveCollision(false);
		collisionManager.setSideIntersection(CollisionManager::Side::BOTTOM, true);
	}
	else {
		physicsManager.setActivePhysics(true);
		collisionManager.setActiveCollision(true);
		stairManager.authorizeManager(false);
	}
	if (collisionManager.getSideIntersection(CollisionManager::Side::BOTTOM) ||
		collisionManager.getSideIntersection(CollisionManager::Side::TOP)) {
		physicsManager.setDeltaY(0.f);
	}
}

void Player::updateWhipRect() {
	whip_rect.size = (isAttacking &&
		animationManager.getAnimSelector((int)player::AnimLayer::BODY).getAnimation().getFrame() >= 4)
		? sf::Vector2f(17.f * gb::SCALE, 3 * gb::SCALE) : sf::Vector2f(0.f, 0.f);
	whip_rect.position = rectEntity.position +
		sf::Vector2f(mainSprite.getScale().x > 0 ? 6.f * gb::SCALE : -whip_rect.size.x - 3 * gb::SCALE, 3 * gb::SCALE);
}

void Player::damagedState() {
	if (isInvencible) {
		stairManager.authorizeManager(false);
		animationManager.setState((int)player::EntityState::DAMAGED);
		char direction = rightKnockback ? 1 : -1;
		desiredPosition.x += p_deltaTime * gb::FPS * (float)direction;
	}
}

void Player::updateTimers(float dt) {
	isInvencible = timeManager.getTimer(0).active;
	timeManager.getTimer(1).active = !timeManager.getTimer(1).active && isInvencible ? true : false;
	if (timeManager.getTimer(1).active) {
		if (timeManager.getTimer(1).passedTime < sf::seconds(0.05f)) {
			mainSprite.setColor(sf::Color(255, 0, 0));
		}
		else {
			mainSprite.setColor(sf::Color(255, 255, 255));
		}
	}
	if (!isInvencible) { mainSprite.setColor(sf::Color(255, 255, 255)); }
}

void Player::collisionWithEntities() {
	if (isInvencible) return;
	std::vector<std::shared_ptr<Entity>>* entities = &gameSpace->getEntities();
	for (auto& e : *entities) {
		if (e->getCollisionManager() != nullptr && collisionManager.collisionEntity(*e->getCollisionManager())) {
			if (e->getName()[0] == 'E') {
				rightKnockback = mainSprite.getPosition().x > e->getCenter().x;
				mainSprite.setScale({ gb::SCALE * (rightKnockback ? -1.f : 1.f), gb::SCALE });
				physicsManager.setDeltaY(-2.f);
				life -= 10;
				timeManager.getTimer(0).active = true;
				timeManager.getTimer(1).active = true;
				damaged.play();
				if (life <= 0) {
					life = 0;
					//annihilateEntity = true;
				}
				break;
			}
			if (e->getName() == "Heart") {
				subWeapon_Manager.hearts += 1;
			} 
			else if (e->getName() == "SubWeaponItem") {
				subWeapon_Manager.setSubWeapon((SubWeapon_Manager::Weapon)((int)e->as<SubWeaponItem>()->getTexture() - 2));
			}
		}
		if (rectEntity.findIntersection(e->getRect()) && e->getName()[0] == 'E') {
			rightKnockback = mainSprite.getPosition().x > e->getCenter().x;
			mainSprite.setScale({ gb::SCALE * (rightKnockback ? -1.f : 1.f), gb::SCALE });
			physicsManager.setDeltaY(-2.25f);
			life -= 10;
			timeManager.getTimer(0).active = true;
			timeManager.getTimer(1).active = true;
			damaged.play();
			if (life <= 0) {
				life = 0;
				//annihilateEntity = true;
			}
			break;
		}
	}
}