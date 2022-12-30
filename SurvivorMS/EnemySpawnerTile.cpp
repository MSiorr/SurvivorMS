#include "stdafx.h"
#include "EnemySpawnerTile.h"

EnemySpawnerTile::EnemySpawnerTile(int gridX, int gridY, float gridSizeF,
	const sf::Texture& texture, const sf::IntRect& textureRect,
	int enemyType, int enemyAmount, sf::Int32 enemyTimeToSpawn, float enemyMaxDistance
) : Tile(TileTypes::ENEMYSPAWNER, gridX, gridY, gridSizeF, texture, textureRect, false) {

	this->enemyType = enemyType;
	this->enemyAmount = enemyAmount;
	this->enemiesCounter = 0;
	this->enemySpawnTimer.restart();
	this->enemyTimeToSpawn = enemyTimeToSpawn;
	this->enemyMaxDistance = enemyMaxDistance;

	this->firstSpawn = true;
}

EnemySpawnerTile::~EnemySpawnerTile() {
}

const std::string EnemySpawnerTile::getAsString() const {
	std::stringstream ss;

	/*
	x,y,z
	type
	rext x, y
	enemyType
	enemyAmount
	enemyTimeToSpawn
	enemyMaxDistance
	*/

	ss << this->type << " " << this->shape.getTextureRect().left << " " << this->shape.getTextureRect().top << " "
		<< this->enemyType << " " << this->enemyAmount << " " << this->enemyTimeToSpawn << " " << this->enemyMaxDistance;

	return ss.str();
}

const int& EnemySpawnerTile::getEnemyCounter() const {
	return this->enemiesCounter;
}

const int& EnemySpawnerTile::getEnemyAmount() const {
	return this->enemyAmount;
}

const bool EnemySpawnerTile::getSpawnTimer() {

	if (this->enemySpawnTimer.getElapsedTime().asMilliseconds() >= this->enemyTimeToSpawn || this->firstSpawn) {

		this->enemySpawnTimer.restart();
		this->firstSpawn = false;
		return true;
	}
	return false;
}

void EnemySpawnerTile::increaseEnemyCounter() {

	if (this->enemiesCounter < this->enemyAmount)
		++this->enemiesCounter;
}

void EnemySpawnerTile::decreaseEnemyCounter() {

	if (this->enemiesCounter > 0)
		--this->enemiesCounter;
}

void EnemySpawnerTile::update() {


}

void EnemySpawnerTile::render(sf::RenderTarget& target, sf::Shader* shader, const sf::Vector2f playerPos) {

	if (shader) {

		shader->setUniform("hasTexture", true);
		shader->setUniform("lightPos", playerPos);

		target.draw(this->shape, shader);
	} else {

		target.draw(this->shape);
	}
}
