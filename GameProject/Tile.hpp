#pragma once
#include <SFML/Graphics.hpp>
#include "globals.hpp"

class Tile {
public:
	Tile(const sf::Texture& texture, uint16_t _index):
	nullTile(false),
	tileSprite(texture),
	index(_index){
		tileSprite.setScale({ gb::SCALE, gb::SCALE });
		tileRect = tileSprite.getGlobalBounds();
	}
	Tile(const sf::Texture& texture, uint16_t _index, std::string _tag) :
		tag(_tag),
		nullTile(false),
		tileSprite(texture),
		index(_index) {
		tileSprite.setScale({ gb::SCALE, gb::SCALE });
		tileRect = tileSprite.getGlobalBounds();
	}
	Tile(const sf::Texture& texture, uint16_t _index, sf::IntRect rectTexture) :
		nullTile(false),
		tileSprite(texture),
		index(_index) {
		tileSprite.setTextureRect(rectTexture);
		tileSprite.setScale({ gb::SCALE, gb::SCALE });
		tileRect = tileSprite.getGlobalBounds();
	}

	void setRect(sf::FloatRect rect) { 
		tileRect = rect; 
		tileSprite.setPosition(tileRect.position + tileRect.size / 2.f - tileSprite.getGlobalBounds().size / 2.f);
		if (tileSprite.getScale().x == -1) {
			tileSprite.setPosition(tileRect.position + tileRect.size / 2.f + 
				sf::Vector2f{tileSprite.getGlobalBounds().size.x / 2.f, -tileSprite.getGlobalBounds().size.y / 2.f});
		}
	}
	void setColor(sf::Color color) {
		tileSprite.setColor(color);
	}
	void changeSide(char side) { 
		tileSprite.setScale(sf::Vector2f{ (float)side,1.f });
	}
	void setNullTile(bool _nullTile) { nullTile = _nullTile; }

	uint16_t getIndex() const { return index; }
	bool isNullTile() const { return nullTile; }
	const std::string& getTag() const { return tag; }
	sf::Vector2f getCenter() { return tileRect.position + tileRect.size / 2.f; }
	const sf::FloatRect& getRect() const { return tileRect; }
	const sf::Sprite& getSprite() const { return tileSprite; }
private:
	const uint16_t index;
	bool nullTile;
	std::string tag;
	sf::Sprite tileSprite;
	sf::FloatRect tileRect;
};