#pragma once
#include "AnimationsSelector.hpp"
class AnimationManager {
	struct StaticState {
		sf::Sprite* sprite;
		sf::IntRect rectFrame;
		bool draw{ false };
	};
public:
	AnimationManager();

	void update(float deltaTime);

	AnimationSelector& getAnimSelector(uint16_t index) { return animationsSelectors[index]; }
	void addAnimationSelector(AnimationSelector as) { animationsSelectors.push_back(as);  }
	void addState(std::vector<AnimationSelector*> animationSelector, std::vector<uint16_t> stateAnimations);

	void setSprite(sf::Sprite& _sprite) { sprite = &_sprite; }
	void setState(uint16_t _stateID);

	const uint16_t& getStateID() const { return stateID; }
private:
	int16_t stateID;
	sf::Sprite* sprite;
	std::vector<AnimationSelector> animationsSelectors;
	std::vector<std::pair<std::vector<AnimationSelector*>, std::vector<uint16_t>>> respectiveStateAnimations;
	std::vector<std::vector<StaticState>> respectiveStaticStates;
};