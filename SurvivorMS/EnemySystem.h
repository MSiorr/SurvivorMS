#ifndef ENEMYSYSTEM_H
#define ENEMYSYSTEM_H

#include "EnemySpawnerTile.h"
#include "Pickable.h"
#include "Coin.h"
#include "ExpGem.h"
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

	const sf::Vector2f randPos(float x, float y, float rad);

	void createEnemy(const short type, const float x, const float y, const float gridSizeF, EnemySpawnerTile& enemySpawnerTile);
	void removeEnemy(const int index, std::vector<Pickable*>* pickables);

	void update(const float& dt);
	void render(sf::RenderTarget& target);
};

#endif 