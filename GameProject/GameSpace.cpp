#include "GameSpace.hpp"

World::World(sf::RenderWindow& g_window, sf::View& _view, float& g_deltaTime) :
	breakSound(sounds.getSoundBuffer(Sound::BREAK)),
	breakGlass(sounds.getSoundBuffer(Sound::HOLY_WATER)),
	background(getTexture(Texture::BACKGROUND_STAGE_1)),
	window(&g_window),
	view(&_view),
	deltaTime(&g_deltaTime),
	levelManager(box_tiles, tiles, walls, binding_tiles, stairs, textures, *this)
{
	background.setOrigin(background.getGlobalBounds().size / 2.f);
	bgm.openFromFile("res/sounds/divine_bloodlines.mp3");
	bgm.setVolume(50);
	bgm.setLooping(true);
	//bgm.play();
}

void World::start() {
	entities.push_back(std::make_shared<Player>(*this, *view));
	entities.push_back(std::make_shared<Dragon>(*this));
	entities[1]->setPosition(sf::Vector2f{ 200.f,100.f });
	player = getPlayer();
	levelManager.drawLevel(RespectiveLevel::STAGE_1);
	uint16_t i(0), j(0);
	for (auto& e : entities) {
		if (auto* coll = e->getCollisionManager()) {
			collisionManagers.push_back(coll);
			coll->setIndex(i);
			++i;
		}
		if (auto* phys = e->getPhysicsManager()) {
			physicsManagers.push_back(phys);
			phys->setIndex(j);
			++j;
		}
	}
	for (auto& e : entities) { e->start(); }
	for (CollisionManager*& e : collisionManagers) { e->setTiles(box_tiles); }
	visibilityManager.setCameraSize(getPlayer()->getCameraSize());
	visibilityManager.setTopLeftCorner(getPlayer()->getCamera().getTopLeft());
	visibilityManager.setWidthAndHeight(levelManager.getLevelWidth(), levelManager.getLevelHeight());
}
void World::update() {
	for (uint16_t i(0); i < entities.size(); ++i) {
		auto& e = entities[i];
		e->firstUpdate(*deltaTime); 
	}
	for (uint16_t i(0); i < physicsManagers.size(); ++i) { 
		auto& e = physicsManagers[i];
		e->update(*deltaTime); 
	}
	for (uint16_t i(0); i < collisionManagers.size(); ++i) {
		auto& e = collisionManagers[i];
		e->collision();
	}
	for (uint16_t i(0); i < entities.size(); ++i) {
		auto& e = entities[i];
		e->finalUpdate(); 
	}
	background.setPosition(view->getCenter());
	entitiesToAnnihilate();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::R)) { reset(); }
}
void World::render() {
	//for (auto& e : box_tiles) { if(!e.isNullTile()) window->draw(e.getSprite()); }
	window->draw(background);
	for (Tile* e : visibilityManager.getCuttedTiles(binding_tiles)) {
		window->draw(e->getSprite());
	}
	for (uint16_t i(0); i < entities.size(); ++i) { 
		if (player->getCamera().spriteIsInScreen(entities[i]->getRect())){ entities[i]->render(*window); }
	}
	entities[0]->render(*window);
}

void World::separateTiles(){

}

void World::entitiesToAnnihilate(){
	for (int16_t i(0); i < entities.size(); ++i) {
		if (entities[i]->getAnnihilateEntity() && i != 0) {
			if (auto* coll = entities[i]->getCollisionManager()) {
				int16_t index = coll->getIndex();
				coll = nullptr;
				collisionManagers[index] = nullptr;
				collisionManagers.erase(collisionManagers.begin() + index);
				for (int16_t j(index); j < collisionManagers.size(); ++j) {
					collisionManagers[j]->setIndex(collisionManagers[j]->getIndex() - 1);
				}
			}
			if (auto* phys = entities[i]->getPhysicsManager()) {
				int16_t index = phys->getIndex();
				phys = nullptr;
				physicsManagers[index] = nullptr;
				physicsManagers.erase(physicsManagers.begin() + index);
				for (int16_t j(index); j < physicsManagers.size(); ++j) {
					physicsManagers[j]->setIndex(physicsManagers[j]->getIndex() - 1);
				}
			}
			entities.erase(entities.begin() + i);
			--i;
		}
	}
	if (entities[0]->getAnnihilateEntity()) {
		reset();
	}
}

void World::reset() {
	box_tiles.clear();
	tiles.clear();
	walls.clear();
	stairs.clear();
	physicsManagers.clear();
	collisionManagers.clear();
	entities.clear();
	start();
}
