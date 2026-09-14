#pragma once
#include <array>
#include <SFML/Audio.hpp>

enum class Sound {
	PLAYER_ATTACK,
	PLAYER_DAMAGED,
	BREAK,
	HOLY_WATER,
	END
};
class Sounds {
public:
	Sounds(){
		sounds[0].loadFromFile("res/sounds/whip.mp3");
		sounds[1].loadFromFile("res/sounds/damaged.mp3");
		sounds[2].loadFromFile("res/sounds/break.mp3");
		sounds[3].loadFromFile("res/sounds/holy_water.mp3");
	}

	const sf::SoundBuffer& getSoundBuffer(Sound sound) const { return sounds[(int)sound]; }
private:
	std::array<sf::SoundBuffer,(int)Sound::END> sounds;
};