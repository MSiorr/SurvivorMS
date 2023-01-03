#include "stdafx.h"
#include "Enemy.h"

void Enemy::initVariables() {

	this->damageTimerMax = 100;
}

Enemy::Enemy(EnemySpawnerTile& enemySpawnerTile)
	: Entity(), enemySpawnerTile(enemySpawnerTile) {

	this->initVariables();
}

Enemy::~Enemy() {
}

EnemySpawnerTile& Enemy::getEnemySpawnerTile() {
	return this->enemySpawnerTile;
}

const bool Enemy::getDamageTimerDone() const {
	return this->damageTimer.getElapsedTime().asMilliseconds() >= this->damageTimerMax;
}

const sf::Vector2f Enemy::getRandomPosAroundEnemy() {
	sf::Vector2f pos(0, 0);

	pos.x = (rand() % 20) - 10 + this->getCenter().x;
	pos.y = (rand() % 20) - 10 + this->getCenter().y;

	return pos;
}

void Enemy::resetDamageTimer() {

	this->damageTimer.restart();

}

void Enemy::instantKill() {

	this->getAttributeComponent()->hp = 0;
}

void Enemy::takeDamage(const int damage) {

	if (this->attributeComponent) {

		this->attributeComponent->loseHP(damage);
		
	}

}

const bool Enemy::isDead() const {

	if (this->attributeComponent) {

		return this->attributeComponent->isDead();
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