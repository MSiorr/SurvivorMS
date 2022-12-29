#ifndef ENEMYSPAWNERTILE_H
#define ENEMYSPAWNERTILE_H

#include "Tile.h"

class Tile;

class EnemySpawnerTile
	: public Tile{
private:

	int enemyType;
	int enemyAmount;
	int enemyTimeToSpawn;
	int enemyMaxDistance;

	bool spawned;

public:
	EnemySpawnerTile(int gridX, int gridY, float gridSizeF,
		const sf::Texture& texture, const sf::IntRect& textureRect, 
		int enemyType, int enemyAmount, int enemyTimeToSpawn, float enemyMaxDistance);
	virtual ~EnemySpawnerTile();

	const std::string getAsString() const;
	const bool& getSpawned() const;

	void setSpawned(const bool spawned);

	void update();
	void render(sf::RenderTarget& target, sf::Shader* shader = NULL, const sf::Vector2f playerPos = sf::Vector2f(0, 0));
};

#endif 