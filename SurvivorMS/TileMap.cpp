#include "stdafx.h"
#include "TileMap.h"

void TileMap::clear() {
	if (!this->map.empty()) {
		for (int i = 0; i < this->map.size(); i++) {
			for (int j = 0; j < this->map[i].size(); j++) {
				for (int k = 0; k < this->map[i][j].size(); k++) {
					for (int l = 0; l < this->map[i][j][k].size(); l++) {

						delete this->map[i][j][k][l];
						this->map[i][j][k][l] = nullptr;
					}
					this->map[i][j][k].clear();
				}
				this->map[i][j].clear();
			}
			this->map[i].clear();
		}
		this->map.clear();
	}
}

TileMap::TileMap(float gridSize, int width, int height, std::string textureFile) {
	
	this->gridSizeF = gridSize;
	this->gridSizeI = static_cast<int>(this->gridSizeF);
	this->maxSizeWorldGrid.x = width;
	this->maxSizeWorldGrid.y = height;
	this->maxSizeWorldF.x = static_cast<float>(width) * gridSizeF;
	this->maxSizeWorldF.y = static_cast<float>(height) * gridSizeF;
	this->layers = 1;

	this->fromX = 0;
	this->toX = 0;
	this->fromY = 0;
	this->toY = 0;
	this->layer = 0;

	this->textureFile = textureFile;

	this->map.resize(this->maxSizeWorldGrid.x, std::vector<std::vector<std::vector<Tile*>>>());
	for (int i = 0; i < this->maxSizeWorldGrid.x; i++) {

		for (int j = 0; j < this->maxSizeWorldGrid.y; j++) {

			this->map[i].resize(this->maxSizeWorldGrid.y, std::vector<std::vector<Tile*>>());

			for (int k = 0; k < this->layers; k++) {

				this->map[i][j].resize(this->layers, std::vector<Tile*>());

			}

		}

	}

	if (!this->tileSheet.loadFromFile(textureFile)) {
		std::cout << "ERROR::TILEMAP:: WITH GRASS TEXTURE" << "\n";
	}

	this->collisionBox.setSize(sf::Vector2f(gridSize, gridSize));
	this->collisionBox.setFillColor(sf::Color(255, 0, 0, 50));
	this->collisionBox.setOutlineThickness(-1.f);
	this->collisionBox.setOutlineColor(sf::Color::Red);
}

TileMap::TileMap(const std::string fileName) {

	this->fromX = 0;
	this->toX = 0;
	this->fromY = 0;
	this->toY = 0;
	this->layer = 0;

	this->loadFromFile(fileName);

	this->collisionBox.setSize(sf::Vector2f(this->gridSizeF, this->gridSizeF));
	this->collisionBox.setFillColor(sf::Color(255, 0, 0, 50));
	this->collisionBox.setOutlineThickness(-1.f);
	this->collisionBox.setOutlineColor(sf::Color::Red);
}

TileMap::~TileMap() {

	this->clear();

}

const bool TileMap::tileEmpty(const int x, const int y, const int z) const {
	
	if (
		x >= 0 && x < this->maxSizeWorldGrid.x &&
		y >= 0 && y < this->maxSizeWorldGrid.y &&
		z >= 0 && z < this->layers
		) {

		return this->map[x][y][z].empty();
	}

	return false;

}

const sf::Texture* TileMap::getTileSheet() const{
	return &this->tileSheet;
}

const int TileMap::getLayerSize(const int x, const int y, const int layer) const {

	if (x >= 0 && x < this->map.size()) {
		if (y >= 0 && y < this->map[x].size()) {
			if (layer >= 0 && layer < this->map[x][y].size()) {
				
				return static_cast<int>(this->map[x][y][layer].size());
			}
		}
	}

	return -1;
}

const sf::Vector2i& TileMap::getMaxSizeGrid() const {
	return this->maxSizeWorldGrid;
}

const sf::Vector2f& TileMap::getMaxSizeF() const {
	return this->maxSizeWorldF;
}

