#pragma once
#include "GameSpace.hpp"
class Game {
public:
	Game();
	void run();
private:
	float deltaTime;
	sf::RenderWindow window;
	sf::View view;
	World inGameManagement;

	void update();
	void render();
};