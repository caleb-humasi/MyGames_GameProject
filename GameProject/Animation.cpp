#include "Animation.hpp"

bool Animation::updateAnim(float delta){
	sprite->setTextureRect(animation_frames[actualFrame]);
	animationTime += delta;
	if (animationInterval < limitAnimationInterval) {
		animationInterval += delta;
		return true;
	}
	animationInterval = 0.f;
	if (actualFrame < quantityFrames - 1)
		++actualFrame;
	else {
		actualFrame = 0;
		if (!continuous) {
			animationTime = 0.f;
			reset();
			return false;
		}
	}
	return true;
}
void Animation::reset() {
	actualFrame = 0;
	animationInterval = 0;
	activeAnimation = false;
}
