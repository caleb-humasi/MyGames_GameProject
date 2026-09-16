#pragma once
#include <array>
#include <SFML/Graphics.hpp>

enum class Texture {
	PLAYER,
	WHIP,
	KNIFE,
	AXE,
	CROSS,
	HOLY_WATER,
	HOLY_FIRE,
	LIFE_BAR,
	BAR,
	ROBOT,
	TILE_DARK_BRICK,
	HEART,
	CANDLESTICK,
	CROW,
	FLYING_EYE,
	STONE_GOLEM,
	STONE,
	DEMON_BUNNY,
	TILE_COLLISION,
	TILE_STONE,
	TILE_SET_BLACKGROUND,
	TILE_MINIBRICK,
	DARK_STAIRS,
	BACKGROUND_STAGE_1,
	BLUE_DRAGON,
	HEAD_DRAGON,
	NULL_TEXTURE
};

class Textures {
public:
	Textures(){
		std::array<bool, (int)Texture::NULL_TEXTURE + 1> hasLoaded;

		hasLoaded[0]  = list_texture[(int)Texture::PLAYER		       ].loadFromFile("res/player/player_sprites.png");
		hasLoaded[1]  = list_texture[(int)Texture::WHIP			       ].loadFromFile("res/player/whip_attack.png");
		hasLoaded[2]  = list_texture[(int)Texture::KNIFE		       ].loadFromFile("res/player/knife.png");
		hasLoaded[3]  = list_texture[(int)Texture::AXE			       ].loadFromFile("res/player/axe.png");
		hasLoaded[4]  = list_texture[(int)Texture::CROSS		       ].loadFromFile("res/player/cross.png");
		hasLoaded[6]  = list_texture[(int)Texture::HOLY_FIRE	       ].loadFromFile("res/player/sacred_fire.png");
		hasLoaded[5]  = list_texture[(int)Texture::HOLY_WATER	       ].loadFromFile("res/player/holy_water.png");
		hasLoaded[7]  = list_texture[(int)Texture::LIFE_BAR		       ].loadFromFile("res/player/life_bar.png");
		hasLoaded[8]  = list_texture[(int)Texture::BAR   		       ].loadFromFile("res/player/bar.png");
		hasLoaded[9]  = list_texture[(int)Texture::ROBOT		       ].loadFromFile("res/enemies/enemy_1.png");
		hasLoaded[10] = list_texture[(int)Texture::TILE_DARK_BRICK     ].loadFromFile("res/ground/tile_darkBrick.png");
		hasLoaded[11] = list_texture[(int)Texture::HEART		       ].loadFromFile("res/ground/heart.png");
		hasLoaded[12] = list_texture[(int)Texture::CANDLESTICK	       ].loadFromFile("res/ground/candelabrum.png");
		hasLoaded[12] = list_texture[(int)Texture::CROW			       ].loadFromFile("res/enemies/enemy_5.png");
		hasLoaded[13] = list_texture[(int)Texture::FLYING_EYE	       ].loadFromFile("res/enemies/enemy_7.png");
		hasLoaded[14] = list_texture[(int)Texture::STONE_GOLEM	       ].loadFromFile("res/enemies/enemy_8.png");
		hasLoaded[15] = list_texture[(int)Texture::STONE		       ].loadFromFile("res/enemies/enemy_8_shoot.png");
		hasLoaded[16] = list_texture[(int)Texture::DEMON_BUNNY	       ].loadFromFile("res/enemies/enemy_9.png");
		hasLoaded[17] = list_texture[(int)Texture::TILE_COLLISION      ].loadFromFile("res/ground/tile_collision.png");
		hasLoaded[18] = list_texture[(int)Texture::TILE_STONE	       ].loadFromFile("res/ground/tile_stone.png");
		hasLoaded[19] = list_texture[(int)Texture::TILE_SET_BLACKGROUND].loadFromFile("res/ground/wall_mountains.png");
		hasLoaded[20] = list_texture[(int)Texture::TILE_MINIBRICK      ].loadFromFile("res/ground/tile_miniBricks.png");
		hasLoaded[21] = list_texture[(int)Texture::DARK_STAIRS         ].loadFromFile("res/ground/darkStairs.png");
		hasLoaded[22] = list_texture[(int)Texture::BACKGROUND_STAGE_1  ].loadFromFile("res/stages/background_stage1.png");
		hasLoaded[23] = list_texture[(int)Texture::BLUE_DRAGON         ].loadFromFile("res/enemies/dragon/dragon.png");
		hasLoaded[24] = list_texture[(int)Texture::HEAD_DRAGON         ].loadFromFile("res/enemies/dragon/dragon_head.png");
		hasLoaded[25] = list_texture[(int)Texture::NULL_TEXTURE        ].loadFromFile("res/ground/tile_null.png");

		for (bool& e : hasLoaded) {
			if (e == false) {
				throw std::runtime_error("some file didn't load effectively!");
			}
		}
	}

	const sf::Texture& getTexture(Texture texture) const { return list_texture[(int)texture]; }
private:
	std::array<sf::Texture, (int)Texture::NULL_TEXTURE + 1> list_texture;
};