#pragma once
#include <SFML/Graphics.hpp>
#include "globals.hpp"
class PhysicsManager {
public:
	static constexpr float ACCELERATION_GRAVITY{0.125f};
	PhysicsManager(sf::Vector2f& _desiredPosition, float _maxNextDistance) :
		desiredPosition(&_desiredPosition),
		maxNextDistance(_maxNextDistance),
		deltaDistanceY(0.f),
		annihilate(false),
		activePhysics(true),
		respectiveIndex(0){
		}

	void update(float deltaTime);
	void setActivePhysics(bool _activePhysics) { activePhysics = _activePhysics; }
	void setDeltaY(float _deltaDistance) { deltaDistanceY = _deltaDistance; }
	void setEntityOwnerName(std::string owner) { entityOwnerName = owner; }
	void setAnnihilatePhysicsManager(bool _annihilate) { annihilate = _annihilate; }
	void setIndex(uint16_t index) { respectiveIndex = index; }

	const uint16_t& getIndex() const { return respectiveIndex; }
	const float& getDeltaDistance() const { return deltaDistanceY; }
	const bool& getAnnihilatePhysicsManager() const { return annihilate; }
	const std::string& getEntityOwnerName() { return entityOwnerName; }
private:
	bool activePhysics;
	uint16_t respectiveIndex;
	const float maxNextDistance;
	bool annihilate;
	float deltaDistanceY;
	std::string entityOwnerName;
	sf::Vector2f* desiredPosition;
};