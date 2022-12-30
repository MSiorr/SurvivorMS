#include "stdafx.h"
#include "Enemy.h"


Enemy::Enemy(EnemySpawnerTile& enemySpawnerTile)
	: Entity(), enemySpawnerTile(enemySpawnerTile) {

}

Enemy::~Enemy() {
}

EnemySpawnerTile& Enemy::getEnemySpawnerTile() {
	return this->enemySpawnerTile;
}

void Enemy::takeDamage(const int damage) {

	if (this->attributeComponent) {

		this->attributeComponent->loseHP(damage);
	}

}

const bool Enemy::isDead() const {

	if (this->attributeComponent) {

		this->attributeComponent->isDead();
	}

	return false;
}

const AttributeComponent* Enemy::getAttributeComp() const {
	if (this->animationComponent)
		return this->attributeComponent;
	else
		std::cout << "ENEMY ATTRIBUTE COMPONENT NO INIT" << "\n";
		return nullptr;
}