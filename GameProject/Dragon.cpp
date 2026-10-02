#include "Dragon.hpp"
#include "GameSpace.hpp"

Dragon::Dragon(World& _gameSpace) :
	deltaTime(0.f),
	speed(0.55f),
	dashSpeed(speed * 7.5f),
	state(dragon::EntityState::ATTACKING),
	isChasing(true),
	enraged(false),
	onRight(true),
	isDashing(false),
	isAttacking(false),
	positioningItself(true),
	gameSpace(&_gameSpace),
	playerPosition(&gameSpace->getPlayer()->getPosition()),
	collisionManager(rectEntity, desiredPosition),
	mainSprite(gameSpace->getTexture(Texture::BLUE_DRAGON)),
	headSprite(gameSpace->getTexture(Texture::DRAGON_HEAD)),
	dragon_fire(gameSpace->getTexture(Texture::DRAGON_FIRE)){

	rectEntity.size = sf::Vector2f{ 72.f, 10.f };
	//SETTING SPRITE SECTION
	mainSprite.setTextureRect(sf::IntRect({ 0,0 }, { 134, 46 }));
	mainSprite.setOrigin({ mainSprite.getGlobalBounds().size.x / 2.f, mainSprite.getGlobalBounds().size.y / 2.f });

	headSprite.setTextureRect(sf::IntRect({ 0,0 }, {32, 11}));
	headSprite.setOrigin({ headSprite.getGlobalBounds().size.x / 2.f, headSprite.getGlobalBounds().size.y / 2.f });

	dragon_fire.setTextureRect(sf::IntRect({ 0,0 }, { 28,28 }));
	mainSprite.setOrigin({ mainSprite.getGlobalBounds().size.x / 2.f, mainSprite.getGlobalBounds().size.y / 2.f });

	AnimationFactory::setDragon(animManager, mainSprite, headSprite, dragon_fire);
	nameEntity = "E_Dragon";
}

void Dragon::start() {
	life = 48;
	collisionManager.addRect(rectEntity);
	desiredPosition = rectEntity.position;
	timeManager.addTimer(Timer{ sf::seconds(0.15f), sf::seconds(0.f), false });
	timeManager.addTimer(Timer{ sf::seconds(0.3f), sf::seconds(0.f), false });
	timeManager.addTimer(Timer{ sf::seconds(0.075f), sf::seconds(0.f), true });
	timeManager.addTimer(Timer{ sf::seconds(10.f), sf::seconds(0.f), true});
	collisionManager.setActiveCollision(false);
}

void Dragon::firstUpdate(float dt) {
	if (timeManager.getTimer(0).active) { mainSprite.setColor(sf::Color::Red); }
	else { mainSprite.setColor(sf::Color(255, 255, 255)); }
	headSprite.setColor(mainSprite.getColor());
	deltaTime = dt;
	dashing();
	movement();
	animate();
	animManager.update(dt);
	if (!timeManager.getTimer(3).active) {
		state = dragon::EntityState::NONE;
	}
}
void Dragon::finalUpdate() {
	timeManager.update(deltaTime);
	for (Shadow& e : shadows) { timeManager.updateTimer(e.timer, deltaTime); }
	collision();
	mainSprite.setPosition(rectEntity.position + gb::dragon::size / 2.f + sf::Vector2f{ 0, (float)moves[animManager.getAnimSelector(0).getAnimation().getFrame() - 1] });
	headSprite.setPosition(mainSprite.getPosition() + sf::Vector2f(-27.f * mainSprite.getScale().x, -3.5f));
	dragon_fire.setPosition(mainSprite.getPosition() + sf::Vector2f(-57.f * mainSprite.getScale().x, -6.5f));
	headSprite.setScale(mainSprite.getScale());
	dragon_fire.setScale(mainSprite.getScale());
}

