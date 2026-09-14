#include "FlyingEye.hpp"
#include "GameSpace.hpp"

FlyingEye::FlyingEye(World& _gameSpace) :
	passedTime(0.f),
	angle(0.f),
	deltaTime(0.f),
	speedAngle(0.075f),
	speed(0.6f),
	accelerationTail(0.050f),
	initPosTail(60.f),
	finalPosTail(120.f),
	isMoving(false),
	gameSpace(&_gameSpace),
	playerPosition(&gameSpace->getPlayer()->getPosition()),
	collisionManager(rectEntity, desiredPosition),
	animationSelector(mainSprite),
	mainSprite(gameSpace->getTexture(Texture::FLYING_EYE)) {

	rectEntity.size = sf::Vector2f{ 6.f, 6.f } * gb::SCALE;

	AnimationFactory::setFlyingEye(animationSelector);
	mainSprite.setTextureRect(sf::IntRect({ 6,0 }, { 6, 6 }));
	mainSprite.setOrigin({ 6.f / 2.f, 6.f / 2.f });
	mainSprite.setScale({ gb::SCALE, gb::SCALE });
	nameEntity = "E_FlyingEye";
	sf::Sprite tailPart(mainSprite);
	tailPart.setTextureRect(sf::IntRect({ 12,1 }, { 4, 4 }));
	tailPart.setOrigin({ 2.f,2.f });
	for (uint8_t i(1); i < 5; ++i){
		tailParts.push_back(TailPart({ 0.f, 0.f, 0.f, 0.f, 1, tailPart, getCenter() + sf::Vector2f(0, gb::SCALE * (radiusEye + 2.f *(float)i))}));
		tailParts.back().sprite.setScale(sf::Vector2f{gb::SCALE,gb::SCALE} * (1.f / powf(1.3f,((float)(i-1)))) );
		tailParts.back().angle = 0.f;
	}
	tailParts[0].angle = (float)convertToPiDegrees(initPosTail);
	tailParts[0].speed = 0.f;
	std::cout << speed << '\n';
}

void FlyingEye::start() {
	collisionManager.addRect(rectEntity);
	desiredPosition = rectEntity.position;
	timeManager.addTimer(Timer{ sf::seconds(0.15f), sf::seconds(0.f), false });
	timeManager.addTimer(Timer{ sf::seconds(0.3f), sf::seconds(0.f), false });
	collisionManager.setActiveCollision(false);
}

void FlyingEye::firstUpdate(float dt) {
	passedTime += dt;
	if (timeManager.getTimer(0).active) { mainSprite.setColor(sf::Color::Red); }
	else { mainSprite.setColor(sf::Color(255, 255, 255)); }
	deltaTime = dt;
	movement();
	animate();
	updateTail();
	animationSelector.update(dt);
}
void FlyingEye::finalUpdate() {
	timeManager.update(deltaTime);
	collision();
	mainSprite.setPosition(getCenter());
	tailParts[0].position = getCenter() + sf::Vector2f(cosf(tailParts[0].angle), sinf(tailParts[0].angle)) * (radiusEye + 2.25f) * gb::SCALE;
	tailParts[0].sprite.setPosition(tailParts[0].position);
	for (uint8_t i(1); i < tailParts.size(); ++i) {
		sf::Vector2f posToCenter = sf::Vector2f(cosf(tailParts[i].angle), sinf(tailParts[i].angle)) * (radiusEye + 0.25f + 2.f * (float)(i + 1)) * gb::SCALE;
		tailParts[i].position = getCenter() + sf::Vector2f(cosf(tailParts[i].angle), sinf(tailParts[i].angle)) * (radiusEye + 0.25f + 2.f * (float)(i + 1)) * gb::SCALE;
		tailParts[i].sprite.setPosition(tailParts[i].position);
	}
}

void FlyingEye::render(sf::RenderWindow& window) {
	for (uint8_t i(0); i < tailParts.size(); ++i) {
		window.draw(tailParts[i].sprite);
	}
	window.draw(mainSprite);
}

void FlyingEye::updateTail(){
	TailPart& tailPart = tailParts[0];
	float initPosPiDegrees = convertToPiDegrees(initPosTail);
	float finalPosPiDegrees = convertToPiDegrees(finalPosTail);
	float tailDelay = 0.03f;
	if (tailPart.angle > finalPosPiDegrees &&
		tailPart.speed * tailPart.direction > 0.f 
		&& finalPosPiDegrees + tailPart.speed > finalPosPiDegrees) {
		tailPart.direction = -tailPart.direction;
		passedTime = 0.f;
	}
	else if (tailPart.angle < initPosPiDegrees && tailPart.speed * tailPart.direction > 0.f 
		&& initPosPiDegrees + tailPart.speed < initPosPiDegrees) {
		tailPart.direction = -tailPart.direction;
		passedTime = 0.f;
	}

	tailPart.speed += tailPart.direction * accelerationTail * gb::FPS * deltaTime;
	if (abs(tailPart.speed) > 0.015f * passedTime * gb::FPS && tailPart.speed * tailPart.direction > 0.f) {
		tailPart.speed = 0.015f * passedTime * tailPart.direction * gb::FPS;
	}
	tailPart.angle += tailPart.speed * deltaTime * gb::FPS / ((radiusEye + 2.f) * gb::SCALE);

	if (tailPart.timer >= tailDelay) {
		tailPart.angles.erase(tailPart.angles.begin());
	}
	else { tailPart.timer += deltaTime; }
	tailPart.angles.push_back(tailPart.angle);
	for (uint8_t i(1); i < 4; ++i) {
		tailParts[i].angles.push_back(tailParts[i].angle);
		if (tailParts[i - 1].timer >= tailDelay) {
			tailParts[i].angle = tailParts[i - 1].angles[0];
			if (tailParts[i].timer >= tailDelay) {
				tailParts[i].angles.erase(tailParts[i].angles.begin());
			}
			else { tailParts[i].timer += deltaTime; }
		}
	}

}

void FlyingEye::movement() {
	sf::Vector2f deltaDistance = *playerPosition + gb::player::size * gb::SCALE / 2.f - getCenter();
	sf::Vector2f direcaoOlho = { cosf(angle), sinf(angle) };
	float distance = sqrtf(deltaDistance.x * deltaDistance.x + deltaDistance.y * deltaDistance.y);

	if (distance < 50.f) isMoving = true;
	if (!isMoving) return;

	sf::Vector2f nDelta = deltaDistance * (distance > 0 ? 1 / distance : 0);

	float sentido = (direcaoOlho.x * nDelta.y) - (direcaoOlho.y * nDelta.x);
	angle += speedAngle * deltaTime * gb::FPS * sentido;
	desiredPosition = rectEntity.position + speed * sf::Vector2f(cosf(angle), sinf(angle)) * deltaTime * gb::FPS;
}
void FlyingEye::animate() {
	if (isMoving) {
		animationSelector.setAnimationID(0);
	}
	else {
		animationSelector.setAnimationID(1);
	}

}
void FlyingEye::collision() {
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
			}
		}
	}
}