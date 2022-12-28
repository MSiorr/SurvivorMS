#include "stdafx.h"
#include "EnemySpawner.h"

EnemySpawner::EnemySpawner(int gridX, int gridY, float gridSizeF, 
	const sf::Texture& texture, const sf::IntRect& textureRect,
	int enemyType, int enemyAmount, int enemyTimeToSpawn, float enemyMaxDistance
) : Tile(gridX, gridY, gridSizeF, texture, textureRect, false, TileTypes::ENEMYSPAWNER) {

	this->enemyType = enemyType;
	this->enemyAmount = enemyAmount;
	this->enemyTimeToSpawn = enemyTimeToSpawn;
	this->enemyMaxDistance = enemyMaxDistance;
}

EnemySpawner::~EnemySpawner() {
}

void EnemySpawner::update() {


}

void EnemySpawner::render(sf::RenderTarget& target, sf::Shader* shader, const sf::Vector2f playerPos) {

	if (shader) {

		shader->setUniform("hasTexture", true);
		shader->setUniform("lightPos", playerPos);

		target.draw(this->shape, shader);
	} else {

		target.draw(this->shape);
	}
}
