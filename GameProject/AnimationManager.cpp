#include "AnimationManager.hpp"

AnimationManager::AnimationManager() :
	stateID(0),
	sprite(nullptr){
}

void AnimationManager::update(float deltaTime) {
	for (AnimationSelector*& e : respectiveStateAnimations[stateID].first) {
		e->update(deltaTime);
	}
}

void AnimationManager::addState(std::vector<AnimationSelector*> animationSelector, std::vector<uint16_t> stateAnimations){
	respectiveStateAnimations.push_back(std::pair<std::vector<AnimationSelector*>, std::vector<uint16_t>>());
	respectiveStateAnimations.back().first = animationSelector;
	respectiveStateAnimations.back().second = stateAnimations;
}

void AnimationManager::setState(uint16_t _stateID){
	if (stateID == _stateID) { return; }

	for (AnimationSelector*& e : respectiveStateAnimations[stateID].first) {
		e->reset();
	}
	uint8_t index(0);
	for (AnimationSelector*& e : respectiveStateAnimations[_stateID].first) {
		e->setAnimationID(respectiveStateAnimations[_stateID].second[index]);
		++index;
	}
	stateID = _stateID;
	
}