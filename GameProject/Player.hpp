#pragma once
#include "Entity.hpp"
#include "AnimationFactory.hpp"
#include "KeyManager.hpp"
#include "Collision.hpp"
#include "PhysicsManager.hpp"
#include "SubWeapon_Manager.hpp"
#include "StairManager.hpp"
#include "GameSpace.hpp"
#include "Textures.hpp"
#include "Time.hpp"
#include "Camera.hpp"

//class SubWeaponItem;
class Player : public Entity{
protected:
	enum class Button {
		ATTACK,
		JUMP,
		THROW_SUBWEAPON,
		SIZE
	};
public:
	Player(World& gameSpace, sf::View&);

	void start() final;
	void firstUpdate(float deltaTime) final;
	void finalUpdate() final;
	void render(sf::RenderWindow&) final;

	void startSpriteConfiguration();

	const sf::Vector2f& getPosition() const final { return rectEntity.position; }
	sf::Vector2f getCenter() final { return rectEntity.position + rectEntity.size / 2.f; }
	sf::Vector2f getCameraSize() { return camera.getSize(); }

	CollisionManager* getCollisionManager() final { return &collisionManager; }
	PhysicsManager* getPhysicsManager() final { return &physicsManager; }
	const Camera& getCamera() const { return camera; }
private:
	bool rightKnockback;
	bool isAttacking;
	bool isThrowingSubWeapon;
	bool isInvencible;
	bool isSquat;
	float accelerationY;
	float p_deltaTime;
	const uint16_t maxLife{ 100 };
	int16_t life;
	Camera camera;
	World* gameSpace;
	TimeManager timeManager;
	SubWeapon_Manager subWeapon_Manager;
	AnimationManager animationManager;
	CollisionManager collisionManager;
	PhysicsManager physicsManager;
	StairManager stairManager;
	ButtonManager<(int)Button::SIZE> keyManager;
	sf::View* view;
	sf::FloatRect whip_rect;
	sf::Vector2f desiredPosition;
	sf::Vector2f barPosition, life_barPosition;
	sf::Sprite mainSprite;
	sf::Sprite whipSprite;
	sf::Sprite bar, life_bar;
	sf::Sound whip, damaged;

	void squat();
	void movement(float deltaTime);
	void updatePlayerView(char direction, bool isGrounded);
	void attack();
	void upStairs();
	void updatePlayerState();

	void updateWhipRect();
	void updateTimers(float dt);
	void damagedState();
	void collisionWithEntities();
};

