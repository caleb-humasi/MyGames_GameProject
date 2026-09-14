#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
class Camera {
public:
	enum CameraMode {
		STATIC,
		HORIZONTAL,
		VERTICAL,
		FREE
	};
	Camera(sf::View&);

	void update(sf::Vector2f playerCenter);


	void setCameraMode(CameraMode mode) { cameraMode = mode; }
	void setCameraLimit(sf::Vector2f camLim1, sf::Vector2f camLim2) { 
		cameraLimitTopLeft = camLim1; 
		cameraLimitBottomRight = camLim2;
	}

	bool spriteIsInScreen(const sf::Sprite& sprite) const;
	bool spriteIsInScreen(const sf::FloatRect& rect) const;
	sf::Vector2f getSize() { return size; }
	const sf::Vector2f& getTopLeft() const { return cameraTopLeft; }
	const sf::Vector2f& getBottomRight() const { return cameraLimitBottomRight; }
private:
	CameraMode cameraMode;
	sf::View* view;
	sf::Vector2f playerCenter;
	sf::Vector2f size;
	sf::Vector2f cameraLimitTopLeft, cameraTopLeft;
	sf::Vector2f cameraLimitBottomRight;
};