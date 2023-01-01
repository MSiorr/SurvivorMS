#include "stdafx.h"
#include "EnemySystem.h"

EnemySystem::EnemySystem(std::vector<Enemy*>& activeEnemies, std::map<std::string, sf::Texture>& textures, Entity& player) 
	: textures(textures), activeEnemies(activeEnemies), player(player) {

}

EnemySystem::~EnemySystem() {
}

void EnemySystem::createEnemy(const short type, const float x, const float y, EnemySpawnerTile& enemySpawnerTile) {

	switch (type) {
	case EnemyTypes::ORC:

		this->activeEnemies.push_back(new Orc(x, y, this->textures["ENEMY_SHEET"], enemySpawnerTile, this->player));
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
