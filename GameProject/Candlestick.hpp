#pragma once
#include <SFML/Audio.hpp>
#include "Textures.hpp"
#include "Entity.hpp"
#include "Animation.hpp"

class World;
class Candlestick : public Entity {
public:
	Candlestick(World& gameSpace);
	void start() final;
	void firstUpdate(float deltaTime) final;
	void finalUpdate() final;
	void render(sf::RenderWindow& window) final;

	void setIsHeart(bool _isHeart) { isHeart = _isHeart; }
	void setItem(Texture texture) { subWeaponTexture = texture; }
	const sf::Vector2f& getPosition() const final { return rectEntity.position; };
	sf::Vector2f getCenter() final { return rectEntity.position + rectEntity.size / 2.f;; };
private:
	bool isHeart;
	Texture subWeaponTexture;
	Animation candle_animation;
	World* gameSpace;
	std::vector<std::shared_ptr<Entity>>* entities;
	sf::Sprite mainSprite;

	void collision();
};