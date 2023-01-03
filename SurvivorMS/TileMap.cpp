#include "stdafx.h"
#include "TileMap.h"

const bool TileMap::getKeytime() {

	if (this->keytime >= this->keytimeMax) {
		this->keytime = 0.f;
		return true;
	}

	return false;
}

void TileMap::updateKeytime(const float& dt) {

	if (this->keytime < this->keytimeMax) {

		this->keytime += 1000.f * dt;
	}
}

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
	
	this->keytime = 0.f;
	this->keytimeMax = 1600.f;

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

	this->keytime = 0.f;
	this->keytimeMax = 160.f;

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

const bool TileMap::checkCollide(sf::Vector2f pos, const float& dt) {

	bool collide = false;

	if (pos.x < 0.f || pos.x > this->maxSizeWorldF.x ||
		pos.y < 0.f || pos.y > this->maxSizeWorldF.y) {

		collide = true;
	}

	if (!collide) {
		sf::Vector2i gridPos(
			static_cast<int>(pos.x) / this->gridSizeI,
			static_cast<int>(pos.y) / this->gridSizeI
		);
	
		this->layer = 0;

		this->fromX = gridPos.x - 1;
		if (this->fromX < 0)
			this->fromX = 0;
		else if (this->fromX > this->maxSizeWorldGrid.x)
			this->fromX = this->maxSizeWorldGrid.x;

		this->toX = gridPos.x + 3;
		if (this->toX < 0)
			this->toX = 0;
		else if (this->toX > this->maxSizeWorldGrid.x)
			this->toX = this->maxSizeWorldGrid.x;

		this->fromY = gridPos.y - 1;
		if (this->fromY < 0)
			this->fromY = 0;
		else if (this->fromY > this->maxSizeWorldGrid.y)
			this->fromY = this->maxSizeWorldGrid.y;

		this->toY = gridPos.y + 3;
		if (this->toY < 0)
			this->toY = 0;
		else if (this->toY > this->maxSizeWorldGrid.y)
			this->toY = this->maxSizeWorldGrid.y;

		for (int i = fromX; i < toX && !collide; i++) {
			for (int j = fromY; j < toY && !collide; j++) {
				for (int k = 0; k < this->map[i][j][this->layer].size() && !collide; k++) {

					sf::FloatRect wallBounds = this->map[i][j][this->layer][k]->getGlobalBounds();

					if (this->map[i][j][this->layer][k]->getCollision() && wallBounds.contains(pos)) {

						collide = true;
					}
				}
			}
		}
	}

	return collide;
}

