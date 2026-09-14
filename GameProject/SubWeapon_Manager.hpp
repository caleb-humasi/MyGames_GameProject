#pragma once
#include "EntityFactory.hpp"
class World;
class Player;
class SubWeapon_Manager {
	friend Player;
	enum class Weapon {
		KNIFE,
		AXE,
		CROSS,
		HOLY_WATER,
		NOTHING
	};
public:
	SubWeapon_Manager(sf::FloatRect& _rectPlayer, sf::Sprite& _mainSprite, World& _gameSpace):
		hearts(10),
		rectPlayer(&_rectPlayer),
		subWeapon(Weapon::NOTHING),
		mainSprite(&_mainSprite),
	gameSpace(&_gameSpace){}

	bool throwSubWeapon();
	void setSubWeapon(Weapon _subWeapon) { subWeapon = _subWeapon; }
private:
	uint8_t hearts;
	Weapon subWeapon;
	World* gameSpace;
	sf::FloatRect* rectPlayer;
	sf::Sprite* mainSprite;
};