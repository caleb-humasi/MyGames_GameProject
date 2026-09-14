#include "StairManager.hpp"

bool StairManager::update() {
	const float thickness = 3.f;
	if (!isAuthorized) {
		stair = nullptr;
		return false; 
	}
	if (stair != nullptr) {
		if (stair->getDirection() == 1) {
			sf::Vector2f t1Corner = stair->getTile1().getRect().getCenter() + sf::Vector2f(-4.f, 4.f);
			sf::Vector2f t2Corner = stair->getTile2().getRect().getCenter() + sf::Vector2f(4.f, -4.f);
			if (rectEntity->getCenter().x > t1Corner.x && rectEntity->getCenter().x < t2Corner.x) {
				rectEntity->position.y = t1Corner.y - (rectEntity->getCenter().x - t1Corner.x) - rectEntity->size.y - 0.5f;
				return true;
			}
			else {
				stair = nullptr;
				return false;
			}
		}
		else if(stair->getDirection() == -1){
			sf::Vector2f t1Corner = stair->getTile1().getRect().getCenter() + sf::Vector2f(4, 4);
			sf::Vector2f t2Corner = stair->getTile2().getRect().getCenter() + sf::Vector2f(-4, -4);
			if (rectEntity->getCenter().x < t1Corner.x && rectEntity->getCenter().x > t2Corner.x) {
				rectEntity->position.y = t1Corner.y - (t1Corner.x - rectEntity->getCenter().x) - rectEntity->size.y - 0.5f;
				return true;
			}
			else {
				stair = nullptr;
				return false;
			}
		}
	}
	
	for (auto& i : *stairs) {
		if (i.getDirection() == 1) {
			sf::Vector2f t1Corner = i.getTile1().getRect().getCenter() + sf::Vector2f(-4.f, 4.f);
			sf::Vector2f t2Corner = i.getTile2().getRect().getCenter() + sf::Vector2f(4.f, -4.f);
			if (rectEntity->getCenter().x > t1Corner.x && rectEntity->getCenter().x < t2Corner.x) {
				sf::Vector2f playerFoot = rectEntity->getCenter() + sf::Vector2f(0.f, rectEntity->size.y / 2.f) - t1Corner;
				double distance = std::abs(-playerFoot.x + (-playerFoot.y)) / sqrtf(2.f);
				if (distance <= thickness / 2.f) {
					rectEntity->position.y = t1Corner.y - (rectEntity->getCenter().x - t1Corner.x) - rectEntity->size.y - 0.5f;
					stair = &i;
					return true;
				}
			}
		}
		else if (i.getDirection() == -1) {
			sf::Vector2f t1Corner = i.getTile1().getRect().getCenter() + sf::Vector2f(4, 4);
			sf::Vector2f t2Corner = i.getTile2().getRect().getCenter() + sf::Vector2f(-4, -4);
			if (rectEntity->getCenter().x < t1Corner.x && rectEntity->getCenter().x > t2Corner.x) {
				sf::Vector2f playerFoot = rectEntity->getCenter() + sf::Vector2f(0.f, rectEntity->size.y / 2.f) - t1Corner;
				double distance = std::abs(playerFoot.x + (-playerFoot.y)) / sqrtf(2.f);
				if (distance <= thickness / 2.f) {
					rectEntity->position.y = t1Corner.y - (t1Corner.x - rectEntity->getCenter().x) - rectEntity->size.y - 0.5f;
					stair = &i;
					return true;
				}
			}
		}
	}
	stair = nullptr;
	return false;
}