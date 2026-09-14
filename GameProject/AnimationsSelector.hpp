#pragma once
#include "Animation.hpp"

class AnimationSelector {
public:
	AnimationSelector(sf::Sprite& _sprite);

	void update(float deltaTime);
	
	void addSprite(sf::Sprite& _sprite) {
		sprite = &_sprite;
	}
	void addAnimation(Animation animation) { 
		animations.push_back(animation); 
		animations.back().setSprite(*sprite);
	}
	void setMainAnimation(const Animation& anim) { mainAnimation = &anim; }
	void setAnimationID(uint16_t _animationID) { animationID = _animationID; }
	
	const bool& getInAction() const { return inAction; }
	Animation& getAnimation() { return animations[animationID]; }
	Animation& getAnimation(uint16_t index) { return animations[index]; }
	void reset();

private:
	bool mainAnimator;
	bool inAction;
	uint16_t animationID;
	sf::Sprite* sprite;
	std::vector<Animation> animations;
	const Animation* mainAnimation;
};