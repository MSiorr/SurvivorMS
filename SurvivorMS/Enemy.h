#ifndef ENEMY_H
#define ENEMY_H

#include "Entity.h"
#include "EnemySpawnerTile.h"

class Entity;
class EnemySpawnerTile;

class Enemy :
	public Entity {
private:

	// EnemySpawner* enemySpawner;

	virtual void initVariables() = 0;
	virtual void initAnimations() = 0;

public:
	Enemy();
	virtual ~Enemy();

	virtual void updateAnimation(const float& dt) = 0;

	virtual void update(const float& dt, sf::Vector2f& mousePosView) = 0;
	virtual void render(sf::RenderTarget& target, sf::Shader* shader = NULL, const sf::Vector2f lightPos = sf::Vector2f(), const bool showHitbox = false) = 0;
};

#endif 