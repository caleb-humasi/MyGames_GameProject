#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

struct Timer {
	const sf::Time time_limit;
	sf::Time passedTime;
	bool active;
};

class TimeManager {
public:
	void update(float dt);
	void addTimer(Timer timer) { timers.push_back(timer); }

	Timer& getTimer(uint16_t index) { return timers[index]; }
private:
	std::vector<Timer> timers;
};