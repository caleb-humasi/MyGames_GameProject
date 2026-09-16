#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
namespace gb {
	constexpr float SCALE{ 1.f };
	constexpr float FPS{ 60.f };
	constexpr sf::Vector2i worldSize = { 90, 29 };

	namespace player {
		constexpr sf::Vector2f size = { 3.f, 14.f };
	}
	namespace robot {
		constexpr sf::Vector2f size = { 7.f, 13.f };
	}
	namespace crow {
		constexpr sf::Vector2f size = { 5.f, 7.f };
	}
	namespace flying_eye {
		constexpr sf::Vector2f size = { 6.f, 6.f };
	}
	namespace stone_golem {
		constexpr sf::Vector2f size = { 10.f, 15.f };
	}
	namespace demon_bunny {
		constexpr sf::Vector2f size = { 8.f, 10.f };
	}
	namespace dragon {
		constexpr sf::Vector2f size = { 72.f, 12.f };
	}
	namespace candlestick {
		constexpr sf::Vector2f size = { 8.f, 14.f };
	}
}