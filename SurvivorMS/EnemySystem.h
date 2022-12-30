#ifndef ENEMYSYSTEM_H
#define ENEMYSYSTEM_H

#include "EnemySpawnerTile.h"
#include "Orc.h"

enum EnemyTypes {ORC = 0};

class EnemySystem {
private:
	
	std::map<std::string, sf::Texture>& textures;
	std::vector<Enemy*>& activeEnemies;
	Entity& player;

public:
	EnemySystem(std::vector<Enemy*>& activeEnemies, std::map<std::string, sf::Texture>& textures, Entity& player);
	virtual ~EnemySystem();

	void createEnemy(const short type, const float x, const float y, EnemySpawnerTile& enemySpawnerTile);
	void removeEnemy(const int index);

	void update(const float& dt);
	void render(sf::RenderTarget& target);
};

#endif 