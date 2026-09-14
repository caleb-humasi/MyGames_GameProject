#include "LevelManager.hpp"
#include "GameSpace.hpp"
LevelManager::LevelManager(std::vector<Tile>& _box_tiles, std::vector<Tile>& _tiles, std::vector<Tile>& _walls, std::vector<std::array<Tile*, 3>>& _binding_tiles, std::vector<Stair>& _stairs, Textures& _textureManager, World& _gameSpace) :
	stairs(&_stairs),
	box_tiles(&_box_tiles),
	tiles(&_tiles),
	walls(&_walls),
	binding_tiles(&_binding_tiles),
	textureManager(&_textureManager),
	gameSpace(&_gameSpace),
	entities(&gameSpace->getEntities()) {
}
void LevelManager::drawLevel(RespectiveLevel level) {
	sf::Image image;
	uint16_t index(0);
	try {
		ldtk_project.loadFromFile("res/stages/legendvania.ldtk");
		const auto& world = ldtk_project.getWorld();
		const auto& level = world.getLevel("Level_0");
		const auto& layer_colisao = level.getLayer("Collision");
		const auto& layer_tiles = level.getLayer("Tiles");
		const auto& layer_background = level.getLayer("Background");
		const auto& layer_entities = level.getLayer("Entities");

		int total_colunas = layer_colisao.getGridSize().x;
		int total_linhas = layer_colisao.getGridSize().y;

		levelWidth = total_colunas * 8;
		levelHeight = total_linhas * 8;
		for (int y = 0; y < total_linhas; ++y) {
			for (int x = 0; x < total_colunas; ++x) {
				ldtk::IntGridValue valor_bloco = layer_colisao.getIntGridVal(x, y);
				if (valor_bloco.value == 1) {
					int posX_na_tela = x * layer_colisao.getCellSize();
					int posY_na_tela = y * layer_colisao.getCellSize();
					box_tiles->push_back(Tile(textureManager->getTexture(Texture::TILE_COLLISION), index, "active"));
					Tile& e = box_tiles->back();
					e.setRect(sf::FloatRect({ x * gb::SCALE * 8.f, y * gb::SCALE * 8 }, { 8 * gb::SCALE, 8 * gb::SCALE }));
					binding_tiles->push_back(std::array<Tile*, 3>({ nullptr, nullptr, nullptr }));
				}
				else if (valor_bloco.value == 2) {
					int posX_na_tela = x * layer_colisao.getCellSize();
					int posY_na_tela = y * layer_colisao.getCellSize();
					box_tiles->push_back(Tile(textureManager->getTexture(Texture::NULL_TEXTURE), index, "stair"));
					Tile& e = box_tiles->back();
					e.setRect(sf::FloatRect({ x * gb::SCALE * 8.f, y * gb::SCALE * 8 }, { 8 * gb::SCALE, 8 * gb::SCALE }));
					binding_tiles->push_back(std::array<Tile*, 3>({ nullptr, nullptr, nullptr }));
				}
				else if (valor_bloco.value == 3) {
					int posX_na_tela = x * layer_colisao.getCellSize();
					int posY_na_tela = y * layer_colisao.getCellSize();
					box_tiles->push_back(Tile(textureManager->getTexture(Texture::NULL_TEXTURE), index, "stair_point"));
					Tile& e = box_tiles->back();
					e.setRect(sf::FloatRect({ x * gb::SCALE * 8.f, y * gb::SCALE * 8 }, { 8 * gb::SCALE, 8 * gb::SCALE }));
					binding_tiles->push_back(std::array<Tile*, 3>({ nullptr, nullptr, nullptr }));
				}
				else if(valor_bloco.value == -1){
					box_tiles->push_back(Tile(textureManager->getTexture(Texture::NULL_TEXTURE), index, "null"));
					Tile& e = box_tiles->back();
					e.setRect(sf::FloatRect({ x * gb::SCALE * 8.f, y * gb::SCALE * 8 }, { 8 * gb::SCALE, 8 * gb::SCALE }));
					e.setNullTile(true);
					binding_tiles->push_back(std::array<Tile*, 3>({nullptr, nullptr, nullptr}));
				}
				index++;
			}
		}
		for (uint16_t i(0); i < box_tiles->size(); ++i) {
			if (box_tiles->at(i).getTag() == "stair_point") {
				int firstIndex1 = i - 1 + total_colunas;
				int firstIndex2 = i + 1 + total_colunas;
				if (box_tiles->at(firstIndex1).getTag() == "stair") {
					uint16_t j(1);
					while (true) {
						if (box_tiles->at(firstIndex1 - j + j * total_colunas).getTag() == "stair_point") {
							stairs->push_back(Stair(box_tiles->at(firstIndex1 - j + j * total_colunas), box_tiles->at(i), 1));
							break;
						}
						++j;
					}
				}
				if (box_tiles->at(firstIndex2).getTag() == "stair") {
					uint16_t j(1);
					while (true) {
						if (box_tiles->at(firstIndex2 + j + j * total_colunas).getTag() == "stair_point") {
							stairs->push_back(Stair(box_tiles->at(firstIndex2 + j + j * total_colunas), box_tiles->at(i), -1));
							break;
						}
						++j;
					}
				}
			}
		}
		const auto& ltiles = layer_tiles.allTiles();
		const auto& tile_set = ldtk_project.getTileset("Phase1_ground");

		tiles->reserve(ltiles.size());
		for (int y = 0; y < ltiles.size(); ++y) {
			const ldtk::Tile& e = ltiles[y];
			std::cout << e.tileId << '\n';
			std::string tile_type = "";
			if (e.tileId == 0) {
				tiles->push_back(Tile(textureManager->getTexture(Texture::TILE_DARK_BRICK), y));
			}
			else if (e.tileId == 1) {
				tiles->push_back(Tile(textureManager->getTexture(Texture::TILE_STONE), y));
			}
			else if (e.tileId == 2) {
				tiles->push_back(Tile(textureManager->getTexture(Texture::DARK_STAIRS), y));
			}
			else if (e.tileId == 3) {
				tiles->push_back(Tile(textureManager->getTexture(Texture::TILE_MINIBRICK), y));
			}
			else if (e.tileId == 4) {
				tiles->push_back(Tile(textureManager->getTexture(Texture::DARK_STAIRS), y));
				tiles->back().changeSide(-1);
			}

			if (e.tileId >= 0 && e.tileId <= 4) {
				int x = e.getGridPosition().x;
				int k = e.getGridPosition().y;
				binding_tiles->at(x + k * total_colunas)[0] = &tiles->back();
			}

			Tile& i = tiles->back();
			i.setRect(sf::FloatRect(
				{ (float)e.getPosition().x , (float)e.getPosition().y },
				{ 8, 8 }));
		}
		
		const auto& lwtiles = layer_background.allTiles();
		walls->reserve(lwtiles.size());
		for (int y = 0; y < lwtiles.size(); ++y) {
			const ldtk::Tile& e = lwtiles[y];
		
			if (e.tileId != -1) {
				walls->push_back(Tile(textureManager->getTexture(Texture::TILE_SET_BLACKGROUND), y, sf::IntRect({ 8 * e.tileId,0 }, { 8, 8 })));
				binding_tiles->at(e.getGridPosition().x + e.getGridPosition().y * total_colunas)[1] = &walls->back();
			}
		
			Tile& i = walls->back();
			i.setRect(sf::FloatRect(
				{ (float)e.getPosition().x, (float)e.getPosition().y },
				{ 8.f, 8.f }));
			//i.setColor(sf::Color(170, 170, 170));
		}
		for (auto& e : layer_entities.allEntities()) {
			if (e.getName() == "PlayerSpawn"){
				entities->at(0)->setPosition(
					sf::Vector2f{ (float)e.getPosition().x, (float)e.getPosition().y } +
					sf::Vector2f{ 4,8 } - sf::Vector2f{ gb::player::size.x / 2.f, gb::player::size.y });
			}
			else if (e.getName() == "Robot") {
				entities->push_back(std::make_shared<Robot>(*gameSpace));
				entities->back()->setPosition(sf::Vector2f{ 
					(float)e.getPosition().x, (float)e.getPosition().y } +
					sf::Vector2f{ 4,8 } - sf::Vector2f{ gb::robot::size.x / 2.f, gb::robot::size.y });
			}
			else if (e.getName() == "StoneGolem") {
				entities->push_back(std::make_shared<StoneGolem>(*gameSpace));
				entities->back()->setPosition(
					sf::Vector2f{(float)e.getPosition().x, (float)e.getPosition().y } + 
					sf::Vector2f{4,8} - sf::Vector2f{gb::stone_golem::size.x / 2.f, gb::stone_golem::size.y});
			}
			else if (e.getName() == "DemonBunny") {
				entities->push_back(std::make_shared<DemonBunny>(*gameSpace));
				entities->back()->setPosition(sf::Vector2f{ 
					(float)e.getPosition().x, (float)e.getPosition().y } +
					sf::Vector2f{ 4,8 } - sf::Vector2f{ gb::demon_bunny::size.x / 2.f, gb::demon_bunny::size.y });
			}
			else if (e.getName() == "Crow") {
				entities->push_back(std::make_shared<Crow>(*gameSpace));
				entities->back()->setPosition(sf::Vector2f{ 
					(float)e.getPosition().x, (float)e.getPosition().y } +
					sf::Vector2f{ 4,8 } - sf::Vector2f{ gb::crow::size.x / 2.f, gb::crow::size.y + 1});
			}
			else if (e.getName() == "Eye") {
				entities->push_back(std::make_shared<FlyingEye>(*gameSpace));
				entities->back()->setPosition(sf::Vector2f{
					(float)e.getPosition().x, (float)e.getPosition().y } +
					sf::Vector2f{ 4,8 } - sf::Vector2f{ gb::flying_eye::size.x / 2.f, gb::flying_eye::size.y });
			}
			else if (e.getName() == "Candle") {
				entities->push_back(std::make_shared<Candlestick>(*gameSpace));
				entities->back()->setPosition(sf::Vector2f{
					(float)e.getPosition().x, (float)e.getPosition().y } +
					sf::Vector2f{ 4,8 } - sf::Vector2f{ gb::candlestick::size.x / 2.f, gb::candlestick::size.y });
			}
			else if (e.getName() == "Candle_1") {
				entities->push_back(std::make_shared<Candlestick>(*gameSpace));
				entities->back()->setPosition(sf::Vector2f{
					(float)e.getPosition().x, (float)e.getPosition().y } +
					sf::Vector2f{ 4,8 } - sf::Vector2f{ gb::candlestick::size.x / 2.f, gb::candlestick::size.y });
				entities->back()->as<Candlestick>()->setIsHeart(false);
				entities->back()->as<Candlestick>()->setItem(Texture::KNIFE);
			}
			else if (e.getName() == "Candle_2") {
				entities->push_back(std::make_shared<Candlestick>(*gameSpace));
				entities->back()->setPosition(sf::Vector2f{
					(float)e.getPosition().x, (float)e.getPosition().y } +
					sf::Vector2f{ 4,8 } - sf::Vector2f{ gb::candlestick::size.x / 2.f, gb::candlestick::size.y });
				entities->back()->as<Candlestick>()->setIsHeart(false);
				entities->back()->as<Candlestick>()->setItem(Texture::AXE);
			}
			else if (e.getName() == "Candle_3") {
				entities->push_back(std::make_shared<Candlestick>(*gameSpace));
				entities->back()->setPosition(sf::Vector2f{
					(float)e.getPosition().x, (float)e.getPosition().y } +
					sf::Vector2f{ 4,8 } - sf::Vector2f{ gb::candlestick::size.x / 2.f, gb::candlestick::size.y });
				entities->back()->as<Candlestick>()->setIsHeart(false);
				entities->back()->as<Candlestick>()->setItem(Texture::CROSS);
			}
			else if (e.getName() == "Candle_4") {
				entities->push_back(std::make_shared<Candlestick>(*gameSpace));
				entities->back()->setPosition(sf::Vector2f{
					(float)e.getPosition().x, (float)e.getPosition().y } +
					sf::Vector2f{ 4,8 } - sf::Vector2f{ gb::candlestick::size.x / 2.f, gb::candlestick::size.y });
				entities->back()->as<Candlestick>()->setIsHeart(false);
				entities->back()->as<Candlestick>()->setItem(Texture::HOLY_WATER);
			}
		}
	}
	catch (const std::exception& e) {
		std::cerr << "Erro ao carregar o mapa: " << e.what() << std::endl;
	}
}
