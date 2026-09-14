#pragma once
#include <SFML/Graphics.hpp>
#include <array>
template<size_t size>
class ButtonManager {
public:
	struct Button {
		sf::Keyboard::Key button;
		bool isPressed{ false };
	};
	ButtonManager(std::array<Button, size> _buttons) :
		buttons(_buttons) {
	}

	bool isButtonDown(uint8_t _key);
private:
	std::array<Button, size> buttons;
};

template<size_t size>
inline bool ButtonManager<size>::isButtonDown(uint8_t _key) {
	bool buttonPressed = false;
	if (sf::Keyboard::isKeyPressed(buttons[_key].button)) {
		if (!buttons[_key].isPressed)
			buttonPressed = true;

		buttons[_key].isPressed = true;
	}
	else {
		buttons[_key].isPressed = false;
	}
	return buttonPressed;
}