const bool TileMap::checkType(const int x, const int y, const int z, const int type) const {
	return this->map[x][y][this->layer].back()->getType() == type;
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

		ofs << this->maxSizeWorldGrid.x << " " << this->maxSizeWorldGrid.y << "\n"
			<< this->gridSizeI << "\n"
			<< this->layers << "\n"
			<< this->textureFile << "\n";


		for (int i = 0; i < this->maxSizeWorldGrid.x; i++) {
			for (int j = 0; j < this->maxSizeWorldGrid.y; j++) {
				for (int k = 0; k < this->layers; k++) {
					if (!this->map[i][j][k].empty()) {
						for (int l = 0; l < this->map[i][j][k].size(); l++) {

							ofs << i << " " << j << " " << k << " " << this->map[i][j][k][l]->getAsString() << " ";
						}
					}
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

		sf::Vector2i size;
		int gridSize = 0;
		int layers = 0;
		std::string textureFile = "";

		ifs >> size.x >> size.y >> gridSize >> layers >> textureFile;

		this->gridSizeF = static_cast<float>(gridSize);
		this->gridSizeI = gridSize;
		this->maxSizeWorldGrid.x = size.x;
		this->maxSizeWorldGrid.y = size.y;
		this->maxSizeWorldF.x = static_cast<float>(size.x * gridSizeF);
		this->maxSizeWorldF.y = static_cast<float>(size.y * gridSizeF);
		this->layers = layers;
		this->textureFile = textureFile;


		// TILES
		this->clear();

		int x = 0;
		int y = 0;
		int z = 0;

		int trX = 0;
		int trY = 0;

		bool collision = false;
		short type = 0;

		this->map.resize(this->maxSizeWorldGrid.x, std::vector<std::vector<std::vector<Tile*>>>());
		for (size_t i = 0; i < this->maxSizeWorldGrid.x; i++) {

			for (size_t j = 0; j < this->maxSizeWorldGrid.y; j++) {

				this->map[i].resize(this->maxSizeWorldGrid.y, std::vector<std::vector<Tile*>>());

				for (size_t k = 0; k < this->layers; k++) {

					this->map[i][j].resize(this->layers, std::vector<Tile*>());

				}

			}

		}

		if (!this->tileSheet.loadFromFile(textureFile)) {
			std::cout << "ERROR::TILEMAP:: WITH GRASS TEXTURE" << "\n";
		}

		while (ifs >> x >> y >> z >> trX >> trY >> collision >> type) {

			this->map[x][y][z].push_back(new Tile(
				x, y, this->gridSizeF, this->tileSheet, 
				sf::IntRect(trX, trY, this->gridSizeI, this->gridSizeI), 
				collision, type
			));
		}


	} else {
		std::cout << "ERROR::TILEMAP:: IN MAP FILE" << "\n";
	}

	ifs.close();

}

void TileMap::addTile(const int x, const int y, const int z, const sf::IntRect& textureRect, const bool& collision, const short& type) {

	if (x < this->maxSizeWorldGrid.x && y < this->maxSizeWorldGrid.y && z < this->layers && x >= 0 && y >= 0 && z >= 0) {

		this->map[x][y][z].push_back(new Tile(
			x, y, 
			this->gridSizeF, 
			this->tileSheet, 
			textureRect, 
			collision, 
			type
		));

	}

}

void TileMap::removeTile(const int x, const int y, const int z, const int type) {

	if (x < this->maxSizeWorldGrid.x && 
		y < this->maxSizeWorldGrid.y && 
		z < this->layers && 
		x >= 0 && y >= 0 && z >= 0) {

		if (!this->map[x][y][z].empty()) {

			if (type >= 0) {

				if (this->map[x][y][z].back()->getType() == type) {

					delete this->map[x][y][z][this->map[x][y][z].size() - 1];
					this->map[x][y][z].pop_back();
				}

			} else {

				delete this->map[x][y][z][this->map[x][y][z].size() - 1];
				this->map[x][y][z].pop_back();
			}

		}

	}
}

void TileMap::update(Entity* entity, const float& dt) {

	if (entity->getPosition().x < 0.f) {

		entity->stopVelocityX();
		entity->setPosition(0.f, entity->getPosition().y);
	}
	else if (entity->getPosition().x + entity->getGlobalBounds().width > this->maxSizeWorldF.x) {

		entity->stopVelocityX();
		entity->setPosition(this->maxSizeWorldF.x - entity->getGlobalBounds().width, entity->getPosition().y);
	}

	if (entity->getPosition().y < 0.f) {

		entity->stopVelocityY();
		entity->setPosition(entity->getPosition().x, 0);
	}
	else if (entity->getPosition().y + entity->getGlobalBounds().height > this->maxSizeWorldF.y) {

		entity->stopVelocityY();
		entity->setPosition(entity->getPosition().x, this->maxSizeWorldF.y - entity->getGlobalBounds().height);
	}

	//TILES
	this->layer = 0;

	this->fromX = entity->getGridPosition(this->gridSizeI).x - 1;
	if (this->fromX < 0)
		this->fromX = 0;
	else if (this->fromX > this->maxSizeWorldGrid.x)
		this->fromX = this->maxSizeWorldGrid.x;

	this->toX = entity->getGridPosition(this->gridSizeI).x + 3;
	if (this->toX < 0)
		this->toX = 0;
	else if (this->toX > this->maxSizeWorldGrid.x)
		this->toX = this->maxSizeWorldGrid.x;

	this->fromY = entity->getGridPosition(this->gridSizeI).y - 1;
	if (this->fromY < 0)
		this->fromY = 0;
	else if (this->fromY > this->maxSizeWorldGrid.y)
		this->fromY = this->maxSizeWorldGrid.y;

	this->toY = entity->getGridPosition(this->gridSizeI).y + 3;
	if (this->toY < 0)
		this->toY = 0;
	else if (this->toY > this->maxSizeWorldGrid.y)
		this->toY = this->maxSizeWorldGrid.y;
	
	

	for (int i = fromX; i < toX; i++) {
		for (int j = fromY; j < toY; j++) {
			for (int k = 0; k < this->map[i][j][this->layer].size(); k++) {

				this->map[i][j][this->layer][k]->update();

				sf::FloatRect entityBounds = entity->getGlobalBounds();
				sf::FloatRect nextEntityBounds = entity->getNextPositionBounds(dt);
				sf::FloatRect wallBounds = this->map[i][j][this->layer][k]->getGlobalBounds();
			
				if (this->map[i][j][this->layer][k]->getCollision() && this->map[i][j][this->layer][k]->intersects(nextEntityBounds)) {
				
					// BOTTOM COLLISION
					if (entityBounds.top < wallBounds.top
						&& entityBounds.top + entityBounds.height < wallBounds.top + wallBounds.height
						&& entityBounds.left < wallBounds.left + wallBounds.width
						&& entityBounds.left + entityBounds.width > wallBounds.left
						) {
						entity->stopVelocityY();
						entity->setPosition(entityBounds.left, wallBounds.top - entityBounds.height);
						//std::cout << "BOTT" << "\n";
					}
					// TOP COLLISION
					else if (entityBounds.top > wallBounds.top
						&& entityBounds.top + entityBounds.height > wallBounds.top + wallBounds.height
						&& entityBounds.left < wallBounds.left + wallBounds.width
						&& entityBounds.left + entityBounds.width > wallBounds.left
						) {
						entity->stopVelocityY();
						entity->setPosition(entityBounds.left, wallBounds.top + wallBounds.height);
						//std::cout << "TOP" << "\n";
					}
				
					// RIGHT COLLISION
					if (entityBounds.left < wallBounds.left
						&& entityBounds.left + entityBounds.width < wallBounds.left + wallBounds.width
						&& entityBounds.top < wallBounds.top + wallBounds.height
						&& entityBounds.top + entityBounds.height > wallBounds.top
						) {
						entity->stopVelocityX();
						entity->setPosition(wallBounds.left - entityBounds.width, entityBounds.top);
						//std::cout << "RIGHT" << "\n";
					}
					// LEFT COLLISION
					else if (entityBounds.left > wallBounds.left
						&& entityBounds.left + entityBounds.width > wallBounds.left + wallBounds.width
						&& entityBounds.top < wallBounds.top + wallBounds.height
						&& entityBounds.top + entityBounds.height > wallBounds.top
						) {
						entity->stopVelocityX();
						entity->setPosition(wallBounds.left + wallBounds.width, entityBounds.top);
						//std::cout << "LEFT" << "\n";
					}

				}
			}
		}
	}

}

void TileMap::renderDeferred(sf::RenderTarget& target, sf::Shader* shader, const sf::Vector2f playerPos) {

	while (!this->deferredRenderStack.empty()) {

		if (shader) 
			this->deferredRenderStack.top()->render(target, shader, playerPos);
		else
			this->deferredRenderStack.top()->render(target);
		
		this->deferredRenderStack.pop();
	}
}

void TileMap::render(sf::RenderTarget& target, const sf::Vector2i& gridPos, sf::Shader* shader, sf::Vector2f playerPos, const bool showCollision) {

	this->layer = 0;

	this->fromX = gridPos.x - 15;
	if (this->fromX < 0)
		this->fromX = 0;
	else if (this->fromX > this->maxSizeWorldGrid.x)
		this->fromX = this->maxSizeWorldGrid.x;

	this->toX = gridPos.x + 16;
	if (this->toX < 0)
		this->toX = 0;
	else if (this->toX > this->maxSizeWorldGrid.x)
		this->toX = this->maxSizeWorldGrid.x ;

	this->fromY = gridPos.y - 8;
	if (this->fromY < 0)
		this->fromY = 0;
	else if (this->fromY > this->maxSizeWorldGrid.y)
		this->fromY = this->maxSizeWorldGrid.y ;

	this->toY = gridPos.y + 9;
	if (this->toY < 0)
		this->toY = 0;
	else if (this->toY > this->maxSizeWorldGrid.y)
		this->toY = this->maxSizeWorldGrid.y;

	for (int i = fromX; i < toX; i++) {
		for (int j = fromY; j < toY; j++) {
			for (int k = 0; k < this->map[i][j][this->layer].size(); k++) {

				if (this->map[i][j][this->layer][k]->getType() == TileTypes::ONTOP){

					this->deferredRenderStack.push(this->map[i][j][this->layer][k]);

				} else {

					if (shader)
						this->map[i][j][this->layer][k]->render(target, shader, playerPos);
					else
						this->map[i][j][this->layer][k]->render(target);

				}
				if (showCollision) {

					if (this->map[i][j][this->layer][k]->getCollision()) {

						this->collisionBox.setPosition(this->map[i][j][this->layer][k]->getPosition());
						target.draw(this->collisionBox);
					}
				}

				if (this->map[i][j][this->layer][k]->getType() == TileTypes::ENEMYSPAWNER) {

					this->collisionBox.setPosition(this->map[i][j][this->layer][k]->getPosition());
					target.draw(this->collisionBox);
				}
			}
		}
	}
}
