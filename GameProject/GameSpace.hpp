#pragma once
#include <iostream>
#include "LevelManager.hpp"
#include "Player.hpp"
#include "Robot.hpp"
#include "Crow.hpp"
#include "Heart.hpp"
#include "FlyingEye.hpp"
#include "StoneGolem.hpp"
#include "DemonBunny.hpp"
#include "Candlestick.hpp"
#include "SubWeaponItem.hpp"
#include "VisibilityManager.hpp"
class World{
public:
	World(sf::RenderWindow&, sf::View&, float&);

	void start();
	void update();
	void render();

	const sf::Texture& getTexture(Texture texture) const { return textures.getTexture(texture); }
	const sf::SoundBuffer& getSoundBuffer(Sound buffer) const { return sounds.getSoundBuffer(buffer); } 
	void playBreakSound() { breakSound.play(); }
	void playBreakGlass() {
		breakSound.play();
		breakGlass.play();
	}

	std::vector<Tile>& getTiles() { return box_tiles; }
	std::vector<Stair>& getStairs() { return stairs; }
	std::vector<PhysicsManager*>& getPhysicsManagers() { return physicsManagers; }
	std::vector<CollisionManager*>& getCollisionManagers() { return collisionManagers; }
	std::vector<std::shared_ptr<Entity>>& getEntities() { return entities; }
	std::shared_ptr<Player> getPlayer() { return entities[0]->as<Player>(); }
private:
	float* deltaTime;
	std::shared_ptr<Player> player;
	LevelManager levelManager;
	Textures textures;
	Sounds sounds;
	VisibilityManager visibilityManager;
	sf::Sprite background;
	sf::Music bgm;
	sf::Sound breakSound;
	sf::Sound breakGlass;
	sf::RenderWindow* window;
	sf::View* view;
	std::vector<Tile> box_tiles;
	std::vector<Tile> tiles;
	std::vector<Tile> walls;
	std::vector<std::array<Tile*, 3>> binding_tiles;
	std::vector<Stair> stairs;
	std::vector<std::shared_ptr<Entity>> entities;
	std::vector<CollisionManager*> collisionManagers;
	std::vector<PhysicsManager*> physicsManagers;

	void separateTiles();
	void entitiesToAnnihilate();
	void reset();
};