void Dragon::render(sf::RenderWindow& window) {
	window.draw(mainSprite);
	if (state != dragon::EntityState::DASHING)
		window.draw(headSprite);
	if (state == dragon::EntityState::ATTACKING && !positioningItself)
		window.draw(dragon_fire);
	for (Shadow& e : shadows) { window.draw(e.sprite); }
}
void Dragon::dashing() {
	sf::Vector2f playerCenter = *playerPosition + gb::player::size / 2.f;
	static std::mt19937 gen(std::random_device{}());
	std::bernoulli_distribution dist(0.5f);

	if (state == dragon::EntityState::DASHING) {
		float yOffSet1 = dist(gen) ? 0.f : -12.f;
		float yOffSet2 = dist(gen) ? 0.f : -8.f;
		if (onRight && !isDashing) {
			rectEntity.position = sf::Vector2f(playerCenter.x, 105) - rectEntity.size / 2.f - sf::Vector2f(175.f, -yOffSet1 - yOffSet2 + 3);
			isDashing = true;
		}
		else if (!onRight && !isDashing) {
			rectEntity.position = sf::Vector2f(playerCenter.x, 105) - rectEntity.size / 2.f + sf::Vector2f(175.f, yOffSet1 + yOffSet2 + 3);
			isDashing = true;
		}
		if (isDashing) {
			if (onRight && (getCenter().x - playerCenter.x > 175.f)) {
				onRight = false;
				isDashing = false;
			}
			else if (!onRight && (getCenter().x - playerCenter.x < -175.f)) {
				onRight = true;
				isDashing = false;
			}
		}
	}
}

void Dragon::movement() {
	sf::Vector2f deltaDistance;
	float direction = (float(onRight) - 0.5f) * 2.f;
	if(state == dragon::EntityState::FLYING)
		deltaDistance = *playerPosition + gb::player::size / 2.f - getCenter();
	else if (state == dragon::EntityState::ATTACKING) {
		deltaDistance = *playerPosition + gb::player::size / 2.f - getCenter() - sf::Vector2f(100 * direction, 12);
	}

	float distance = sqrtf(deltaDistance.x * deltaDistance.x + deltaDistance.y * deltaDistance.y);

	if (distance < 200.f) isChasing = true;
	desiredPosition = rectEntity.position;
	if (state == dragon::EntityState::DASHING) {
		isChasing = false;
		desiredPosition.x += dashSpeed * gb::FPS * deltaTime * direction;
		mainSprite.setScale({ gb::SCALE * (-direction), gb::SCALE});
	}
	else if (state == dragon::EntityState::NONE) {
		isChasing = false;
		desiredPosition.y -= speed * 2 * gb::FPS * deltaTime;
	}

	if (!isChasing) return;
	float cosX = deltaDistance.x / distance, sinX = deltaDistance.y / distance;
	
	if (state == dragon::EntityState::ATTACKING) {
		attacking(distance, direction, sf::Vector2f(cosX, sinX), deltaDistance);
	}
	else {
		desiredPosition = rectEntity.position + sf::Vector2f(cosX, sinX) * speed * deltaTime * gb::FPS;
		mainSprite.setScale({ gb::SCALE * (direction), gb::SCALE });
	}
}

void Dragon::attacking(float distance, float direction, sf::Vector2f normalVector, sf::Vector2f delta){
	isAttacking = true;
	if (positioningItself) {
		desiredPosition = rectEntity.position + normalVector * speed * 3.f * deltaTime * gb::FPS;
		if (distance - 3.f * speed < 2.25f) {
			positioningItself = false;
		}
		mainSprite.setScale({ gb::SCALE * -(delta.x / std::abs(delta.x)), gb::SCALE});
	}
	else {
		sf::Vector2f playerCenter = *playerPosition + gb::player::size / 2.f;
		if (onRight && (getCenter().x - playerCenter.x > 120.f)) {
			onRight = false;
			positioningItself = true;
		}
		else if (!onRight && (getCenter().x - playerCenter.x < -120.f)) {
			onRight = true;
			positioningItself = true;
		}
		else {
			desiredPosition.x += dashSpeed / 1.5f * gb::FPS * deltaTime * direction;
			mainSprite.setScale({ gb::SCALE * (-direction), gb::SCALE });
		}
	}
}
void Dragon::animate() {
	for (int16_t i(0); i < shadows.size(); ++i) {
		if (shadows[i].timer.active == false) {
			shadows.erase(shadows.begin() + i);
			--i;
		}
	}
	if (state == dragon::EntityState::NONE) { animManager.setState(int(dragon::EntityState::FLYING)); }
	else { animManager.setState((int)state); }
	if (state != dragon::EntityState::DASHING) return;

	if (!timeManager.getTimer(2).active) {
		shadows.push_back(Shadow{ mainSprite, Timer({sf::seconds(0.3f), sf::seconds(0), true})});
		shadows.back().sprite.setColor(sf::Color(0, 220, 220, 150));
		timeManager.getTimer(2).active = true;
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