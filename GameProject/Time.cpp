#include "Time.hpp"

void TimeManager::update(float dt) {
	for (Timer& e : timers) {
		if (e.active) {
			if (e.passedTime < e.time_limit) {
				e.passedTime += sf::seconds(dt);
			}
			else {
				e.passedTime = sf::seconds(0.f);
				e.active = false;
			}
		}
	}
}