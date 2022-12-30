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

	this->spawned = false;
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

const bool& EnemySpawnerTile::getSpawned() const {
	return this->spawned;
}

const int& EnemySpawnerTile::getEnemyCounter() const {
	return this->enemiesCounter;
}

const int& EnemySpawnerTile::getEnemyAmount() const {
	return this->enemyAmount;
}

const bool EnemySpawnerTile::canSpawn() const {

	if (this->enemySpawnTimer.getElapsedTime().asMilliseconds() >= this->enemyTimeToSpawn) {

		return true;
	}

	return false;
}

void EnemySpawnerTile::increaseEnemyCounter() {

	if (this->enemiesCounter > this->enemyAmount)
		this->enemiesCounter = this->enemyAmount;
	else
		++this->enemiesCounter;
}

void EnemySpawnerTile::decreaseEnemyCounter() {

	if (this->enemiesCounter < 0)
		this->enemiesCounter = 0;
	else
		--this->enemiesCounter;
}

void EnemySpawnerTile::setSpawned(const bool spawned) {

	this->spawned = spawned;
	this->enemySpawnTimer.restart();
}

void EnemySpawnerTile::update() {

	if (this->canSpawn())
		this->spawned = false;

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
