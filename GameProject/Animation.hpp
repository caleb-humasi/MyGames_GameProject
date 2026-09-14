#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
class Animation{
public:
	Animation(float _limitAnimationInterval, sf::IntRect rect, uint16_t _quantityFrames) :
		sprite(nullptr),
		continuous(false),
		activeAnimation(false),
		mainAnimation(false),
		actualFrame(0),
		quantityFrames(_quantityFrames),
		animationInterval(0.f),
		animationTime(0.f),
		animation_frames(0),
		limitAnimationInterval(_limitAnimationInterval) {
		for (uint16_t i(0); i < _quantityFrames; ++i) {
			animation_frames.push_back(sf::IntRect(
				sf::Vector2i(rect.position.x + i * rect.size.x, rect.position.y),
				rect.size
			));
		}
	}
	bool updateAnim(float delta);

	void setSprite(sf::Sprite& _sprite) { sprite = &_sprite; }
	void reset();
	void setAnimationActive(bool _activeAnimation) { activeAnimation = true; }
	void setIsContinuous(bool _continuous) { continuous = _continuous; }
	void setIsMainAnimation(bool _mainAnimation) { mainAnimation = _mainAnimation; }
	const bool& getIsAnimationActive() const { return activeAnimation; }
	const float& getAnimationTime() const { return animationTime; }
	const uint16_t& getFrame() const { return actualFrame + 1; }

private:
	bool mainAnimation;
	bool continuous;
	bool activeAnimation;
	float animationInterval;
	float animationTime;
	float limitAnimationInterval;
	sf::Sprite* sprite;
	std::vector<sf::IntRect> animation_frames;
	uint16_t actualFrame;
	uint16_t quantityFrames;
};

