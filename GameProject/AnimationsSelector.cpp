#include "AnimationsSelector.hpp"

AnimationSelector::AnimationSelector(sf::Sprite& _sprite):
	animationID(0),
	mainAnimator(false),
	sprite(&_sprite),
	mainAnimation(nullptr){
}

void AnimationSelector::update(float deltaTime) {
	if (animations[animationID].getIsAnimationActive())
		animations[animationID].setAnimationActive(true);
	inAction = animations[animationID].updateAnim(deltaTime);
}

void AnimationSelector::reset(){
	animations[animationID].reset();
}
