#include "EntityFactory.hpp"
#include "GameSpace.hpp"
#include "Axe.hpp"
#include "Cross.hpp"
#include "HolyWater.hpp"
#include "HolyFire.hpp"
#include "Knife.hpp"
#include "Heart.hpp"
#include "Stone.hpp"
#include "SubWeaponItem.hpp"
void EntityFactory::invokeKnife(World& gameSpace, const sf::Vector2f& _playerPosition, bool _isRight)
{
	gameSpace.getEntities().push_back(std::make_shared<Knife>(gameSpace.getTexture(Texture::KNIFE), _playerPosition, _isRight));
	gameSpace.getEntities().back()->start();
}

void EntityFactory::invokeAxe(World& gameSpace, const sf::Vector2f& _playerPosition, bool _isRight)
{
	gameSpace.getEntities().push_back(std::make_shared<Axe>(gameSpace.getTexture(Texture::AXE), _playerPosition, _isRight));
	gameSpace.getEntities().back()->start();
	gameSpace.getPhysicsManagers().push_back(gameSpace.getEntities().back()->as<Axe>()->getPhysicsManager());
	gameSpace.getPhysicsManagers().back()->setIndex(gameSpace.getPhysicsManagers().size() - 1);
}

void EntityFactory::invokeHolyWater(World& gameSpace, const sf::Vector2f& _playerPosition, bool _isRight){
	gameSpace.getEntities().push_back(std::make_shared<HolyWater>(gameSpace, _playerPosition, _isRight));
	gameSpace.getEntities().back()->start();
	gameSpace.getPhysicsManagers().push_back(gameSpace.getEntities().back()->as<HolyWater>()->getPhysicsManager());
	gameSpace.getCollisionManagers().push_back(gameSpace.getEntities().back()->as<HolyWater>()->getCollisionManager());

	gameSpace.getPhysicsManagers().back()->setIndex(gameSpace.getPhysicsManagers().size() - 1);
	gameSpace.getCollisionManagers().back()->setIndex(gameSpace.getCollisionManagers().size() - 1);
}

void EntityFactory::invokeCross(World& gameSpace, const sf::Vector2f& _playerPosition, bool _isRight)
{
	gameSpace.getEntities().push_back(std::make_shared<Cross>(gameSpace.getTexture(Texture::CROSS), _playerPosition, _isRight));
	gameSpace.getEntities().back()->start();
}

void EntityFactory::invokeFire(World& gameSpace, sf::Vector2f respectivePosition){
	gameSpace.getEntities().push_back(std::make_shared<HolyFire>(gameSpace, respectivePosition));
	gameSpace.getEntities().back()->start();
}

void EntityFactory::invokeHeart(World& gameSpace, sf::Vector2f respectivePosition){
	gameSpace.getEntities().push_back(std::make_shared<Heart>(gameSpace, respectivePosition));
	gameSpace.getEntities().back()->start();
	gameSpace.getCollisionManagers().push_back(gameSpace.getEntities().back()->as<Heart>()->getCollisionManager());
	gameSpace.getEntities().back()->as<Heart>()->getCollisionManager()->setTiles(gameSpace.getTiles());
	gameSpace.getCollisionManagers().back()->setIndex(gameSpace.getCollisionManagers().size() - 1);
}

void EntityFactory::invokeSubWeaponItem(World& gameSpace, sf::Vector2f respectivePosition, Texture texture){
	gameSpace.getEntities().push_back(std::make_shared<SubWeaponItem>(gameSpace, respectivePosition, texture));
	gameSpace.getEntities().back()->start();
	gameSpace.getCollisionManagers().push_back(gameSpace.getEntities().back()->as<SubWeaponItem>()->getCollisionManager());

	gameSpace.getEntities().back()->as<SubWeaponItem>()->getCollisionManager()->setTiles(gameSpace.getTiles());
	gameSpace.getCollisionManagers().back()->setIndex(gameSpace.getCollisionManagers().size() - 1);
}

void EntityFactory::invokeStone(World& gameSpace, const sf::Vector2f& _playerPosition, sf::Angle angle)
{
	gameSpace.getEntities().push_back(std::make_shared<Stone>(gameSpace.getTexture(Texture::STONE), _playerPosition, angle));
	gameSpace.getEntities().back()->start();
	gameSpace.getPhysicsManagers().push_back(gameSpace.getEntities().back()->as<Stone>()->getPhysicsManager());
	gameSpace.getPhysicsManagers().back()->setIndex(gameSpace.getPhysicsManagers().size() - 1);
}