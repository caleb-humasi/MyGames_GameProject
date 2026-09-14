#include "PhysicsManager.hpp"

void PhysicsManager::update(float deltaTime) {
	if (!activePhysics) return;
	deltaDistanceY += ACCELERATION_GRAVITY * deltaTime * gb::FPS;
	if (deltaDistanceY > maxNextDistance) { deltaDistanceY = maxNextDistance; }
	desiredPosition->y += deltaDistanceY * deltaTime * gb::FPS;
}