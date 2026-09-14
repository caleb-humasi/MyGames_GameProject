#include "Game.hpp"
#include "GameSpace.hpp"
Game::Game():
    window(sf::VideoMode({ (int)(200 * 5) , (int)(152 * 5) }), "SFML works!"),
    deltaTime(0),
    view({ 100, 76 }, { 200 , 152 }),
    inGameManagement(window, view, deltaTime){
    window.setFramerateLimit(240);
}

void Game::run() {
    inGameManagement.start();
    sf::Clock clock;
    while (window.isOpen())
    {
        deltaTime = clock.restart().asSeconds();
        if (deltaTime > 1.f / 60) deltaTime = 1.f / 60;
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }
        update();
        window.setView(view);
        render();
    }
}

void Game::update() {
    inGameManagement.update();
}

void Game::render(){
	window.clear(sf::Color(5,0,56));
    inGameManagement.render();
	window.display();
}
