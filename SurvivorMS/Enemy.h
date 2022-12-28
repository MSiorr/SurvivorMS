#ifndef ENEMY_H
#define ENEMY_H

#include "Entity.h"
#include "EnemySpawner.h"

class Entity;
class EnemySpawner;

class Enemy :
	public Entity {
private:

	EnemySpawner* enemySpawner;

	void initVariables();
	void initAnimations();

public:
	Enemy(EnemySpawner& enemySpawner, float x, float y, sf::Texture& textureSheet);
	virtual ~Enemy();

	void updateAnimation(const float& dt);

	void update(const float& dt, sf::Vector2f& mousePosView);
	void render(sf::RenderTarget& target, sf::Shader* shader, const bool showHitbox);
};

#endif 