void TileMap::saveToFile(const std::string path) {
	/*FORMAT:
		BASIC:
		Size x y
		gridSize
		layers
		texture file

		ALL TILES:
		type
		gridPos x y layer, 
		Texture rect x y, 
		collision,
		tile specific data...
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

		while (ifs >> x >> y >> z >> type) {
			if (type == TileTypes::ENEMYSPAWNER) {

				int enemyType = 0;
				int enemyAmount = 0;
				int enemyTimeToSpawn = 0;
				int enemyMaxDist = 0;

				ifs >> trX >> trY
					>> enemyType >> enemyAmount >> enemyTimeToSpawn >> enemyMaxDist;

				this->map[x][y][z].push_back(new EnemySpawnerTile(
					x, y,
					this->gridSizeF,
					this->tileSheet,
					sf::IntRect(trX, trY, this->gridSizeI, this->gridSizeI),
					enemyType,
					enemyAmount,
					enemyTimeToSpawn,
					enemyMaxDist
				));
			} else if(type == TileTypes::BLOCKADE){

				int blockadeLvl = 0;

				ifs >> trX >> trY >> blockadeLvl;

				this->map[x][y][z].push_back(new LvLBlockadeTile(
					x, y,
					this->gridSizeF,
					this->tileSheet,
					sf::IntRect(trX, trY, this->gridSizeI, this->gridSizeI),
					blockadeLvl
				));

			} else {

				ifs >> trX >> trY >> collision;

				this->map[x][y][z].push_back(new RegularTile(
					type, x, y, this->gridSizeF, this->tileSheet,
					sf::IntRect(trX, trY, this->gridSizeI, this->gridSizeI),
					collision
				));
			}
		}


	} else {
		std::cout << "ERROR::TILEMAP:: IN MAP FILE" << "\n";
	}

	ifs.close();

}

void TileMap::addTile(const int x, const int y, const int z, const sf::IntRect& textureRect, const bool& collision, const short& type) {

	if (x < this->maxSizeWorldGrid.x && y < this->maxSizeWorldGrid.y && z < this->layers && x >= 0 && y >= 0 && z >= 0) {

		if (type == TileTypes::DEFAULT || type == TileTypes::ONTOP) {

			this->map[x][y][z].push_back(new RegularTile(
				type,
				x, y,
				this->gridSizeF, 
				this->tileSheet, 
				textureRect, 
				collision
			));
		} 

	}

}

void TileMap::addTile(const int x, const int y, const int z, const sf::IntRect& textureRect,
	const int enemyType, const int enemyAmount, const int enemyTimeToSpawn, const int enemyMaxDistance ) {

	if (x < this->maxSizeWorldGrid.x && y < this->maxSizeWorldGrid.y && z < this->layers && x >= 0 && y >= 0 && z >= 0) {

		this->map[x][y][z].push_back(new EnemySpawnerTile(
			x, y,
			this->gridSizeF,
			this->tileSheet,
			textureRect,
			enemyType,
			enemyAmount,
			enemyTimeToSpawn,
			enemyMaxDistance
		));
	}

}

void TileMap::addTile(const int x, const int y, const int z, const sf::IntRect& textureRect, int blockadeLvl) {

	if (x < this->maxSizeWorldGrid.x && y < this->maxSizeWorldGrid.y && z < this->layers && x >= 0 && y >= 0 && z >= 0) {

		std::cout << "ADD BLOCKADE" << "\n";

		this->map[x][y][z].push_back(new LvLBlockadeTile(
			x, y,
			this->gridSizeF,
			this->tileSheet,
			textureRect,
			blockadeLvl
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

void TileMap::updateWorldBoundsCollision(Entity* entity, const float& dt) {

	if (entity->getPosition().x < 0.f) {

		entity->stopVelocityX();
		entity->setPosition(0.f, entity->getPosition().y);
	} else if (entity->getPosition().x + entity->getGlobalBounds().width > this->maxSizeWorldF.x) {

		entity->stopVelocityX();
		entity->setPosition(this->maxSizeWorldF.x - entity->getGlobalBounds().width, entity->getPosition().y);
	}

	if (entity->getPosition().y < 0.f) {

		entity->stopVelocityY();
		entity->setPosition(entity->getPosition().x, 0);
	} else if (entity->getPosition().y + entity->getGlobalBounds().height > this->maxSizeWorldF.y) {

		entity->stopVelocityY();
		entity->setPosition(entity->getPosition().x, this->maxSizeWorldF.y - entity->getGlobalBounds().height);
	}

}

void TileMap::updateTileCollision(Entity* entity, const float& dt, TextTagSystem* tts) {

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

				sf::FloatRect entityBounds = entity->getGlobalBounds();
				sf::FloatRect nextEntityBounds = entity->getNextPositionBounds(dt);
				sf::FloatRect wallBounds = this->map[i][j][this->layer][k]->getGlobalBounds();

				bool collision = false;

				if (this->map[i][j][this->layer][k]->getCollision() && this->map[i][j][this->layer][k]->intersects(nextEntityBounds)) {

					// BOTTOM COLLISION
					if (entityBounds.top < wallBounds.top
						&& entityBounds.top + entityBounds.height < wallBounds.top + wallBounds.height
						&& entityBounds.left < wallBounds.left + wallBounds.width
						&& entityBounds.left + entityBounds.width > wallBounds.left
						) {
						entity->stopVelocityY();
						entity->setPosition(entityBounds.left, wallBounds.top - entityBounds.height);
						collision = true;
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
						collision = true;
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
						collision = true;
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
						collision = true;
						//std::cout << "LEFT" << "\n";
					}

				}

				if (collision && this->getKeytime()) {
					if (instanceof<Player>(entity) && this->map[i][j][this->layer][k]->getType() == TileTypes::BLOCKADE) {

						LvLBlockadeTile* lbt = dynamic_cast<LvLBlockadeTile*>(this->map[i][j][this->layer][k]);

						tts->addTextTag(TAGTYPES::EXPERIENCE_TAG, entity->getPosition().x - 100.f, entity->getPosition().y - 10.f, lbt->getBarierLvl(), "YOU NEED ", " LVL");
					}
				}
			}
		}
	}

}

void TileMap::updateTiles(Entity* entity, const float& dt, EnemySystem& enemySystem, bool& bossPhase) {

	//TILES
	this->layer = 0;

	this->fromX = entity->getGridPosition(this->gridSizeI).x - 15;
	if (this->fromX < 0)
		this->fromX = 0;
	else if (this->fromX > this->maxSizeWorldGrid.x)
		this->fromX = this->maxSizeWorldGrid.x;

	this->toX = entity->getGridPosition(this->gridSizeI).x + 16;
	if (this->toX < 0)
		this->toX = 0;
	else if (this->toX > this->maxSizeWorldGrid.x)
		this->toX = this->maxSizeWorldGrid.x;

	this->fromY = entity->getGridPosition(this->gridSizeI).y - 8;
	if (this->fromY < 0)
		this->fromY = 0;
	else if (this->fromY > this->maxSizeWorldGrid.y)
		this->fromY = this->maxSizeWorldGrid.y;

	this->toY = entity->getGridPosition(this->gridSizeI).y + 9;
	if (this->toY < 0)
		this->toY = 0;
	else if (this->toY > this->maxSizeWorldGrid.y)
		this->toY = this->maxSizeWorldGrid.y;



	for (int i = fromX; i < toX; i++) {
		for (int j = fromY; j < toY; j++) {
			for (int k = 0; k < this->map[i][j][this->layer].size(); k++) {

				this->map[i][j][this->layer][k]->update();

				if (this->map[i][j][this->layer][k]->getType() == TileTypes::ENEMYSPAWNER) {

					EnemySpawnerTile* est = dynamic_cast<EnemySpawnerTile*>(this->map[i][j][this->layer][k]);

					if (instanceof<Player>(entity)) {

						Player* player = dynamic_cast<Player*>(entity);
						float dist = vectorDistance(sf::Vector2f(
							i * this->gridSizeF + this->gridSizeF / 2.f,
							j * this->gridSizeF + this->gridSizeF / 2.f
						), player->getCenter());
						
						if (dist > 2.f * this->gridSizeF) {

							if (est && est->getSpawnTimer() && est->getEnemyCounter() < est->getEnemyAmount()) {

								if(est->getEnemyType() == EnemyTypes::BOSS && bossPhase)
									enemySystem.createEnemy(BOSS, i * this->gridSizeF, j * this->gridSizeF, this->gridSizeF, *est);
								else if (est->getEnemyType() != EnemyTypes::BOSS && !bossPhase) {

									enemySystem.createEnemy(est->getEnemyType(), i * this->gridSizeF, j * this->gridSizeF, this->gridSizeF, *est);
								}
							}
						}

					} else {

						if (est && est->getSpawnTimer() && est->getEnemyCounter() < est->getEnemyAmount())
							enemySystem.createEnemy(ORC, i * this->gridSizeF, j * this->gridSizeF, this->gridSizeF, *est);
					}
				} else if(this->map[i][j][this->layer][k]->getType() == TileTypes::BLOCKADE) {

					LvLBlockadeTile* lbt = dynamic_cast<LvLBlockadeTile*>(this->map[i][j][this->layer][k]);

					if (instanceof<Player>(entity)) {
						
						Player* player = dynamic_cast<Player*>(entity);

						if (player->getAttributeComponent()->lvl >= lbt->getBarierLvl()) {

							lbt->setCollision(false);
						}

						if (lbt->getGlobalBounds().contains(player->getCenter())) {

							bossPhase = true;
						}
					}
				}
			}
		}
	}

}

void TileMap::update(const float& dt) {

	this->updateKeytime(dt);
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

				if (!showCollision &&
					this->map[i][j][this->layer][k]->getType() == TileTypes::BLOCKADE && this->map[i][j][this->layer][k]->getCollision()) {

					this->collisionBox.setPosition(this->map[i][j][this->layer][k]->getPosition());
					this->collisionBox.setFillColor(sf::Color(200, 124, 0, 20));
					this->collisionBox.setOutlineColor(sf::Color(200, 124, 0, 125));
					target.draw(this->collisionBox);
				}

				if (showCollision) {

					if (this->map[i][j][this->layer][k]->getCollision()) {

						this->collisionBox.setPosition(this->map[i][j][this->layer][k]->getPosition());
						this->collisionBox.setFillColor(sf::Color(255, 0, 0, 50));
						this->collisionBox.setOutlineColor(sf::Color::Red);
						target.draw(this->collisionBox);
					}

					if (this->map[i][j][this->layer][k]->getType() == TileTypes::ENEMYSPAWNER) {

						this->collisionBox.setPosition(this->map[i][j][this->layer][k]->getPosition());
						this->collisionBox.setFillColor(sf::Color(0, 0, 255, 50));
						this->collisionBox.setOutlineColor(sf::Color::Blue);
						target.draw(this->collisionBox);
					}

					if (this->map[i][j][this->layer][k]->getType() == TileTypes::BLOCKADE) {

						this->collisionBox.setPosition(this->map[i][j][this->layer][k]->getPosition());
						this->collisionBox.setFillColor(sf::Color(255, 165, 0, 50));
						this->collisionBox.setOutlineColor(sf::Color(255,165,0,255));
						target.draw(this->collisionBox);
					}
				}
			}
		}
	}
}
