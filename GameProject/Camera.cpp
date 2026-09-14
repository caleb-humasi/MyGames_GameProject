#include "Camera.hpp"

Camera::Camera(sf::View& _view):
view(&_view),
cameraMode(CameraMode::FREE){
	size = view->getSize();
}

void Camera::update(sf::Vector2f _playerCenter) {
	sf::Vector2f finalPosition = _playerCenter;
	playerCenter = _playerCenter;
	switch (cameraMode) {
	case CameraMode::FREE:
		if (playerCenter.x - size.x / 2.f < cameraLimitTopLeft.x) {
			finalPosition.x = size.x / 2.f;
		}
		else if (playerCenter.x + size.x / 2.f > cameraLimitBottomRight.x) {
			finalPosition.x = cameraLimitBottomRight.x - size.x / 2.f;
		}
		if (playerCenter.y - size.y / 2.f < cameraLimitTopLeft.y) {
			finalPosition.y = size.y / 2.f; 
		}
		else if (playerCenter.y + size.y / 2.f > cameraLimitBottomRight.y) {
			finalPosition.y = cameraLimitBottomRight.y - size.y / 2.f;
		}
		break;
	case CameraMode::HORIZONTAL:
		finalPosition.y = size.y / 2.f;
		if (playerCenter.x - size.x / 2.f < cameraLimitTopLeft.x) {
			finalPosition.x = size.x / 2.f;
		}
		else if (playerCenter.x + size.x / 2.f > cameraLimitBottomRight.x) {
			finalPosition.x = cameraLimitBottomRight.x - size.x / 2.f;
		}
		break;
	}
	cameraTopLeft = finalPosition - size / 2.f;
	view->setCenter(sf::Vector2f{ (float)(finalPosition.x), (float)(finalPosition.y)});
}

bool Camera::spriteIsInScreen(const sf::Sprite& sprite) const {
	sf::FloatRect viewCollision = sf::FloatRect(view->getCenter() - size / 2.f, size);
	if (sprite.getGlobalBounds().findIntersection(viewCollision)) return true;
	return false;
}
bool Camera::spriteIsInScreen(const sf::FloatRect& rect) const {
	sf::FloatRect viewCollision = sf::FloatRect(view->getCenter() - size / 2.f, size);
	if (rect.findIntersection(viewCollision)) return true;
	return false;
}
