#ifndef ENEMYSPAWNERTILE_H
#define ENEMYSPAWNERTILE_H

#include "Tile.h"

class Tile;

class EnemySpawnerTile
	: public Tile{
private:

	int enemyType;
	int enemyAmount;
	int enemiesCounter;
	sf::Clock enemySpawnTimer;
	sf::Int32 enemyTimeToSpawn;

	int enemyMaxDistance;

	bool firstSpawn;


public:
	EnemySpawnerTile(int gridX, int gridY, float gridSizeF,
		const sf::Texture& texture, const sf::IntRect& textureRect, 
		int enemyType, int enemyAmount, sf::Int32 enemyTimeToSpawn, float enemyMaxDistance);
	virtual ~EnemySpawnerTile();

	const std::string getAsString() const;
	const int& getEnemyType() const;
	const int& getEnemyCounter() const;
	const int& getEnemyAmount() const;
	const bool getSpawnTimer();

	void increaseEnemyCounter();
	void decreaseEnemyCounter();

	void update();
	void render(sf::RenderTarget& target, sf::Shader* shader = NULL, const sf::Vector2f playerPos = sf::Vector2f(0, 0));
};

#endif 