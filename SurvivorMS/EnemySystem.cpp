#include "stdafx.h"
#include "EnemySystem.h"

EnemySystem::EnemySystem(std::vector<Enemy*>& activeEnemies, std::map<std::string, sf::Texture>& textures) 
	: textures(textures), activeEnemies(activeEnemies) {

}

EnemySystem::~EnemySystem() {
}

void EnemySystem::createEnemy(const short type, const float x, const float y) {

	switch (type) {
	case EnemyTypes::ORC:

		this->activeEnemies.push_back(new Orc(x, y, this->textures["ENEMY_SHEET"]));

		break;
	default:
		std::cout << "WRONG ENEMY TYPE" << "\n";
		break;
	}
}

void EnemySystem::update(const float& dt) {
}

void EnemySystem::render(sf::RenderTarget& target) {
}
