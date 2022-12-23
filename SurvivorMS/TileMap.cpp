#include "stdafx.h"
#include "TileMap.h"

void TileMap::clear() {
	for (size_t i = 0; i < this->maxSize.x; i++) {
		for (size_t j = 0; j < this->maxSize.y; j++) {
			for (size_t k = 0; k < this->layers; k++) {
				delete this->map[i][j][k];
				this->map[i][j][k] = nullptr;
			}
			this->map[i][j].clear();
		}
		this->map[i].clear();
	}
	this->map.clear();
}

TileMap::TileMap(float gridSize, unsigned width, unsigned height, std::string textureFile) {
	
	this->gridSizeF = gridSize;
	this->gridSizeU = static_cast<unsigned>(this->gridSizeF);
	this->maxSize.x = width;
	this->maxSize.y = height;
	this->layers = 1;

	this->textureFile = textureFile;

	this->map.resize(this->maxSize.x, std::vector<std::vector<Tile*>>());
	for (size_t i = 0; i < this->maxSize.x; i++) {

		for (size_t j = 0; j < this->maxSize.y; j++) {

			this->map[i].resize(this->maxSize.y, std::vector<Tile*>());

			for (size_t k = 0; k < this->layers; k++) {

				this->map[i][j].resize(this->layers, nullptr);

			}

		}

	}

	if (!this->tileSheet.loadFromFile(textureFile)) {
		std::cout << "ERROR::TILEMAP:: WITH GRASS TEXTURE" << "\n";
	}
}

TileMap::~TileMap() {

	this->clear();

}

const sf::Texture* TileMap::getTileSheet() const{
	return &this->tileSheet;
}

void TileMap::saveToFile(const std::string path) {
	/*FORMAT:
		BASIC:
		Size x y
		gridSize
		layers
		texture file

		ALL TILES:
		gridPos x y layer, Texture rect x y, type
	*/

	std::ofstream ofs;

	ofs.open(path);

	if (ofs.is_open()) {

		ofs << this->maxSize.x << " " << this->maxSize.y << "\n"
			<< this->gridSizeU << "\n"
			<< this->layers << "\n"
			<< this->textureFile << "\n";


		for (size_t i = 0; i < this->maxSize.x; i++) {
			for (size_t j = 0; j < this->maxSize.y; j++) {
				for (size_t k = 0; k < this->layers; k++) {
					if(this->map[i][j][k])
						ofs << i << " " << j << " " << k << " " << this->map[i][j][k]->getAsString() << " ";
				}
			}
		}


	} else {
		std::cout << "ERROR::TILEMAP:: IN MAP FILE" << "\n";
	}

	ofs.close();
}

void TileMap::loadFromFile(const std::string path) {

	std::ifstream ifs;

	ifs.open(path);

	if (ifs.is_open()) {

		// BASIC

		sf::Vector2u size;
		unsigned gridSize = 0;
		unsigned layers = 0;
		std::string textureFile = "";

		ifs >> size.x >> size.y >> gridSize >> layers >> textureFile;

		this->gridSizeF = static_cast<float>(gridSize);
		this->gridSizeU = gridSize;
		this->maxSize.x = size.x;
		this->maxSize.y = size.y;
		this->layers = layers;
		this->textureFile = textureFile;


		// TILES
		this->clear();

		unsigned x = 0;
		unsigned y = 0;
		unsigned z = 0;

		unsigned trX = 0;
		unsigned trY = 0;

		bool collision = false;
		short type = 0;

		this->map.resize(this->maxSize.x, std::vector<std::vector<Tile*>>());
		for (size_t i = 0; i < this->maxSize.x; i++) {

			for (size_t j = 0; j < this->maxSize.y; j++) {

				this->map[i].resize(this->maxSize.y, std::vector<Tile*>());

				for (size_t k = 0; k < this->layers; k++) {

					this->map[i][j].resize(this->layers, nullptr);

				}

			}

		}

		if (!this->tileSheet.loadFromFile(textureFile)) {
			std::cout << "ERROR::TILEMAP:: WITH GRASS TEXTURE" << "\n";
		}

		while (ifs >> x >> y >> z >> trX >> trY >> collision >> type) {

			this->map[x][y][z] = new Tile(x, y, this->gridSizeF, this->tileSheet, sf::IntRect(trX, trY, this->gridSizeU, this->gridSizeU), collision, type);
		}


	} else {
		std::cout << "ERROR::TILEMAP:: IN MAP FILE" << "\n";
	}

	ifs.close();

}

void TileMap::addTile(const unsigned x, const unsigned y, const unsigned z, const sf::IntRect& textureRect, const bool& collision, const short& type) {

	if (x < this->maxSize.x && y < this->maxSize.y && z < this->layers && x >= 0 && y >= 0 && z >= 0) {

		if (this->map[x][y][z] == nullptr) {

			this->map[x][y][z] = new Tile(x, y, this->gridSizeF, this->tileSheet, textureRect, collision, type);
		}

	}

}

void TileMap::removeTile(const unsigned x, const unsigned y, const unsigned z) {

	if (x < this->maxSize.x && y < this->maxSize.y && z < this->layers && x >= 0 && y >= 0 && z >= 0) {

		if (this->map[x][y][z] != nullptr) {

			delete this->map[x][y][z];
			this->map[x][y][z] = nullptr;
		}

	}
}

void TileMap::update(const float& dt) {
}

void TileMap::render(sf::RenderTarget& target) {
	for (auto& x : this->map) {

		for (auto& y : x) {

			for (auto*z : y) {

				if(z != nullptr)
					z->render(target);

			}

		}

	}
}
