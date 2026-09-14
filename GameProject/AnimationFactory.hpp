#pragma once
#include "AnimationManager.hpp"
#include "Enum.hpp"
class AnimationFactory {
public:
	static void setPlayer(AnimationManager& animationManager, sf::Sprite& body, sf::Sprite& whip) {
		sf::IntRect bodyRect = body.getTextureRect();
		sf::IntRect whipRect = whip.getTextureRect();
		animationManager.setSprite(body);
		animationManager.addAnimationSelector(AnimationSelector(body));
		animationManager.addAnimationSelector(AnimationSelector(whip));

		animationManager.addState({
			&animationManager.getAnimSelector((int)player::AnimLayer::BODY) },
			{ (int)player::CorrespondingBodyAnimation::IDDLE });

		animationManager.addState({ &animationManager.getAnimSelector((int)player::AnimLayer::BODY) },
			{ (int)player::CorrespondingBodyAnimation::WALKING });

		animationManager.addState({
			&animationManager.getAnimSelector((int)player::AnimLayer::BODY),
			&animationManager.getAnimSelector((int)player::AnimLayer::WHIP) },
			{ (int)player::CorrespondingBodyAnimation::ATTACKING, (int)player::CorrespondingWhipAnimation::ATTACKING });

		animationManager.addState({
			&animationManager.getAnimSelector((int)player::AnimLayer::BODY) },
			{ (int)player::CorrespondingBodyAnimation::JUMPING });

		animationManager.addState({
			&animationManager.getAnimSelector((int)player::AnimLayer::BODY) },
			{ (int)player::CorrespondingBodyAnimation::THROWING_SUBWEAPON });

		animationManager.addState({
			&animationManager.getAnimSelector((int)player::AnimLayer::BODY) },
			{ (int)player::CorrespondingBodyAnimation::DAMAGED });

		animationManager.addState({
			&animationManager.getAnimSelector((int)player::AnimLayer::BODY) },
			{ (int)player::CorrespondingBodyAnimation::SQUAT });

		animationManager.addState({
			&animationManager.getAnimSelector((int)player::AnimLayer::BODY),
			&animationManager.getAnimSelector((int)player::AnimLayer::WHIP) },
			{ (int)player::CorrespondingBodyAnimation::SQUAT_ATTACK, (int)player::CorrespondingWhipAnimation::ATTACKING });

		animationManager.addState({
			&animationManager.getAnimSelector((int)player::AnimLayer::BODY) },
			{ (int)player::CorrespondingBodyAnimation::SQUAT_ATTACK });


		//IDDLE
		animationManager.getAnimSelector((int)player::AnimLayer::BODY).addAnimation(Animation(
			0.15f,
			sf::IntRect(bodyRect.position + sf::Vector2i(19, 0), bodyRect.size), 1));

		//WALKING
		animationManager.getAnimSelector((int)player::AnimLayer::BODY).addAnimation(Animation(0.15f, bodyRect, 4));

		float attackSpeed = 0.07f;

		//ATTACKING
		animationManager.getAnimSelector((int)player::AnimLayer::BODY).addAnimation(Animation(
			attackSpeed,
			sf::IntRect(bodyRect.position + sf::Vector2i(0, bodyRect.size.y + 1), bodyRect.size),
			5));

		//JUMPING
		animationManager.getAnimSelector((int)player::AnimLayer::BODY).addAnimation(Animation(
			0.15f,
			sf::IntRect(bodyRect.position + sf::Vector2i(19 * 4, 0), bodyRect.size), 1));

		//THROWING SUBWEAPON
		animationManager.getAnimSelector((int)player::AnimLayer::BODY).addAnimation(Animation(
			0.060f,
			sf::IntRect(bodyRect.position + sf::Vector2i(0, bodyRect.size.y + 1), bodyRect.size), 4));
	
		//ATTACKING WHIP
		animationManager.getAnimSelector((int)player::AnimLayer::WHIP).addAnimation(Animation(attackSpeed, whipRect, 5));

		//DAMAGED
		animationManager.getAnimSelector((int)player::AnimLayer::BODY).addAnimation(Animation(
			0.060f,
			sf::IntRect(bodyRect.position + sf::Vector2i(19 * 5, bodyRect.size.y + 1), bodyRect.size), 1));
	
		//SQUAT
		animationManager.getAnimSelector((int)player::AnimLayer::BODY).addAnimation(Animation(
			0.060f,
			sf::IntRect(bodyRect.position + sf::Vector2i(19 * 5, 0), bodyRect.size), 1));
	
		//SQUAT_ATTACK
		animationManager.getAnimSelector((int)player::AnimLayer::BODY).addAnimation(Animation(
			attackSpeed,
			sf::IntRect(bodyRect.position + sf::Vector2i(0, (bodyRect.size.y + 1) * 2), bodyRect.size), 5));

		//SQUAT_THROWING_SUBWEAPON
		animationManager.getAnimSelector((int)player::AnimLayer::BODY).addAnimation(Animation(
			0.060f,
			sf::IntRect(bodyRect.position + sf::Vector2i(0, (bodyRect.size.y + 1) * 2), bodyRect.size), 4));

		animationManager.setState((int)player::EntityState::IDDLE);
	}
	static void setRobot(AnimationSelector& animationSelector) {
		animationSelector.addAnimation(Animation(0.15f, sf::IntRect({ 0,0 }, { 11, 13 }), 4));
		animationSelector.addAnimation(Animation(0.15f, sf::IntRect({ 11 * 2,14 }, { 11, 13 }), 1));
		animationSelector.addAnimation(Animation(0.15f, sf::IntRect({ 0,0 }, { 11, 13 }), 1));
	}
	static void setCrow(AnimationSelector& animationSelector) {
		animationSelector.addAnimation(Animation(0.15f, sf::IntRect({ 0,0 }, { 11, 9 }), 6));
		animationSelector.addAnimation(Animation(0.15f, sf::IntRect({ 0,10 }, { 11, 9 }), 1));
	}
	static void setFlyingEye(AnimationSelector& animationSelector) {
		animationSelector.addAnimation(Animation(0.15f, sf::IntRect({ 6,0 }, { 6, 6 }), 1));
		animationSelector.addAnimation(Animation(0.15f, sf::IntRect({ 0,0 }, { 6, 6 }), 1));
	}
	static void setStoneGolem(AnimationSelector& animationSelector) {
		animationSelector.addAnimation(Animation(0.15f, sf::IntRect({ 0,0 }, { 16, 16 }), 3));
		animationSelector.addAnimation(Animation(0.15f, sf::IntRect({ 16*2,0 }, { 16, 16 }), 3));
		animationSelector.getAnimation(1).setIsContinuous(false);
	}
};