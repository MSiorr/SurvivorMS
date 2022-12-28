#ifndef ENEMYSPAWNER_H
#define ENEMYSPAWNER_H

#include "Tile.h"

class Tile;

class EnemySpawner 
	: public Tile{
private:

	int enemyType;
	int enemyAmount;
	int enemyTimeToSpawn;
	int enemyMaxDistance;

public:
	EnemySpawner(int gridX, int gridY, float gridSizeF, 
		const sf::Texture& texture, const sf::IntRect& textureRect, 
		int enemyType, int enemyAmount, int enemyTimeToSpawn, float enemyMaxDistance);
	virtual ~EnemySpawner();

	void update();
	void render(sf::RenderTarget& target, sf::Shader* shader = NULL, const sf::Vector2f playerPos = sf::Vector2f(0, 0));
};

#endif 