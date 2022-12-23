#include "stdafx.h"
#include "TileMap.h"

TileMap::TileMap(float gridSize, unsigned width, unsigned height) {
	
	this->gridSizeF = gridSize;
	this->gridSizeU = static_cast<unsigned>(this->gridSizeF);
	this->maxSize.x = width;
	this->maxSize.y = height;
	this->layers = 1;

	this->map.resize(this->maxSize.x);
	for (size_t i = 0; i < this->maxSize.x; i++) {

		this->map.push_back(std::vector<std::vector<Tile*>>());

		for (size_t j = 0; j < this->maxSize.y; j++) {

			this->map[i].resize(this->maxSize.y);
			this->map[i].push_back(std::vector<Tile*>());

			for (size_t k = 0; k < this->layers; k++) {

				this->map[i][j].resize(this->layers);
				//this->map[i][j].push_back(new Tile(i * this->gridSizeF, j * this->gridSizeF, this->gridSizeF));
				this->map[i][j].push_back(nullptr);

			}

		}

	}
}

TileMap::~TileMap() {

	for (size_t i = 0; i < this->maxSize.x; i++) {
		for (size_t j = 0; j < this->maxSize.y; j++) {
			for (size_t k = 0; k < this->layers; k++) {
				delete this->map[i][j][k];
			}
		}
	}

}

void TileMap::addTile() {
}

void TileMap::removeTile() {
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
