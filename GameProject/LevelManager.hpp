#pragma once
#include "Textures.hpp"
#include "Sounds.hpp"
#include "globals.hpp"
#include "Entity.hpp"
#include "Stair.hpp"
#include <LDtkLoader/Project.hpp>

enum class RespectiveLevel {
	STAGE_1,
	STAGE_2,
};
class World;
class LevelManager {
public:
	LevelManager(std::vector<Tile>& _box_tiles, std::vector<Tile>& _tiles, std::vector<Tile>& _walls, std::vector<std::array<Tile*, 3>>& _binding_tiles, std::vector<Stair>& stairs,
		Textures& _textureManager, World& _gameSpace);

	void drawLevel(RespectiveLevel level);
	int getLevelWidth() { return levelWidth; }
	int getLevelHeight() { return levelHeight; }
private:
	int levelWidth{ 0 }, levelHeight{ 0 };
	World* gameSpace;
	Textures* textureManager;
	ldtk::Project ldtk_project;
	std::vector<Tile>* box_tiles;
	std::vector<Tile>* tiles;
	std::vector<Tile>* walls;
	std::vector<std::array<Tile*, 3>>* binding_tiles;
	std::vector<Stair>* stairs;
	std::vector<std::shared_ptr<Entity>>* entities;
};