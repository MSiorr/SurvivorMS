#include "stdafx.h"
#include "EnemySystem.h"

EnemySystem::EnemySystem(std::vector<Enemy*>& activeEnemies, std::map<std::string, sf::Texture>& textures, Entity& player) 
	: textures(textures), activeEnemies(activeEnemies), player(player) {

}

EnemySystem::~EnemySystem() {
}

const sf::Vector2f EnemySystem::randPos(float x, float y, float rad) {

	sf::Vector2f pos;

	pos.x = x + rand() % static_cast<int>(rad);
	pos.y = y + rand() % static_cast<int>(rad / 2);

	return pos;
}

void EnemySystem::createEnemy(const short type, const float x, const float y, const float gridSizeF, EnemySpawnerTile& enemySpawnerTile) {

	sf::Vector2f pos = this->randPos(x, y, gridSizeF / 2);

	switch (type) {
	case EnemyTypes::ORC:

		this->activeEnemies.push_back(new Orc(pos.x, pos.y, this->textures["ENEMY_SHEET"], enemySpawnerTile, this->player));
		enemySpawnerTile.increaseEnemyCounter();

		break;
	default:
		std::cout << "WRONG ENEMY TYPE" << "\n";
		break;
	}
}

void EnemySystem::removeEnemy(const int index, std::vector<Pickable*>* pickables) {

	this->activeEnemies[index]->getEnemySpawnerTile().decreaseEnemyCounter();

	pickables->push_back(new Coin(
		this->activeEnemies[index]->getRandomPosAroundEnemy(),
		this->textures["PICKABLE_SHEET"]
	));

	pickables->push_back(new ExpGem(
		this->activeEnemies[index]->getRandomPosAroundEnemy(),
		this->textures["PICKABLE_SHEET"]
	));

	delete this->activeEnemies[index];
	this->activeEnemies.erase(this->activeEnemies.begin() + index);
}

void EnemySystem::update(const float& dt) {
}

void EnemySystem::render(sf::RenderTarget& target) {
}
