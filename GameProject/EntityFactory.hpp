#pragma once
#include <memory>
#include <vector>
#include <SFML/Graphics.hpp>

class World;
class Entity;
class SubWeaponItem;
enum class Texture;
class EntityFactory {
public:
	static void invokeKnife(World& gameSpace, const sf::Vector2f& _playerPosition, bool _isRight);
	static void invokeAxe(World& gameSpace, const sf::Vector2f& _playerPosition, bool _isRight);
	static void invokeHolyWater(World& gameSpace, const sf::Vector2f& _playerPosition, bool _isRight);
	static void invokeCross(World& gameSpace, const sf::Vector2f& _playerPosition, bool _isRight);
	static void invokeFire(World& gameSpace, sf::Vector2f respectivePosition);
	static void invokeHeart(World& gameSpace, sf::Vector2f respectivePosition);
	static void invokeSubWeaponItem(World& gameSpace, sf::Vector2f respectivePosition, Texture texture);
	static void invokeStone(World& gameSpace, const sf::Vector2f& _playerPosition, sf::Angle angle);
};