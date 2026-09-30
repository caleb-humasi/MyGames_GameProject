#pragma once
#include "AnimationManager.hpp"
#include "Enum.hpp"
class AnimationFactory {
public:
	//SETTING PLAYER ANIMATION SCHEME
	static void setPlayer(AnimationManager& animationManager, sf::Sprite& body, sf::Sprite& whip) {
		sf::IntRect bodyRect = body.getTextureRect();
		sf::IntRect whipRect = whip.getTextureRect();
		animationManager.setSprite(body);
		animationManager.addAnimationSelector(AnimationSelector(body));
		animationManager.addAnimationSelector(AnimationSelector(whip));

		animationManager.addState(
			{ &animationManager.getAnimSelector((int)player::CorrespondingLayer::BODY) },
			{ (int)player::CorrespondingBodyAnimation::IDDLE });

		animationManager.addState({ &animationManager.getAnimSelector((int)player::CorrespondingLayer::BODY) },
			{ (int)player::CorrespondingBodyAnimation::WALKING });

		animationManager.addState({
			&animationManager.getAnimSelector((int)player::CorrespondingLayer::BODY),
			&animationManager.getAnimSelector((int)player::CorrespondingLayer::WHIP) },
			{ (int)player::CorrespondingBodyAnimation::ATTACKING, (int)player::CorrespondingWhipAnimation::ATTACKING });

		animationManager.addState({
			&animationManager.getAnimSelector((int)player::CorrespondingLayer::BODY) },
			{ (int)player::CorrespondingBodyAnimation::JUMPING });

		animationManager.addState({
			&animationManager.getAnimSelector((int)player::CorrespondingLayer::BODY) },
			{ (int)player::CorrespondingBodyAnimation::THROWING_SUBWEAPON });

		animationManager.addState({
			&animationManager.getAnimSelector((int)player::CorrespondingLayer::BODY) },
			{ (int)player::CorrespondingBodyAnimation::DAMAGED });

		animationManager.addState({
			&animationManager.getAnimSelector((int)player::CorrespondingLayer::BODY) },
			{ (int)player::CorrespondingBodyAnimation::SQUAT });

		animationManager.addState({
			&animationManager.getAnimSelector((int)player::CorrespondingLayer::BODY),
			&animationManager.getAnimSelector((int)player::CorrespondingLayer::WHIP) },
			{ (int)player::CorrespondingBodyAnimation::SQUAT_ATTACK, (int)player::CorrespondingWhipAnimation::ATTACKING });

		animationManager.addState({
			&animationManager.getAnimSelector((int)player::CorrespondingLayer::BODY) },
			{ (int)player::CorrespondingBodyAnimation::SQUAT_ATTACK });


		//IDDLE
		animationManager.getAnimSelector((int)player::CorrespondingLayer::BODY).addAnimation(Animation(
			0.15f,
			sf::IntRect(bodyRect.position + sf::Vector2i(19, 0), bodyRect.size), 1));

		//WALKING
		animationManager.getAnimSelector((int)player::CorrespondingLayer::BODY).addAnimation(Animation(0.15f, bodyRect, 4));

		float attackSpeed = 0.07f;

		//ATTACKING
		animationManager.getAnimSelector((int)player::CorrespondingLayer::BODY).addAnimation(Animation(
			attackSpeed,
			sf::IntRect(bodyRect.position + sf::Vector2i(0, bodyRect.size.y + 1), bodyRect.size),
			5));

		//JUMPING
		animationManager.getAnimSelector((int)player::CorrespondingLayer::BODY).addAnimation(Animation(
			0.15f,
			sf::IntRect(bodyRect.position + sf::Vector2i(19 * 4, 0), bodyRect.size), 1));

		//THROWING SUBWEAPON
		animationManager.getAnimSelector((int)player::CorrespondingLayer::BODY).addAnimation(Animation(
			0.060f,
			sf::IntRect(bodyRect.position + sf::Vector2i(0, bodyRect.size.y + 1), bodyRect.size), 4));
	
		//WHIP ATTACK
		animationManager.getAnimSelector((int)player::CorrespondingLayer::WHIP).addAnimation(Animation(attackSpeed, whipRect, 5));

		//DAMAGED
		animationManager.getAnimSelector((int)player::CorrespondingLayer::BODY).addAnimation(Animation(
			0.060f,
			sf::IntRect(bodyRect.position + sf::Vector2i(19 * 5, bodyRect.size.y + 1), bodyRect.size), 1));
	
		//SQUAT
		animationManager.getAnimSelector((int)player::CorrespondingLayer::BODY).addAnimation(Animation(
			0.060f,
			sf::IntRect(bodyRect.position + sf::Vector2i(19 * 5, 0), bodyRect.size), 1));
	
		//SQUAT_ATTACK
		animationManager.getAnimSelector((int)player::CorrespondingLayer::BODY).addAnimation(Animation(
			attackSpeed,
			sf::IntRect(bodyRect.position + sf::Vector2i(0, (bodyRect.size.y + 1) * 2), bodyRect.size), 5));

		//SQUAT_THROWING_SUBWEAPON
		animationManager.getAnimSelector((int)player::CorrespondingLayer::BODY).addAnimation(Animation(
			0.060f,
			sf::IntRect(bodyRect.position + sf::Vector2i(0, (bodyRect.size.y + 1) * 2), bodyRect.size), 4));

		animationManager.setState((int)player::EntityState::IDDLE);
	}
	//SETTING DRAGON ANIMATION SCHEME
	static void setDragon(AnimationManager& animManager, sf::Sprite& body, sf::Sprite& head, sf::Sprite& fire) {
		animManager.setSprite(body);
		sf::IntRect bodyRect = body.getTextureRect();
		sf::IntRect headRect = head.getTextureRect();
		sf::IntRect fireRect = fire.getTextureRect();
		animManager.addAnimationSelector(AnimationSelector(body));
		animManager.addAnimationSelector(AnimationSelector(head));
		animManager.addAnimationSelector(AnimationSelector(fire));

		//Flying
		animManager.addState({ 
			&animManager.getAnimSelector((int)dragon::CorrespondingLayer::BODY), 
			&animManager.getAnimSelector((int)dragon::CorrespondingLayer::HEAD)},
			{ (int)dragon::CorrespondingBodyAnimation::FLYING,(int)dragon::CorrespondingHeadAnimation::NORMAL});

		//Dashing
		animManager.addState({
			&animManager.getAnimSelector((int)dragon::CorrespondingLayer::BODY) },
			{ (int)dragon::CorrespondingBodyAnimation::DASHING });

		//Attacking1
		animManager.addState({
			&animManager.getAnimSelector((int)dragon::CorrespondingLayer::BODY),
			&animManager.getAnimSelector((int)dragon::CorrespondingLayer::HEAD),
			&animManager.getAnimSelector((int)dragon::CorrespondingLayer::FIRE)},
			{ int(dragon::CorrespondingBodyAnimation::FLYING), int(dragon::CorrespondingHeadAnimation::FIRE_BREATHING),
			  int(dragon::CorrespondigFireAnimation::FIRING)
			});

		//***************** BODY BRO *********************
		
		//FLYING
		animManager.getAnimSelector(int(dragon::CorrespondingLayer::BODY)).addAnimation(Animation(
			0.075f, bodyRect, 7
		));
		//DASHING
		animManager.getAnimSelector(int(dragon::CorrespondingLayer::BODY)).addAnimation(Animation(
			0.05f, sf::IntRect(bodyRect.position + sf::Vector2i{0, bodyRect.size.y}, bodyRect.size), 2
		));

		//***************** HEAD BRO *********************
		
		//NORMAL
		animManager.getAnimSelector(int(dragon::CorrespondingLayer::HEAD)).addAnimation(Animation(
			1.f, headRect, 1
		));

		//FIRE BREATHING
		animManager.getAnimSelector(int(dragon::CorrespondingLayer::HEAD)).addAnimation(Animation(
			1.f, sf::IntRect(headRect.position + sf::Vector2i(headRect.size.x, 0), headRect.size), 1
		));
		
		//***************** FIRE BRO *********************

		//FIRE BREATHING
		animManager.getAnimSelector(int(dragon::CorrespondingLayer::FIRE)).addAnimation(Animation(
			0.1f, fireRect, 3
		));
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