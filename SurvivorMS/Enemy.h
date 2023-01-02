#ifndef ENEMY_H
#define ENEMY_H

#include "Entity.h"
#include "EnemySpawnerTile.h"


class Enemy :
	public Entity {
protected:

	EnemySpawnerTile& enemySpawnerTile;

	bool noRedOnSpawn;

	sf::Clock damageTimer;
	sf::Int32 damageTimerMax;

	virtual void initVariables() = 0;
	virtual void initAnimations() = 0;

public:
	Enemy(EnemySpawnerTile& enemySpawnerTile);
	virtual ~Enemy();

	EnemySpawnerTile& getEnemySpawnerTile();
	const bool getDamageTimerDone() const;
	const sf::Vector2f getRandomPosAroundEnemy();

	void resetDamageTimer();


	virtual void takeDamage(const int damage);
	virtual const bool isDead() const;

	virtual const AttributeComponent* getAttributeComp() const;

	virtual void updateAnimation(const float& dt) = 0;

	virtual void update(const float& dt, sf::Vector2f& mousePosView) = 0;
	virtual void render(sf::RenderTarget& target, sf::Shader* shader = NULL, const sf::Vector2f lightPos = sf::Vector2f(), const bool showHitbox = false) = 0;
};

#endif 